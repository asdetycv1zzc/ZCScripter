#include<iostream>
#include<fstream>
#include<string>
#include<vector>

typedef int StatusCode;
typedef std::wstring SingleScript;
typedef std::wstring SingleLineOfWords;
enum InputMode
{
	byScriptAddress,
	byScriptContent
};

struct ScriptContent
{
	char* FileName = NULL;
	StatusCode Status = -1;
	std::wstring Content;
	long long FileLength = -1;
};
struct SplitedScripts
{
	long long ScriptAmount = -1;
	StatusCode Status = -1;
	std::vector<SingleScript> Scripts;
};
struct ScriptBlocks
{
	long long BlockAmount = -1;
	StatusCode Status = -1;
	std::vector<SplitedScripts> Blocks;
};
struct SystemScript
{
	unsigned long Order = -1;
	StatusCode Status = -1;
	SingleScript Script;
};
struct CharacterScript
{
	unsigned long Order = -1;
	StatusCode Status = -1;
	std::wstring Speaker;
	SingleScript Script;
};
struct SystemScripts
{
	unsigned long BlockAmount = -1;
	StatusCode Status = -1;
	std::vector<SystemScript> Blocks;
};
struct CharacterScripts
{
	unsigned long BlockAmount = -1;
	StatusCode Status = -1;
	std::vector<CharacterScript> Blocks;
};
struct SortedScriptBlock
{
	StatusCode Status = -1;
	unsigned long Order = -1;
	unsigned long BlockAmount = -1;
	SystemScripts _SystemScripts;
	CharacterScripts _CharacterScripts;
};
struct SortedScripts
{
	StatusCode Status = -1;
	unsigned long BlockAmount = -1;
	SystemScripts _SystemScripts;
	CharacterScripts _CharacterScripts;
};

class Script_Read
{
private:
	char* _ScriptAddress;
	long long _Length;
	ScriptContent _Content;
	long long _GetScriptLength();
	ScriptContent _ReadScript();

public:
	ScriptContent Read();
	void init(const char* _ScriptAddress);
	Script_Read();
	Script_Read(const char* k_ScriptAddress);
	~Script_Read();
};
class Script_Analyze
{
private:
	char* _ScriptAddress;
	long long _Length;

	ScriptContent _ScriptContent;
	SplitedScripts _LineSplitedScriptContent;
	ScriptBlocks _ScriptBlocks;

	SystemScripts _SystemScripts;
	CharacterScripts _CharacterScripts;
	SortedScripts _SortedScripts;

	SplitedScripts _SplitLinesByCRLF();
	/// <param name="JudgeLines">�ж���ֵ����һ��\r\n���ִ������ڵ�����ֵʱ��ɾ����Щ\r\n</param> 
	/// <returns>Status code of 0 on successful run</returns>
	ScriptBlocks _SplitScript(const wchar_t* ConvertedCRLF = L"\n", long long JudgeLines = 15);
	SortedScripts _SortScript();
public:
	SplitedScripts SplitLinesByCRLF();
	ScriptBlocks SplitScript(const wchar_t* ConvertedCRLF = L"\n", long long JudgeLines = 15);
	SortedScripts SortScript();
	Script_Analyze();
	Script_Analyze(const char*);
	~Script_Analyze();
};


