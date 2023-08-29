#pragma once
#include <string>
class StageDataEditor;
/// <summary>
/// 編集中の操作説明
/// </summary>
class EditManual
{
public:
    /// <summary>
    /// フォントサイズと表示位置の調整
    /// </summary>
    EditManual();
    /// <summary>
    /// 操作説明表示
    /// </summary>
    /// <param name="editor">今編集中か教えてもらう</param>
    void Draw(StageDataEditor* const editor);
private:
    //十字編集中
    const std::string selectCrossKeyAction="十字キー編集物変更";
    //十字選択中
    const std::string editCrossAction="十字キー編集物移動";
    //SpaceKey選択中
    const std::string selectSpaceKeyAction="spaceで編集開始";
    //SpaceKey編集中
    const std::string editSpaceKeyAction="spaceで配置";
    //DKey
    const std::string dKeyAction="Dで削除";
    //WKey
    const std::string wKeyAction="方向変更";
    //AKey
    const std::string aKeyAction="Aと十字でカメラ操作";
    //SKey
    const std::string sKeyAction="Sと十字で出てくる時期を変更";
    //表示位置の高さ
    int screenHeight;

    //描画する文字のサイズ
    const int fontSize = 24;
    //文字列の距離Y
    const int strBetweenY = 50;
    //文字列の距離X
    const int strBetweenX = 300;
};

