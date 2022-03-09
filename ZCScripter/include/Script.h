#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Assemble.h>
#include <map>

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
	//------------------------------
	//Non-Engine System Script Types
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
	SetSound,			//example:^se03,file:●波羅密多_loop,loop:true,vol:20
								//^se03,vol:10,oncetime:2000
	SetCamera,			//example:^camera,genfilter:"mode:abssin,cycle:500,fade:none,time:250,delay:0,infinity:false,target:position,x:0,y:0,z:-10"
	SetCharacterFace,	//example:^face,show:false **UNKNOWN USAGE, NO FILE SELECTED AT ALL
								//^face,file:月丘_顔_私服_017驚き1,show:true **THE ONLY PROPER USAGE
	SetEntryName,		//example:@@MAIN
	SetIncludeFile,		//example:@@@Avg\Header.s
	SetSelect,			//example:^select,回应月丘女士的心情,果断拒绝
	SetSelectLabel,		//example:^selectlabel,"@@k01_01sel_0","@@k01_01sel_1"
	__UNKNOWN_SCRIPT3,	//example:^textani,file:none
	SetMessage,			//example:^message,show:false
	SetEffect,			//example:^ef02,file:立ち絵/香恋_胸
	__UNKNOWN_SCRIPT4,	//example:^format,log:continue

	//------------------------------
	//Engine-related System Script Types
	_JMP,				//example:\jmp,Avg_SelectCurLabel
	_SUB,				//example:\sub,@@!KRouteJmp,"Scenario\Root.s",SelfFileName,01
};
enum CharacterScriptTypes
{
	_UNDEFINED_CharacterScript,
	PlayVoice			//example:％reng2820％
};
enum ScriptWriteStatus
{
	Success = true,
	OpenFileFailed,
	UndefinedError = false,
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
	//std::wstring Speaker;
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
	std::wstring _Filename;
	SingleScript Script;
	std::wstring _command;
	QLIE::_QLIEParameters _parameters;
};
struct CharacterScript
{
	unsigned long Order = -1;
	StatusCode Status = -1;
	std::wstring Speaker;
	CharacterScriptTypes ScriptType = CharacterScriptTypes::_UNDEFINED_CharacterScript;
	std::wstring _Filename;
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
	//std::wstring Speaker;
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
	std::wstring CompleteFileName;
	std::map<unsigned long long, std::pair<unsigned long long,short> > _Typetable;
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

	ScriptContent _ScriptContent;
	SplitedScripts _LineSplitedScriptContent;
	ScriptBlocks _ScriptBlocks;
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
class Script_Converter
{
private:
	ScriptBlocks _ScriptBlocks;
	QLIE::_QLIEScripts _QLIEScriptBlocks;
	//QLIE::_QLIEScript _ScriptBlock_TO_QLIEScript();
	static QLIE::_QLIEScripts _SplitedScripts_TO_QLIEScripts(const SplitedScripts _k_source);
	QLIE::_QLIEScriptBlocks _ScriptBlocks_TO_QLIEScriptBlocks();

public:
	//QLIE::_QLIEScript ScriptBlock_TO_QLIEScript();
	static QLIE::_QLIEScripts SplitedScripts_TO_QLIEScripts(const SplitedScripts k_source);
	QLIE::_QLIEScriptBlocks ScriptBlocks_TO_QLIEScriptBlocks();

	Script_Converter();
	Script_Converter(const char *);
	~Script_Converter();
};
class Script_Writer
{
private:
	std::wstring DestAddress;
	const static ScriptWriteStatus _s_WriteScripts(const std::wstring& _k_DestAddress, const TranslatedScripts& _k_source);

public:
	const static ScriptWriteStatus s_WriteScripts(const std::wstring& k_DestAddress, const TranslatedScripts& k_source);
};
