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
/// <summary>
/// 収集アイテムを予めNewして最大枚数を保存
/// </summary>
CollectItemController::CollectItemController()
    :ActorController(InitObjKind::collect)
{
    //配置情報所得
    auto positionGetter = new FirstPositionGetter();
    auto editDataVec = positionGetter->GetPlaceData(Object::ObjectTag::collect);
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
    //今出てきている収集アイテムの数
    collectCount = 0;
    //描画役
    drawModel = new DrawModel(InitObjKind::collect);
    //今のアイテムの位置
    nowActiveCollectItemPos = {};
    //回収されているかどうかのフラグ
    isCollectLastOne = false;
}
/// <summary>
/// actorListの先頭の収集アイテムだけ更新
/// </summary>
void CollectItemController::Update()
{
    //何もない状態なら終了
    if (actorList.empty())return;
    //actorListの先頭の一つだけ動かす
    auto objIte = actorList.begin();
    (*objIte)->Update();
    //今現在動いているアイテムの場所を更新
    nowActiveCollectItemPos = (*objIte)->GetPos();

    using enum Object::ObjectState;
    //取っているけどエフェクトを出している途中なら現存数をへらす
    Object::ObjectState objState = (*objIte)->GetObjectState();
    //プレイヤーにぶつかって取られたならアクティブ以外の状態になっている
    if (objState == dead)
    {
        //残り数を全体から1減らす
        remainingCollectNum = actorList.size() - 1;
        //壊していいようにする
        Actor* brokenObj = (*objIte);
        //消していいやつだったら消す
        actorList.erase(objIte);
        SAFE_DELETE(brokenObj);
        //次のアイテムは何番目か
        collectCount = totalCollectNum - remainingCollectNum;
    }
    //最後の一つが回収されたか
    else if (objState == activeEnd && static_cast<int>(actorList.size()) == 1)
    {
        isCollectLastOne = true;
    }
}
/// <summary>
/// 収集アイテムの描画
/// </summary>
void CollectItemController::Draw(std::weak_ptr<CameraObserver> cameraObserever) const
{
    if (!actorList.empty())
    {
        drawModel->Draw((*actorList.begin()));
    }
}
/// <summary>
/// ゲームが始まる前の処理
/// </summary>
void CollectItemController::PrepareGame()
{
    //イテレーター
    auto objIte = actorList.begin();
    (*objIte)->PrepareGame();
    //今現在動いているアイテムの場所を更新
    nowActiveCollectItemPos = (*objIte)->GetPos();
}
/// <summary>
/// 引数と収集アイテムの距離
/// </summary>
/// <param name="pos">収集アイテムとの距離を調べたい位置</param>
/// <returns>引数と収集アイテムの距離ベクトル</returns>
VECTOR CollectItemController::GetItemBetween(VECTOR pos)const
{
    return VSub(nowActiveCollectItemPos, pos);
}
/// <summary>
/// 最初にステージに配置される枚数
/// </summary>
/// <returns>ステージに配置された最大数</returns>
int CollectItemController::GetTotalNum()const
{
    return totalCollectNum;
}
/// <summary>
/// アイテムの残り枚数
/// </summary>
/// <returns>プレイヤーに取られると減る</returns>
int CollectItemController::GetRemainingNum()const
{
    return remainingCollectNum;
}
/// <summary>
/// 今の収集アイテムが何番目のアイテムか
/// </summary>
/// <returns>取られたら増える</returns>
int CollectItemController::GetCollectCount()const
{
    return collectCount;
}
/// <summary>
/// 最後の一つのアイテムが回収されたか
/// </summary>
/// <returns>回収されたらTrue</returns>
bool CollectItemController::IsCollectLastOne()const
{
    return isCollectLastOne;
}
