#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef int StatusCode;
typedef std::wstring SingleScript;
typedef std::wstring SingleLineOfWords;
enum InputMode
{
	byScriptAddress,
	byScriptContent
};
enum SystemScriptTypes
{
	_UNDEFINED_SystemScript,
	SetPostScript,		//example:^include,allset
	SetBackground,		//example:^bg01,$zoom_near,scalex:120,scaley:120
	SetMusic,			//example:^music01,file:12切ない曲
	SetCharacterModel,	//example:^chara01,file0:夏彦_,file1:小_,file2:制服_,file3:001通常01,show:true,alpha:128
						//^chara01,addcolor:$FFFFFF
						//^chara01,file0:none
						//^chara01,file3:082泣き3
	SetSentenceEffects, //example:^sentence,fademode:overlap,fadetime:1000
						//^sentence,$overlap
	__UnknownScript1,	//example:^se03,file:●波羅密多_loop,loop:true,vol:20
						//^se03,vol:10,oncetime:2000
	SetCamera,			//example:^camera,genfilter:"mode:abssin,cycle:500,fade:none,time:250,delay:0,infinity:false,target:position,x:0,y:0,z:-10"
	__UnknownScript2	//example:^face,show:false
};
enum CharacterScriptTypes
{
	_UNDEFINED_CharacterScript,
	PlayVoice //example:％reng2820％//
};

struct ScriptContent
{
	char *FileName = NULL;
	StatusCode Status = -1;
	std::wstring Content;
	long long FileLength = -1;
};
struct SplitedScripts
{
	unsigned long ScriptAmount = -1;
	StatusCode Status = -1;
	std::vector<SingleScript> Scripts;
};
struct ScriptBlocks
{
	unsigned long BlockAmount = -1;
	StatusCode Status = -1;
	std::vector<SplitedScripts> Blocks;
};
struct SystemScript
{
	unsigned long Order = -1;
	StatusCode Status = -1;
	SystemScriptTypes ScriptType = SystemScriptTypes::_UNDEFINED_SystemScript;
	SingleScript Script;
};
struct CharacterScript
{
	unsigned long Order = -1;
	StatusCode Status = -1;
	std::wstring Speaker;
	CharacterScriptTypes ScriptType = CharacterScriptTypes::_UNDEFINED_CharacterScript;
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
	char *_ScriptAddress;
	long long _Length;
	ScriptContent _Content;
	long long _GetScriptLength();
	ScriptContent _ReadScript();

public:
	ScriptContent Read();
	void init(const char *_ScriptAddress);
	Script_Read();
	Script_Read(const char *k_ScriptAddress);
	~Script_Read();
};
class Script_Analyze
{
private:
	char *_ScriptAddress;
	long long _Length;

	ScriptContent _ScriptContent;
	SplitedScripts _LineSplitedScriptContent;
	ScriptBlocks _ScriptBlocks;

	SystemScripts _SystemScripts;
	CharacterScripts _CharacterScripts;
	SortedScripts _SortedScripts;

	SplitedScripts _SplitLinesByCRLF();
	ScriptBlocks _SplitScript(const wchar_t *_ConvertedCRLF = L"\n", unsigned long long _JudgeLines = 15);
	SortedScripts _SortScript();

	static std::wstring _GetSpeaker(const SplitedScripts _k_SplitedScripts);
	static SystemScriptTypes _GetSystemScriptType(const SingleScript _k_SingleScript);
	static CharacterScriptTypes _GetCharacterScriptType(const SingleScript _k_SingleScript);

public:
	SplitedScripts SplitLinesByCRLF();
	ScriptBlocks SplitScript(const wchar_t *ConvertedCRLF = L"\n", unsigned long long JudgeLines = 15);
	SortedScripts SortScript();

	static std::wstring GetSpeaker(const SplitedScripts k_SplitedScripts);
	static SystemScriptTypes GetSystemScriptType(const SingleScript k_SingleScript);
	static CharacterScriptTypes GetCharacterScriptType(const SingleScript k_SingleScript);
	
	Script_Analyze();
	Script_Analyze(const char *);
	~Script_Analyze();
};
class Script_System
{
private:
	SystemScripts _SystemScripts;
	SortedScripts _SortedScripts;
};
