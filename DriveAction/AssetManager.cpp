#include "AssetManager.h"
#include "DxLib.h"
#include "Utility.h"

//model�̃A�h���X��Ⴄ�ƃ��f���n���h����Ԃ�
std::map<std::string, int> AssetManager::assetMap;
/// <summary>
/// �`�惂�f���n���h����������
/// </summary>
AssetManager::AssetManager()
{
    assetMap.clear();
}
/// <summary>
/// �e���f���̏����f���[�g
/// </summary>
AssetManager::~AssetManager()
{
    for (auto ite = assetMap.begin(); ite != assetMap.end(); ite++)
    {
        MV1DeleteModel((*ite).second);
    }
    assetMap.clear();
}
/// <summary>
/// ���f����n��
/// </summary>
/// <param name="assetPass"></param>
/// <returns>���łɃ��[�h���Ă��畡��</returns>
int AssetManager::Get3DModelAssetHandle(std::string assetPass)
{
    if (assetMap.contains(assetPass))//���łɒǉ����[�h����Ă����畡��
    {
        return MV1DuplicateModel(assetMap[assetPass]);
    }
    //�܂����[�h���ĂȂ��Ȃ烍�[�h����
    assetMap.insert(std::make_pair(assetPass, MV1LoadModel(assetPass.c_str())));
    return assetMap[assetPass];
}