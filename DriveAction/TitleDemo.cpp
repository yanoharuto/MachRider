#include "TitleDemo.h"
#include "ActorControllerManager.h"
#include "DemoCarController.h"
#include "Timer.h"
#include "StageObjectController.h"
#include "Utility.h"
#include "FirstPositionGetter.h"
#include "TitleCamera.h"
#include "CollectController.h"
#include "ShadowMap.h"
#include "EnemyGenerator.h"
#include "EffekseerForDXLib.h"
#include "ReusableTimer.h"
/// <summary>
/// タイトル画面の裏で車を走らせる
/// </summary>
TitleDemo::TitleDemo()
{
    //車とか収集アイテムなど動かす
    manager = new ActorControllerManager();
    manager->AddActorController(new CollectController());
    manager->AddActorController(new StageObjectController());
    initTimer = new ReusableTimer(initTime);
    demoCarController = new DemoCarController(demoCarFirstPos, demoCarFirstDir);

    manager->AddActorController(demoCarController);
    demoObserver = demoCarController->CreateCarObserver();
    shadowMap = new ShadowMap(demoObserver);
    camera = new TitleCamera(demoObserver);
}

TitleDemo::~TitleDemo()
{
    SAFE_DELETE(initTimer);
    SAFE_DELETE(manager);
    SAFE_DELETE(camera);
    SAFE_DELETE(shadowMap);
}
/// <summary>
/// 
/// </summary>
void TitleDemo::Update()
{
    manager->Update();
    shadowMap->SetShadowMapErea();
    camera->Update();
    //エフェクトの位置を現在のカメラに合わせる
    Effekseer_Sync3DSetting();
    UpdateEffekseer3D();
    UpdateEffekseer2D();
    //タイマーが切れたらデモを最初からにする
    if (initTimer->IsOverLimitTime())
    {
        if (isAValueIncrement)//フェードアウト
        {
            fadeValue += fadeSpeed;

            if (fadeValue > MAX1BYTEVALUE)
            {
                isAValueIncrement = false;
                demoCarController->InitPosition();
            }
        }
        else if (!isAValueIncrement)//フェードイン
        {
            fadeValue -= fadeSpeed;

            if (fadeValue < 0)
            {
                initTimer->Reuse();//タイマー再利用
                isAValueIncrement = true;
            }
        }
    }
}
/// <summary>
/// タイトル画面で走っている車と風景とエフェクトと影を描画
/// </summary>
void TitleDemo::Draw() const
{
    shadowMap->SetUP();
    manager->Draw();
    shadowMap->DrawEnd();
    manager->Draw();
    shadowMap->Use();

    DrawEffekseer3D();
    DrawEffekseer2D();
    
    if (initTimer->IsOverLimitTime())
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int> (fadeValue));//α値をいじる
        int colorValue = MAX1BYTEVALUE;
        DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(colorValue, colorValue, colorValue), true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//元に戻す
    }
}
