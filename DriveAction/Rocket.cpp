#include "Rocket.h"
#include "EffectManager.h"
#include "AssetManager.h"
#include "EffekseerForDXLib.h"
#include "ConflictManager.h"
#include "Utility.h"
#include "InitObjKind.h"
#include "SphereCollider.h"
#include "ObjectObserver.h"
//�������x
 const float Rocket::setFallingSpeed = 0.7f;
//�d��
 const float Rocket::gravityPower = 0.08f;
 //�R�������̓����蔻��̑傫��
 const float Rocket::setBurnRadius = 42.0f;
Rocket::Rocket(ObjectObserver* setObserver)
    :DamageObject(ObjectInit::bomber,setObserver)
{
    position = observer->GetSubPos();
    fallingSpeed = setFallingSpeed;
    tag = ObjectTag::damageObject;
    EffectManager::LoadEffect(bombExplosion);
    velocity = VGet(0, 0, 0);
    direction = VGet(1, 0, 0);
    onGround = false;
    collider = new SphereCollider(this);
}
/// <summary>
/// �������蔻��
/// </summary>
Rocket::~Rocket()
{
    StopEffekseer3DEffect(burnEffect);
    ConflictManager::EraceConflictObjInfo(collider);
    SAFE_DELETE(collider);
    SAFE_DELETE(observer);
}
/// <summary>
/// �X�V
/// </summary>
/// <param name="deltaTime"></param>
void Rocket::Update()
{
    //�n�ʂɂԂ���O�͗����Ă���
    if (!onGround)
    {
        position.y -= fallingSpeed;
        fallingSpeed += fallingSpeed * gravityPower;
        //�n�ʂɂԂ��肻���ɂȂ�������G�t�F�N�g���o��
        if (position.y < 0.0f)
        {
            if (burnEffect == -1)
            {
                burnEffect = EffectManager::GetPlayEffect3D(bombExplosion);
                float positionY = position.y - radius;
                SetPosPlayingEffekseer3DEffect(burnEffect, position.x, positionY, position.z);
                radius = setBurnRadius;
                onGround = true;
            }
        }
    }
    else
    {
        //�G�t�F�N�g��`�悵�I�������I��
        if (IsEffekseer3DEffectPlaying(burnEffect) == -1)
        {
            aliveFlag = false;
            burnEffect = -1;
        }
    }
    UpdatePosition();
}
/// <summary>
/// �Փˌ�̏���
/// </summary>
void Rocket::ConflictProccess(ConflictExamineResultInfo resultInfo)
{
    if (resultInfo.tag != ObjectTag::damageObject)
    {
        if (burnEffect==-1)
        {
            //�_���[�W����̂���I�u�W�F�N�g�ȊO�ɏՓˌ�G�t�F�N�g���o��
            burnEffect = EffectManager::GetPlayEffect3D(bombExplosion);
            float positionY = position.y - radius;
            SetPosPlayingEffekseer3DEffect(burnEffect, position.x, positionY, position.z);
            //�����蔻��𔚔��Ɠ������炢�ɂ���
            radius = setBurnRadius;
            onGround = true;
        }
    }
}