#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <Assemble.h>
using namespace std;

const bool QLIEVarientPool::_CmpVarientByHash(const QLIE::_QLIEVarient& a, const QLIE::_QLIEVarient& b)
{
	return a._Hash < b._Hash;
}
const void QLIEVarientPool::_SortVarientByHash()
{
	sort(_Varients.begin(), _Varients.end(), _CmpVarientByHash);
}
const void QLIEVarientPool::_SortVarientByHash_Reversed()
{
	sort(_Varients.rbegin(), _Varients.rend(), _CmpVarientByHash);
}

const bool QLIEVarientPool::_AddVarient(const QLIE::_QLIEVarient& _k_Varient)
{
	if (_Check_HashIsExist(_k_Varient._Hash))
		return false;
	_Varients.push_back(_k_Varient);
	_VarientHashMap[_k_Varient._Hash] = _k_Varient;
	return true;
}
const bool QLIEVarientPool::_AddVarient(const wstring& _k_Token, const wstring& _k_Value, const QLIE::_QLIEParameterTypes _k_Type)
{
	QLIE::_QLIEVarient _temp;
	_temp.Token = _k_Token;
	_temp.Value = _k_Value;
	_temp.Type = _k_Type;
	_temp._Hash = _AllocateNewHash();
	return _AddVarient(_temp);
}
const bool QLIEVarientPool::_AddVarient(const unsigned long& _k_Hash, const wstring& _k_Value, const QLIE::_QLIEParameterTypes _k_Type)
{
	if (_Check_HashIsExist(_k_Hash))
		return false;
	QLIE::_QLIEVarient _temp;
	_temp.Token = L"_Unspecified";
	_temp._Hash = _k_Hash;
	_temp.Value = _k_Value;
	_temp.Type = _k_Type;
	return _AddVarient(_temp);
}
const bool QLIEVarientPool::_DeleteVarient(const QLIE::_QLIEVarient& _k_Varient)
{
	if (!_Check_HashIsExist(_k_Varient._Hash))
		return false;
	_SetVarient(_k_Varient._Hash, _NULLVarient);
	_DeletedHashes.push_back(_k_Varient._Hash);
	_VarientHashMap[_k_Varient._Hash] = _NULLVarient;
	return false;
}
const bool QLIEVarientPool::_DeleteVarient(const wstring& _k_Token, const wstring& _k_Value)
{
	auto _temp_Hash = _GetHashByToken(_k_Token);
	if (!_Check_TokenValuePaired(_k_Token, _k_Value))
		return false;
	if (_Check_VarientIsDeleted(_temp_Hash))
		return false;
	auto& _temp = _GetVarient(_temp_Hash);
	return _DeleteVarient(_temp);
}
const bool QLIEVarientPool::_DeleteVarient(const unsigned long& _k_Hash)
{
	if (_Check_VarientIsDeleted(_k_Hash))
		return false;
	auto& _temp = _GetVarient(_k_Hash);
	return _DeleteVarient(_temp);
}
const bool QLIEVarientPool::_DeleteVarient(const unsigned long& _k_Hash, const wstring& _k_Value)
{
	if (!_Check_HashValuePaired(_k_Hash, _k_Value))
		return false;
	if (_Check_VarientIsDeleted(_k_Hash))
		return false;
	return _DeleteVarient(_k_Hash);
}
const bool QLIEVarientPool::_SetVarient(const QLIE::_QLIEVarient& _k_SourceVarient, const QLIE::_QLIEVarient& _k_DestVarient)
{
	_Refresh();
	if (!_Check_SourceDestPaired(_k_SourceVarient, _k_DestVarient))
		return false;
	auto _temp = _GetVarientPointer(_k_SourceVarient._Hash);
	_temp->Value = _k_DestVarient.Value;
	_Refresh();
	return true;
}
const bool QLIEVarientPool::_SetVarient(QLIE::_QLIEVarient* _k_SourceVarientPointer, const QLIE::_QLIEVarient& _k_DestVarient)
{
	_Refresh();
	if(!_Check_SourceDestPaired(_k_SourceVarientPointer, _k_DestVarient))
		return false;
	_k_SourceVarientPointer->Value = _k_DestVarient.Value;
	_Refresh();
	return true;
}
const bool QLIEVarientPool::_SetVarient(const unsigned long& _k_Hash, const wstring& _k_Token, wstring _k_Value)
{
	_Refresh();
	auto _temp = _GetVarientPointer(_k_Hash);
	if (!_Check_TokenValuePaired(_k_Token, _k_Value))
		return false;
	if (!_Check_HashValuePaired(_k_Hash, _k_Value))
		return false;
	_temp->Value = _k_Value;
	_Refresh();
	return true;
}
const bool QLIEVarientPool::_SetVarient(const unsigned long& _k_Hash, const wstring& _k_Value)
{
	_Refresh();
	auto _temp = _GetVarientPointer(_k_Hash);
	_temp->Value = _k_Value;
	_Refresh();
	return true;
}
const bool QLIEVarientPool::_SetVarient(const unsigned long& _k_Hash, const QLIE::_QLIEVarient& _k_DestVarient)
{
	_Refresh();
	auto _temp = _GetVarientPointer(_k_Hash);
	if (!_Check_SourceDestPaired(_temp, _k_DestVarient))
		return false;
	_temp->Value = _k_DestVarient.Value;
	_Refresh();
	return true;
}

