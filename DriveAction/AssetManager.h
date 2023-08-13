#pragma once
#include <string>
#include <map>

/// <summary>
/// モデルハンドル供給役
/// </summary>
class AssetManager final
{
public:

    /// <summary>
    /// modelをロードして渡す
    /// </summary>
    /// <param name="assetPass"></param>
    /// <returns>すでにロードしてたら複製</returns>
    static int Get3DModelAssetHandle(std::string assetPass);
private :
    AssetManager();
    ~AssetManager();
    //modelのアドレスを貰うとモデルハンドルを返す
    static std::map<std::string, int> assetMap;
};