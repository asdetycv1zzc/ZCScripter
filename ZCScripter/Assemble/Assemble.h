#pragma once
#include<iostream>
#include<string>
#include<Script.h>

enum _QLIEKeywords
{
	_UNDEFINED__QLIEKeywords,
	_SUB,
	_JMP,
	_IF,
	_THEN,
	_END,
	_FRAGCAL,
	_FRAGTRACK,
	_CAL,
	_RET,
	LOGINCAL_JUDGE,
};
enum _QLIEParameterTypes
{
	_UNDEFINED,
	_INT,
	_STRING
};

struct _QLIEScript
{
	unsigned long Order = -1;
	StatusCode Status = -1;
	SingleScript Script;
};

struct _QLIEScripts
{
	unsigned long BlockAmount = -1;
	StatusCode Status = -1;
	std::vector<_QLIEScript> Blocks;
};
struct _QLIEFunction
{
	_QLIEKeywords Keyword;
	
};
struct _QLIEParameter_NormalForm
{
	_QLIEParameterTypes ParameterType = _QLIEParameterTypes::_UNDEFINED;
	unsigned long ParameterCount = 0;
	std::vector<std::wstring> Parameters;
};
struct _QLIEAssembleCommand_NormalForm
{
	_QLIEScripts _SourceScript;
	StatusCode Status = -1;
	_QLIEParameter_NormalForm _Parameter;
};