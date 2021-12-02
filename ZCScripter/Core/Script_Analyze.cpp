#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"Script.h"
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

ScriptBlocks Script_Analyze::_SplitScript(const wchar_t* ConvertedCRLF, long long JudgeLines)
{
	vector<wstring> _source(_LineSplitedScriptContent.Scripts);
	ScriptBlocks _result;
	SplitedScripts _TempResult;
	auto _size = _source.size();
	long long i = 0, _counts = 0;
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
			if (_counts >= JudgeLines)
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
ScriptBlocks Script_Analyze::SplitScript(const wchar_t* ConvertedCRLF, long long JudgeLines)
{
	return _SplitScript(ConvertedCRLF, JudgeLines);
}

SortedScripts Script_Analyze::_SortScript()
{
	SystemScripts _system_part;
	CharacterScripts _character_part;
	for (unsigned long long i = 0; i < _ScriptBlocks.BlockAmount; i++)
	{
		for (unsigned long long j = 0; j < _ScriptBlocks.Blocks[i].ScriptAmount; j++)
		{
			if (_ScriptBlocks.Blocks[i].Scripts[j][0] == L'^')
			{
				_system_part
			}
		}
	}
}

Script_Analyze::Script_Analyze()
{
	ScriptContent NULLContent;
	_ScriptAddress = NULL;
	_Length = -1;
	_ScriptContent = NULLContent;
}
Script_Analyze::Script_Analyze(const char* k_ScriptAddress)
{
	_ScriptAddress = const_cast<char*>(k_ScriptAddress);
	_ScriptContent = Script_Read(k_ScriptAddress).Read();
	_LineSplitedScriptContent = SplitLinesByCRLF();
	_ScriptBlocks = SplitScript();
}
Script_Analyze::~Script_Analyze()
{
	_ScriptAddress = NULL;
}