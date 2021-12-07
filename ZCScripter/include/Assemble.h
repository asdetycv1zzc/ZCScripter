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
		_STRING
	};
	enum _QLIELogicalConditionTypes
	{
		_UNDEFINED_QLIELogicalConditionTypes,
		_EQUALS,
		_BIGGER_THAN,
		_SMALLER_THAN,
	};
	struct _QLIEScript
	{
		unsigned long Order = -1;
		StatusCode Status = -1;
		SingleScript Script;
	};
	struct _QLIEParameter_NormalForm
	{
		_QLIEParameterTypes ParameterType = _QLIEParameterTypes::_UNDEFINED__QLIEParameterTypes;
		unsigned long ParameterCount = 0;
		std::vector<std::wstring> Parameters_String;
		std::vector<int> Parameters_Int;
	};
	struct _QLIEScripts
	{
		unsigned long BlockAmount = -1;
		StatusCode Status = -1;
		std::vector<_QLIEScript> Blocks;
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
