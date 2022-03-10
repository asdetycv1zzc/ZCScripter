#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Script.h>
using namespace std;

ScriptContent Script_Read::Read()
{
	return Script_Read::_Content;
}
ScriptContent Script_Read::_ReadScript()
{
	fstream _File;
	ScriptContent _result;
	try
	{
		long long i = 0;
		_File.open(Script_Read::_ScriptAddress, ios::in | ios::binary);
		_File.seekg(0, ios::beg);

		vector<wchar_t> _TempContent(_Length, 0);
		wstring _Content;
		_Content.resize(_Length, 0);

		while (_File.read((char *)&_TempContent[i], sizeof(wchar_t)))
		{
			if (_TempContent[i] == L'・')
				_TempContent[i] = L'·';
			if (_TempContent[i] == L'♪')
				_TempContent[i] = L' ';
			_Content[i] = _TempContent[i];
			i++;
		}
		_result.FileName = Script_Read::_ScriptAddress;
		_result.Content = _Content;
		_result.Status = 0;
		_result.FileLength = _Length;

		return _result;
	}
	catch (const exception &e)
	{
		cerr << e.what() << endl;
		if (_File.is_open())
			_File.close();
		return _result;
	}
}
long long Script_Read::_GetScriptLength()
{
	fstream k_FILE;
	try
	{
		k_FILE.open(Script_Read::_ScriptAddress, ios::in | ios::binary);
		auto OriginLocation = k_FILE.tellg();
		k_FILE.seekg(0, ios::end);
		auto Length = k_FILE.tellg();
		k_FILE.seekg(OriginLocation, ios::beg);
		return Length;
	}
	catch (const exception &e)
	{
		cerr << e.what() << endl;
		if (k_FILE.is_open())
			k_FILE.close();
		return -1;
	}
}
void Script_Read::init(const char *k_ScriptAddress)
{
	Script_Read::_ScriptAddress = const_cast<char *>(k_ScriptAddress);
	Script_Read::_Length = Script_Read::_GetScriptLength();
	Script_Read::_Content = Script_Read::_ReadScript();
}
Script_Read::Script_Read()
{
	ScriptContent NULLContent;
	_ScriptAddress = NULL;
	_Length = -1;
	_Content = NULLContent;
}
Script_Read::Script_Read(const char *k_ScriptAddress)
{
	_ScriptAddress = const_cast<char *>(k_ScriptAddress);
	_Length = _GetScriptLength();
	_Content = _ReadScript();
}
Script_Read::~Script_Read()
{
	_ScriptAddress = NULL;
}