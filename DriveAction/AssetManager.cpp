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
/// 複製したモデルを渡す
/// </summary>
/// <param name="assetPass"></param>
/// <returns></returns>
int AssetManager::Get3DModelAssetHandle(std::string assetPass)
{
    if (!assetMap.contains(assetPass))//まだロードしてないならロードする
    {
        assetMap.insert(std::make_pair(assetPass, MV1LoadModel(assetPass.c_str())));
    }
    return assetMap[assetPass];
}