const bool QLIEVarientPool::_Check_HashIsExist(const unsigned long& _k_Hash)
{
	_Refresh();
	if (find(_Registered_Hashes.begin(), _Registered_Hashes.end(), _k_Hash) == _Registered_Hashes.end())
		return false;
	else
		return true;
}
const bool QLIEVarientPool::_Check_HashIsDeleted(const unsigned long& _k_Hash)
{
	_Refresh();
	if (find(_DeletedHashes.begin(), _DeletedHashes.end(), _k_Hash) == _DeletedHashes.end())
		return false;
	else
		return true;
}
const bool QLIEVarientPool::_Check_VarientIsDeleted(const unsigned long& _k_Hash)
{
	return _Check_HashIsDeleted(_k_Hash);
}
const bool QLIEVarientPool::_Check_VarientIsDeleted(const wstring& _k_Token)
{
	auto _temp = _GetHashByToken(_k_Token);
	return _Check_VarientIsDeleted(_temp);
}
const bool QLIEVarientPool::_Check_VarientIsDeleted(const unsigned long& _k_Hash, const wstring& _k_Token)
{
	if (!_Check_TokenHashPaired(_k_Hash, _k_Token))
		return false;
	return _Check_VarientIsDeleted(_k_Hash);
}
const bool QLIEVarientPool::_Check_VarientIsDeleted(const unsigned long& _k_Hash, const wstring& _k_Token, const wstring& _k_Value)
{
	if (!_Check_HashValuePaired(_k_Hash, _k_Value))
		return false;
	if (!_Check_TokenHashPaired(_k_Hash, _k_Token))
		return false;
	if (!_Check_TokenValuePaired(_k_Token, _k_Value))
		return false;
	return _Check_VarientIsDeleted(_k_Hash);
}
const bool QLIEVarientPool::_Check_VarientIsDeleted(const QLIE::_QLIEVarient& _k_Varient)
{
	if (!_ValidateVarient(_k_Varient))
		return false;
	auto _temp = _k_Varient._Hash;
	return _Check_VarientIsDeleted(_temp);
}
const bool QLIEVarientPool::_Check_TokenHashPaired(const unsigned long& _k_Hash, const wstring& _k_Token)
{
	auto& _temp = _GetVarient(_k_Hash);
	if (_temp.Token != _k_Token)
		return false;
	return true;
}
const bool QLIEVarientPool::_Check_TokenValuePaired(const wstring& _k_Token, const wstring& _k_Value)
{
	auto& _temp = _GetVarient(_k_Token);
	if (_temp.Value != _k_Value)
		return false;
	return true;
}
const bool QLIEVarientPool::_Check_HashValuePaired(const unsigned long& _k_Hash, const wstring& _k_Value)
{
	auto& _temp = _GetVarient(_k_Hash);
	if (_temp.Value != _k_Value)
		return false;
	return true;
}
const bool QLIEVarientPool::_Check_SourceDestPaired(const QLIE::_QLIEVarient& _k_SourceVarient, const QLIE::_QLIEVarient& _k_DestVarient)
{
	if (_k_SourceVarient.Token == _k_DestVarient.Token &&
		_k_SourceVarient.Type == _k_DestVarient.Type &&
		_k_SourceVarient._Hash == _k_DestVarient._Hash &&
		_k_SourceVarient.Value == _k_DestVarient.Value)
		return true;
	return false;
}
const bool QLIEVarientPool::_Check_SourceDestPaired(const QLIE::_QLIEVarient* _k_SourceVarientPointer, const QLIE::_QLIEVarient& _k_DestVarient)
{
	return _Check_SourceDestPaired(*_k_SourceVarientPointer, _k_DestVarient);
}
const bool QLIEVarientPool::_Check_SourceDestPaired(const QLIE::_QLIEVarient* _k_SourceVarientPointer, const QLIE::_QLIEVarient* _k_DestVarientPointer)
{
	return _Check_SourceDestPaired(*_k_SourceVarientPointer, *_k_DestVarientPointer);
}
const bool QLIEVarientPool::_Check_SourceDestPaired(const QLIE::_QLIEVarient& _k_SourceVarient, const QLIE::_QLIEVarient* _k_DestVarientPointer)
{
	return _Check_SourceDestPaired(_k_SourceVarient, *_k_DestVarientPointer);
}
const bool QLIEVarientPool::_ValidateVarient(const QLIE::_QLIEVarient& _k_SourceVarient)
{
	auto& _temp = _GetVarient(_k_SourceVarient._Hash);
	return _Check_SourceDestPaired(_temp, _k_SourceVarient);
}
const bool QLIEVarientPool::_ValidateVarient(const QLIE::_QLIEVarient* _k_SourceVarientPointer)
{
	auto& _temp = _GetVarient(_k_SourceVarientPointer->_Hash);
	return _Check_SourceDestPaired(_temp, *_k_SourceVarientPointer);
}

