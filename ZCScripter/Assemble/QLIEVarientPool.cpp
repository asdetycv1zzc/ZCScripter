#include <iostream>
#include <string>
#include <algorithm>
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

const bool QLIEVarientPool::_AddVarient(const QLIE::_QLIEVarient& _k_Varient)
{
	if (_Check_HashIsExist(_k_Varient._Hash))
		return false;
	_Varients.push_back(_k_Varient);
	return true;
}
const bool QLIEVarientPool::_AddVarient(const std::wstring& _k_Token, const std::wstring& _k_Value, const QLIE::_QLIEParameterTypes _k_Type)
{
	QLIE::_QLIEVarient _temp;
	_temp.Token = _k_Token;
	_temp.Value = _k_Value;
	_temp.Type = _k_Type;
	_temp._Hash = _AllocateNewHash();
	_Varients.push_back(_temp);
	return true;
}
const bool QLIEVarientPool::_AddVarient(const unsigned long& _k_Hash, const std::wstring& _k_Value, const QLIE::_QLIEParameterTypes _k_Type)
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
	return false;
}
const bool QLIEVarientPool::_DeleteVarient(const std::wstring& _k_Token, const std::wstring& _k_Value)
{
	auto _temp_Hash = _GetHashByToken(_k_Token);
	if (!_Check_TokenValuePaired(_k_Token, _k_Value))
		return false;
	if (_Check_VarientIsDeleted(_temp_Hash))
		return false;
	_DeletedHashes.push_back(_temp_Hash);
	return true;
}
const bool QLIEVarientPool::_DeleteVarient(const unsigned long& _k_Hash)
{
	if (_Check_VarientIsDeleted(_k_Hash))
		return false;
	_DeletedHashes.push_back(_k_Hash);
	return true;
}
const bool QLIEVarientPool::_DeleteVarient(const unsigned long& _k_Hash, const std::wstring& _k_Value)
{
	if (!_Check_HashValuePaired(_k_Hash, _k_Value))
		return false;
	if (_Check_VarientIsDeleted(_k_Hash))
		return false;
	_DeletedHashes.push_back(_k_Hash);
	return true;
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
const bool QLIEVarientPool::_SetVarient(const unsigned long& _k_Hash, const std::wstring& _k_Token, std::wstring _k_Value)
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
const bool QLIEVarientPool::_SetVarient(const unsigned long& _k_Hash, std::wstring _k_Value)
{

}