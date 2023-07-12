#pragma once
#include "UIManager.h"
#include "StageDataPass.h"
/// <summary>
/// タイトル画面でステージ選ぶ時に使う
/// </summary>
class StageSelect :public StageDataPass
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
private:
    //ステージ番号
    int stageNum;
    //選んでいるステージの名前を表示
    UIData stageNameData;
    //ステージを決定するときのボタンを表示
    UIData selectButtonData;
};

