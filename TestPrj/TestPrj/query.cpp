#include "query.h"
#include <algorithm>

TextQuery::TextQuery(std::ifstream &is) :file(new std::vector<std::string>)
{
	std::string text;
	while (getline(is, text))		//���ļ���ÿһ��
	{
		file->push_back(text);		//��������ı�
		int n = file->size() - 1;	//��ǰ�к�
		std::istringstream line(text); //���ı��ֽ�Ϊ����

		std::string word;

		while (line >> word) //������ÿһ������
		{
			auto &lines = wm[word];				//lines��һ��shared_ptr				
			if (!lines)				//�����ǵ�һ�������������ʱ,��ָ��Ϊ��						
				lines.reset(new std::set<line_no>); //����һ���µ�set
			lines->insert(n);			//�����кŲ���set��
		}
	}
}

QueryResult TextQuery::query(const std::string &s) const
{
	//ָ��set����������ָ��nodata,set����Ϊ��
	static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>); //static�ֲ���̬����,ֻ�趨��һ��,�������ں�ȫ�ֱ���һ��
	auto loc = wm.find(s); //map������
	if (loc == wm.end())
		return QueryResult(s, file, nodata); //δ�ҵ�
	else
		return QueryResult(s, file, loc->second);
}


//�ַ�������
std::string make_plural(size_t sz, const std::string &word, const std::string &ending)
{
	return sz > 1 ? word + ending : word;
}

std::ostream &print(std::ostream &os, const QueryResult &qr)
{
	os << qr.sought << " occurs " << qr.line->size()
		<< " " << make_plural(qr.line->size(), "time", "s") << std::endl;
	for (auto num : *qr.line)
		os << "\t(line " << num + 1 << ")\t" << *(qr.file->begin() + num) << std::endl;
	return os;
}



QueryResult OrQuery::eval(const TextQuery &t) const
{
	auto right = rhs.eval(t), left = lhs.eval(t);
	auto ret_lines =
		std::make_shared<std::set<line_no>>(left.begin(), left.end());
	ret_lines->insert(left.begin(), left.end());
	return QueryResult(rep(), left.get_file(),ret_lines);
}

QueryResult AndQuery::eval(const TextQuery &t) const
{
	auto right = rhs.eval(t), left = lhs.eval(t);
	auto ret_lines = std::make_shared<std::set<line_no>>();
	std::set_intersection(left.begin(), left.end(), right.begin(), right.end(),
		std::inserter(*ret_lines, ret_lines->begin()));
	return QueryResult(rep(), left.get_file(), ret_lines);

}

QueryResult NotQuery::eval(const TextQuery &t) const
{
	auto result = query.eval(t);
	auto ret_lines = std::make_shared<std::set<line_no>>();
	auto beg = result.begin(), end = result.end();
	auto sz = result.get_file()->size();
	for (size_t n = 0; n != sz; ++n)
	{
		if (beg == end || *beg != n)
			ret_lines->insert(n);
		else if (beg != end)
			++beg;
	}
	return QueryResult(rep(), result.get_file(), ret_lines);
}
