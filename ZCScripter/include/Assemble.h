#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <global.h>
#include <types.h>
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
		_SYSTEM_SCRIPT,
	};
	enum _QLIELogicalConditionTypes
	{
		_UNDEFINED_QLIELogicalConditionTypes,
		_EQUALS,
		_BIGGER_THAN,
		_SMALLER_THAN,
		_BIGGER_THAN_OR_EQUAL,
		_SMALLER_THAN_OR_EQUAL,
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
	struct _QLIEVarient
	{
		std::wstring Token;
		unsigned long _Hash = -1;
		std::wstring Value;
		_QLIEParameterTypes Type = _QLIEParameterTypes::_UNDEFINED__QLIEParameterTypes;
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
	const static QLIE::_QLIEParameterTypes _GetParameterType(const _QLIEScript& _k_Script);
	const static QLIE::_QLIEParameters _GetParameters(const _QLIEScript& _k_Script);
	const static std::wstring _GetCommand(const _QLIEScript& _k_Script);

public:
	const static QLIE::_QLIEParameterTypes GetParameterType(const _QLIEScript& k_Script);
	const static QLIE::_QLIEParameters GetParameters(const _QLIEScript& k_Script);
	const static std::wstring GetCommand(const _QLIEScript& k_Script);
};
class QLIEVarientPool
{
private:
	/*
	参数里面提供_QLIEVarient类型参数的，提供的是已经指定了Hash的参数，非常不推荐使用
	建议使用自动的提供_k_Token与_k_Value名称的函数，能够自动管理Hash值
	*/
	/*
	所有Hash值都从0开始
	*/
	unsigned long _Self_Hash;
	unsigned long _RegisteredVarientAmount;
	std::vector<QLIE::_QLIEVarient> _Varients;
	std::vector<std::pair<unsigned long, unsigned long>> _VarientHash_SourceOrder;
	std::vector<unsigned long> _DeletedHashes;
	QLIE::_QLIEVarient _NULLVarient;

	static bool _CmpVarientByHash(QLIE::_QLIEVarient a, QLIE::_QLIEVarient b);
	void _SortVarientByHash();
	//void _SortVarientByHash(std::vector<QLIE::_QLIEVarient>::const_iterator _k_begin, std::vector<std::allocator< QLIE::_QLIEVarient>::value_type>::const_iterator _k_end);
	//void _SortVarientByHash_Reversed();
	//void _SortVarientByHash_Reversed(std::reverse_iterator<std::vector<QLIE::_QLIEVarient>::iterator> _k_rbegin, std::reverse_iterator<std::vector<QLIE::_QLIEVarient>::iterator> _k_rend);

	bool _AddVarient(QLIE::_QLIEVarient _k_Varient);
	bool _AddVarient(std::wstring _k_Token, std::wstring _k_Value, QLIE::_QLIEParameterTypes _k_Type = QLIE::_QLIEParameterTypes::_UNDEFINED__QLIEParameterTypes);
	bool _AddVarient(unsigned long _k_Hash, std::wstring _k_Value, QLIE::_QLIEParameterTypes _k_Type = QLIE::_QLIEParameterTypes::_UNDEFINED__QLIEParameterTypes);
	bool _DeleteVarient(QLIE::_QLIEVarient _k_Varient);
	bool _DeleteVarient(std::wstring _k_Token, std::wstring _k_Value);
	bool _DeleteVarient(unsigned long _k_Hash);
	bool _DeleteVarient(unsigned long _k_Hash, std::wstring _k_Value);
	//bool _SetVarient(QLIE::_QLIEVarient _k_SourceVarient, QLIE::_QLIEVarient _k_DestVarient);
	//bool _SetVarient(QLIE::_QLIEVarient* _k_SourceVarientPointer, QLIE::_QLIEVarient _k_DestVarient);
	//bool _SetVarient(unsigned long _k_Hash, std::wstring _k_Token, std::wstring _k_Value);
	//bool _SetVarient(unsigned long _k_Hash, std::wstring _k_Value);
	//bool _SetVarient(unsigned long _k_Hash, QLIE::_QLIEVarient _k_DestVarient);

	//bool _Check_HashIsExist(unsigned long _k_Hash);
	//bool _Check_HashIsDeleted(unsigned long _k_Hash);
	//bool _Check_VarientIsDeleted(unsigned long _k_Hash);
	//bool _Check_VarientIsDeleted(std::wstring _k_Token);
	//bool _Check_VarientIsDeleted(unsigned long _k_Hash,std::wstring _k_Token);
	//bool _Check_VarientIsDeleted(unsigned long _k_Hash, std::wstring _k_Token, std::wstring _k_Value);
	//bool _Check_VarientIsDeleted(QLIE::_QLIEVarient _k_Varient);
	//bool _Check_TokenHashPaired(unsigned long _k_Hash, std::wstring _k_Token);
	//bool _Check_TokenValuePaired(std::wstring _k_Token, std::wstring _k_Value);

	//const unsigned long _GetVarientAmount();
	//const unsigned long _AllocateNewHash();

	//QLIE::_QLIEVarient _GetVarient(std::wstring _k_Token);
	//QLIE::_QLIEVarient _GetVarient(unsigned long _k_Hash);
	//QLIE::_QLIEVarient _GetVarient(std::wstring _k_Token, unsigned long _k_Hash);
	//const QLIE::_QLIEVarient* _GetVarientPointer(std::wstring _k_Token);
	//const QLIE::_QLIEVarient* _GetVarientPointer(unsigned long _k_Hash);
	//const QLIE::_QLIEVarient* _GetVarientPointer(std::wstring _k_Token, unsigned long _k_Hash);

	//unsigned long _GetHashByToken(std::wstring _k_Token);
	//unsigned long _GetHashByToken(std::wstring _k_Token, std::wstring _k_Value);
	//std::wstring _GetTokenByValue(std::wstring _k_Token);
	//std::wstring _GetValueByHash(unsigned long _k_Hash);

public:
	QLIEVarientPool();
	//QLIEVarientPool(unsigned long k_SpecificHash);
	~QLIEVarientPool();
};

class HashExistedException : public std::exception
{
private:
	unsigned long _ConflictHash;

public:
	//unsigned long GetConflictHash();
};