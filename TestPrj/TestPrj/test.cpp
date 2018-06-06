#include "test.h"
#include <iostream>

TableDrive::TableDrive()
{
	std::cout << "\n TableDrive::TableDrive()  default constructor\n";
	MapKeyToHandle();

}

TableDrive::~TableDrive()
{
	std::cout << "\n TableDrive::~TableDrive() \n";
}

bool TableDrive::HandleKeyA()
{
	std::cout << "\n**A		KEYWORD_A\n\n";
	return true;
}

bool TableDrive::HandleKeyB()
{
	std::cout << "\n**B		KEYWORD_B\n\n";
	return true;
}

bool TableDrive::HandleKeyC()
{
	std::cout << "\n**C		KEYWORD_C\n\n";
	return true;
}

bool TableDrive::MapKeyToHandle()
{
	m_KeyToHandle[KEYWORD_A] =  &TableDrive::HandleKeyA;
	m_KeyToHandle[KEYWORD_B] =	&TableDrive::HandleKeyB;
	m_KeyToHandle[KEYWORD_C] =	&TableDrive::HandleKeyC;

	return true;
}

// 关键值处理函数接口
bool TableDrive::HandleKeyword(int keyword)
{
	auto map_it = m_KeyToHandle.find(keyword);
	if (map_it == m_KeyToHandle.end())
	{
		std::cout << "Don't find " << keyword << std::endl;
		return false;
	}

	auto pFunc = map_it->second;
	return (this->*pFunc)();

	
}