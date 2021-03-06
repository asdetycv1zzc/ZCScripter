#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<Script.h>

const bool _cmpByFileNum(const QLIE::_QLIEParameter_NormalForm& _a, const QLIE::_QLIEParameter_NormalForm& _b);

class Script_Translator
{
private:
	std::wstring _DestAddress;
	
	const static std::vector<std::wstring> _s_From_QLIECharacter_To_KRKRCharacter(const CharacterScript& _k_source);
	const static std::vector<std::wstring> _s_From_QLIESystem_To_KRKRSystem(const SystemScript& _k_source);
	const static std::wstring _s_From_QLIELabel_To_KRKRLabel(const std::wstring& _k_source);
	const static std::pair<std::wstring, std::wstring> _s_Extract_QLIESubParameter(const std::wstring& _k_source,const std::wstring& _k_split);
	const static std::wstring _s_Extract_QLIESubParameter(const std::wstring& _k_source,const std::wstring& _k_name ,const std::wstring& _k_split);
	const static TranslatedScripts _s_TranslateAll(const SortedScripts& _k_source);
public:
	const static std::vector<std::wstring> s_From_QLIECharacter_To_KRKRCharacter(const CharacterScript& k_source);
	const static std::vector<std::wstring> s_From_QLIESystem_To_KRKRSystem(const SystemScript& k_source);
	const static std::wstring s_From_QLIELabel_To_KRKRLabel(const std::wstring& k_source);
	const static std::pair<std::wstring, std::wstring> s_Extract_QLIESubParameter(const std::wstring& k_source, const std::wstring& k_split);
	const static std::wstring s_Extract_QLIESubParameter(const std::wstring& k_source, const std::wstring& k_name, const std::wstring& k_split);
	const static TranslatedScripts s_TranslateAll(const SortedScripts& k_source);
};