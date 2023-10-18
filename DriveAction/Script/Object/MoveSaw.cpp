#include "MoveSaw.h"
#include "ReusableTimer.h"
#include "AddMoveSawDataLoader.h"
#include "InitActor.h"
#include "OriginalMath.h"
#include "SphereHitChecker.h"
#include "ConflictManager.h"
#include "Utility.h"
#include "ConflictProcessor.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"

/// <summary>
/// 移動回転のこぎり
/// </summary>
/// <param name="editData"></param>
MoveSaw::MoveSaw(PlacementData editData)
    :Saw(InitObjKind::moveSaw,editData)
{   
    //追加情報から移動速度などを所得
    auto addDataLoader = new AddMoveSawDataLoader();
    auto addStrDataVec = addDataLoader->GetLoadData();
    using enum MoveParametor;
    //タイマーが動いている間だけ動く
    moveLarpTimer = new ReusableTimer(STR_TO_D(addStrDataVec[CAST_I(moveTime)]));
    //前方方向に動く
    velocity = VScale(direction, STR_TO_F(addStrDataVec[CAST_I(moveSpeed)]));
    //当たり判定
    collider = new SphereHitChecker(this);
    conflictProcessor = new ConflictProcessor(this);
    ConflictManager::AddConflictProcessor(conflictProcessor, collider);
    //破壊時のエフェクト
    EffectManager::LoadEffect(EffectKind::bombExplosion);
}
/// <summary>
/// 移動しながら回転する
/// </summary>
void MoveSaw::Update()
{
    if (moveLarpTimer->IsOverLimitTime())//時間いっぱい動いたら反対方向に動く
    {
        moveLarpTimer->Reuse();//移動時間をリセット
        
        velocity = VSub(VGet(0,0,0),velocity);//移動方向反転
    }
    position = VAdd(position, velocity);
    //回転
    Saw::Update();
}