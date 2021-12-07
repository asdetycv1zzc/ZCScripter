#include <iostream>
#include <string>
#include <Script.h>
using namespace std;

QLIE::_QLIEScripts Script_Converter::_SplitedScripts_TO_QLIEScripts(const SplitedScripts _k_source)
{
    QLIE::_QLIEScripts _result;
    _result.ScriptAmount = _k_source.ScriptAmount;
    _result.Status = _k_source.Status;
    _result.Scripts = _k_source.Scripts;
    return _result;
}
QLIE::_QLIEScripts Script_Converter::SplitedScripts_TO_QLIEScripts(const SplitedScripts k_source)
{
    return _SplitedScripts_TO_QLIEScripts(k_source);
}

QLIE::_QLIEScriptBlocks Script_Converter::_ScriptBlocks_TO_QLIEScriptBlocks()
{
    ScriptBlocks _tempScriptBlocks = _ScriptBlocks;
    QLIE::_QLIEScriptBlocks _result;

    _result.BlockAmount = _tempScriptBlocks.BlockAmount;
    _result.Status = _tempScriptBlocks.Status;
    _result.Scripts.resize(_result.BlockAmount);

    for (unsigned long i = 0; i < _result.BlockAmount; i++)
        _result.Scripts[i] = SplitedScripts_TO_QLIEScripts(_tempScriptBlocks.Blocks[i]);

    return _result;
}
QLIE::_QLIEScriptBlocks Script_Converter::ScriptBlocks_TO_QLIEScriptBlocks()
{
    return _ScriptBlocks_TO_QLIEScriptBlocks();
}
