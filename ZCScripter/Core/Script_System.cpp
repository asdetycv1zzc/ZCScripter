#include<iostream>
#include<string>
#include<System.h>
#include<Converter.h>
using namespace std;

QLIESystem::QLIESystem(const wstring& k_ScriptAddress)
{
	if (k_ScriptAddress.find(L"\\") != wstring::npos)
		SelfFileName = k_ScriptAddress.substr(k_ScriptAddress.find_last_of(L"\\") + 1);
	else
		SelfFileName = k_ScriptAddress;
	RootFile = L"root.s";
}
QLIESystem::QLIESystem(const wchar_t* k_ScriptAddress)
{
	wstring _temp(k_ScriptAddress);
	QLIESystem::QLIESystem(_temp);
}
QLIESystem::QLIESystem(const char* k_ScriptAddress)
{
	string _temp(k_ScriptAddress);
	QLIESystem::QLIESystem(StringToWString(_temp));
}
QLIESystem::QLIESystem(const string& k_ScriptAddress)
{
	QLIESystem::QLIESystem(StringToWString(k_ScriptAddress));
}
QLIESystem::~QLIESystem()
{

}