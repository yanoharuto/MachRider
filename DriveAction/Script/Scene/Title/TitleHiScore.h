#pragma once
#include "NumUI.h"
/// <summary>
/// タイトルで表示するハイスコア
/// </summary>
class TitleHiScore:private NumUI
{
public:
    /// <summary>
    /// タイトルで表示するハイスコア
    /// </summary>
    TitleHiScore();
    /// <summary>
    /// 特になし
    /// </summary>
    ~TitleHiScore() {};
    /// <summary>
    /// 現在選ばれているステージのハイスコア表示
    /// </summary>
    void Draw()const;

private:
    //各ステージのハイスコア
    UIData hiScoreUI;
};

