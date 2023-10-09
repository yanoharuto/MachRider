#pragma once
#include <string>
#include <unordered_map>

class AssetManager abstract
{
public:
    enum class AssetList;
    AssetManager() {};
    virtual ~AssetManager() {};

    enum class AssetList
    {
        camera,
        effect,
        object,
        ui,
        sound,
        stageData,
        objectAddData
    };
protected:
    /// <summary>
    /// 初期化で使うファイルのパスを所得
    /// </summary>
    /// <param name="fileKind">欲しいファイルの種類</param>
    /// <returns></returns>
   static std::string GetInitFilePass(AssetList fileKind);
private:
    //初期化ファイルの名前
    static std::string const initFileNames[];
    //csvファイルまでのパス
    static std::string const initCSVFilePass;
    //jsonファイルまでのパス
    static std::string const initJSONFilePass;
};