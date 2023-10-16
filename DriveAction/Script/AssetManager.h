#pragma once
#include <vector>
#include <string>
#include <unordered_map>
class JsonFileLoader;
/// <summary>
/// アセットまでのパスを共有できるように親クラスに渡す
/// </summary>
class AssetManager abstract
{
public:
    enum class AssetList;
    /// <summary>
    /// デフォルトコンストラクタ
    /// </summary>
    AssetManager() {};
    virtual ~AssetManager() {};

    enum class AssetList
    {
        camera,//カメラ
        effect,//エフェクト
        object,//オブジェクト
        ui,//UI
        sound,//音
        stageData,//ステージの初期位置や制限時間
        objectAddData//オブジェクトの追加情報
    };
protected:
    /// <summary>
    /// 初期化で使うCSVファイルのパスを所得
    /// </summary>
    /// <param name="fileKind">欲しいファイルの種類</param>
    /// <returns>初期化で使うCSVファイルのパス</returns>
   static std::string GetInitCsvFilePass(AssetList fileKind);
   /// <summary>
   /// 初期化で使うJsonファイルのパスを所得
   /// </summary>
   /// <param name="fileKind">欲しいファイルの種類</param>
   /// <returns>初期化で使うJsonファイルのパス</returns>
   static std::string GetInitJsonFilePass(AssetList fileKind);
   /// <summary>
   /// 読み取ったファイルからasset一覧をVectorに移していく
   /// </summary>
   /// <param name="fileLoader">読み取ったファイル</param>
   std::vector<std::string> GetAssetListJson( JsonFileLoader* const fileLoader);
   //csvファイルまでのパス
   static std::string const initCSVFilePass;
   //jsonファイルまでのパス
   static std::string const initJSONFilePass;
private:
    //初期化ファイルの名前
    static std::string const initFileNames[];
};