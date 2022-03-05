#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>

std::vector<std::wstring> g_AppearedCharacterModelNames;
std::vector<std::wstring> g_BackgroundScripts;
std::vector<std::pair<std::wstring,std::wstring> > g_BackgroundFiles; //<Layer,File>
std::map<std::wstring, std::wstring> g_BackgroundBuffer;