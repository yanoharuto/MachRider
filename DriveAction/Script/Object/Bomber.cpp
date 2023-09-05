#include "Bomber.h"
#include "EffectManager.h"
#include "AssetManager.h"
#include "EffekseerForDXLib.h"
#include "ConflictManager.h"
#include "Utility.h"
#include "InitObjKind.h"
#include "SphereHitChecker.h"
#include "ConflictProcessor.h"
#include "ObjectObserver.h"
//�������x
 const float Bomber::setFallingSpeed = 0.3f;
//�d��
 const float Bomber::gravityPower = 0.1f;
/// <summary>
/// �ォ�牺�ɗ��Ƃ����e
/// </summary>
Bomber::Bomber(std::unique_ptr<ObjectObserver> setObserver)
    :DamageObject(ObjectInit::bomber,std::move(setObserver))
{
    //�����ʒu�͔��˂����L�����̈ʒu�ɏ���
    position = observer->GetSubjectPos();
    //�������Z�b�g
    fallingSpeed = setFallingSpeed;
    //�G�t�F�N�g
    EffectManager::LoadEffect(bombExplosion);
    //�����Ƒ��x
    velocity = VGet(0, 0, 0);
    direction = VGet(1, 0, 0);
    //�����蔻��
    collider = new SphereHitChecker(this);
    conflictProcessor = new ConflictProcessor(this);
    ConflictManager::AddConflictProcessor(conflictProcessor, collider);
}
/// <summary>
/// �������蔻��폜
/// </summary>
Bomber::~Bomber()
{
    //�����蔻��폜
    EraceCollider();
    StopEffekseer3DEffect(burnEffect);
    observer.reset();
}
/// <summary>
/// �X�V
/// </summary>
/// <param name="deltaTime"></param>
void Bomber::Update()
{
    //�n�ʂɂԂ���O�͗����Ă���
    if (burnEffect == -1)
    {
        //���񂾂�������Ȃ��痎���Ă���
        position.y -= fallingSpeed;
        fallingSpeed += fallingSpeed * gravityPower;
        //�n�ʂɂԂ��肻���ɂȂ�������G�t�F�N�g���o��
        if (position.y < 0.0f)
        {
            burnEffect = EffectManager::GetPlayEffect3D(bombExplosion);
            float positionY = position.y - radius;
            SetPosPlayingEffekseer3DEffect(burnEffect, position.x, positionY, position.z);
        }
    }
    else
    {
        //�G�t�F�N�g��`�悵�I�������I��
        if (IsEffekseer3DEffectPlaying(burnEffect) == -1)
        {
            objState = dead;
        }
    }
}
/// <summary>
/// �Փˌ�̏���
/// </summary>
void Bomber::OnConflict(CollisionResultInfo resultInfo)
{
    if (resultInfo.tag != ObjectTag::damageObject && burnEffect == -1)
    {
        //�_���[�W����̂���I�u�W�F�N�g�ȊO�ɏՓˌ�G�t�F�N�g���o��
        burnEffect = EffectManager::GetPlayEffect3D(bombExplosion);
        float positionY = position.y - radius;
        SetPosPlayingEffekseer3DEffect(burnEffect, position.x, positionY, position.z);
        //���������̂��v���C���[�������瓖���蔻�����
        if (resultInfo.tag == player)
        {
            objState = activeEnd;
        }
    }
}
/// <summary>
/// �����蔻��폜
/// </summary>
void Bomber::EraceCollider()
{
    if (collider != nullptr)
    {
        ConflictManager::EraceConflictProcessor(conflictProcessor, collider);
        SAFE_DELETE(collider);
        SAFE_DELETE(conflictProcessor);
    }
}
