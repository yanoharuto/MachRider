#pragma once
#include <vector>
#include "document.h"
/// <summary>
/// Json�t�@�C���ǂݎ��N���X
/// </summary>
class JsonFileLoader
{
public:
    /// <summary>
    /// Json�`���̃t�@�C�����J��
    /// </summary>
    /// <param name="filePass">�J�������t�@�C��</param>
    /// <param name="schemaFilePass">�J���t�@�C����Schema</param>
    JsonFileLoader(std::string filePass,std::string schemaFilePass);
    /// <summary>
    /// Schema�ƊJ�������t�@�C�����K�����Ă���Ȃ�
    /// </summary>
    /// <returns>�K�������Ȃ�True</returns>
    bool IsAccept()const;
    /// <summary>
    /// float�^
    /// </summary>
    /// <param name="dataName">�ǂݎ�肽���f�[�^</param>
    /// <returns>��肽���f�[�^</returns>
    float GetLoadFloat(std::string dataName)const;
    /// <summary>
    /// �K�v�ȃf�[�^�������ǂݎ��
    /// </summary>
    /// <param name="dataName">�ǂݎ�肽���f�[�^�̖��O</param>
    /// <returns>��肽���f�[�^</returns>
    std::string GetLoadString(std::string dataName)const;
private:
    //Schema�ƊJ�������t�@�C�����K�����Ă���Ȃ�
    bool isAccept;
    //�ǂݎ����
    rapidjson::Document loadDoc;
};