const unsigned long QLIEVarientPool::_GetVarientAmount()
{
	_Refresh();
	return _RegisteredVarientAmount - _DeletedVarientAmount;
}
const unsigned long QLIEVarientPool::_GetRegisteredHashAmount()
{
	return _Registered_Hashes.size();
}
const unsigned long QLIEVarientPool::_AllocateNewHash()
{
	_Refresh();
	auto _NewHash = _GetRegisteredHashAmount();
	_NewHash += 1;
	_Registered_Hashes.push_back(_NewHash);
	_VarientHashMap[_NewHash] = _NULLVarient;
	auto _temp_Var = _NULLVarient;
	_temp_Var._Hash = _NewHash;
	_Varients.push_back(_temp_Var);
	_Refresh();
	return _NewHash;
}

QLIE::_QLIEVarient QLIEVarientPool::_GetVarient(const unsigned long& _k_Hash)
{
	_Refresh();
	if (!_Check_HashIsExist(_k_Hash))
		return _NULLVarient;
	return _VarientHashMap[_k_Hash];
}
QLIE::_QLIEVarient QLIEVarientPool::_GetVarient(const wstring& _k_Token)
{
	_Refresh();
	auto _temp = _GetHashByToken(_k_Token);
	return _GetVarient(_temp);
}
QLIE::_QLIEVarient QLIEVarientPool::_GetVarient(const wstring& _k_Token, const unsigned long& _k_Hash)
{
	_Refresh();
	if (!_Check_TokenHashPaired(_k_Hash, _k_Token))
		return _NULLVarient;
	auto _temp = _GetHashByToken(_k_Token);
	return _GetVarient(_temp);
}
QLIE::_QLIEVarient QLIEVarientPool::_GetVarient(const QLIE::_QLIEVarient* _k_SourceVarientPointer)
{
	_Refresh();
	if (!_ValidateVarient(_k_SourceVarientPointer))
		return _NULLVarient;
	return *_k_SourceVarientPointer;
}
QLIE::_QLIEVarient* QLIEVarientPool::_GetVarientPointer(const unsigned long& _k_Hash)
{
	_Refresh();
	return &(_GetVarient(_k_Hash));
}
QLIE::_QLIEVarient* QLIEVarientPool::_GetVarientPointer(const std::wstring& _k_Token)
{
	_Refresh();
	auto _temp = _GetHashByToken(_k_Token);
	return _GetVarientPointer(_temp);
}
QLIE::_QLIEVarient* QLIEVarientPool::_GetVarientPointer(const std::wstring& _k_Token, const unsigned long& _k_Hash)
{
	_Refresh();
	if (!_Check_TokenHashPaired(_k_Hash, _k_Token))
		return &_NULLVarient;
	return &(_GetVarient(_k_Token, _k_Hash));
}

const unsigned long QLIEVarientPool::_GetHashByToken(const std::wstring& _k_Token)
{
	_Refresh();
	_SortVarientByHash_Reversed();
	auto _pos = find(_Varients.begin(),_Varients.end(),)
}