#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>

constexpr auto DEFAULT_BACKGROUND = L"color_�\";
constexpr auto DEFAULT_BACKGROUND_SWITCH_METHOD = L"crossfade";
constexpr auto DEFAULT_CHARACTER_SWITCH_METHOD = L"crossfade";
constexpr auto DEFAULT_CHARACTER_LAYER = L"0";
constexpr auto DEFAULT_CHARACTER_SEPERATE_CHAR = L"_";
constexpr auto DEFAULT_CHARACTER_POSITION = L"center";
constexpr auto DEFAULT_QLIE_SUBPARAMETER_SPLIT = L":";
constexpr auto DEFAULT_BACKGROUND_PAGE = L"fore";
constexpr auto DEFAULT_BACKGROUND_COVER_MODE = L"opaque";
constexpr auto DEFAULT_BACKGROUND_POSITION = L"center";
constexpr auto DEFAULT_BACKGROUND_VISIBILITY = L"1";

std::vector<std::wstring> g_AppearedCharacterModelNames;
std::vector<std::wstring> g_BackgroundScripts;
std::vector<std::map<std::wstring,std::wstring> > g_BackgroundFiles; //<Layer,File>
std::map<std::wstring, std::wstring> g_BackgroundBuffer;
std::pair<std::vector<std::wstring>,bool> g_LastSelectTextBuffer;
std::vector<std::wstring> g_PlayedSounds;

