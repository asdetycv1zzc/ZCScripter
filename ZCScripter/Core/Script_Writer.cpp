#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <Script.h>
#include <wstring_extend.h>
#include <Translator.h>
using namespace std;

const ScriptWriteStatus Script_Writer::_s_WriteScripts(const wstring& _k_DestAddress, const TranslatedScripts& _k_source)
{
	FILE* _ScriptFile = NULL;
	try
	{
		_wfopen_s(&_ScriptFile, _k_DestAddress.c_str(), L"wb");
		fseek(_ScriptFile, 0, 0);
		if (_ScriptFile == NULL) return ScriptWriteStatus::OpenFileFailed;
		for (size_t i = 0; i < _k_source.size(); i++)
		{
			fwrite(_k_source[i].c_str(), sizeof(wchar_t), wstrlen(_k_source[i].c_str()), _ScriptFile);
		}
		fclose(_ScriptFile);
		return ScriptWriteStatus::Success;
	}
	catch (const exception& e)
	{
		wcerr << e.what() << endl;
		if (_ScriptFile != NULL)
			fclose(_ScriptFile);
		return ScriptWriteStatus::UndefinedError;
	}
}
const ScriptWriteStatus Script_Writer::s_WriteScripts(const wstring& k_DestAddress, const TranslatedScripts& k_source)
{
	return _s_WriteScripts(k_DestAddress, k_source);
}