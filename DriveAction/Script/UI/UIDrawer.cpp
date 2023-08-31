#include "UIDrawer.h"
#include "DxLib.h"
#include "Utility.h"

//横幅
 int UIDrawer::screenWidth = SCREEN_WIDTH;
//縦幅
 int UIDrawer::screenHeight = SCREEN_HEIGHT;
//横幅比率
 float UIDrawer:: widthRaito = 0.0f;
//縦幅比率
 float UIDrawer:: heightRaito = 0.0f;
 //画面の大きさ比率
 float UIDrawer::UIDrawer::screenSizeRaito = 1.0f;
 /// <summary>
 /// drawRotaGraphを画面のサイズに合わせて出来るようにする
 /// </summary>
 /// <param name="data">描画したいUI</param>
 /// <param name="gHIndex">描画したいUIの添え字</param>
 /// <param name="angle">UIを傾ける</param>
 /// <param name="trans">透明度有効フラグ</param>
 /// <returns>失敗するとfalse</returns>
bool UIDrawer::DrawRotaUI(UIData data, int gHIndex, float angle, bool trans)
{
    gHIndex = gHIndex % data.dataHandle.size();
   int success = DrawRotaGraph(data.x * widthRaito, data.y * heightRaito, data.size * screenSizeRaito, angle, data.dataHandle[gHIndex], trans);
   return success != -1;
}
/// <summary>
/// スクリーンの想定の大きさとの差を倍率で渡す
/// </summary>
/// <returns></returns>
float UIDrawer::GetScreenRaito()
{
    return screenSizeRaito;
}
/// <summary>
/// 画面サイズ所得する
/// </summary>
UIDrawer::UIDrawer()
{
    int color;
    //画面サイズ
    GetScreenState(&screenWidth, &screenHeight, &color);
    //横幅比率
    widthRaito = screenWidth / SCREEN_WIDTH;
    //縦幅比率
    heightRaito = screenHeight / SCREEN_HEIGHT;
    //HDの大きさと比較した大きさ
    screenSizeRaito = (screenWidth + screenHeight) / (SCREEN_WIDTH + SCREEN_HEIGHT);
}