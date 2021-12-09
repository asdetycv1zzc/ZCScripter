#include <iostream>
#include <string>
#include <algorithm>
#include <Assemble.h>
#include <Converter.h>
#include <Script.h>
#include <types.h>
using namespace std;

bool QLIEVarientPool::_SortVarientByHash(QLIE::_QLIEVarient a, QLIE::_QLIEVarient b)
{
    return a._Hash < b._Hash;
}
void QLIEVarientPool::_SortVarient()
{
    sort(_Varients.begin(), _Varients.end(), _SortVarientByHash);
}
bool QLIEVarientPool::_AddVarient(QLIE::_QLIEVarient _k_Varient)
{
    if (_HashIsExist(_k_Varient._Hash))
        return false;
    _Varients.push_back(_k_Varient);
    return true;
}
bool QLIEVarientPool::_AddVarient(std::wstring _k_Token, std::wstring _k_Value, QLIE::_QLIEParameterTypes _k_Type = QLIE::_QLIEParameterTypes::_UNDEFINED__QLIEParameterTypes)
{
    QLIE::_QLIEVarient _temp;
    _temp.Token = _k_Token;
    _temp.Value = _k_Value;
    _temp.Type = _k_Type;
    _temp._Hash = _AllocateNewHash();
    _Varients.push_back(_temp);
    return true;
}
bool QLIEVarientPool::_AddVarient(unsigned long _k_Hash, std::wstring _k_Value, QLIE::_QLIEParameterTypes _k_Type = QLIE::_QLIEParameterTypes::_UNDEFINED__QLIEParameterTypes)
{
}
bool QLIEVarientPool::_DeleteVarient(QLIE::_QLIEVarient _k_Varient)
{
}
bool QLIEVarientPool::_DeleteVarient(std::wstring _k_Token, std::wstring _k_Value)
{
}
bool QLIEVarientPool::_DeleteVarient(unsigned long _k_Hash)
{
}
bool QLIEVarientPool::_DeleteVarient(unsigned long _k_Hash, std::wstring _k_Value)
{
}