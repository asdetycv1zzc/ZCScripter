#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>

constexpr auto DEFAULT_BACKGROUND = L"color_ü\";
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
constexpr auto DEFAULT_MUSIC_FADE_TIME = L"100";

enum ItemTypes
{
	Background,
	Character,
};

std::vector<std::map<std::wstring, std::wstring> > g_AppearedCharacterModelNames;//<Layer,File>
std::map<std::wstring, std::wstring> g_CharacterBuffer;
std::vector<std::wstring> g_BackgroundScripts;
std::vector<std::map<std::wstring,std::wstring> > g_BackgroundFiles; //<Layer,File>
std::vector<std::map<std::wstring,std::wstring> > g_CharacterFiles; //<Layer,File>
std::map<std::wstring, std::wstring> g_BackgroundBuffer;
std::pair<std::vector<std::wstring>,bool> g_LastSelectTextBuffer;
std::vector<std::wstring> g_PlayedSounds;

std::vector<std::wstring> g_ResultStr;
std::vector<std::wstring> g_Avg_SelectCurLabel;

const std::wstring g_SearchLastItemByLayer(const std::wstring& k_Layer,const ItemTypes& k_type) noexcept
{
	std::wstring _result = L"";
	switch (k_type)
	{
	case ItemTypes::Background:
	{
		for (auto i = g_BackgroundFiles.begin(); i != g_BackgroundFiles.end();)
		{
			if ((*i)[k_Layer].empty())
				i++;
			else
			{
				_result = (*i)[k_Layer];
				i++;
			}
				
		}
		return _result;;
	}
	case ItemTypes::Character:
	{
		for (auto i = g_AppearedCharacterModelNames.begin(); i != g_AppearedCharacterModelNames.end();)
		{
			if ((*i)[k_Layer].empty())
				i--;
			else
			{
				_result = (*i)[k_Layer];
				i++;
			}
		}
		return _result;
	}
	}
	
}

