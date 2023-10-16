#include <unordered_map>
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "UIDrawer.h"
//エフェクトのハンドルが入るマップ
std::unordered_map <EffectKind, int> EffectManager:: effectMap;
//エフェクトのパスが入る文字列
std::vector<std::string> EffectManager::initDataVec;
/// <summary>
/// エフェクトの保管庫
/// </summary>
EffectManager::EffectManager()
{
    effectMap.clear();
    CSVFileLoader* initDataFile = new CSVFileLoader(GetInitCsvFilePass(AssetList::effect));
    initDataVec = initDataFile->GeFileStringData();
    SAFE_DELETE(initDataFile);
}
/// <summary>
/// エフェクトを解放
/// </summary>
EffectManager::~EffectManager()
{
    for (auto ite = effectMap.begin(); ite != effectMap.end(); ite++)
    {
        DeleteEffekseerEffect((*ite).second);
    }
    effectMap.clear();
}
/// <summary>
/// エフェクトを読み込む
/// </summary>
/// <param name="kind">エフェクトの種類</param>
void EffectManager::LoadEffect(EffectKind kind)
{
    if (!effectMap.contains(kind))
    {
        //データ読み取り
        CSVFileLoader* initDataFile = new CSVFileLoader(initDataVec[static_cast<int>(kind)]);
        
        std::vector<std::string> dataVec = initDataFile->GeFileStringData();
        using enum EffectInitData;
        //エフェクトのアセットのパス
        const char* effectPassStr = dataVec[static_cast<int>(effectPass)].c_str();
        //エフェクトの大きさ
        float size = STR_TO_F(dataVec[static_cast<int>(effectSize)]);
        //エフェクトの読み込みと大きさをセット
        int effectHandle = LoadEffekseerEffect(effectPassStr, size);
        effectMap.insert(std::make_pair(kind, effectHandle));
    }
}
/// <summary>
/// ロード済みの3Ⅾエフェクトを渡す
/// </summary>
/// <param name="kind">エフェクトの種類</param>
/// <returns>3Ⅾエフェクトのハンドル</returns>
int EffectManager::GetPlayEffect3D(EffectKind kind)
{
    int isPlay = -1;
    //ロード済みなら渡す
    if (effectMap.contains(kind))
    {
        isPlay = PlayEffekseer3DEffect(effectMap[kind]);
    }
    return isPlay;
}
/// <summary>
/// ロード済みの2Dエフェクトを渡す
/// </summary>
/// <param name="kind"></param>
/// <returns>2Ⅾエフェクトのハンドル</returns>
int EffectManager::GetPlayEffect2D(EffectKind kind)
{
    int isPlay = -1;
    //ロード済みなら渡す
    if (effectMap.contains(kind))
    {
        isPlay = PlayEffekseer2DEffect(effectMap[kind]);
    }
    return isPlay;
}