#include <unordered_map>
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "CSVFileLoader.h"
#include "Utility.h"
std::unordered_map <EffectKind, int> EffectManager:: effectMap;
std::vector<std::string> EffectManager::initDataVec;
EffectManager::EffectManager()
{
    effectMap.clear();
    CSVFileLoader* initDataFile = new CSVFileLoader(initDataPassFile);
    initDataVec = initDataFile->GetLoadStringData();
    SAFE_DELETE(initDataFile);
}

EffectManager::~EffectManager()
{
    for (auto ite = effectMap.begin(); ite != effectMap.end(); ite++)
    {
        DeleteEffekseerEffect((*ite).second);
    }
    effectMap.clear();
}

void EffectManager::LoadEffect(EffectKind kind)
{
    if (!effectMap.contains(kind))
    {
        //データ読み取り
        CSVFileLoader* initDataFile = new CSVFileLoader(initDataVec[kind]);

        std::vector<std::string> dataVec = initDataFile->GetLoadStringData();

        const char* effectPass = dataVec[EffectInitData::effectPass].c_str();

        float size = atof(dataVec[EffectInitData::effectSize].c_str());
        //エフェクトの読み込みと大きさをセット
        int effectHandle = LoadEffekseerEffect(effectPass, size);
        effectMap.insert(std::make_pair(kind, effectHandle));
    }
}

int EffectManager::GetPlayEffect3D(EffectKind kind)
{
    int isPlay = -1;
    if (effectMap.contains(kind))
    {
        isPlay = PlayEffekseer3DEffect(effectMap[kind]);
    }
    return isPlay;
}

int EffectManager::GetPlayEffect2D(EffectKind kind)
{
    int isPlay = -1;
    if (effectMap.contains(kind))
    {
        isPlay = PlayEffekseer2DEffect(effectMap[kind]);
    }
    return isPlay;
}