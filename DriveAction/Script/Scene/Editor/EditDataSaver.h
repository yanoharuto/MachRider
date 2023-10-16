#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <rapidjson.h>
#include <document.h>
#include <ostreamwrapper.h>
#include "EditObjectData.h"
#include "InitObjKind.h"
class StageDataEditor;
using namespace ObjectInit;
/// <summary>
/// 編集したものをファイルに保存する
/// </summary>
class EditDataSaver
{
public:
    EditDataSaver();
    ~EditDataSaver();
    /// <summary>
    /// 編集した情報を保存する
    /// </summary>
    /// <param name="editor">編集内容を渡すクラス</param>
    void SaveEditData(std::weak_ptr<StageDataEditor> editor);
private:
    /// <summary>
    /// 編集した情報を保存する
    /// </summary>
    /// <param name="editData">編集した情報</param>
    /// <param name="saveFileName">保存するファイル</param>
    void SaveEditDataForCSV(std::vector<PlacementData> editData,std::string saveFileName)const;
    /// <summary>
    /// 引数の編集情報をJsonに保存できるようにする
    /// </summary>
    /// <param name="editData">編集情報</param>
    /// <param name="allocator">編集のために必要なallocator</param>
    /// <returns>Jsonに保存できるようにしたもの</returns>
    rapidjson::Value GetEditPlaceData(PlacementData editData, rapidjson::Document::AllocatorType& allocator)const;
    /// <summary>
    /// Json形式で保存する
    /// </summary>
    /// <param name="editData">編集したい情報纏め</param>
    /// <param name="saveFileName">保存先のファイルの名前</param>
    void SaveEditDataForJSON(std::vector<PlacementData> editData, std::string saveFileName)const;
    //プレイヤーの配置情報の保存先ファイル
    const std::string playerSaveFileName = "playerData(1)";
    //収集アイテムの配置情報の保存ファイル
    const std::string collectSaveFileName = "collectData(1)";
    //敵の配置情報の保存ファイル
    const std::string enemySaveFileName = "enemyData(1)";
    //json形式
    const std::string jsonFile = ".json";
    //ｃｓｖ形式
    const std::string csvFile = ".csv";
    //プレイヤー編集位置情報
    std::vector<PlacementData> playerPlaceData;
    //敵編集位置情報
    std::vector<PlacementData> enemyPlaceData;
    //収集アイテム位置情報
    std::vector<PlacementData> collectPlaceData;
};