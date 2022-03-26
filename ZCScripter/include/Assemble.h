#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <types.h>
#include <map>
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
		bool _IsDeleted = false;														//变量是否被删除
	};

	class QLIEVector
	{
	private:
		std::vector<_QLIEVarient> _base;
	public:
		_QLIEVarient operator[](const unsigned _k_Hash) noexcept;
		//inline _QLIEVarient operator[](const std::wstring& _k_Token) noexcept;
		std::vector<std::allocator<_QLIEVarient>::value_type>::iterator begin() noexcept;
		std::vector<std::allocator<_QLIEVarient>::value_type>::iterator end() noexcept;
		std::vector<std::allocator<_QLIEVarient>::value_type>::reverse_iterator rbegin() noexcept;
		std::vector<std::allocator<_QLIEVarient>::value_type>::reverse_iterator rend() noexcept;
		const size_t size() noexcept;
		const void push_back(const _QLIEVarient& _Val) noexcept;
		const void push_front(const _QLIEVarient& _Val) noexcept;
		const void pop_back() noexcept;
		const void resize(const size_t _Val) noexcept;
		const void clear() noexcept;
		QLIEVector();
		QLIEVector(const size_t k_PreAllocate);
		QLIEVector(const std::vector<_QLIEVarient>& k_PreBase);
		QLIEVector(QLIEVector& k_PreBase);
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

	unsigned long _Self_Hash;				//这个变量池自身的Hash值
	unsigned long _RegisteredVarientAmount;	//所有Hash，包括已经删除了的
	unsigned long _DeletedVarientAmount;
	size_t _RefreshTimes;

	QLIE::QLIEVector _Varients;
	std::vector<unsigned long> _Registered_Hashes;//所有Hash，包括已经删除了的
	std::map<unsigned long, QLIE::_QLIEVarient> _VarientHashMap;
	std::map<unsigned long, std::wstring> _HashTokenMap;
	std::vector<unsigned long> _DeletedHashes;
	QLIE::_QLIEVarient _NULLVarient;

public:
	inline const static bool _CmpVarientByHash(const QLIE::_QLIEVarient& a, const QLIE::_QLIEVarient& b);
	inline const void _SortVarientByHash();
	inline const void _SortVarientByHash_Reversed();

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
	const bool _Check_VarientIsDeleted(const QLIE::_QLIEVarient& _k_Varient);
	const bool _Check_TokenHashPaired(const unsigned long& _k_Hash, const std::wstring& _k_Token);
	const bool _Check_TokenValuePaired(const std::wstring& _k_Token, const std::wstring& _k_Value);
	const bool _Check_HashValuePaired(const unsigned long& _k_Hash, const std::wstring& _k_Value);
	const bool _Check_SourceDestPaired(const QLIE::_QLIEVarient& _k_SourceVarient, const QLIE::_QLIEVarient& _k_DestVarient);
	const bool _Check_SourceDestPaired(const QLIE::_QLIEVarient* _k_SourceVarientPointer, const QLIE::_QLIEVarient& _k_DestVarient);
	const bool _Check_SourceDestPaired(const QLIE::_QLIEVarient* _k_SourceVarientPointer, const QLIE::_QLIEVarient* _k_DestVarientPointer);
	const bool _Check_SourceDestPaired(const QLIE::_QLIEVarient& _k_SourceVarient, const QLIE::_QLIEVarient* _k_DestVarientPointer);
	const bool _ValidateVarient(const QLIE::_QLIEVarient& _k_SourceVarient);
	const bool _ValidateVarient(const QLIE::_QLIEVarient* _k_SourceVarientPointer);

	inline const unsigned long _GetVarientAmount() noexcept;
	inline const unsigned long _GetRegisteredHashAmount() noexcept;
	inline const unsigned long _AllocateNewHash() noexcept;

	QLIE::_QLIEVarient _GetVarient(const unsigned long& _k_Hash);//Basement
	QLIE::_QLIEVarient _GetVarient(const std::wstring& _k_Token);
	QLIE::_QLIEVarient _GetVarient(const std::wstring& _k_Token, const unsigned long& _k_Hash);
	QLIE::_QLIEVarient _GetVarient(const QLIE::_QLIEVarient* _k_SourceVarientPointer);
	QLIE::_QLIEVarient* _GetVarientPointer(const unsigned long& _k_Hash);//Basement
	QLIE::_QLIEVarient* _GetVarientPointer(const std::wstring& _k_Token);
	QLIE::_QLIEVarient* _GetVarientPointer(const std::wstring& _k_Token, const unsigned long& _k_Hash);
	QLIE::_QLIEVarient* _GetVarientPointer(const QLIE::_QLIEVarient _k_SourceVarient);

	const unsigned long _GetHashByToken(const std::wstring& _k_Token);
	const unsigned long _GetHashByToken(const std::wstring& _k_Token, std::wstring& _k_Value);

	const std::wstring _GetTokenByValue(const std::wstring& _k_Value);
	const std::wstring _GetTokenByHash(const unsigned long& _k_Hash);

	inline const bool _Refresh(const unsigned long _k_ResortStandard = 500) noexcept;
	void _Clear();

	QLIEVarientPool operator+(const QLIE::_QLIEVarient& _b);
	void operator+=(const QLIE::_QLIEVarient& _b);
	QLIEVarientPool operator-(const QLIE::_QLIEVarient& _b);
	void operator-=(const QLIE::_QLIEVarient& _b);
	QLIE::_QLIEVarient operator[](const unsigned long _k_Hash);
	QLIE::_QLIEVarient operator[](const std::wstring& _k_Token);

	QLIEVarientPool();
	QLIEVarientPool(unsigned long k_SpecificHash);
	QLIEVarientPool(const QLIE::_QLIEVarient& k_SpecificNULLVar);
	QLIEVarientPool(unsigned long k_SpecificHash,const QLIE::_QLIEVarient& k_SpecificNULLVar);
	~QLIEVarientPool();
};
class HashExistedException : public std::exception
{
private:
	unsigned long _ConflictHash;

public:
	//unsigned long GetConflictHash();
};