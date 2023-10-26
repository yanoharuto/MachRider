#include <iostream>
#include <cassert>
#include <vector>
#include "EditDataSaver.h"
#include "Utility.h"
#include "writer.h"
#include "StageDataEditor.h"


EditDataSaver::EditDataSaver()
{
}
/// <summary>
/// 編集データを保存する
/// </summary>
EditDataSaver::~EditDataSaver()
{
    //プレイヤーの編集データを保存する
    SaveEditDataForCSV(playerPlaceData,playerSaveFileName);
    SaveEditDataForJSON(playerPlaceData,playerSaveFileName);
    //収集アイテムの編集データを保存する
    SaveEditDataForCSV(collectPlaceData, collectSaveFileName);
    SaveEditDataForJSON(collectPlaceData, collectSaveFileName);
    //敵の編集データを保存する
    SaveEditDataForCSV(enemyPlaceData, enemySaveFileName);
    SaveEditDataForJSON(enemyPlaceData, enemySaveFileName);
}
/// <summary>
/// 編集した情報を保存する
/// </summary>
/// <param name="editData">編集した情報を纏めたVector</param>
/// <param name="editObjKind">編集した情報</param>
void EditDataSaver::SaveEditData(std::weak_ptr<StageDataEditor> editor)
{
    std::string saveFileName;
    //保存したい情報
    auto placeVector = editor.lock()->GetPlacementDataVector();
    //種類ごとに保存したい情報を分ける
    switch (editor.lock()->GetEditObjectKind())
    {
    case InitObjKind::player:
        playerPlaceData.insert(playerPlaceData.end(), placeVector.begin(), placeVector.end());
        break;
    case InitObjKind::collect:
        collectPlaceData.insert(collectPlaceData.end(), placeVector.begin(), placeVector.end());
        break;
    default:
        enemyPlaceData.insert(enemyPlaceData.end(), placeVector.begin(),placeVector.end());
        break;
    }
}

/// <summary>
/// 編集した情報を保存する
/// </summary>
/// <param name="editData">編集した情報</param>
/// <param name="saveFileName">保存するファイル</param>
void EditDataSaver::SaveEditDataForCSV(std::vector<PlacementData> editData, std::string saveFileName) const
{
    //配置した収集アイテムを保存
    for (int i = 0; i < CONTAINER_GET_SIZE(editData); i++)
    {
        std::ofstream writing_file;
        auto data = editData[i];
        // ファイルを開いて
        writing_file.open(editFilePath + saveFileName + Utility::CSV_FILE, std::ios::app);
        //区切り文字
        std::string colon = ",";
        //オブジェクトの種類と
        writing_file << std::to_string(data.objKind) + colon << std::endl;
        //何番目の収集アイテムの時か
        writing_file << std::to_string(data.collectNum) + colon << std::endl;
        //位置
        writing_file << std::to_string(data.posX) + colon << std::endl;
        writing_file << std::to_string(data.posZ) + colon << std::endl;
        //向き
        writing_file << std::to_string(data.dirX) + colon << std::endl;
        writing_file << std::to_string(data.dirZ) + colon << std::endl;
        writing_file.close();
    }
}
/// <summary>
/// 引数の編集情報をJsonに保存できるようにする
/// </summary>
/// <param name="editData">編集情報</param>
/// <param name="allocator">編集のために必要なallocator</param>
/// <returns>Jsonに保存できるようにしたもの</returns>
rapidjson::Value EditDataSaver::GetEditPlaceData(PlacementData editData, rapidjson::Document::AllocatorType& allocator) const
{
    //編集内容をメンバに登録
    rapidjson::Value objValue;
    objValue.SetObject();
    objValue.AddMember("objNum", editData.objKind, allocator);
    objValue.AddMember("collectNum", editData.collectNum, allocator);
    objValue.AddMember("x", editData.posX, allocator);
    objValue.AddMember("z", editData.posZ, allocator);
    objValue.AddMember("dirX", editData.dirX, allocator);
    objValue.AddMember("dirZ", editData.dirZ, allocator);
    return objValue;
}
/// <summary>
/// Json形式で保存する
/// </summary>
/// <param name="editData">編集したい情報纏め</param>
/// <param name="saveFileName">保存先のファイルの名前</param>
void EditDataSaver::SaveEditDataForJSON(std::vector<PlacementData> editData, std::string saveFileName)const
{
    //ドキュメント作成
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //jsonに書き込む準備
    //配列にして詰め込む
    rapidjson::Value myArray(rapidjson::kArrayType);
    //配置した収集アイテムを保存
    for (int i = 0; i < CONTAINER_GET_SIZE(editData); i++)
    {
        myArray.PushBack(GetEditPlaceData(editData[i], allocator),allocator);
    }
    //編集内容をsaveFileNameのファイルに書き込む
    jsonDoc.AddMember("arrangeData", myArray, allocator);
    //ファイルの中身を全部消した状態で書き込む
    saveFileName = editFilePath + saveFileName + Utility::JSON_FILE;
    std::ofstream ofs(saveFileName);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    jsonDoc.Accept(writer);
}