#pragma once
#include <string>
#include <map>

/// <summary>
/// �A�Z�b�g�̕����Ƃ�����p
/// </summary>
class AssetManager final
{
public:

    /// <summary>
    /// model�����[�h���ĕ����ł���悤�ɂ���
    /// </summary>
    /// <param name="assetPass"></param>
    /// <returns></returns>
    static int Get3DModelAssetHandle(std::string assetPass);
private :
    AssetManager();
    ~AssetManager();
    //model�̃A�h���X��Ⴄ�ƃ��f���n���h����Ԃ�
    static std::map<std::string, int> assetMap;
};