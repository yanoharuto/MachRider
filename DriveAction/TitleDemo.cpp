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
/// �^�C�g����ʂ̗��ŎԂ𑖂点��
/// </summary>
TitleDemo::TitleDemo()
{
    //�ԂƂ����W�A�C�e���ȂǓ�����
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
    //�G�t�F�N�g�̈ʒu�����݂̃J�����ɍ��킹��
    Effekseer_Sync3DSetting();
    UpdateEffekseer3D();
    UpdateEffekseer2D();
    //�^�C�}�[���؂ꂽ��f�����ŏ�����ɂ���
    if (initTimer->IsOverLimitTime())
    {
        if (isAValueIncrement)//�t�F�[�h�A�E�g
        {
            fadeValue += fadeSpeed;

            if (fadeValue > MAX1BYTEVALUE)
            {
                isAValueIncrement = false;
                demoCarController->InitPosition();
            }
        }
        else if (!isAValueIncrement)//�t�F�[�h�C��
        {
            fadeValue -= fadeSpeed;

            if (fadeValue < 0)
            {
                initTimer->Reuse();//�^�C�}�[�ė��p
                isAValueIncrement = true;
            }
        }
    }
}
/// <summary>
/// �^�C�g����ʂő����Ă���Ԃƕ��i�ƃG�t�F�N�g�Ɖe��`��
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
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int> (fadeValue));//���l��������
        int colorValue = MAX1BYTEVALUE;
        DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(colorValue, colorValue, colorValue), true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//���ɖ߂�
    }
}
