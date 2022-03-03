// ZCScripter.cpp: 定义应用程序的入口点。
//

#include <iostream>
#include <Assemble.h>
#include <Script.h>
#include <Translator.h>
using namespace std;

int main()
{
	Script_Analyze temp("N:\\方力U盘备份\\机密\\Shojo\\scenario\\本編\\k18_01.s");
	//ios_base::sync_with_stdio(false);
	setlocale(LC_ALL, "chs");
	//auto _output = temp.SplitScript();
	auto _output = temp.SortScript();
	
	vector<wstring> _test1;
	_test1.reserve(100000);
	for (unsigned long j = 0; j < _output.BlockAmount; j++)
	{
		//std::wcout.imbue(std::locale("chs"));
		//wcout << _output.Blocks[i].Scripts[j];
		//wprintf(L"%s\n", Script_Analyze::GetSpeaker(_output.Blocks[i]).c_str());
		//wprintf(L"%s\n", _output.Blocks[i].Scripts[j].c_str());
		
		if (_output._Typetable[j].second == 0)
		{
			auto _test_p = _output._SystemScripts.Blocks[_output._Typetable[j].first];
			auto _temp = vector<wstring>(Script_Translator::s_From_QLIESystem_To_KRKRSystem(_test_p));
			_test1.assign(_temp.begin(), _temp.end());
		}
		else
		{
			auto _temp = vector<wstring>(Script_Translator::s_From_QLIECharacter_To_KRKRCharacter(_output._CharacterScripts.Blocks[_output._Typetable[j].first]));
			_test1.assign(_temp.begin(), _temp.end());
		}
		
		for (unsigned long k = 0; k < _test1.size(); k++)
		{
			wprintf(L"%s\n", _test1[k].c_str());
		}
		_test1.clear();
		//wprintf(L"%s\n", _output._CharacterScripts.Blocks[j].Script.c_str());
	}
	wprintf(L"\n");

	system("pause");
	return 0;
}
