#pragma once
#include "StageDataEditor.h"
#include <unordered_map>
#include <vector> 
/// <summary>
/// 敵の編集クラス
/// </summary>
class EnemyDataEditor :
    public StageDataEditor
{
public:
    /// <summary>
/// 敵の編集クラス
/// </summary>
    EnemyDataEditor(InitObjKind enemyKind);
private:
    //読み込む配置情報の書いてあるファイルのパス
    static const std::string loadEditFilePath;
};