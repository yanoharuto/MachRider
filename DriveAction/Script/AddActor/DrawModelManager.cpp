#include "DrawModelManager.h"
#include "DxLib.h"

//modelのアドレスを貰うとモデルハンドルを返す
std::unordered_map<std::string, int> DrawModelManager::modelMap;
//複製準備
DrawModelManager::DrawModelManager()
{
    modelMap.clear();
}
/// <summary>
/// 各モデルの情報をデリート
/// </summary>
DrawModelManager::~DrawModelManager()
{
    for (auto ite = modelMap.begin(); ite != modelMap.end(); ite++)
    {
        MV1DeleteModel((*ite).second);
    }
    modelMap.clear();
}
/// <summary>
/// modelをロードして渡す
/// </summary>
/// <param name="assetPass"></param>
/// <returns>すでにロードしてたら複製</returns>
int DrawModelManager::Get3DModelAssetHandle(std::string assetPass)
{
    if (modelMap.contains(assetPass))//すでに追加ロードされていたら複製
    {
        return MV1DuplicateModel(modelMap[assetPass]);
    }
    //まだロードしてないならロードする
    modelMap.insert(std::make_pair(assetPass, MV1LoadModel(assetPass.c_str())));
    return modelMap[assetPass];
}
