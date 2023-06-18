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
/// コインの設置
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
    //イテレーター
    auto objIte = actorList.begin();
    (*objIte)->Update();
    //今現在動いているアイテムの場所を更新
    nowActiveCollectItemPos = (*objIte)->GetPos();
    //もう存在していなかったら更新終了
    if ((*objIte)->GetObjectState(Object::ObjectState::dead))
    {
        //消していいやつ消す
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
/// 引数のオブジェクトの向きとアイテムの位置までの角度差を出す
/// </summary>
/// <param name="obj"></param>
/// <returns>アイテムが引数のオブジェクトからみて右側にあるならマイナスの角度が返ってくる</returns>
float CollectController::GetCollectItemDegreeDifference(std::weak_ptr<ObjectObserver> obj)
{   
    VECTOR between = VSub(nowActiveCollectItemPos, obj.lock()->GetSubjectPos());
    VECTOR dir = obj.lock()->GetSubjectDir();
    float degree = OriginalMath::GetDegreeMisalignment(between, dir);
    degree = VCross(between, dir).y > 0 ? degree : -degree;
    return degree;
}