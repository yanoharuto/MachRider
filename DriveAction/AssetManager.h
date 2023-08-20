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
    /// 描画モデルハンドル供給準備
    /// </summary>
    AssetManager();
    /// <summary>
    /// 各モデルの情報をデリート
    /// </summary>
    ~AssetManager();
    /// <summary>
    /// modelをロードして渡す
    /// </summary>
    /// <param name="assetPass"></param>
    /// <returns>すでにロードしてたら複製</returns>
    int Get3DModelAssetHandle(std::string assetPass);
private :

    //modelのアドレスを貰うとモデルハンドルを返す
    static std::map<std::string, int> assetMap;
};