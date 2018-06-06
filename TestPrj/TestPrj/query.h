#ifndef QUERY_H
#define QUERY_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream> //ifstream
#include <set>
#include <sstream> // istringstream
#include <memory> // share_ptr
#include <map>
#include <iterator>

using line_no = std::vector<std::string>::size_type; //泪洗定义line_no行号
class QueryResult;

class TextQuery
{
public:
	TextQuery(std::ifstream &);
	QueryResult query(const std::string &) const;

private:
	std::shared_ptr<std::vector<std::string>> file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult
{
	friend std::ostream &print(std::ostream &, const QueryResult &); 
public:
	QueryResult(std::string s, std::shared_ptr<std::vector<std::string>> f,
		std::shared_ptr<std::set<line_no>> line_no)
		: sought(s), file(f), line(line_no){}
	std::set<line_no>::iterator begin(){ return line->begin(); }			//返回set容器中指向首元素迭代器
	std::set<line_no>::iterator end(){ return line->end(); }
	std::shared_ptr<std::vector<std::string>> get_file() { return file; } 

private:
	std::string sought;  
	std::shared_ptr<std::vector<std::string>> file; 
	std::shared_ptr<std::set<line_no>> line; 
};


class QueryBase
{
	friend class Query;
protected:
	virtual ~QueryBase() = default;
private:
	// eval是返回与当前Query匹配的QueryResult
	virtual QueryResult eval(const TextQuery &) const = 0;
	// rep是一个表示查询的string
	virtual std::string rep() const = 0; 
};

class Query
{
	friend Query operator~(const Query &);
	friend Query operator&(const Query &, const Query &);
	friend Query operator|(const Query &, const Query &);
public:
	Query(const std::string &);
	// 接口函数,调用对应的QueryBase操作
	QueryResult eval(const TextQuery &t)const { return q->eval(t); }
	std::string rep() const { return q->rep(); }
private:
	Query(std::shared_ptr<QueryBase> query) : q(query){}
	std::shared_ptr<QueryBase> q;
};

class WordQuery: public QueryBase
{
	friend class Query;  // Query使用WordQuery构造函数
	WordQuery(const std::string &s) : query_word(s){}
	QueryResult eval(const TextQuery &t) const { return t.query(query_word); }
	std::string rep() const { return query_word; }
	std::string query_word;
};

inline Query::Query(const std::string &s) : q(new WordQuery(s)){}

class NotQuery : public QueryBase
{
	friend Query operator~(const Query &);
	NotQuery(const Query &q) : query(q){}
	QueryResult eval(const TextQuery &t) const;
	std::string rep() const { return "~(" + query.rep() + ")"; }

	Query query;
};

inline Query operator~(const Query &operand)
{
	return std::shared_ptr<QueryBase>(new NotQuery(operand));
}

class BinaryQuery : public QueryBase
{
protected:
	BinaryQuery(const Query &l, const Query &r, const std::string &s)
		: lhs(l), rhs(r), opSym(s){}
	std::string rep() const { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }

	Query lhs, rhs;
	std::string opSym;
};

class OrQuery : public BinaryQuery
{
	friend Query operator|(const Query &, const Query &);
	OrQuery(const Query &l, const Query &r)
		: BinaryQuery(l, r, "|"){}
	QueryResult eval(const TextQuery &t) const;
};

inline Query operator|(const Query &lhs, const Query &rhs)
{
	return std::shared_ptr<QueryBase>(new OrQuery(lhs, rhs));
}

class AndQuery : public BinaryQuery
{
	friend Query operator&(const Query &, const Query &);
	AndQuery(const Query &l, const Query &r)
		: BinaryQuery(l, r, "&"){}
	QueryResult eval(const TextQuery &t) const;
};

inline Query operator&(const Query &lhs, const Query &rhs)
{
	return std::shared_ptr<QueryBase>(new AndQuery(lhs, rhs));
}


#endif