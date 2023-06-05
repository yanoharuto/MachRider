#include "AssetManager.h"
#include "DxLib.h"
#include "Utility.h"

//model�̃A�h���X��Ⴄ�ƃ��f���n���h����Ԃ�
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
/// �����������f����n��
/// </summary>
/// <param name="assetPass"></param>
/// <returns></returns>
int AssetManager::Get3DModelAssetHandle(std::string assetPass)
{
    if (!assetMap.contains(assetPass))//�܂����[�h���ĂȂ��Ȃ烍�[�h����
    {
        assetMap.insert(std::make_pair(assetPass, MV1LoadModel(assetPass.c_str())));
    }
    return assetMap[assetPass];
}