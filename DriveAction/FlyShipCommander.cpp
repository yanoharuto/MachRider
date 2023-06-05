#include "FlyShipCommander.h"
#include "Utility.h"
#include "FlyShip.h"
#include "CSVFileLoader.h"

FlyShipCommander::FlyShipCommander()
{
}

FlyShipCommander::FlyShipCommander(ObjectInit::InitObjKind objKind, VECTOR playerPos)
{
    
}

FlyShipCommander::~FlyShipCommander()
{
    for (auto ite = flyShipList.begin(); ite != flyShipList.end(); ite++)
    {
        SAFE_DELETE(*(ite));
    }
}

void FlyShipCommander::Update()
{
    for (auto ite = flyShipList.begin(); ite != flyShipList.end(); ite++)
    {
        if ((*ite)->GetAliveFlag())
        {
            (*ite)->Update();
        }
    }
}

void FlyShipCommander::Draw()
{
    for (auto ite = flyShipList.begin(); ite != flyShipList.end(); ite++)
    {
        (*ite)->Draw();
    }
}
using namespace FlyShipInit;
FlyShipInit::InitFlyShipParamator FlyShipCommander::GetInitData(ObjectInit::InitObjKind kind)
{
    //modelの当たり判定とか取ってくる
    FlyShipInit::InitFlyShipParamator param = {};
    param.actorParam = InitActor::GetActorParamator(kind);
    //FlyShip用のデータをロード
    CSVFileLoader* addDataLoader = new CSVFileLoader(InitActor::GetActorInitPassData(kind).addData);
    auto addData = addDataLoader->GetLoadCharData();
    param.moveSpeed = atof(addData[moveSpeed]);
    param.setAliveTime = atof(addData[aliveTime]);
    param.setCoolTime = atof(addData[coolTime]);
    param.unitNum = atof(addData[unitNum]);
    param.unitBetween = atof(addData[unitBetween]);
    return param;
}
