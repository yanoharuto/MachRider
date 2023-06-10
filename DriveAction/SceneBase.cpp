#include "SceneBase.h"
#include "FadeInFadeOut.h"
#include "Clock.h"
#include "Utility.h"
#include "SceneFlowBase.h"
#include "SoundPlayer.h"
#include "InitActor.h"
#include "EffectManager.h"
#include "UIManager.h"
SceneBase::SceneBase(SceneType _SceneType)
{
    nowSceneType = _SceneType;

    clock = std::make_unique<Clock*>(new Clock());
    uiManager = std::make_unique<UIManager*>(new UIManager());
    initActor = std::make_unique<InitActor* >(new InitActor());
    soundPlayer = std::make_unique <SoundPlayer*> (new SoundPlayer());
    effectManager = std::make_unique <EffectManager*>(new EffectManager());
}

SceneBase::~SceneBase()
{
    
    SAFE_DELETE(sceneFlow);
}

SceneType SceneBase::Update()
{
    //ƒV[ƒ“‚²‚Æ‚Ìˆ—
    sceneFlow->Update();
    if (sceneFlow->GetIsEndProccess())//ˆ—‚ªI‚í‚Á‚½‚ç
    {
        return sceneFlow->GetNextSceneType();
    }
    (*clock)->Update();
    return nowSceneType;
}
void SceneBase::Draw()
{
    sceneFlow->Draw();
}
void SceneBase::DeleteUniquePtr()
{
    SAFE_UNIQUE_DELETE(uiManager);
    SAFE_UNIQUE_DELETE(initActor);
    SAFE_UNIQUE_DELETE(soundPlayer);
    SAFE_UNIQUE_DELETE(effectManager);
    SAFE_UNIQUE_DELETE(clock);
};
