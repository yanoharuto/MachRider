#include "CircleFlyShipController.h"
#include "InitActor.h"
#include "ListUtility.h"
#include "FirstPositionGetter.h"
#include "CircleLaserFlyShip.h"
#include "OriginalMath.h"
#include "DrawModel.h"
/// <summary>
/// 輪になっているレーザー照射機の更新とかする
/// </summary>
CircleFlyShipController::CircleFlyShipController()
    :FlyShipController(circleLaserShip)
{
    drawModel = new DrawModel(circleLaserShip);
}
/// <summary>
/// 輪になっているレーザー照射機の配置と追加
/// </summary>
void CircleFlyShipController::AddObject(std::vector<PlacementData> editData)
{
    if (!editData.empty())
    {
        for (int i = 0; i < editData.size(); i++)
        {
            //同じ種類なら追加
            if (editData[i].objKind == controllObjKind)
            {
                AddObject(editData[i]);
            }
        }
    }

}
/// <summary>
/// 輪になっているレーザー照射機の配置と追加
/// </summary>
void CircleFlyShipController::AddObject(PlacementData arrangementData)
{
    //機体が囲んでいる中心座標
    VECTOR centerPos = VGet(arrangementData.posX, 0, arrangementData.posZ);
    //生成位置
    VECTOR generatePos = {};
    //方向　GeneratePosを計算するのに使う
    VECTOR dir = VGet(arrangementData.dirX, 0, arrangementData.dirZ);
    //作る度にdirが曲がる角度
    float tempRota = static_cast<float>(360 / param.unitNum);
    //firstPosを囲むように配置
    for (int i = 0; i < param.unitNum; i++)
    {
        //離れる方向
        dir = VNorm(OriginalMath::GetYRotateVector(dir, tempRota));
        //生成位置はdirの方向にbetween分離れた所
        generatePos = VAdd(centerPos, VScale(dir, param.unitBetween));
        //機体生成位置と機体が向く位置
        actorList.push_back(new CircleLaserFlyShip(generatePos, centerPos));
    }
}
