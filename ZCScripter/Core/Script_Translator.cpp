#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<global.h>
using namespace std;

const bool _cmpByFileNum(const QLIE::_QLIEParameter_NormalForm& _a, const QLIE::_QLIEParameter_NormalForm& _b)
{
	auto _a_num = _a.Parameter.substr(_a.Parameter.find_first_of(L"file") + 1, 1)[0] - L'0';
	auto _b_num = _b.Parameter.substr(_b.Parameter.find_first_of(L"file") + 1, 1)[0] - L'0';
	return _a_num < _b_num;
}

const TranslatedScripts Script_Translator::_s_From_QLIECharacter_To_KRKRCharacter(const CharacterScript& _k_source)
{
	wstring _krkr_speaker_script, _krkr_text;
	if (_k_source.Script[0] == L'％' && _k_source.Script[_k_source.Script.size() - 1] == L'％')
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
const TranslatedScripts Script_Translator::s_From_QLIECharacter_To_KRKRCharacter(const CharacterScript& k_source)
{
	return _s_From_QLIECharacter_To_KRKRCharacter(k_source);
}

const TranslatedScripts Script_Translator::_s_From_QLIESystem_To_KRKRSystem(const SystemScript& _k_source)
{
	wstring _krkr_script;
	switch (_k_source.ScriptType)
	{
	case SystemScriptTypes::SetBackground:
	{
		//Get filename
		wstring _filename, _bgSwitchMode,_layer;
		if (_k_source._command.find_first_of(L"^bg") != wstring::npos)
		{
			auto beginPos = _k_source._command.find_first_of(L"^bg") + 3;
			auto endPos = _k_source._command.find_first_of(L':');
			auto _size = endPos - beginPos;
			_layer = _k_source._command.substr(beginPos, _size);
		}
		for (size_t i = 0; i < _k_source._parameters.ParameterCount; i++)
		{
			if (_k_source._parameters.Parameters[i].Parameter.substr(0,5) == L"file:")
			{
				if (_k_source._parameters.Parameters[i].Parameter.find(L"/") != wstring::npos)
					_filename = wstring(_k_source._parameters.Parameters[i].Parameter.substr(_k_source._parameters.Parameters[i].Parameter.find_last_of(L"/") + 1));
				else
					_filename = wstring(_k_source._parameters.Parameters[i].Parameter.substr(_k_source._parameters.Parameters[i].Parameter.find_last_of(L":") + 1));
				if (_filename.find(L"none") != wstring::npos)
					_filename = wstring(DEFAULT_BACKGROUND);
			}
			
		}
		for (size_t i = 0; i < _k_source._parameters.ParameterCount; i++)
		{
			if (_k_source._parameters.Parameters[i].Parameter[0] == L'$')
			{
				_bgSwitchMode = wstring(_k_source._parameters.Parameters[i].Parameter.substr(1));
				if (_bgSwitchMode != L"reset_bg")
					_bgSwitchMode = DEFAULT_BACKGROUND_SWITCH_METHOD;
				else
					_bgSwitchMode = L"";
			}
			if (_k_source._parameters.Parameters[i].Parameter.find(L"show:false") != wstring::npos)
			{
				_filename = wstring(DEFAULT_BACKGROUND);
				g_BackgroundBuffer[_layer].assign(g_BackgroundFiles[g_BackgroundFiles.size() - 1].second);
			}
			if (_k_source._parameters.Parameters[i].Parameter.find(L"show:true") != wstring::npos)
			{
				if(_filename.empty())
					_filename = g_BackgroundBuffer[_layer];
			}
			if (_k_source._parameters.Parameters[i].Parameter.substr(0, 3) == L"rep")
			{
				_filename = wstring(_k_source._parameters.Parameters[i].Parameter.substr(_k_source._parameters.Parameters[i].Parameter.find_last_of(L"/") + 1));
			}
		}
		_krkr_script = L"@bg method=\"" + _bgSwitchMode + L"\" storage=\"" + _filename + L"\"";
		g_BackgroundScripts.push_back(_k_source.Script);
		if(!_filename.empty())
			g_BackgroundFiles.push_back(make_pair(_layer,_filename));
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
		wstring _alpha,_layer;
		bool _RequireRebuild = false;
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
		if (_tempPara.ParameterCount != 0)
		{
			sort(_tempPara.Parameters.begin(), _tempPara.Parameters.end(), _cmpByFileNum);
			auto _testNum = _tempPara.Parameters[_tempPara.ParameterCount - 1].Parameter[_tempPara.Parameters[_tempPara.ParameterCount - 1].Parameter.find_first_of(L':') - 1] - L'0' + 1;
			if (_tempPara.ParameterCount != _testNum)
			{
				_RequireRebuild = true;
				vector<pair<int,wstring> > _modify_list(_tempPara.ParameterCount);
				for (size_t i = 0; i < _tempPara.ParameterCount; i++)
				{
					//找到需要拆分修改的编号
					auto _hash = _tempPara.Parameters[i].Parameter[_tempPara.Parameters[i].Parameter.find_first_of(L':') - 1] - L'0';
					_modify_list[i].first = _hash;
					_modify_list[i].second = _tempPara.Parameters[i].Parameter.substr(_tempPara.Parameters[i].Parameter.find_first_of(L':') + 1);
					if (_modify_list[i].second.find(L"_") != wstring::npos)
						_modify_list[i].second = _modify_list[i].second.substr(0, _modify_list[i].second.size() - 1);
				}
				auto _LastUsedCharacter = g_AppearedCharacterModelNames[g_AppearedCharacterModelNames.size() - 1];
				auto _temp_splitedLastUsedCharacter = splitwstr(_LastUsedCharacter, DEFAULT_CHARACTER_SEPERATE_CHAR);
				vector<wstring> _splitedLastUsedCharacter(_temp_splitedLastUsedCharacter.size(),L"");
				for (size_t i = 0; i < _temp_splitedLastUsedCharacter.size(); i++)
					_splitedLastUsedCharacter[i] = _temp_splitedLastUsedCharacter[i];
				for (size_t i = 0; i < _tempPara.ParameterCount; i++)
				{
					while (_splitedLastUsedCharacter.size() <= _modify_list[i].first)
						_splitedLastUsedCharacter.resize(_modify_list[i].first + 1);
					_splitedLastUsedCharacter[_modify_list[i].first] = _modify_list[i].second;
				}
				for (auto i = _splitedLastUsedCharacter.begin();i != _splitedLastUsedCharacter.end();)
				{
					if (*i == L"")
						i = _splitedLastUsedCharacter.erase(i);
					else
						i++;
				}

				//重建文件名
				for (size_t i = 0; i < _splitedLastUsedCharacter.size(); i++)
					_allFilename.append(_splitedLastUsedCharacter[i] + L"_");
				_allFilename = _allFilename.substr(0, _allFilename.size() - 1);
				if (_allFilename.find(L"__") != wstring::npos)
				{
					_allFilename.substr();
				}
				
			}
		}
		for (size_t i = 0; i < _tempPara.ParameterCount && !_RequireRebuild; i++)
		{
			_tempFilename = _tempPara.Parameters[i].Parameter.substr(_tempPara.Parameters[i].Parameter.find_first_of(L':') + 1);
			_allFilename.append(_tempFilename);
		}
		//获取角色编号并转为相应图层
		if (_k_source._command.find_first_of(L"chara") != wstring::npos)
		{
			auto beginPos = _k_source._command.find_first_of(L"chara") + 5;
			auto endPos = _k_source._command.find_first_of(L':');
			auto _size = endPos - beginPos;
			_layer = _k_source._command.substr(beginPos, _size);
		}
		else
			_layer = wstring(DEFAULT_CHARACTER_LAYER);
		if (_allFilename.find(L"none") == wstring::npos)
		{
			_krkr_script.append(L"@fg ");
			if (!_NoAlpha)
				_krkr_script.append(L"opcacity=\"" + _alpha + L"\" ");
			_krkr_script.append(L"layer=\"" + _layer + L"\" ");
			_krkr_script.append(L"method=\"" + wstring(DEFAULT_CHARACTER_SWITCH_METHOD) + L"\" ");
			_krkr_script.append(L"storage=\"" + _allFilename + L"\"");
			
		}
		else
		{
			_krkr_script.append(L"@clfg ");
			_krkr_script.append(L"layer=\"" + _layer + L"\" ");
			_krkr_script.append(L"method=\"" + wstring(DEFAULT_CHARACTER_SWITCH_METHOD) + L"\" ");
			_krkr_script.append(L"pos=\"" + wstring(DEFAULT_CHARACTER_POSITION) + L"\" ");
		}
		if (_allFilename.empty())
		{
			_krkr_script.clear(); //连文件都没有就更不用说别的了 直接全删掉
		}
		else
			g_AppearedCharacterModelNames.push_back(_allFilename);
		break;
	}
	case SystemScriptTypes::SetPostScript: [[fallthrough]];
	case SystemScriptTypes::SetEntryName: [[fallthrough]];
	case SystemScriptTypes::SetIncludeFile:break;
	}
	vector<wstring> _result;
	_result.push_back(_krkr_script);
	return _result;
}
const TranslatedScripts Script_Translator::s_From_QLIESystem_To_KRKRSystem(const SystemScript& k_source)
{
	return _s_From_QLIESystem_To_KRKRSystem(k_source);
}

const TranslatedScripts Script_Translator::_s_TranslateAll(const SortedScripts& _k_source)
{
	TranslatedScripts _result;
	for (size_t i = 0; i < _k_source.BlockAmount; i++)
	{
		auto _type = _k_source._Typetable.at(i).second;
		switch (_type)
		{
		case 0:
		{
			auto _test_p = _k_source._SystemScripts.Blocks[_k_source._Typetable.at(i).first];
			auto _temp = Script_Translator::s_From_QLIESystem_To_KRKRSystem(_test_p);
			_result.insert(_result.end(), _temp.begin(), _temp.end());
			break;
		}
		case 1:
		{
			auto _test_p = _k_source._CharacterScripts.Blocks[_k_source._Typetable.at(i).first];
			auto _temp = Script_Translator::s_From_QLIECharacter_To_KRKRCharacter(_test_p);
			_result.insert(_result.end(), _temp.begin(), _temp.end());
			break;
		}
		}
	}
	return _result;
}
const TranslatedScripts Script_Translator::s_TranslateAll(const SortedScripts& k_source)
{
	return _s_TranslateAll(k_source);
}