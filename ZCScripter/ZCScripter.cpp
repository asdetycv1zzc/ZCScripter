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
	Script_Analyze temp("E:\\TRANSPLANT_TEMP\\Bishojo Mangekyo - Kotowari to Meikyu no Shojo\\scenario\\本編\\k07_01.s");
	/*
	QLIEVarientPool _pool;
	const wstring _test1 = L"TEST_TOKEN", _test2 = L"TEST_VALUE";
	string _temp1, _temp2;
	QLIE::_QLIEVarient _qvar;
	for (size_t i = 0; i <= 100000; i++)
	{
		_qvar.Token = _test1 + to_wstring(i);
		_qvar.Value = _test2;
		_qvar.Type = QLIE::_QLIEParameterTypes::_STRING;
		_qvar._Hash = i;
		_pool += _qvar;
	}
	for (size_t i = 0; i <= 100000; i += 4000)
	{
		//_pool._Clear();
		//_qvar.Token = _test1 + to_wstring(i);
		//_qvar.Value = _test2;
		//_qvar.Type = QLIE::_QLIEParameterTypes::_STRING;
		auto tStart = clock();
		for (size_t j = 0; j < i; j++)
		{
			//_qvar._Hash = j;
			//auto _temp = _pool[_test1 + to_wstring(j)];
			auto _temp = _pool[i];
		}
		auto tEnd = clock();
		auto t = tEnd - tStart;
		_temp1.append(to_string(i) + ",");
		_temp2.append(to_string(t) + ",");
		printf("%lld\n", i);
	}
	system("cls");
	printf("%s\n", _temp1.c_str());
	printf("%s\n", _temp2.c_str());
	*/
	setlocale(LC_ALL, "chs");
	auto _output = Script_Translator::s_TranslateAll(temp._SortedScripts);
	auto _result = Script_Writer::s_WriteScripts(L"E:\\TRANSPLANT_TEMP\\Bishojo Mangekyo - Kotowari to Meikyu no Shojo\\scenario\\本編\\k07_01.ks", _output);
	system("pause");
	return 0;
}
