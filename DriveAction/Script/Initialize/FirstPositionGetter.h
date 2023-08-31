#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "DxLib.h"
#include "StageDataManager.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
#include "Object.h"
using namespace InitStage;
/// <summary>
/// 初期位置をファイルからとってきて変換する
/// </summary>
class FirstPositionGetter
{
public:
    /// <summary>
    /// 初期位置を渡す
    /// </summary>
    /// <param name="dataKind">オブジェクトの種類によって読み込む情報を変更する</param>
    /// <returns>そのオブジェクトの位置をまとめたコンテナ</returns>
    static std::vector<PlacementData> GetPlaceData(Object::ObjectTag tag);
    /// <summary>
    /// CSVファイルからステージに配置するための情報を所得
    /// </summary>
    /// <param name="fileName">配置情報までのパス</param>
    /// /// <returns>CSVファイルからステージに配置するための情報</returns>
    static std::vector<PlacementData> CSVConvertFirstData(std::string fileName);
    /// <summary>
    /// CSVファイルからステージに配置するための情報を所得
    /// </summary>
    /// <param name="fileName">配置情報までのパス</param>
    /// <param name="kind">所得したい配置物の種類</param>
    /// <returns>CSVファイルからステージに配置するための情報</returns>
    static std::vector<PlacementData> CSVConvertFirstData(std::string fileName,ObjectInit::InitObjKind kind);
};