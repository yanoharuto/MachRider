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
    /// <param name="dataKind"></param>
    /// <returns></returns>
    static std::vector<EditArrangementData> GetInitData(Object::ObjectTag tag);
    /// <summary>
    /// CSVファイルからステージに配置するための情報を所得
    /// </summary>
    /// <param name="fileName"></param>
    static std::vector<EditArrangementData> CSVConvertFirstData(std::string fileName);
private:

};