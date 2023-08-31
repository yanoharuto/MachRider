#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "EditObjectData.h"
#include "InitObjKind.h"

using namespace ObjectInit;
/// <summary>
/// 編集したものをCSVファイルに保存する
/// </summary>
class EditDataSaver
{
public:
    /// <summary>
    /// 編集したものをCSVファイルに保存する
    /// </summary>
    EditDataSaver() {};

    ~EditDataSaver() {};
    /// <summary>
    /// 編集した情報を保存する
    /// </summary>
    /// <param name="editData">編集した情報を纏めたVector</param>
    /// <param name="editObjKind">編集した情報</param>
    void SaveEditData(std::vector<PlacementData> editData,InitObjKind editObjKind)const;
private:
    /// <summary>
    /// 編集した情報を保存する
    /// </summary>
    /// <param name="editData">編集した情報</param>
    /// <param name="saveFileName">保存するファイル</param>
    void SaveEditData(PlacementData editData,std::string saveFileName)const;
    //プレイヤーの配置情報の保存先ファイル
    const std::string playerSaveFileName = "playerData(1).csv";
    //収集アイテムの配置情報の保存ファイル
    const std::string collectSaveFileName = "collectData(1).csv";
    //敵の配置情報の保存ファイル
    const std::string enemySaveFileName = "enemyData(1).csv";
};