#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<Script.h>
#include<Translator.h>
#include<global.h>
#include<wstring_extend.h>
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
		wstring _filename, _bgSwitchMode = wstring(DEFAULT_BACKGROUND_SWITCH_METHOD),_layer;
		vector<pair<wstring, wstring> > _paras(_k_source._parameters.ParameterCount);
		bool _visible = true;
		if (_k_source._command.find_first_of(L"^bg") != wstring::npos)
		{
			auto beginPos = _k_source._command.find_first_of(L"^bg") + 3;
			auto endPos = _k_source._command.find_first_of(L':');
			auto _size = endPos - beginPos;
			_layer = _k_source._command.substr(beginPos, _size);
		}
		for (size_t i = 0; i < _k_source._parameters.ParameterCount; i++)
		{
			auto _temp_para = _s_Extract_QLIESubParameter(_k_source._parameters.Parameters[i].Parameter, DEFAULT_QLIE_SUBPARAMETER_SPLIT);
			_paras[i] = _temp_para;
		}
		for (size_t i = 0; i < _paras.size(); i++)
		{
			if (_paras[i].first == L"file")
			{
				if (_paras[i].second.find(L"/") != wstring::npos)
					_filename = _paras[i].second.substr(_paras[i].second.find_last_of(L"/") + 1);
				else
					_filename = _paras[i].second.substr(_paras[i].second.find_last_of(L":") + 1);
				if (_filename.find(L"none") != wstring::npos)
				{
					_visible = false;
					//_filename = wstring(DEFAULT_BACKGROUND);
					_krkr_script.append(L"@image pages=\"" + wstring(DEFAULT_BACKGROUND_PAGE) + L"\" ");
					_krkr_script.append(L"mode=\"" + wstring(DEFAULT_BACKGROUND_COVER_MODE) + L"\" ");
					_krkr_script.append(L"layer=\"" + _layer + L"\" ");
					_krkr_script.append(L"storage=\"" + _filename + L"\"");
					_krkr_script.append(L"pos=\"" + wstring(DEFAULT_BACKGROUND_POSITION) + L"\" ");
					_krkr_script.append(L"visible=\"0\"");
				}
			}	
		}
		for (size_t i = 0; i < _paras.size(); i++)
		{
			if (_paras[i].first[0] == L'$')
			{
				_bgSwitchMode = _paras[i].second.substr(1);
				if (_bgSwitchMode != L"reset_bg")
					_bgSwitchMode = DEFAULT_BACKGROUND_SWITCH_METHOD;
				else
					_bgSwitchMode = L"";
			}
			if (_paras[i].first == L"show")
			{
				if (_paras[i].second == L"false")
				{
					_filename = wstring(DEFAULT_BACKGROUND);
					g_BackgroundBuffer[_layer].assign(g_BackgroundFiles[g_BackgroundFiles.size() - 1][_layer]);
				}
				if (_paras[i].second == L"true")
				{
					if (_filename.empty())
						_filename = g_BackgroundBuffer[_layer];
				}
				if (_paras[i].first.substr(0, 3) == L"rep")
				{
					_filename = _paras[i].second.substr(_paras[i].second.find_last_of(L"/") + 1);
				}
					
			}
		}
		if (_filename.empty())
			_filename = wstring(DEFAULT_BACKGROUND);
		if (_visible)
		{
			_krkr_script.append(L"@image pages=\"" + wstring(DEFAULT_BACKGROUND_PAGE) + L"\" ");
			_krkr_script.append(L"mode=\"" + wstring(DEFAULT_BACKGROUND_COVER_MODE) + L"\" ");
			_krkr_script.append(L"layer=\"" + _layer + L"\" ");
			_krkr_script.append(L"storage=\"" + _filename + L"\" ");
			_krkr_script.append(L"pos=\"" + wstring(DEFAULT_BACKGROUND_POSITION) + L"\" ");
			_krkr_script.append(L"visible=\"" + wstring(DEFAULT_BACKGROUND_VISIBILITY) + L"\" ");
		}
		g_BackgroundScripts.push_back(_k_source.Script);
		if (!_filename.empty())
		{
			map<wstring, wstring> _temp_map;
			_temp_map[_layer] = _filename;
			g_BackgroundFiles.push_back(_temp_map);
		}
		vector<wstring> _result;
		_result.push_back(_krkr_script);
		return _result;
	}
	case SystemScriptTypes::SetSound: [[fallthrough]];
	case SystemScriptTypes::SetMusic:
	{
		wstring _filename,_volume,_loop;
		vector<pair<wstring, wstring> > _paras(_k_source._parameters.ParameterCount);
		for (size_t i = 0; i < _k_source._parameters.ParameterCount; i++)
		{
			auto _temp_para = _s_Extract_QLIESubParameter(_k_source._parameters.Parameters[i].Parameter, DEFAULT_QLIE_SUBPARAMETER_SPLIT);
			_paras[i] = _temp_para;
		}
		for (size_t i = 0; i < _paras.size(); i++)
		{
			if (_paras[i].first == L"file")
				_filename = _paras[i].second;
			if (_paras[i].first == L"vol")
				_volume = _paras[i].second;
			if (_paras[i].first == L"loop")
				_loop = _paras[i].second;
		}
		if (_filename.empty())
			_filename = g_PlayedSounds[g_PlayedSounds.size() - 1];
		else
			g_PlayedSounds.push_back(_filename);
		_krkr_script.append(L"@bgm storage=\"" + _filename + L"\" ");
		if (!_loop.empty())
		{
			if (_loop == L"true")
				_krkr_script.append(L"loop=1 ");
			else
				_krkr_script.append(L"loop=0 ");
		}
		if (!_volume.empty())
			_krkr_script.append(L"vol=" + _volume);
		vector<wstring> _result;
		_result.push_back(_krkr_script);
		return _result;
	}
	case SystemScriptTypes::SetCharacterModel:
	{
		wstring _allFilename = L"", _tempFilename;
		wstring _alpha,_layer,_pos = wstring(DEFAULT_CHARACTER_POSITION);
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
		//获得角色位置
		for (size_t i = 0; i < _k_source._parameters.ParameterCount; i++)
		{
			if (_k_source._parameters.Parameters[i].Parameter.substr(0, 2) == L"x:")
			{
				auto _temp_pos = _k_source._parameters.Parameters[i].Parameter.substr(3);
				if (wstrcmp(L"$c_left", _temp_pos.c_str())) _pos = L"left";
				else if (wstrcmp(L"$c_right", _temp_pos.c_str())) _pos = L"right";
			}
		}
		if (_allFilename.find(L"none") == wstring::npos)
		{
			_krkr_script.append(L"@fg ");
			if (!_NoAlpha)
				_krkr_script.append(L"opcacity=\"" + _alpha + L"\" ");
			_krkr_script.append(L"layer=\"" + _layer + L"\" ");
			_krkr_script.append(L"method=\"" + wstring(DEFAULT_CHARACTER_SWITCH_METHOD) + L"\" ");
			_krkr_script.append(L"storage=\"" + _allFilename + L"\" ");
			_krkr_script.append(L"pos=\"" + _pos + L"\" ");
			
		}
		else
		{
			_krkr_script.append(L"@clfg ");
			_krkr_script.append(L"layer=\"" + _layer + L"\" ");
			_krkr_script.append(L"method=\"" + wstring(DEFAULT_CHARACTER_SWITCH_METHOD) + L"\" ");
		}
		if (_allFilename.empty())
		{
			_krkr_script.clear(); //连文件都没有就更不用说别的了 直接全删掉
		}
		else
			g_AppearedCharacterModelNames.push_back(_allFilename);
		break;
	}
	case SystemScriptTypes::SetPostScript: break;
	case SystemScriptTypes::SetEntryName:
	{
		vector<wstring> _result;

		auto _EntryName = _s_From_QLIELabel_To_KRKRLabel(_k_source.Script);
		wstring _ChapterName;
		_ChapterName = _k_source._Filename.substr(0, _k_source._Filename.find_last_of(L".s") - 1);

		_krkr_script.append(L"*" + _EntryName);
		_krkr_script.append(L"|" + _ChapterName); //Fixed Issue
		break;
	}
	case SystemScriptTypes::SetIncludeFile:break;
	case SystemScriptTypes::SetSelect:
	{
		if (!g_LastSelectTextBuffer.second); //throw exception();
		else g_LastSelectTextBuffer.first.clear();
		g_LastSelectTextBuffer.first.resize(_k_source._parameters.ParameterCount);
		for (size_t i = 0; i < _k_source._parameters.ParameterCount; i++)
		{
			g_LastSelectTextBuffer.first[i] = _k_source._parameters.Parameters[i].Parameter;
		}
		g_LastSelectTextBuffer.second = false;
		break;
	}
	case SystemScriptTypes::SetSelectLabel:
	{
		vector<wstring> _temp_Labels(_k_source._parameters.ParameterCount);
		vector<wstring> _result;
		if (g_LastSelectTextBuffer.second);//throw exception();
		for (size_t i = 0; i < _k_source._parameters.ParameterCount; i++)
		{
			auto _protect_ = _k_source._parameters.Parameters[i].Parameter;
			_temp_Labels[i] = _protect_;
			clearwstr(_temp_Labels[i],L'\"');
			_temp_Labels[i] = _s_From_QLIELabel_To_KRKRLabel(_temp_Labels[i]);
		}
		for (size_t i = 0; i < _k_source._parameters.ParameterCount; i++)
		{
			_krkr_script.append(L"@selbutton target=\"*" + _temp_Labels[i] + L"\" ");
			_krkr_script.append(L"text=\"" + g_LastSelectTextBuffer.first[i] + L"\"");
			_result.push_back(_krkr_script);
			_krkr_script.clear();
		}
		g_LastSelectTextBuffer.second = false;
		return _result;
		break;
	}
	}
	
	vector<wstring> _result;
	_result.push_back(_krkr_script);
	return _result;
}
const TranslatedScripts Script_Translator::s_From_QLIESystem_To_KRKRSystem(const SystemScript& k_source)
{
	return _s_From_QLIESystem_To_KRKRSystem(k_source);
}

