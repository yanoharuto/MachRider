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

    int GetStageNum()const;
private:
    //ステージ番号
    int stageNum;
    //選択しているステージだけ強調表示
    const float selectSizeCoefficient = 1.4f;
    //選んでいるステージの名前を表示
    UIData stageNameData;
    //ステージを決定するときのボタンを表示
    UIData selectButtonData;
};

