#pragma once
#include <iostream>
#include <string>
#include <vector>
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
		std::wstring Token;																//变量名称
		unsigned long _Hash = -1;														//变量的唯一标识符
		std::wstring Value;																//变量值
		_QLIEParameterTypes Type = _QLIEParameterTypes::_UNDEFINED__QLIEParameterTypes;	//变量类型
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
	unsigned long _Self_Hash;//这个变量池自身的Hash值
	unsigned long _RegisteredVarientAmount;
	std::vector<QLIE::_QLIEVarient> _Varients;
	std::vector<std::pair<unsigned long, unsigned long>> _VarientHash_SourceOrder;
	std::vector<unsigned long> _DeletedHashes;
	QLIE::_QLIEVarient _NULLVarient;

	const static bool _CmpVarientByHash(const QLIE::_QLIEVarient& a, const QLIE::_QLIEVarient& b);
	const void _SortVarientByHash();
	const void _SortVarientByHash(const std::vector<QLIE::_QLIEVarient>::const_iterator& _k_begin, const std::vector<std::allocator< QLIE::_QLIEVarient>::value_type>::const_iterator& _k_end);
	const void _SortVarientByHash_Reversed();
	const void _SortVarientByHash_Reversed(const std::reverse_iterator<std::vector<QLIE::_QLIEVarient>::iterator>& _k_rbegin, const std::reverse_iterator<std::vector<QLIE::_QLIEVarient>::iterator>& _k_rend);

	const bool _AddVarient(const QLIE::_QLIEVarient& _k_Varient);
	const bool _AddVarient(const std::wstring& _k_Token, const std::wstring& _k_Value, const QLIE::_QLIEParameterTypes _k_Type = QLIE::_QLIEParameterTypes::_UNDEFINED__QLIEParameterTypes);
	const bool _AddVarient(const unsigned long& _k_Hash, const std::wstring& _k_Value, const QLIE::_QLIEParameterTypes _k_Type = QLIE::_QLIEParameterTypes::_UNDEFINED__QLIEParameterTypes);
	const bool _DeleteVarient(const QLIE::_QLIEVarient& _k_Varient);
	const bool _DeleteVarient(const std::wstring& _k_Token, const std::wstring& _k_Value);
	const bool _DeleteVarient(const unsigned long& _k_Hash);
	const bool _DeleteVarient(const unsigned long& _k_Hash, const std::wstring& _k_Value);
	const bool _SetVarient(const QLIE::_QLIEVarient& _k_SourceVarient, const QLIE::_QLIEVarient& _k_DestVarient);
	const bool _SetVarient(QLIE::_QLIEVarient* _k_SourceVarientPointer, const QLIE::_QLIEVarient& _k_DestVarient);
	const bool _SetVarient(const unsigned long& _k_Hash, const std::wstring& _k_Token, std::wstring _k_Value);
	const bool _SetVarient(const unsigned long& _k_Hash, const std::wstring& _k_Value);
	const bool _SetVarient(const unsigned long& _k_Hash, const QLIE::_QLIEVarient& _k_DestVarient);

	const bool _Check_HashIsExist(const unsigned long& _k_Hash);
	const bool _Check_HashIsDeleted(const unsigned long& _k_Hash);
	const bool _Check_VarientIsDeleted(const unsigned long& _k_Hash);
	const bool _Check_VarientIsDeleted(const std::wstring& _k_Token);
	const bool _Check_VarientIsDeleted(const unsigned long& _k_Hash, const std::wstring& _k_Token);
	const bool _Check_VarientIsDeleted(const unsigned long& _k_Hash, const std::wstring& _k_Token, const std::wstring& _k_Value);
	const bool _Check_VarientIsDeleted(const QLIE::_QLIEVarient _k_Varient);
	const bool _Check_TokenHashPaired(const unsigned long& _k_Hash, const std::wstring& _k_Token);
	const bool _Check_TokenValuePaired(const std::wstring& _k_Token, const std::wstring& _k_Value);
	const bool _Check_HashValuePaired(const unsigned long& _k_hash, const std::wstring& _k_Value);
	const bool _Check_SourceDestPaired(const QLIE::_QLIEVarient& _k_SourceVarient, const QLIE::_QLIEVarient& _k_DestVarient);
	const bool _Check_SourceDestPaired(const QLIE::_QLIEVarient* _k_SourceVarientPointer, const QLIE::_QLIEVarient& _k_DestVarient);

	const unsigned long _GetVarientAmount();
	const unsigned long _AllocateNewHash();

	QLIE::_QLIEVarient _GetVarient(const std::wstring& _k_Token);
	QLIE::_QLIEVarient _GetVarient(const unsigned long& _k_Hash);
	QLIE::_QLIEVarient _GetVarient(const std::wstring& _k_Token, const unsigned long& _k_Hash);
	QLIE::_QLIEVarient* _GetVarientPointer(const std::wstring& _k_Token);
	QLIE::_QLIEVarient* _GetVarientPointer(const unsigned long& _k_Hash);
	QLIE::_QLIEVarient* _GetVarientPointer(const std::wstring& _k_Token, const unsigned long& _k_Hash);

	const unsigned long _GetHashByToken(const std::wstring _k_Token);
	const unsigned long _GetHashByToken(const std::wstring _k_Token, std::wstring _k_Value);

	const std::wstring _GetTokenByValue(const std::wstring _k_Token);
	const std::wstring _GetTokenByHash(const std::wstring _k_Token);

	const std::wstring _GetValueByHash(const unsigned long _k_Hash);

	inline const bool _Refresh();
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