#ifndef TABLEDRIVE_H
#define TABLEDRIVE_H  //表驱动
#include <map>

// 测试用关键字  
enum KEYWORD
{
	KEYWORD_START = -1,

	KEYWORD_A = 0,
	KEYWORD_B,
	KEYWORD_C,
	KEYWORD_D,

	KEYWORD_END,	//注意逗号
};


class TableDrive
{
public:

	// ------------------------------------------------------------  
	// Description :   
	//      根据关键字，执行处理函数  
	// Parameters :   
	//      string keyword，关键字  
	// Return Value :   
	//      bool，true，函数执行成功，false，找不到键字对应的函数，或函数执行失败  
	// Errors :   
	//      无  
	// ------------------------------------------------------------   
	bool HandleKeyword(int keyword);

	// ------------------------------------------------------------  
	// Description :   
	//      关联关键字到处理函数  
	// Parameters :   
	//      无  
	// Return Value :   
	//      bool，true，正常，false，异常  
	// Errors :   
	//      无  
	// ------------------------------------------------------------   
	bool MapKeyToHandle();


	TableDrive();

	~TableDrive();

private:

	// vv 处理函数，true，执行成功，false，执行失败  
	bool HandleKeyA();
	bool HandleKeyB();
	bool HandleKeyC();
	// ^^  

private:

	// :TRICKY: 成员函数指针定义  
	typedef bool (TableDrive:: *PHandle)(void);
	std::map<int, PHandle>   m_KeyToHandle;      // 关键字对应处理函数  
};

 

// ^^^^^ TableDrive.h end  




// vvvvv TableDrive.cpp begin  

// ------------------------------------------------------------  
// Name         :   TableDrive.cpp  
// Description  :   表驱动实现文件  
// History      :   
// ------------------------------------------------------------  

#include    <stdio.h>  

 

// ------------------------------------------------------------  


// 根据关键字，执行处理函数  
bool TableDrive::HandleKeyword(int keyword)
{
	typedef std::map<int, PHandle>::const_iterator CI;
	CI iter = m_KeyToHandle.find(keyword);

	// 没有搜索到关键字  
	if (m_KeyToHandle.end() == iter)
	{
		printf("\n  @@ search Keyword %d fail!\n", keyword);
		return false;
	}

	// :TRICKY: 注意成员函数指针的引用格式  
	PHandle pFunction = iter->second;
	return (this->*pFunction)();
}


TableDrive::TableDrive()
{
	printf("\n  vv TableDrive::TableDrive()\n");
	MapKeyToHandle();
}

TableDrive::~TableDrive()
{
	printf("\n  ^^ TableDrive::~TableDrive()\n");
}


// ------------------------------------------------------------  

// 关联关键字到处理函数  
bool TableDrive::MapKeyToHandle()
{
	m_KeyToHandle[KEYWORD_A] = &TableDrive::HandleKeyA;
	m_KeyToHandle[KEYWORD_B] = &TableDrive::HandleKeyB;
	m_KeyToHandle[KEYWORD_C] = &TableDrive::HandleKeyC;

	return true;
}


// 处理函数 A  
bool TableDrive::HandleKeyA()
{
	printf("\n  ** A, HandleKeyA()\n\n");

	return true;
}

bool TableDrive::HandleKeyB()
{
	printf("\n  ** B, HandleKeyB()\n\n");

	return true;
}

bool TableDrive::HandleKeyC()
{
	printf("\n  ** C, HandleKeyC()\n\n");

	return true;
}

#endif