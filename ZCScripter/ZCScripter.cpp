// ZCScripter.cpp: 定义应用程序的入口点。
//

#include <iostream>
#include <Script.h>
#include <Translator.h>
using namespace std;

int main()
{
	Script_Analyze temp("N:\\方力U盘备份\\机密\\Shojo\\scenario\\本編\\k18_01.s");
	setlocale(LC_ALL, "chs");
	auto _output = Script_Translator::s_TranslateAll(temp.SortScript());
	auto _result = Script_Writer::s_WriteScripts(L"N:\\方力U盘备份\\机密\\Shojo\\scenario\\本編\\k18_01.ks", _output);
	system("pause");
	return 0;
}
