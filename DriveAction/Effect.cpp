#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Utility.h"
//エフェクトの初期化
int Effect_Initialize() {
    // DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
    // Effekseerを使用するには必ず設定する。
    SetUseDirect3DVersion(DX_DIRECT3D_11);
    //Effekseerを初期化する
    if (Effekseer_Init(8000) == -1)
    {
        return -1;
    }
    // フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
    // Effekseerを使用する場合は必ず設定する。
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
    // DXライブラリのデバイスロストした時のコールバックを設定する。
    // ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
    // ただし、DirectX11を使用する場合は実行する必要はない。
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();
    // Zバッファを有効にする。
    // Effekseerを使用する場合、2DゲームでもZバッファを使用する。
    SetUseZBuffer3D(TRUE);
    // Zバッファへの書き込みを有効にする。
    // Effekseerを使用する場合、2DゲームでもZバッファを使用する。
    SetWriteZBuffer3D(TRUE);

    Effekseer_Set2DSetting(SCREEN_WIDTH,SCREEN_HEIGHT);
    return 0;
}
//エフェクトの更新
void Effect_Update() 
{
}
//エフェクトの描写
void Effect_Draw() {


}
//エフェクトの終了処理
void Effect_Finalize() {

    // Effekseerを終了する。
    Effkseer_End();
}