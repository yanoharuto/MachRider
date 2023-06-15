#include "CircleFlyshipCommander.h"
#include "InitActor.h"
#include "ListUtility.h"
#include "FirstPositionGetter.h"
#include "CircleLaserFlyShip.h"
#include "OriginalMath.h"

CircleFlyshipCommander::CircleFlyshipCommander(VECTOR firstPos)
{
    auto param = GetInitData(circleLaserShip);

    VECTOR generatePos = {};//生成位置
    FlyShip* flyship;
    VECTOR dir = VGet(1, 0, 0);//方向　GeneratePosを計算するのに使う
    float temp = 0;
    temp = 360 / param.unitNum;
    //firstPosを囲むように配置
    for (int i = 0; i < param.unitNum; i++)
    {
        dir = VNorm(OriginalMath::GetYRotateVector(dir, temp));
        generatePos = VAdd(firstPos, VScale(dir, param.unitBetween));
        flyship = new CircleLaserFlyShip(generatePos, firstPos);
        actorList.push_back(flyship);
    }
}