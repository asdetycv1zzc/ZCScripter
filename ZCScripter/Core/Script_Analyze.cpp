#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <Script.h>
#include <Converter.h>
#include <wstring_extend.h>
using namespace std;


SplitedScripts Script_Analyze::_SplitLinesByCRLF()
{
	wstring _temp(_ScriptContent.Content), buffer;
	auto _size = _temp.size();
	vector<wstring> _temp_result;
	for (unsigned long long i = 0; i < _size; i++)
	{
		if (_temp[i] != L'\r' && _temp[i] != L'\n')
		{
			buffer.push_back(_temp[i]);
			continue;
		}
		if (_temp[i] == L'\r' || _temp[i] == L'\n')
		{
			if (buffer.size() > 0)
			{
				_temp_result.push_back(buffer);
				buffer.clear();
			}
			else
				_temp_result.push_back(L"\n");
			i += 1;
		}
	}
	SplitedScripts _result;
	_result.Scripts = _temp_result;
	_result.ScriptAmount = _temp_result.size();
	_result.Status = 0;
	return _result;
}
SplitedScripts Script_Analyze::SplitLinesByCRLF()
{
	return _SplitLinesByCRLF();
}

ScriptBlocks Script_Analyze::_SplitScript(const wchar_t* _ConvertedCRLF, unsigned long long _JudgeLines)
{
	vector<wstring> _source(_LineSplitedScriptContent.Scripts);
	ScriptBlocks _result;
	SplitedScripts _TempResult;
	auto _size = _source.size();
	unsigned long long i = 0, _counts = 0;
	while (i < _size)
	{
		if (_source[i] != L"\n")
		{
			_TempResult.Scripts.push_back(_source[i]);
			i++;
			continue;
		}
		if (_source[i] == L"\n")
		{
			_counts += 1;
			auto j = i;
			while (_source[j + 1] == L"\n")
			{
				j++;
				_counts++;
			}
			if (_counts >= _JudgeLines)
			{
				i = j;
				_TempResult.ScriptAmount = _TempResult.Scripts.size();
				_TempResult.Status = 0;
				_result.Blocks.push_back(_TempResult);
				_TempResult.Scripts.clear();
				_counts = 0;
			}
			i++;
		}
	}
	/*
	long long _beginPos = 0, _endPos;
	wstring _DeleteContent;
	auto _DeleteContentSize = _DeleteContent.size();
	for (i = 0; i < JudgeLines; i++)
		_DeleteContent.push_back(ConvertedCRLF);

	while (_source.find(_DeleteContent) != wstring::npos)
	{
		_endPos = _source.find(_DeleteContent);
		_TempResult.Scripts.push_back(_source.substr(_beginPos, _endPos - _beginPos));
		_counts += 1;
		_source.erase(_endPos, _DeleteContentSize);
		_beginPos = _endPos + _DeleteContentSize;
	}
	*/
	_result.BlockAmount = _result.Blocks.size();
	_result.Status = 0;

	return _result;
}
ScriptBlocks Script_Analyze::SplitScript(const wchar_t* ConvertedCRLF, unsigned long long JudgeLines)
{
	return _SplitScript(ConvertedCRLF, JudgeLines);
}

SortedScripts Script_Analyze::_SortScript()
{
	SystemScripts _system_part;
	CharacterScripts _character_part;
	SortedScripts _result;
	size_t _currentScriptAmount = 0;

	_result.CompleteFileName = StringToWString(string(_ScriptAddress));
	auto _RelativeFileName = _result.CompleteFileName.substr(_result.CompleteFileName.find_last_of(L"\\") + 1);

	for (unsigned long long i = 0; i < _ScriptBlocks.BlockAmount; i++)
	{
		for (unsigned long long j = 0; j < _ScriptBlocks.Blocks[i].ScriptAmount; j++)
		{
			if (_ScriptBlocks.Blocks[i].Scripts[j][0] == L'^' || _ScriptBlocks.Blocks[i].Scripts[j].find(L"@@") != wstring::npos)
			{
				SystemScript _temp;
				_temp.Script = _ScriptBlocks.Blocks[i].Scripts[j];
				_temp.Order = j;
				_temp.Status = 0;
				_temp.ScriptType = GetSystemScriptType(_ScriptBlocks.Blocks[i].Scripts[j]);
				_temp._command = QLIEHelper::GetCommand(_temp.Script);
				_temp._parameters = QLIEHelper::GetParameters(_temp.Script);
				_temp._Filename = _RelativeFileName;
				_system_part.Blocks.push_back(_temp);
				pair<unsigned long long, short> _temp_map;
				_temp_map.first = _system_part.Blocks.size() - 1;
				_temp_map.second = 0;
				_result._Typetable[_currentScriptAmount] = _temp_map;
			}
			else
			{
				CharacterScript _temp;
				_temp.Script = _ScriptBlocks.Blocks[i].Scripts[j];
				_temp.Order = j;
				_temp.Status = 0;
				_temp.Speaker = GetSpeaker(_ScriptBlocks.Blocks[i]);
				if (wstrcmp((L"【" + _temp.Speaker + L"】").c_str(), _temp.Script.c_str()))
					_temp.Script = L"";
				_temp._Filename = _RelativeFileName;
				_character_part.Blocks.push_back(_temp);
				pair<unsigned long long, short> _temp_map;
				_temp_map.first = _character_part.Blocks.size() - 1;
				_temp_map.second = 1;
				_result._Typetable[_currentScriptAmount] = _temp_map;
			}
			_currentScriptAmount += 1;
		}
	}
	_system_part.BlockAmount = _system_part.Blocks.size();
	_character_part.BlockAmount = _character_part.Blocks.size();
	_system_part.Status = 0;
	_character_part.Status = 0;
	
	_result._CharacterScripts = _character_part;
	_result._SystemScripts = _system_part;
	_result.BlockAmount = _result._CharacterScripts.BlockAmount + _result._SystemScripts.BlockAmount;
	_result.Status = 0;
	return _result;
}
SortedScripts Script_Analyze::SortScript()
{
	return _SortScript();
}

