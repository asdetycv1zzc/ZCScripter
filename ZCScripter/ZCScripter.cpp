// ZCScripter.cpp: 定义应用程序的入口点。
//

#include <iostream>
#include "Core/Script.h"
#include "Converter/Converter.h"
using namespace std;

int main()
{
	//Script_Read temp("J:\\1.s");
	Script_Analyze temp("1.s");
	//temp.SplitLinesByCRLF();
	//temp.SplitScript();
	auto _output = temp.SplitScript();
	for (long long i = 0; i < _output.BlockAmount; i++)
	{
		for (long long j = 0; j < _output.Blocks[i].ScriptAmount; j++)
		{
			wcout.imbue(locale("chs"));
			wcout << WStringToString(_output.Blocks[i].Scripts[j]);
		}
	}
	system("pause");
	return 0;
}
