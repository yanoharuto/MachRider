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
    ~TitleHiScore();
    /// <summary>
    /// 現在選ばれているステージのハイスコア表示
    /// </summary>
    /// <param name="num"></param>
    void Draw()const;

private:
    //各ステージのハイスコア
    UIData hiScoreUI;
};

