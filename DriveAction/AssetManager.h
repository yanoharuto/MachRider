#pragma once
#include <string>
#include <map>

/// <summary>
/// ���f���n���h��������
/// </summary>
class AssetManager final
{
public:
    /// <summary>
    /// �`�惂�f���n���h����������
    /// </summary>
    AssetManager();
    /// <summary>
    /// �e���f���̏����f���[�g
    /// </summary>
    ~AssetManager();
    /// <summary>
    /// model�����[�h���ēn��
    /// </summary>
    /// <param name="assetPass"></param>
    /// <returns>���łɃ��[�h���Ă��畡��</returns>
    int Get3DModelAssetHandle(std::string assetPass);
private :

    //model�̃A�h���X��Ⴄ�ƃ��f���n���h����Ԃ�
    static std::map<std::string, int> assetMap;
};