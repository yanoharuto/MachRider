#include "conflictProccesor.h"
#include "HitChecker.h"
#include "OriginalMath.h"
#include "ConflictManager.h"

ConflictProccesor::ConflictProccesor(Actor* obj)
{
    object = obj;
    ConflictManager::AddConflictObjInfo(this);
}

ConflictProccesor::~ConflictProccesor()
{

}
/// <summary>
/// 当たり判定で必要な情報を渡す
/// </summary>
/// <returns></returns>
HitCheckExamineObjectInfo ConflictProccesor::GetHitExamineCheckInfo() const
{
    HitCheckExamineObjectInfo info;
    info.SetExamineInfo(object);
    info.velocity = object->GetVelocity();
    return info;
}
/// <summary>
/// 当たり判定の処理を呼び出す
/// </summary>
/// <param name="resultInfo"></param>
void ConflictProccesor::ConflictProccess(std::list<ConflictExamineResultInfo> resultInfo)
{
    //衝突後の処理を行う必要がないなら終了
    if (object == nullptr)return;

    for (auto ite = resultInfo.begin(); ite != resultInfo.end(); ite++)
    {
        if ((*ite).hit != HitSituation::NotHit)
        {
            if (coolTimer.contains((*ite).tag))
            {
                //クールタイムが過ぎていて当たっているなら
                if (coolTimer[(*ite).tag]->IsOverLimitTime())
                {
                    //当たった時の処理を行う
                    object->ConflictProccess((*ite));
                    IncrementHitCount((*ite).tag);
                }
            }
            else
            {
                //当たった時の処理を行う
                object->ConflictProccess((*ite));
                IncrementHitCount((*ite).tag);
            }
        }
    }

}
/// <summary>
/// 当たり判定で特定のものにクールタイムが発生する場合タイマーをセット出来る
/// </summary>
/// <param name="tag">特定の者のタグ</param>
/// 
/// <param name="timer">クールタイム計測用のタイマー</param>
void ConflictProccesor::SetCoolTimer(Object::ObjectTag tag,float setCoolTime)
{
    Timer* timer = new Timer(setCoolTime);
    coolTimer.insert(std::make_pair(tag, timer));
}
/// <summary>
/// 引数のタグのオブジェクトに何回ぶつかったか返す
/// </summary>
/// <param name="objTag"></param>
/// <returns></returns>
int ConflictProccesor::GetTagHitCount(Object::ObjectTag objTag)
{
    return hitCountMap[objTag];
}
/// <summary>
/// 今当たり判定を持つオブジェクトが動いているか
/// </summary>
/// <returns></returns>
bool ConflictProccesor::IsObjectAlive() const
{
    return object->GetObjectState() == Object::active;
}
/// <summary>
/// 引数のオブジェクトの当たった回数を増やす
/// </summary>
/// <param name="objTag"></param>
void ConflictProccesor::IncrementHitCount(Object::ObjectTag objTag)
{
    //まだ追加したことのないタグなら当たった回数を記録
    if (!hitCountMap.contains(objTag))
    {
        int hitCount = 1;
        hitCountMap.insert(std::make_pair(objTag, hitCount));
    }
    //あるならぶつかった時に回数を増やす
    else
    {
        hitCountMap[objTag]++;
    }
}
