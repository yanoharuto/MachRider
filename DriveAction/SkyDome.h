#pragma once
#include "Object.h"
/// <summary>
/// スカイドーム
/// </summary>
class SkyDome final :public Object
{
public:
    /// <summary>
    /// modelのロードとタグ付け
    /// </summary>
    /// <returns></returns>
    SkyDome();
    //modelのデリート
    ~SkyDome();
    /// <summary>
    /// 回転させる
    /// </summary>
    void Update();
    /// <summary>
    /// modelの描画
    /// </summary>
    void Draw();

private:
    int modelHandle;
    float setSize = 4.0f;
    float rotaSpeed = 0.2f;
};

