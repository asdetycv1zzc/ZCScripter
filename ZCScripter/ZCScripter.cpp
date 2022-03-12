// ZCScripter.cpp: 定义应用程序的入口点。
//

#include <iostream>
#include <Script.h>
#include <Translator.h>
#include <Assemble.h>
#include "time.h"
using namespace std;

int main()
{
	//Script_Analyze temp("N:\\方力U盘备份\\机密\\Shojo\\scenario\\本編\\k18_01.s");
	//Script_Analyze temp("E:\\TRANSPLANT_TEMP\\Bishojo Mangekyo - Kotowari to Meikyu no Shojo\\scenario\\本編\\k07_01.s");
	QLIEVarientPool _pool;
	const wstring _test1 = L"TEST_TOKEN", _test2 = L"TEST_VALUE";
	string _temp1, _temp2;
	for (size_t i = 10000; i <= 100000; i += 1000)
	{
		_pool._Clear();
		auto tStart = clock();
		for (size_t j = 0; j < i; j++)
		{
			_pool._AddVarient(_test1, _test2);
		}
		auto tEnd = clock();
		auto t = tEnd - tStart;
		_temp1.append(to_string(i) + ",");
		_temp2.append(to_string(t) + ",");
		printf("%lld\n", i);
	}
	//setlocale(LC_ALL, "chs");
	//auto _output = Script_Translator::s_TranslateAll(temp._SortedScripts);
	//auto _result = Script_Writer::s_WriteScripts(L"E:\\TRANSPLANT_TEMP\\Bishojo Mangekyo - Kotowari to Meikyu no Shojo\\scenario\\本編\\k07_01.ks", _output);
	system("pause");
	return 0;
}
