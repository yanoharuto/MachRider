#include "MoveSaw.h"
#include "ReusableTimer.h"
#include "CSVFileLoader.h"
#include "InitActor.h"
#include "OriginalMath.h"
#include "SphereCollider.h"
/// <summary>
/// ˆÚ“®‰ñ“]‚Ì‚±‚¬‚è
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
    //‘O•û•ûŒü‚É“®‚­
    velocity = VScale(direction, speed);
    //“–‚½‚è”»’è
    collider = new SphereCollider(this);
}
/// <summary>
/// ˆÚ“®‚µ‚È‚ª‚ç‰ñ“]‚·‚é
/// </summary>
void MoveSaw::Update()
{
    if (moveLarpTimer->IsOverLimitTime())//ŽžŠÔ‚¢‚Á‚Ï‚¢“®‚¢‚½‚ç”½‘Î•ûŒü‚É“®‚­
    {
        moveLarpTimer->Reuse();
        
        velocity = VSub(VGet(0,0,0),velocity);
    }
    position = VAdd(position, velocity);
    //‰ñ“]
    direction = VNorm(OriginalMath::GetYRotateVector(direction, addRotate));
}