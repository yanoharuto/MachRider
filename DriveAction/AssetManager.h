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
    /// model�����[�h���ēn��
    /// </summary>
    /// <param name="assetPass"></param>
    /// <returns>���łɃ��[�h���Ă��畡��</returns>
    static int Get3DModelAssetHandle(std::string assetPass);
private :
    AssetManager();
    ~AssetManager();
    //model�̃A�h���X��Ⴄ�ƃ��f���n���h����Ԃ�
    static std::map<std::string, int> assetMap;
};