SystemScriptTypes Script_Analyze::_GetSystemScriptType(const SingleScript _k_SplitedScript)
{
	SingleScript _temp(_k_SplitedScript);
	auto _command = _temp.substr(0, _temp.find_first_of(L','));
	if (_command.find(L"^bg") != wstring::npos)
		return SystemScriptTypes::SetBackground;
	if (_command.find(L"^chara") != wstring::npos)
		return SystemScriptTypes::SetCharacterModel;
	if (_command.find(L"^music") != wstring::npos)
		return SystemScriptTypes::SetMusic;
	if (_command.find(L"^sentence") != wstring::npos)
		return SystemScriptTypes::SetSentenceEffects;
	if (_command.find(L"^select") != wstring::npos)
		return SystemScriptTypes::SetSelect;
	if (_command.find(L"^selectlabel") != wstring::npos)
		return SystemScriptTypes::SetSelectLabel;
	if (_command.find(L"^se") != wstring::npos)
		return SystemScriptTypes::SetSound;
	if (_command.find(L"^camera") != wstring::npos)
		return SystemScriptTypes::SetCamera;
	if (_command.find(L"include") != wstring::npos)
		return SystemScriptTypes::SetPostScript;
	if (_command.find(L"^face") != wstring::npos)
		return SystemScriptTypes::SetCharacterFace;
	if (_command.find(L"^textani") != wstring::npos)
		return SystemScriptTypes::__UNKNOWN_SCRIPT3;
	if (_command.find(L"^message") != wstring::npos)
		return SystemScriptTypes::SetMessageBox;
	if (_command.find(L"^ef") != wstring::npos)
		return SystemScriptTypes::SetEffect;
	if (_command.find(L"\\jmp") != wstring::npos)
		return SystemScriptTypes::_JMP;
	if (_command.find(L"\\sub") != wstring::npos)
		return SystemScriptTypes::_SUB;
	if (_command.find(L"@@") != wstring::npos && _command.find(L"@@@") == wstring::npos)
		return SystemScriptTypes::SetEntryName;
	if (_command.find(L"@@@") != wstring::npos)
		return SystemScriptTypes::SetIncludeFile;
	return SystemScriptTypes::_UNDEFINED_SystemScript;
}
SystemScriptTypes Script_Analyze::GetSystemScriptType(const SingleScript k_SplitedScript)
{
	return _GetSystemScriptType(k_SplitedScript);
}

CharacterScriptTypes Script_Analyze::_GetCharacterScriptType(const SingleScript _k_SplitedScript)
{
	SingleScript _temp(_k_SplitedScript);
	auto _command = _temp.substr(0, _temp.find_first_of(L','));
	if (_command.find(L'%') != wstring::npos)
		return CharacterScriptTypes::PlayVoice;
	return CharacterScriptTypes::_UNDEFINED_CharacterScript;
}
CharacterScriptTypes Script_Analyze::GetCharacterScriptType(const SingleScript k_SplitedScript)
{
	return _GetCharacterScriptType(k_SplitedScript);
}

wstring Script_Analyze::_GetSpeaker(const SplitedScripts _k_SplitedScripts)
{
	wstring _result;
	for (unsigned long long i = 0; i < _k_SplitedScripts.ScriptAmount; i++)
	{
		auto beginPos = _k_SplitedScripts.Scripts[i].find_first_of(L"【");
		auto endPos = _k_SplitedScripts.Scripts[i].find_first_of(L"】");
		if (beginPos != wstring::npos)
			if (GetCharacterScriptType(_k_SplitedScripts.Scripts[i]) == CharacterScriptTypes::_UNDEFINED_CharacterScript)
			{
				if (_result.empty())
					_result = _k_SplitedScripts.Scripts[i].substr(beginPos + 1, endPos - beginPos - 1);
				else
					_result = _result + _k_SplitedScripts.Scripts[i].substr(beginPos + 1, endPos - beginPos - 1);
			}
	}
	return _result;
}
wstring Script_Analyze::GetSpeaker(const SplitedScripts k_SplitedScripts)
{
	return _GetSpeaker(k_SplitedScripts);
}

Script_Analyze::Script_Analyze()
{
	ScriptContent NULLContent;
	_ScriptAddress = NULL;
	_ScriptContent = NULLContent;
}
Script_Analyze::Script_Analyze(const char* k_ScriptAddress)
{
	_ScriptAddress = const_cast<char*>(k_ScriptAddress);
	_ScriptContent = Script_Read(k_ScriptAddress).Read();
	_LineSplitedScriptContent = SplitLinesByCRLF();
	_ScriptBlocks = SplitScript();
	_SortedScripts = SortScript();
}
Script_Analyze::~Script_Analyze()
{
}