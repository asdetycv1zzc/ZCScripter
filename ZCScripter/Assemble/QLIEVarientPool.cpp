#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/*
bool QLIEVarientPool::_CmpVarientByHash(QLIE::_QLIEVarient a, QLIE::_QLIEVarient b)
{
    return a._Hash < b._Hash;
}
void QLIEVarientPool::_SortVarientByHash()
{
    sort(_Varients.begin(), _Varients.end(), _CmpVarientByHash);
}
bool QLIEVarientPool::_AddVarient(QLIE::_QLIEVarient _k_Varient)
{
    if (_Check_HashIsExist(_k_Varient._Hash))
        return false;
    _Varients.push_back(_k_Varient);
    return true;
}
bool QLIEVarientPool::_AddVarient(std::wstring _k_Token, std::wstring _k_Value, QLIE::_QLIEParameterTypes _k_Type)
{
    QLIE::_QLIEVarient _temp;
    _temp.Token = _k_Token;
    _temp.Value = _k_Value;
    _temp.Type = _k_Type;
    _temp._Hash = _AllocateNewHash();
    _Varients.push_back(_temp);
    return true;
}
bool QLIEVarientPool::_AddVarient(unsigned long _k_Hash, std::wstring _k_Value, QLIE::_QLIEParameterTypes _k_Type)
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
bool QLIEVarientPool::_DeleteVarient(QLIE::_QLIEVarient _k_Varient)
{
    if (!_Check_HashIsExist(_k_Varient._Hash))
        return false;
    _SetVarient(_k_Varient._Hash, _NULLVarient);
    _DeletedHashes.push_back(_k_Varient._Hash);
    return false;
}
bool QLIEVarientPool::_DeleteVarient(std::wstring _k_Token, std::wstring _k_Value)
{
    auto _temp_Hash = _GetHashByToken(_k_Token);
    if(!_Check_TokenValuePaired(_GetTokenByValue(_k_Token),_k_Value))
        return false;
    if (_Check_VarientIsDeleted(_temp_Hash))
        return false;
    _DeletedHashes.push_back(_temp_Hash);
    return true;
}
bool QLIEVarientPool::_DeleteVarient(unsigned long _k_Hash)
{
    if (_Check_VarientIsDeleted(_k_Hash))
        return false;
    _DeletedHashes.push_back(_k_Hash);
    return true;
}
bool QLIEVarientPool::_DeleteVarient(unsigned long _k_Hash, std::wstring _k_Value)
{
    return false;
}
*/