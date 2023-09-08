#include "TitleObject.h"
#include "ActorControllerManager.h"
#include "TitleCarController.h"
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
#include "CollectItemObserver.h"

/// <summary>
/// �^�C�g����ʂ̗��ŎԂ𑖂点��
/// </summary>
TitleObject::TitleObject()
{
    //�������^�C�}�[
    initTimer = std::make_shared<ReusableTimer>(initTime);
    //�^�C�g���V�[���̎�
    titleCarController = std::make_shared <TitlteCarController>(demoCarFirstPos, demoCarFirstDir,initTimer);
    demoObserver = titleCarController->CreateCarObserver();
    //���W�A�C�e��
    std::shared_ptr<CollectItemController> collectController = std::make_shared<CollectItemController>();
    collectItemObserver = std::make_shared<CollectItemObserver>(collectController);
    //�Ǘ��N���X�ɓn��
    manager = new ActorControllerManager(collectItemObserver);
    manager->AddActorController(collectController);
    manager->AddActorController(titleCarController);
    //���L��ɊJ��
    collectController.reset();
    
    shadowMap = new ShadowMap(demoObserver);
    camera = new TitleCamera(demoObserver);
}
/// <summary>
/// �����������^�C�}�[�⑖���Ă���ԂȂǂ̉��
/// </summary>
TitleObject::~TitleObject()
{
    initTimer.reset();
    SAFE_DELETE(manager);
    SAFE_DELETE(camera);
    SAFE_DELETE(shadowMap);
}
/// <summary>
/// �Ԃ�X�e�[�W�I���̍X�V
/// </summary>
void TitleObject::Update()
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

            if (fadeValue > MAX1BYTEVALUE)//���E�܂ŗ����玟�͌��炵�Ă���
            {
                isAValueIncrement = false;
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
void TitleObject::Draw() const
{
    //�e�ƃI�u�W�F�N�g��`��
    shadowMap->SetUPDrawShadow();
    manager->Draw();
    shadowMap->EndDrawShadow();
    manager->Draw();
    shadowMap->Use();

    DrawEffekseer3D();
    DrawEffekseer2D();
    //��莞�Ԃ�����ƃt�F�[�h�C���t�F�[�h�A�E�g
    if (initTimer->IsOverLimitTime())
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int> (fadeValue));//���l��������
        int colorValue = MAX1BYTEVALUE;
        DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(colorValue, colorValue, colorValue), true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//���ɖ߂�
    }
}