#pragma once
#include <iostream>
#include <string>
#include <types.h>
#include <vector>

namespace QLIE
{
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
		_UNDEFINED__QLIEParameterTypes,
		_INT,
		_STRING,
		_BOOLEAN,
	};
	enum _QLIELogicalConditionTypes
	{
		_UNDEFINED_QLIELogicalConditionTypes,
		_EQUALS,
		_BIGGER_THAN,
		_SMALLER_THAN,
	};

	struct _QLIEParameter_NormalForm
	{
		_QLIEParameterTypes ParameterType = _QLIEParameterTypes::_UNDEFINED__QLIEParameterTypes;
		std::wstring Parameter;
	};
	struct _QLIEParameters
	{
		unsigned long ParameterCount = -1;
		std::vector<_QLIEParameter_NormalForm> Parameters;
	};
	struct _QLIEScripts
	{
		unsigned long ScriptAmount = -1;
		StatusCode Status = -1;
		std::vector<_QLIEScript> Scripts;
	};
	struct _QLIEScriptBlocks
	{
		unsigned long BlockAmount = -1;
		StatusCode Status = -1;
		std::vector<_QLIEScripts> Scripts;
	};
	struct _QLIEFunction_NormalForm
	{
		_QLIEKeywords Keyword;
		_QLIEParameter_NormalForm Parameters;
	};
	struct _QLIELogicalCondition
	{
		//bool _IS = false;
		_QLIEParameterTypes _ParameterType;
		_QLIELogicalConditionTypes _LogicalType;
		std::wstring LeftValue;
		std::wstring RightValue;
	};
	struct _QLIELogicalFunction
	{
		_QLIEKeywords LogicalKeyword;
		_QLIELogicalCondition Condition;
		_QLIEScripts _TODO_IF_TRUE;
		_QLIEScripts _TODO_IF_FALSE;
	};

	struct _QLIEAssembleCommand_NormalForm
	{
		_QLIEScripts _SourceScripts;
		StatusCode Status = -1;
		_QLIEParameter_NormalForm _Parameters;
	};

	class ExtractCommands
	{
	private:
		_QLIEScripts _Scripts;
	};
};
class QLIEHelper
{
private:
	static QLIE::_QLIEParameterTypes _GetParameterType(const _QLIEScript _k_Script);
	static QLIE::_QLIEParameters _GetParameters(const _QLIEScript _k_Script);

public:
	static QLIE::_QLIEParameterTypes GetParameterType(const _QLIEScript k_Script);
	static QLIE::_QLIEParameters GetParameters(const _QLIEScript k_Script);
};
