﻿// ZCScripter.cpp: 定义应用程序的入口点。
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
	

	for (unsigned long j = 0; j < _output.BlockAmount; j++)
	{
		//std::wcout.imbue(std::locale("chs"));
		//wcout << _output.Blocks[i].Scripts[j];
		//wprintf(L"%s\n", Script_Analyze::GetSpeaker(_output.Blocks[i]).c_str());
		//wprintf(L"%s\n", _output.Blocks[i].Scripts[j].c_str());
		vector<wstring> _test1;
		if (_output._Typetable[j].second == 0)
		{
			_test1 = vector<wstring>(Script_Translator::s_From_QLIESystem_To_KRKRSystem(_output._SystemScripts.Blocks[_output._Typetable[j].first]));
		}
		else
		{
			_test1 = vector<wstring>(Script_Translator::s_From_QLIECharacter_To_KRKRCharacter(_output._CharacterScripts.Blocks[_output._Typetable[j].first]));
		}
		
		for (unsigned long k = 0; k < _test1.size(); k++)
		{
			wprintf(L"%s\n", _test1[k].c_str());
		}
		//wprintf(L"%s\n", _output._CharacterScripts.Blocks[j].Script.c_str());
	}
	wprintf(L"\n");

	system("pause");
	return 0;
}
