#include <iostream>
#include <memory>
#include "CollectController.h"
#include "FirstPositionGetter.h"
#include "CollectItem.h"
#include "MiniMap.h"
#include "ObjectObserver.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "InitActor.h"
#include "DrawModel.h"
#include "Object.h"

//収集アイテムの状態
Object::ObjectState CollectController::objState = Object::sleep;
//収集アイテムが全部Deleteされたか
bool CollectController::isDestroyAll = false;
//ゲーム終了したか
bool CollectController::isGameEnd = false;
/// 現在動いている収集アイテムの位置
VECTOR CollectController:: nowActiveCollectItemPos;
//残っている収集アイテムの数
int CollectController::remainingCollectNum = 0;
//収集アイテムの総数
int CollectController::totalCollectNum = 0;
/// <summary>
/// 収集アイテムを予めNewして最大枚数を保存
/// </summary>
CollectController::CollectController()
    :ActorController(collect)
{
    //配置情報所得
    auto positionGetter = new FirstPositionGetter();
    auto editDataVec = positionGetter->GetPlaceData(Object::collect);
    //配置情報に基づいてNewしていく
    for (unsigned int i = 0; i < editDataVec.size(); i++)
    {
        //収集アイテムの位置をコンストラクタに与える
        Coin* newCoin = new Coin(editDataVec[i]);
        actorList.push_back(newCoin);  
        //マップに位置を伝えるためオブザーバーを渡す
        MiniMap::AddMarker(std::make_unique<ObjectObserver>(newCoin));
    }
    //収集アイテム最大値
    totalCollectNum = actorList.size();
    //残りの数
    remainingCollectNum = totalCollectNum;
    //ゲーム終了フラグ
    isGameEnd = false;
    //今動いている
    objState = Object::active;
    isDestroyAll = false;
    //描画役
    drawModel = new DrawModel(collect);
}
/// <summary>
/// actorListの先頭の収集アイテムだけ更新
/// </summary>
void CollectController::Update()
{
    //何もない状態なら終了
    if (actorList.empty())return;
    //actorListの先頭の一つだけ動かす
    auto objIte = actorList.begin();
    (*objIte)->Update();
    //今現在動いているアイテムの場所を更新
    nowActiveCollectItemPos = (*objIte)->GetPos();

    //取っているけどエフェクトを出している途中なら現存数をへらす
    objState = (*objIte)->GetObjectState();
    //プレイヤーにぶつかって取られたならアクティブ以外の状態になっている
    if (objState != Object::ObjectState::active)
    {
        //残り数を全体から1減らす
        remainingCollectNum = actorList.size() - 1;
        //壊していいようにする
        Actor* brokenObj = (*objIte);
        //
        switch (objState)
        {
        case Object::activeEnd:
            //最後の一つならゲーム終了条件達成
            isGameEnd = actorList.size() == 1;
            break;
        case Object::dead:
            //消していいやつだったら消す
            actorList.erase(objIte);
            SAFE_DELETE(brokenObj);
            //全部消されたならTrue
            isDestroyAll = actorList.empty();
            break;
        }
    }
}
/// <summary>
/// 収集アイテムの描画
/// </summary>
void CollectController::Draw() const
{
    if (!actorList.empty())
    {
        drawModel->Draw((*actorList.begin()));
    }
}
/// <summary>
/// ゲームが始まる前の処理
/// </summary>
void CollectController::PrepareGame()
{
    //イテレーター
    auto objIte = actorList.begin();
    (*objIte)->PrepareGame();
    //今現在動いているアイテムの場所を更新
    nowActiveCollectItemPos = (*objIte)->GetPos();
}
/// <summary>
/// 引数の場所と収集アイテムの位置の距離ベクトルを出す
/// </summary>
/// <param name="pos"></param>
/// <returns></returns>
VECTOR CollectController::GetCollectItemBetween(VECTOR pos)
{
    return VSub(nowActiveCollectItemPos, pos);
}
/// <summary>
/// 収集アイテムが動いているか
/// </summary>
/// <returns></returns>
bool CollectController::IsActiveCollect()
{
    return objState;
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
bool CollectController::IsEndGame()
{
    return isGameEnd;
}
/// <summary>
/// 全てのアイテムが破壊されたか
/// </summary>
/// <returns></returns>
bool CollectController::IsDestroyAllItem()
{
    return isDestroyAll;
}
