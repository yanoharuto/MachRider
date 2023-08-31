#pragma once
#include "UIManager.h"

/// <summary>
/// タイトル画面でステージ選ぶ時に使う
/// </summary>
class StageSelect
{
public:
    /// <summary>
    /// ステージごとに必要なアセットのアドレスが
    /// 書いてあるファイルの
    /// アドレスが書いてあるファイルを読み込む
    /// </summary>
    /// <returns></returns>
    StageSelect();
    /// <summary>
    /// 遊ぶステージ変更するときに使う
    /// </summary>
    /// <param name="next">次のステージTrue前のステージかfalse</param>
    void Update();
    /// <summary>
    /// 現在選んでいるステージを表示
    /// </summary>
    void Draw()const;
    /// <summary>
    /// ステージの番号所得
    /// </summary>
    /// <returns>今選択しているステージの番号</returns>
    int GetSelectStageNum()const;
private:
    //ステージ番号
    int selectStageNum;
    //選択しているステージだけ強調表示
    const float selectSizeCoefficient = 1.4f;
    //選んでいるステージの名前を表示
    UIData stageNameUI;
    //ステージを決定するときのボタンを表示
    UIData selectButtonUI;
};

