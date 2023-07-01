#include "CollectController.h"
#include "FirstPositionGetter.h"
#include "Coin.h"
#include "MiniMap.h"
#include "ObjectObserver.h"
#include "ObjectSubject.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "InitActor.h"
//収集アイテムが今動いているか
bool CollectController::isActive = false;
//ゲーム終了したか
bool CollectController::isChallengeEnd = false;
/// 現在動いている収集アイテムの位置
VECTOR CollectController:: nowActiveCollectItemPos;
//残っている収集アイテムの数
int CollectController::remainingCollectNum = 0;
//収集アイテムの総数
int CollectController::totalCollectNum = 0;
/// <summary>
/// コインの設置
/// </summary>
CollectController::CollectController()
{
    auto getter = new FirstPositionGetter();
    auto challengeDataVec = getter->GetChallengeData();

    for (auto ite = challengeDataVec.begin(); ite != challengeDataVec.end(); ite++)
    {
        //収集アイテムの位置をコンストラクタに与える
        Coin* newCoin = new Coin((*ite).collectPos[InitActor::GetActorTileNum(collect)][0]);

        actorList.push_back(newCoin);
        ObjectSubject* subject = new ObjectSubject(newCoin);
        subjectList.push_back(std::move(subject));
        //マップに位置を伝えるためオブザーバーを渡す
        MiniMap::AddMarker(new ObjectObserver(subject));
    }
    //static変数の初期化
    totalCollectNum = actorList.size();//収集アイテム最大値
    remainingCollectNum = totalCollectNum;//残りの数
    isChallengeEnd = false;
    isActive = false;//今活動中か
}
/// <summary>
/// actorListの先頭の収集アイテムだけ更新
/// </summary>
void CollectController::Update()
{
    //イテレーター
    auto objIte = actorList.begin();
    (*objIte)->Update();
    isActive = (*objIte)->GetObjectState() == Object::ObjectState::active;
    //今現在動いているアイテムの場所を更新
    nowActiveCollectItemPos = (*objIte)->GetPos();
    //残っているアイテムの数
    remainingCollectNum = actorList.size();
    //取っているけどエフェクトを出している途中なら現存数をへらす
    if ((*objIte)->GetObjectState() != Object::ObjectState::active) remainingCollectNum --;
    //もう存在していなかったら更新終了
    if ((*objIte)->GetObjectState()== Object::ObjectState::dead)
    {
        //消していいやつ消す
        Actor* brokenObj = (*objIte);
        actorList.erase(objIte);
        SAFE_DELETE(brokenObj);
        //リストの中身が空になったら
        isChallengeEnd = actorList.empty();
    }
}
/// <summary>
/// 収集アイテムの描画
/// </summary>
void CollectController::Draw() const
{
    (*actorList.begin())->Draw();
}
/// <summary>
/// ゲームが始まる前の処理
/// </summary>
void CollectController::GameReserve()
{
    //イテレーター
    auto objIte = actorList.begin();
    (*objIte)->GameReserve();
    //今現在動いているアイテムの場所を更新
    nowActiveCollectItemPos = (*objIte)->GetPos();
}
/// <summary>
/// 引数の場所と収集アイテムの位置の距離ベクトルを出す
/// </summary>
/// <param name="pos"></param>
/// <returns></returns>
VECTOR CollectController::GetBetween(VECTOR pos)
{
    return VSub(nowActiveCollectItemPos, pos);
}
/// <summary>
/// 収集アイテムが動いているか
/// </summary>
/// <returns></returns>
bool CollectController::IsActiveCollect()
{
    return isActive;
}
/// <summary>
/// プレイヤーが集めなければいけないアイテムの数
/// </summary>
/// <returns></returns>
int CollectController::GetTotalCollectNum()
{
    return totalCollectNum;
}
/// <summary>
/// 残っているアイテムの数
/// </summary>
/// <returns></returns>
int CollectController::GetRemainingCollectNum()
{
    return remainingCollectNum;
}
/// <summary>
/// 全てのアイテムを回収し終えたかどうか
/// </summary>
/// <returns></returns>
bool CollectController::IsEndingChallenge()
{
    return isChallengeEnd;
}
