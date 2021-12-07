#include <iostream>
#include <string>
#include <Assemble.h>
using namespace std;

QLIE::_QLIEParameterTypes QLIEHelper::_GetParameterType(const _QLIEScript _k_Script)
{
    auto _temp = _k_Script;
    QLIE::_QLIEParameterTypes _result = QLIE::_QLIEParameterTypes::_UNDEFINED__QLIEParameterTypes;
    if (_temp.find(L"\"") != wstring::npos && _temp.find_first_of(L"\"") != _temp.find_last_of(L"\""))
        _result = QLIE::_QLIEParameterTypes::_STRING;
    else
        _result = QLIE::_QLIEParameterTypes::_INT;
    return _result;
}
QLIE::_QLIEParameterTypes QLIEHelper::GetParameterType(const _QLIEScript k_Script)
{
    return _GetParameterType(k_Script);
}

QLIE::_QLIEParameters QLIEHelper::_GetParameters(const _QLIEScript _k_Script)
{
    QLIE::_QLIEParameters _result;
    _QLIEScript _temp(_k_Script);
    unsigned long beginPos, endPos = 0;
    while (_temp.substr(beginPos, _temp.size()).find(L",") != wstring::npos)
    {
        endPos = _temp.substr(beginPos, _temp.size()).find(L",");
        auto size = endPos - 1;
        QLIE::_QLIEParameter_NormalForm _t;
        _t.Parameter = _temp.substr(beginPos, size);
        _t.ParameterType = GetParameterType(_t.Parameter);
        _result.Parameters.push_back(_t);
        beginPos = endPos + 1;
    }
    QLIE::_QLIEParameter_NormalForm _t;
    _t.Parameter = _temp.substr(beginPos);
    _t.ParameterType = GetParameterType(_t.Parameter);
    _result.Parameters.push_back(_t);
    return _result;
}
QLIE::_QLIEParameters QLIEHelper::GetParameters(const _QLIEScript k_Script)
{
    return _GetParameters(k_Script);
}