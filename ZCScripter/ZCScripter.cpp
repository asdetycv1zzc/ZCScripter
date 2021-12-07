// ZCScripter.cpp: 定义应用程序的入口点。
//

#include <iostream>
#include <Assemble.h>
#include <Script.h>
using namespace std;

int main()
{
	Script_Analyze temp("N:\\1.s");
	//ios_base::sync_with_stdio(false);
	setlocale(LC_ALL, "chs");
	auto _output = temp.SplitScript();
	for (unsigned long long i = 0; i < _output.Blocks.size(); i++)
	{
		for (unsigned long j = 0; j < _output.Blocks[i].ScriptAmount; j++)
		{
			//std::wcout.imbue(std::locale("chs"));
			//wcout << _output.Blocks[i].Scripts[j];
			//wprintf(L"%s\n", Script_Analyze::GetSpeaker(_output.Blocks[i]).c_str());
			wprintf(L"%s\n", _output.Blocks[i].Scripts[j].c_str());
		}
		wprintf(L"\n");
	}
	system("pause");
	return 0;
}
