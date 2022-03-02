#include<iostream>
#include<string>
#include<vector>
#include<Script.h>
#include<Translator.h>
using namespace std;

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
		_krkr_script = L"@bg method=\"" + wstring(DEFAULT_BACKGROUND_SWITCH_METHOD) + L"\" storage=\"" + _filename + L"\"";
		break;
	}
	case SystemScriptTypes::SetSound:
	{
		for (size_t i = 0; i < _k_source._parameters.ParameterCount; i++)
		{

		}
	}
	}
	vector<wstring> _result(1);
	_result[0] = _krkr_script;
	return _result;
}
const vector<wstring> Script_Translator::s_From_QLIESystem_To_KRKRSystem(const SystemScript& k_source)
{
	return _s_From_QLIESystem_To_KRKRSystem(k_source);
}