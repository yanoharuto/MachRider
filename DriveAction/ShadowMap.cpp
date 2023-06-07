#include "ShadowMap.h"
#include "ObjectObserver.h"

#include "ObjectSubject.h"
#include "RacerManager.h"

ShadowMap::ShadowMap(RacerManager* racerManager)
{
    //�����̌���
    SetShadowMapLightDirection(shadowMap, VGet(0.1f, -1, 0));
    SetShadowMapDrawArea(shadowMap, DrawAreaMinPos, DrawAreaMaxPos);
    playerObserber = new ObjectObserver(racerManager->GetPlayerSubject(0));;
}

ShadowMap::~ShadowMap()
{
    DeleteShadowMap(shadowMap);
}
/// <summary>
/// �e�̕`��͈͂̕ύX
/// </summary>
/// <param name="objInfo">�����̍��W�𒆐S�ɂ���</param>
void ShadowMap::SetShadowMapErea()
{
    VECTOR minPos = VAdd(playerObserber->GetSubjectPos(), DrawAreaMinPos);
    VECTOR maxPos = VAdd(playerObserber->GetSubjectPos(), DrawAreaMaxPos);
    SetShadowMapDrawArea(shadowMap, minPos, maxPos);
}
/// <summary>
/// ���ꂩ��`�悷��e�̏���
/// </summary>
void ShadowMap::SetUP()
{
    ShadowMap_DrawSetup(shadowMap);
}
/// <summary>
/// �e��`�悷��̏I��
/// </summary>
void ShadowMap::DrawEnd()
{
    //�V���h�E�}�b�v�ւ̕`����I��
    ShadowMap_DrawEnd();
    SetUseShadowMap(0, shadowMap);
}
/// <summary>
/// �������񂾃V���h�E�}�b�v���g��
/// </summary>
void ShadowMap::Use()
{
    SetUseShadowMap(0, -1);
}
