#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<Script.h>

constexpr auto DEFAULT_BACKGROUND = L"color_ºÚ";
constexpr auto DEFAULT_BACKGROUND_SWITCH_METHOD = L"crossfade";

class Script_Translator
{
private:
	std::wstring _DestAddress;
	const static std::vector<std::wstring> _s_From_QLIECharacter_To_KRKRCharacter(const CharacterScript& _k_source);
	const static std::vector<std::wstring> _s_From_QLIESystem_To_KRKRSystem(const SystemScript& _k_source);
public:
	const static std::vector<std::wstring> s_From_QLIECharacter_To_KRKRCharacter(const CharacterScript& k_source);
	const static std::vector<std::wstring> s_From_QLIESystem_To_KRKRSystem(const SystemScript& k_source);
};