const wstring Script_Translator::_s_From_QLIELabel_To_KRKRLabel(const wstring& _k_source)
{
	wstring _result = L"";
	if (_k_source.find(L"@@") == wstring::npos) return _result;
	_result = _k_source.substr(_k_source.find_first_of(L"@@") + 2);
	if (wstrcmp(_result.c_str(), L"MAIN")) _result = L"TOP";
	return _result;
}
const wstring Script_Translator::s_From_QLIELabel_To_KRKRLabel(const wstring& k_source)
{
	return _s_From_QLIELabel_To_KRKRLabel(k_source);
}

const pair<wstring,wstring> Script_Translator::_s_Extract_QLIESubParameter(const wstring& _k_source, const std::wstring& _k_split)
{
	pair<wstring, wstring> _result;
	auto _first = _k_source.substr(0, _k_source.find_first_of(_k_split));
	auto _second = _k_source.substr(_k_source.find_first_of(_k_split) + 1);
	_result.first = _first;
	_result.second = _second;
	return _result;
}
const wstring Script_Translator::_s_Extract_QLIESubParameter(const wstring& _k_source, const std::wstring& _k_name, const std::wstring& _k_split)
{
	wstring _result = _k_source;
	if (_k_source.find(_k_name) == wstring::npos)return _result;
	auto _beginPos = _k_source.find_first_of(_k_name) + _k_name.size() + _k_split.size();
	_result = _k_source.substr(_beginPos);
	return _result;
}

const pair<wstring, wstring> Script_Translator::s_Extract_QLIESubParameter(const wstring& k_source, const std::wstring& k_split)
{
	return _s_Extract_QLIESubParameter(k_source, k_split);
}
const wstring Script_Translator::s_Extract_QLIESubParameter(const wstring& k_source, const std::wstring& k_name, const std::wstring& k_split)
{
	return _s_Extract_QLIESubParameter(k_source, k_name, k_split);
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
	for (auto i = _result.begin(); i != _result.end();)
	{
		if (*i == L"")
			i = _result.erase(i);
		else
			i++;
	}
	
	for (auto i = _result.begin() + 1; i != _result.end();)
	{
		if (*i == *(i - 1))
			i = _result.erase(i);
		else
			i++;
	}
	
	return _result;
}
const TranslatedScripts Script_Translator::s_TranslateAll(const SortedScripts& k_source)
{
	return _s_TranslateAll(k_source);
}