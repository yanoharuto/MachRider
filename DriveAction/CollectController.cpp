#include "CollectController.h"
#include "FirstPositionGetter.h"
#include "Coin.h"
#include "MiniMap.h"
#include "ObjectObserver.h"
#include "ObjectSubject.h"
#include "OriginalMath.h"
#include "Utility.h"

VECTOR CollectController:: nowActiveCollectItemPos;
/// <summary>
/// �R�C���̐ݒu
/// </summary>
CollectController::CollectController()
{
    auto getter = new FirstPositionGetter();
    auto challengeDataVec = getter->GetChallengeData();
    for (auto ite = challengeDataVec.begin(); ite != challengeDataVec.end(); ite++)
    {
        Coin* newCoin = new Coin((*ite).collectPos[0][0]);
        actorList.push_back(newCoin);
        ObjectSubject* subject = new ObjectSubject(newCoin);
        subjectList.push_back(std::move(subject));
        MiniMap::AddMarker(new ObjectObserver(subject));
    }
}

void CollectController::Update()
{
    //�C�e���[�^�[
    auto objIte = actorList.begin();
    (*objIte)->Update();
    //�����ݓ����Ă���A�C�e���̏ꏊ���X�V
    nowActiveCollectItemPos = (*objIte)->GetPos();
    //�������݂��Ă��Ȃ�������X�V�I��
    if ((*objIte)->GetObjectState(Object::ObjectState::dead))
    {
        //�����Ă��������
        Actor* brokenObj = (*objIte);
        actorList.erase(objIte);
        SAFE_DELETE(brokenObj);
    }
}

void CollectController::Draw() const
{
    (*actorList.begin())->Draw();
}
/// <summary>
/// �����̃I�u�W�F�N�g�̌����ƃA�C�e���̈ʒu�܂ł̊p�x�����o��
/// </summary>
/// <param name="obj"></param>
/// <returns>�A�C�e���������̃I�u�W�F�N�g����݂ĉE���ɂ���Ȃ�}�C�i�X�̊p�x���Ԃ��Ă���</returns>
float CollectController::GetCollectItemDegreeDifference(std::weak_ptr<ObjectObserver> obj)
{   
    VECTOR between = VSub(nowActiveCollectItemPos, obj.lock()->GetSubjectPos());
    VECTOR dir = obj.lock()->GetSubjectDir();
    float degree = OriginalMath::GetDegreeMisalignment(between, dir);
    degree = VCross(between, dir).y > 0 ? degree : -degree;
    return degree;
}