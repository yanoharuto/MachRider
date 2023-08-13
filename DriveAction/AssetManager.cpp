#include "AssetManager.h"
#include "DxLib.h"
#include "Utility.h"

//modelのアドレスを貰うとモデルハンドルを返す
std::map<std::string, int> AssetManager::assetMap;
AssetManager::AssetManager()
{
    assetMap.clear();
}

AssetManager::~AssetManager()
{
    for (auto ite = assetMap.begin(); ite != assetMap.end(); ite++)
    {
        MV1DeleteModel((*ite).second);
    }
    assetMap.clear();
}
/// <summary>
/// モデルを渡す
/// </summary>
/// <param name="assetPass"></param>
/// <returns>すでにロードしてたら複製</returns>
int AssetManager::Get3DModelAssetHandle(std::string assetPass)
{
    if (assetMap.contains(assetPass))//すでに追加ロードされていたら複製
    {
        return MV1DuplicateModel(assetMap[assetPass]);
    }
    //まだロードしてないならロードする
    assetMap.insert(std::make_pair(assetPass, MV1LoadModel(assetPass.c_str())));
    return assetMap[assetPass];
}