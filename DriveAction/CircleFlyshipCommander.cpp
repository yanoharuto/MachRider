#include "CircleFlyshipCommander.h"
#include "InitActor.h"
#include "ListUtility.h"
#include "FirstPositionGetter.h"
#include "CircleLaserFlyShip.h"
#include "OriginalMath.h"

CircleFlyshipCommander::CircleFlyshipCommander(VECTOR firstPos)
{
    auto param = GetInitData(circleLaserShip);

    VECTOR generatePos = {};
    FlyShip* flyship;
    VECTOR dir = VGet(1, 0, 0);
    float temp = 0;
    temp = 360 / param.unitNum;
    for (int i = 0; i < param.unitNum; i++)
    {
        dir = VNorm(OriginalMath::GetYRotateVector(dir, 60));
        generatePos = VAdd(firstPos, VScale(dir, param.unitBetween));
        flyship = new CircleLaserFlyShip(generatePos, firstPos);
        flyShipList.push_back(flyship);
    }
}

CircleFlyshipCommander::~CircleFlyshipCommander()
{
}
