// ZCScripter.cpp: 定义应用程序的入口点。
//

#include <iostream>
#include <Script.h>
#include <Translator.h>
#include <Assemble.h>
using namespace std;

int main()
{
	//Script_Analyze temp("N:\\方力U盘备份\\机密\\Shojo\\scenario\\本編\\k18_01.s");
	//Script_Analyze temp("E:\\TRANSPLANT_TEMP\\Bishojo Mangekyo - Kotowari to Meikyu no Shojo\\scenario\\本編\\k07_01.s");
	QLIEVarientPool _pool;
	for (size_t i = 0; i < 10000; i++)
	{
		_pool._AllocateNewHash();
	}
	//setlocale(LC_ALL, "chs");
	//auto _output = Script_Translator::s_TranslateAll(temp._SortedScripts);
	//auto _result = Script_Writer::s_WriteScripts(L"E:\\TRANSPLANT_TEMP\\Bishojo Mangekyo - Kotowari to Meikyu no Shojo\\scenario\\本編\\k07_01.ks", _output);
	system("pause");
	return 0;
}
