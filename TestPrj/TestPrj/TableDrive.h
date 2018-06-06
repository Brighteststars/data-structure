#ifndef TABLEDRIVE_H
#define TABLEDRIVE_H  //������
#include <map>

// �����ùؼ���  
enum KEYWORD
{
	KEYWORD_START = -1,

	KEYWORD_A = 0,
	KEYWORD_B,
	KEYWORD_C,
	KEYWORD_D,

	KEYWORD_END,	//ע�ⶺ��
};


class TableDrive
{
public:

	// ------------------------------------------------------------  
	// Description :   
	//      ���ݹؼ��֣�ִ�д�����  
	// Parameters :   
	//      string keyword���ؼ���  
	// Return Value :   
	//      bool��true������ִ�гɹ���false���Ҳ������ֶ�Ӧ�ĺ���������ִ��ʧ��  
	// Errors :   
	//      ��  
	// ------------------------------------------------------------   
	bool HandleKeyword(int keyword);

	// ------------------------------------------------------------  
	// Description :   
	//      �����ؼ��ֵ�������  
	// Parameters :   
	//      ��  
	// Return Value :   
	//      bool��true��������false���쳣  
	// Errors :   
	//      ��  
	// ------------------------------------------------------------   
	bool MapKeyToHandle();


	TableDrive();

	~TableDrive();

private:

	// vv ��������true��ִ�гɹ���false��ִ��ʧ��  
	bool HandleKeyA();
	bool HandleKeyB();
	bool HandleKeyC();
	// ^^  

private:

	// :TRICKY: ��Ա����ָ�붨��  
	typedef bool (TableDrive:: *PHandle)(void);
	std::map<int, PHandle>   m_KeyToHandle;      // �ؼ��ֶ�Ӧ������  
};

 

// ^^^^^ TableDrive.h end  




// vvvvv TableDrive.cpp begin  

// ------------------------------------------------------------  
// Name         :   TableDrive.cpp  
// Description  :   ������ʵ���ļ�  
// History      :   
// ------------------------------------------------------------  

#include    <stdio.h>  

 

// ------------------------------------------------------------  


// ���ݹؼ��֣�ִ�д�����  
bool TableDrive::HandleKeyword(int keyword)
{
	typedef std::map<int, PHandle>::const_iterator CI;
	CI iter = m_KeyToHandle.find(keyword);

	// û���������ؼ���  
	if (m_KeyToHandle.end() == iter)
	{
		printf("\n  @@ search Keyword %d fail!\n", keyword);
		return false;
	}

	// :TRICKY: ע���Ա����ָ������ø�ʽ  
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

// �����ؼ��ֵ�������  
bool TableDrive::MapKeyToHandle()
{
	m_KeyToHandle[KEYWORD_A] = &TableDrive::HandleKeyA;
	m_KeyToHandle[KEYWORD_B] = &TableDrive::HandleKeyB;
	m_KeyToHandle[KEYWORD_C] = &TableDrive::HandleKeyC;

	return true;
}


// ������ A  
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