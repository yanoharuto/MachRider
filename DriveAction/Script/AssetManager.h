#pragma once
#include <vector>
#include <string>
#include <unordered_map>
class JsonFileLoader;
/// <summary>
/// �A�Z�b�g�܂ł̃p�X�����L�ł���悤�ɐe�N���X�ɓn��
/// </summary>
class AssetManager abstract
{
public:
    enum class AssetList;
    /// <summary>
    /// �f�t�H���g�R���X�g���N�^
    /// </summary>
    AssetManager() {};
    virtual ~AssetManager() {};

    enum class AssetList
    {
        camera,//�J����
        effect,//�G�t�F�N�g
        object,//�I�u�W�F�N�g
        ui,//UI
        sound,//��
        stageData,//�X�e�[�W�̏����ʒu�␧������
        objectAddData//�I�u�W�F�N�g�̒ǉ����
    };
protected:
    /// <summary>
    /// �������Ŏg��CSV�t�@�C���̃p�X������
    /// </summary>
    /// <param name="fileKind">�~�����t�@�C���̎��</param>
    /// <returns>�������Ŏg��CSV�t�@�C���̃p�X</returns>
   static std::string GetInitCsvFilePass(AssetList fileKind);
   /// <summary>
   /// �������Ŏg��Json�t�@�C���̃p�X������
   /// </summary>
   /// <param name="fileKind">�~�����t�@�C���̎��</param>
   /// <returns>�������Ŏg��Json�t�@�C���̃p�X</returns>
   static std::string GetInitJsonFilePass(AssetList fileKind);
   /// <summary>
   /// �ǂݎ�����t�@�C������asset�ꗗ��Vector�Ɉڂ��Ă���
   /// </summary>
   /// <param name="fileLoader">�ǂݎ�����t�@�C��</param>
   std::vector<std::string> GetAssetListJson( JsonFileLoader* const fileLoader);
   //csv�t�@�C���܂ł̃p�X
   static std::string const initCSVFilePass;
   //json�t�@�C���܂ł̃p�X
   static std::string const initJSONFilePass;
private:
    //�������t�@�C���̖��O
    static std::string const initFileNames[];
};