#include "DrawModelManager.h"
#include "DxLib.h"

//model�̃A�h���X��Ⴄ�ƃ��f���n���h����Ԃ�
std::unordered_map<std::string, int> DrawModelManager::modelMap;
//��������
DrawModelManager::DrawModelManager()
{
    modelMap.clear();
}
/// <summary>
/// �e���f���̏����f���[�g
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
/// model�����[�h���ēn��
/// </summary>
/// <param name="assetPass"></param>
/// <returns>���łɃ��[�h���Ă��畡��</returns>
int DrawModelManager::Get3DModelAssetHandle(std::string assetPass)
{
    if (modelMap.contains(assetPass))//���łɒǉ����[�h����Ă����畡��
    {
        return MV1DuplicateModel(modelMap[assetPass]);
    }
    //�܂����[�h���ĂȂ��Ȃ烍�[�h����
    modelMap.insert(std::make_pair(assetPass, MV1LoadModel(assetPass.c_str())));
    return modelMap[assetPass];
}