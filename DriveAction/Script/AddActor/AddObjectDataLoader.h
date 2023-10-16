#pragma once
#include "AssetManager.h"
#include <string>
#include <vector>
/// <summary>
/// �I�u�W�F�N�g�̒ǉ�����ǂݎ��N���X
/// </summary>
class AddObjectDataLoader final:public AssetManager
{
public:
    enum class AddData;
    /// <summary>
    /// �ǉ�����ǂݎ��
    /// </summary>
    /// <param name="loadData">�ǂݎ�肽���ǉ����</param>
    AddObjectDataLoader(AddData loadData);
    /// <summary>
    /// �ǉ����𕶎���œn��
    /// </summary>
    /// <returns>������œn��</returns>
    std::vector<std::string> GetLoadData()const;
    //�ǉ����̎��
    enum class AddData
    {
        circleFlyShip,//�~�w�g��ł��s�D�̒ǉ����
        upDownFlyShip,//�㉺�Ɉړ������s�D�̒ǉ����
        bomberShip,//���e���Ƃ���s�D�̒ǉ����
        moveSaw,//�ړ���]�̂�����̒ǉ����
        playerSpeed//�v���C���[�̈ړ����
    };
private:
    //�ǂݎ�����ǉ����
    std::vector<std::string> loadAddData;
    //Json�Ŏg���X�L�[�}�̃p�X
    const std::string schemaPass = "data/Json/Schema/objectAddDataSchema.json";
};