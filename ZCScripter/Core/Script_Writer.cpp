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
	//setlocale(LC_ALL, "chs");
	wfstream _ScriptFile;
	try
	{
		_ScriptFile.open(_k_DestAddress, wios::beg | wios::out | wios::binary);
		_ScriptFile.seekg(0, wios::beg);
		//_ScriptFile.imbue(locale("", locale::all ^ locale::numeric));
		_ScriptFile.imbue(locale("chs"));
		for (size_t i = 0; i < _k_source.size(); i++)
		{
			auto _temp = _k_source[i];
			_ScriptFile.write(_temp.c_str(), _temp.size());
			_ScriptFile.write(L"\n", 1);
			_ScriptFile.flush();
		}
		_ScriptFile.close();
		return ScriptWriteStatus::Success;
	}
	catch (const exception& e)
	{
		wcerr << e.what() << endl;
		if (_ScriptFile.is_open()) _ScriptFile.close();
		return ScriptWriteStatus::UndefinedError;
	}
}
const ScriptWriteStatus Script_Writer::s_WriteScripts(const wstring& k_DestAddress, const TranslatedScripts& k_source)
{
	return _s_WriteScripts(k_DestAddress, k_source);
}