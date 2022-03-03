#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<Script.h>
#include<Translator.h>
#include<wstring_extend.h>
#include<global.h>
using namespace std;

const bool _cmpByFileNum(const QLIE::_QLIEParameter_NormalForm& _a, const QLIE::_QLIEParameter_NormalForm& _b)
{
	auto _a_num = _a.Parameter.substr(_a.Parameter.find_first_of(L"file") + 1, 1)[0] - L'0';
	auto _b_num = _b.Parameter.substr(_b.Parameter.find_first_of(L"file") + 1, 1)[0] - L'0';
	return _a_num < _b_num;
}
const vector<wstring> Script_Translator::_s_From_QLIECharacter_To_KRKRCharacter(const CharacterScript& _k_source)
{
	wstring _krkr_speaker_script, _krkr_text;
	if (_k_source.Script[0] == L'ге' && _k_source.Script[_k_source.Script.size() - 1] == L'ге')
	{
		//@se storage="kaizan-system02.wav" loop="1"
		if (_k_source.Speaker == L"") _krkr_speaker_script = L"";
		auto _temp_soundname = _k_source.Script.substr(1, _k_source.Script.size() - 2);
		_krkr_text = L"@se storage=\"" + _temp_soundname + L".ogg\"";
	}
	else
	{
		if (_k_source.Speaker == L"") 
			_krkr_speaker_script = L"";
		_krkr_speaker_script = L"@npc id=\"" + _k_source.Speaker + L"\"";
		if (_k_source.Script != L"")
			_krkr_text = wstring(_k_source.Script + L"[w]");
		else
			_krkr_text = L"";
	}
	vector<wstring> _result(2);
	_result[0] = _krkr_speaker_script;
	_result[1] = _krkr_text;
	return _result;

}
const vector<wstring> Script_Translator::s_From_QLIECharacter_To_KRKRCharacter(const CharacterScript& k_source)
{
	return _s_From_QLIECharacter_To_KRKRCharacter(k_source);
}

const vector<wstring> Script_Translator::_s_From_QLIESystem_To_KRKRSystem(const SystemScript& _k_source)
{
	wstring _krkr_script;
	switch (_k_source.ScriptType)
	{
	case SystemScriptTypes::SetBackground:
	{
		//Get filename
		wstring _filename, _bgSwitchMode;
		for (size_t i = 0; i < _k_source._parameters.ParameterCount; i++)
		{
			if (_k_source._parameters.Parameters[i].Parameter.substr(0,5) == L"file:")
			{
				_filename = wstring(_k_source._parameters.Parameters[i].Parameter.substr(_k_source._parameters.Parameters[i].Parameter.find_last_of(L"/") + 1));
				if (_filename == L"none") 
					_filename = DEFAULT_BACKGROUND;
			}
			if (_k_source._parameters.Parameters[i].Parameter[0] == L'$')
			{
				_bgSwitchMode = wstring(_k_source._parameters.Parameters[i].Parameter.substr(1));
				if (_bgSwitchMode != L"reset_bg") 
					_bgSwitchMode = DEFAULT_BACKGROUND_SWITCH_METHOD;
				else
					_bgSwitchMode = L"";
			}
			
		}
		_krkr_script = L"@bg method=\"" + _bgSwitchMode + L"\" storage=\"" + _filename + L"\"";
		break;
	}
	case SystemScriptTypes::SetSound:
	{
		for (size_t i = 0; i < _k_source._parameters.ParameterCount; i++)
		{

		}
		break;
	}
	case SystemScriptTypes::SetCharacterModel:
	{
		wstring _allFilename = L"", _tempFilename;
		wstring _alpha;
		bool _NoAlpha = true;
		QLIE::_QLIEParameters _tempPara;
		for (size_t i = 0; i < _k_source._parameters.ParameterCount; i++)
		{
			if (wstrcmp(_k_source._parameters.Parameters[i].Parameter.substr(0, 4).c_str(), L"file"))
			{
				_tempPara.Parameters.push_back(_k_source._parameters.Parameters[i]);
			}
			if (wstrcmp(_k_source._parameters.Parameters[i].Parameter.substr(0, 5).c_str(), L"alpha") && _NoAlpha)
			{
				_NoAlpha = false;
				_alpha = _k_source._parameters.Parameters[i].Parameter.substr(_k_source._parameters.Parameters[i].Parameter.find_first_of(L':') + 1);
			}
		}
		_tempPara.ParameterCount = _tempPara.Parameters.size();
		sort(_tempPara.Parameters.begin(), _tempPara.Parameters.end(), _cmpByFileNum);
		auto _testNum = _tempPara.Parameters[_tempPara.ParameterCount - 1].Parameter[_tempPara.Parameters[_tempPara.ParameterCount - 1].Parameter.find_first_of(L':') - 1] - L'0' + 1;
		if (_tempPara.ParameterCount != _testNum)
		{
			auto _LastUsedCharacter = g_AppearedCharacterModelNames[g_AppearedCharacterModelNames.size() - 1];
			auto _temp = splitwstr(_LastUsedCharacter, DEFAULT_CHARACTER_SEPERATE_CHAR);
			throw exception();
		}
		
		for (size_t i = 0; i < _tempPara.ParameterCount; i++)
		{
			_tempFilename = _tempPara.Parameters[i].Parameter.substr(_tempPara.Parameters[i].Parameter.find_first_of(L':') + 1);
			_allFilename.append(_tempFilename);
		}
		_krkr_script.append(L"@fg ");
		if (!_NoAlpha)
			_krkr_script.append(L"opcacity=\"" + _alpha + L"\" ");
		_krkr_script.append(L"layer=\"" + wstring(DEFAULT_CHARACTER_LAYER) + L"\" ");
		_krkr_script.append(L"method=\"" + wstring(DEFAULT_CHARACTER_SWITCH_METHOD) + L"\" ");
		_krkr_script.append(L"storage=\"" + _allFilename + L"\"");
		break;
	}
	}
	vector<wstring> _result;
	if (_krkr_script == L"")
		_krkr_script = L"NULL";
	_result.push_back(_krkr_script);
	return _result;
}
const vector<wstring> Script_Translator::s_From_QLIESystem_To_KRKRSystem(const SystemScript& k_source)
{
	return _s_From_QLIESystem_To_KRKRSystem(k_source);
}