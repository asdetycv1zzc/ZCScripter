#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<Script.h>
#include<Converter.h>
#include<Assemble.h>
#include<types.h>
#include<wstring_extend.h>
#include<Translator.h>

std::vector<std::wstring> g_AppearedCharacterModelNames;
std::vector<std::wstring> g_BackgroundScripts;
std::vector<std::pair<std::wstring,std::wstring> > g_BackgroundFiles; //<Layer,File>
std::map<std::wstring, std::wstring> g_BackgroundBuffer;