#ifndef TEST_H
#define TEST_H
#include <map>

enum KEYWORD{
	KEYWORD_START = -1,
	KEYWORD_A = 0,
	KEYWORD_B,
	KEYWORD_C,
	KEYWORD_D,
};
class TableDrive
{
public:
	bool HandleKeyword(int keyword);

	bool MapKeyToHandle();

	TableDrive();
	~TableDrive();
private:
	bool HandleKeyA();
	bool HandleKeyB();
	bool HandleKeyC();
private:
	typedef bool(TableDrive::*pHandle)(void);
	std::map<int, pHandle> m_KeyToHandle;
};

#endif