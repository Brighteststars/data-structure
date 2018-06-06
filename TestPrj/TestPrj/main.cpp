#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <memory>
#include <algorithm>
#include <iterator>
#include <stdio.h>
using namespace std;

using line_no = vector<string>::size_type;
class QueryResult;

class TextQuery
{
public:
	TextQuery(ifstream &is);
	QueryResult query(const string &sought) const;
private:
	shared_ptr<vector<string>> file;
	map<string, shared_ptr<set<line_no>>> wm;
};

TextQuery::TextQuery(ifstream &is) : file(new vector<string>)
{
	string text;
	while (getline(is, text))
	{
		file->push_back(text);
		int n = file->size() - 1;
		istringstream stream(text);
		string word;
		while (stream >> word)
		{
			auto &lines = wm[word];
			if (!lines)
				lines.reset(new set<line_no>); //reset is shared_pter member function 
			lines->insert(n);

		}
	}
}

class QueryResult
{
	friend ostream& print(ostream &os, const QueryResult &qr);
public:
	QueryResult(const string &s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f)
		: sought(s), lines(p), file(f){}
	set<line_no>::iterator begin() const { return lines->begin(); }
	set<line_no>::iterator end() const { return lines->end(); }
	shared_ptr<vector<string>> get_file() const { return file; }
private:
	string sought;
	shared_ptr<set<line_no>> lines;
	shared_ptr<vector<string>> file;

};

string make_plural(size_t sz, const std::string &word, const std::string &ending)
{
	return sz > 1 ? word + ending : word;
}

ostream & print(std::ostream &os, const QueryResult &qr)
{
	os << qr.sought << " occurs " << qr.lines->size()
		<< make_plural(qr.lines->size(), "time", "s") << endl;
	for (auto num : *qr.lines)
	{
		os << "\t(line " << num + 1 << ") "
			<< qr.file->at(num) << endl;
	}
	return os;

}

QueryResult TextQuery::query(const string &sought) const
{
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = wm.find(sought);
	if (loc == wm.end())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
}


class Query_Base
{
	friend class Query;
protected:
	virtual ~Query_Base() = default;
private:
	virtual QueryResult eval(const TextQuery &t) const = 0;
	virtual string rep() const = 0;
};

class Query
{
	friend Query operator~(const Query &lhs);
	friend Query operator|(const Query &lhs, const Query &rhs);
	friend Query operator&(const Query &lhs, const Query &rhs);
public:
	Query(const string &s);
	QueryResult eval(const TextQuery &t) const 
	{
		return q->eval(t);
	}
	string rep() const { return q->rep(); }
private:
	Query(shared_ptr<Query_Base> query)
		: q(query) {}
	shared_ptr<Query_Base> q;
};

class WordQuery : public Query_Base
{
	friend class Query;
	WordQuery(const string &s)
		: query_word(s){}
	QueryResult eval(const TextQuery &t) const 
	{
		return t.query(query_word);
	}
	string rep() const
	{
		return query_word;
	}
	string query_word;

};

inline Query::Query(const string &s) : q(new WordQuery(s)){}

class NotQuery : public Query_Base
{
	friend Query operator~(const Query &lhs);
	NotQuery(const Query &q) : query(q){}
	QueryResult eval(const TextQuery &t) const;
	string rep() const { return "~(" + query.rep() + ")"; }
	Query query;
};

inline Query operator~(const Query &lhs)
{
	return shared_ptr<Query_Base>(new NotQuery(lhs));
}

class BinaryQuery : public Query_Base
{
protected:
	BinaryQuery(const Query &l, const Query &r, const string &s)
		: lhs(l), rhs(r), opSym(s){}
	string rep() const { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }

	Query lhs, rhs;
	string opSym;
};

class AndQuery : public BinaryQuery
{
	friend Query operator&(const Query &lhs, const Query &rhs);
	AndQuery(const Query &l, const Query &r)
		: BinaryQuery(l, r, "&"){}
	QueryResult eval(const TextQuery &t) const;

};

inline Query operator&(const Query &lhs, const Query &rhs)
{
	return shared_ptr<Query_Base>(new AndQuery(lhs, rhs));
}

class OrQuery : public BinaryQuery
{
	friend Query operator|(const Query &lhs, const Query &rhs);
	OrQuery(const Query &l, const Query &r)
		: BinaryQuery(l, r, "|"){ }
	QueryResult eval(const TextQuery &t) const;
};

inline Query operator|(const Query &lhs, const Query &rhs)
{
	return shared_ptr<Query_Base>(new OrQuery(lhs, rhs));
}

QueryResult AndQuery::eval(const TextQuery &t) const
{
	auto left = lhs.eval(t), right = rhs.eval(t);
	auto ret_lines = make_shared<set<line_no>>(left.begin(), left.end());
	ret_lines->insert(right.begin(), right.end());

	return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult OrQuery::eval(const TextQuery &t) const
{
	auto left = lhs.eval(t), right = rhs.eval(t);
	auto ret_lines = make_shared<set<line_no>>();
	set_intersection(left.begin(), left.end(), right.begin(), right.end(),
		inserter(*ret_lines, ret_lines->begin()));

	return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult NotQuery::eval(const TextQuery &t) const
{
	auto result = query.eval(t);
	auto ret_lines = make_shared<set<line_no>>();
	auto beg = result.begin(), end = result.end();
	auto sz = result.get_file()->size();
	for (size_t i = 0; i < sz; i++)
	{
		if (beg == end || *beg != i)
			ret_lines->insert(i);
		else if (beg != end)
			++beg;
	}
	return QueryResult(rep(), ret_lines, result.get_file());
}

void RunQuery(ifstream &is)
{
	TextQuery t(is);
	while (true)
	{
		cout << "Enter word to query, or q to quit\n";
		string s;
		if (!(cin >> s) || s == "q")
			break;
		print(cout, t.query(s)) << endl;

	}
}

void Permutation(char* pStr, char* pBeg)
{
	if (*pBeg == '\0')
		printf("%s\n", pStr);
	else
	{
		for (char* pCh = pBeg; *pCh != '\0'; ++pCh)
		{
			char temp = *pCh;
			*pCh = *pBeg;
			*pBeg = temp;
			Permutation(pStr, pBeg + 1);

			temp = *pBeg;
			*pBeg = *pCh;
			*pCh = temp;
		}
	}
}

void Permutation(char* pStr)
{
	if (pStr == nullptr)
		return;
	Permutation(pStr, pStr);
}