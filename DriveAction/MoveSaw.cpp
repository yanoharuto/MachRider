#include "MoveSaw.h"
#include "ReusableTimer.h"
#include "CSVFileLoader.h"
#include "InitActor.h"
#include "OriginalMath.h"
#include "SphereCollider.h"
/// <summary>
/// 移動回転のこぎり
/// </summary>
/// <param name="editData"></param>
MoveSaw::MoveSaw(EditArrangementData editData)
    :Saw(editData)
{
    InitParamater(moveSaw);
    firstDir = direction;
    ActorParameter initParam = InitActor::GetActorParamator(moveSaw);
    auto addDataLoader = new CSVFileLoader(initParam.addData);
    auto addStrDataVec = addDataLoader->GetLoadStringData();
    speed= atoi(addStrDataVec[moveSpeed].c_str());
    moveLarpTimer = new ReusableTimer(atoi(addStrDataVec[moveTime].c_str()));
    //前方方向に動く
    velocity = VScale(direction, speed);
    //当たり判定
    collider = new SphereCollider(this);
}
/// <summary>
/// 移動しながら回転する
/// </summary>
void MoveSaw::Update()
{
    if (moveLarpTimer->IsOverLimitTime())//時間いっぱい動いたら反対方向に動く
    {
        moveLarpTimer->Reuse();
        
        velocity = VSub(VGet(0,0,0),velocity);
    }
    position = VAdd(position, velocity);
    //回転
    direction = VNorm(OriginalMath::GetYRotateVector(direction, addRotate));
}