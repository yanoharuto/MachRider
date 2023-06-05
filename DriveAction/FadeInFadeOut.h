#pragma once
#include "FadeMode.h"
/// <summary>
/// 場面の切り替えをするよ
/// </summary>
class FadeInFadeOut
{
public:
    /// <summary>
    /// フェードインフェードアウトをする
    /// </summary>
    FadeInFadeOut();
    ~FadeInFadeOut();
    /// <summary>
    /// フェードインの更新
    /// </summary>
    void FadeIn();
    /// <summary>
    /// フェードアウトの準備
    /// </summary>
    void FadeOutStart();
    /// <summary>
    /// フェードインの準備
    /// </summary>
    void FadeInStart();
    /// <summary>
    /// フェードアウトの更新
    /// </summary>
    void FadeOut();
    /// <summary>
    /// 今何の作業中か
    /// </summary>
    /// <returns></returns>
    FadeMode GetFadeMode();
    /// <summary>
    /// アウト中なら白くなる　インなら周りのモデルとかが見える
    /// </summary>
    void Draw();
private:
    //高いほど白くなるよ
    float fadeValue = 0;
    //フェードアウトする速度
    const float fadeSpeed = 10.0f;
    //今何の作業しているか
    FadeMode fadeMode;
};

