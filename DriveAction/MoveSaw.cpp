#include "MoveSaw.h"
#include "ReusableTimer.h"
#include "CSVFileLoader.h"
#include "InitActor.h"
#include "OriginalMath.h"
#include "SphereCollider.h"
#include "ConflictManager.h"
#include "Utility.h"
#include "ConflictProcessor.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"

/// <summary>
/// 移動回転のこぎり
/// </summary>
/// <param name="editData"></param>
MoveSaw::MoveSaw(EditArrangementData editData)
    :Saw(moveSaw,editData)
{   
    //追加情報から移動速度などを所得
    auto addDataLoader = new CSVFileLoader(InitActor::GetAddDataPass(moveSaw));
    auto addStrDataVec = addDataLoader->GetLoadStringData();
    //タイマーが動いている間だけ動く
    moveLarpTimer = new ReusableTimer(atoi(addStrDataVec[moveTime].c_str()));
    //前方方向に動く
    velocity = VScale(direction, atoi(addStrDataVec[moveSpeed].c_str()));
    //当たり判定
    collider = new SphereCollider(this);
    conflictProcessor = new ConflictProcessor(this);
    ConflictManager::AddConflictProcessor(conflictProcessor, collider);
    //破壊時のエフェクト
    EffectManager::LoadEffect(bombExplosion);
    
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