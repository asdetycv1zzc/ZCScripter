#include <iostream>
#include <string>
#include <Converter.h>
#include <Assemble.h>
using namespace std;

const QLIE::_QLIEParameterTypes QLIEHelper::_GetParameterType(const _QLIEScript& _k_Script)
{
    auto _temp = _k_Script;
    QLIE::_QLIEParameterTypes _result = QLIE::_QLIEParameterTypes::_UNDEFINED__QLIEParameterTypes;
    if (_temp.find(L"\"") != wstring::npos && _temp.find_first_of(L"\"") != _temp.find_last_of(L"\""))
        _result = QLIE::_QLIEParameterTypes::_STRING;
    else if (_temp.find(L"true") != wstring::npos || _temp.find(L"false") != wstring::npos)
        _result = QLIE::_QLIEParameterTypes::_BOOLEAN;
    else
        _result = QLIE::_QLIEParameterTypes::_INT;
    return _result;
}
const QLIE::_QLIEParameterTypes QLIEHelper::GetParameterType(const _QLIEScript& k_Script)
{
    return _GetParameterType(k_Script);
}

const wstring QLIEHelper::_GetCommand(const _QLIEScript& _k_Script)
{
    auto _result = wstring(_k_Script);
    return _result.substr(0, _result.find_first_of(L','));
}
const wstring QLIEHelper::GetCommand(const _QLIEScript& k_Script)
{
    return _GetCommand(k_Script);
}

const QLIE::_QLIEParameters QLIEHelper::_GetParameters(const _QLIEScript& _k_Script)
{
    QLIE::_QLIEParameters _result;
    _QLIEScript _temp(_k_Script);
    unsigned long beginPos = _temp.substr(0).find(L",") + 1, endPos = _temp.substr(beginPos).find(L",") + 1;
    while (_temp.substr(beginPos, _temp.size()).find(L",") != wstring::npos)
    {
        //auto _test = _temp.substr(beginPos, _temp.size());
        //auto _test1 = _test.find(L',');
        endPos = _temp.substr(beginPos,_temp.size()).find_first_of(L',') + 1;
        auto size = endPos - 1;
        QLIE::_QLIEParameter_NormalForm _t;
        _t.Parameter = _temp.substr(beginPos, size);
        _t.ParameterType = GetParameterType(_t.Parameter);
        _result.Parameters.push_back(_t);
        beginPos += endPos;
    }
    if (_temp.find(L',') == wstring::npos)
    {
        _result.ParameterCount = 0;
        QLIE::_QLIEParameter_NormalForm _t;
        _t.Parameter = L"";
        _t.ParameterType = QLIE::_QLIEParameterTypes::_UNDEFINED__QLIEParameterTypes;
        _result.Parameters.push_back(_t);
        return _result;
    }
    QLIE::_QLIEParameter_NormalForm _t;
    _t.Parameter = _temp.substr(beginPos);
    _t.ParameterType = GetParameterType(_t.Parameter);
    _result.Parameters.push_back(_t);
    _result.ParameterCount = _result.Parameters.size();
    return _result;
}
const QLIE::_QLIEParameters QLIEHelper::GetParameters(const _QLIEScript& k_Script)
{
    return _GetParameters(k_Script);
}
