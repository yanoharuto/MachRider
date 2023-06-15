#include "CircleFlyshipCommander.h"
#include "InitActor.h"
#include "ListUtility.h"
#include "FirstPositionGetter.h"
#include "CircleLaserFlyShip.h"
#include "OriginalMath.h"

CircleFlyshipCommander::CircleFlyshipCommander(VECTOR firstPos)
{
    auto param = GetInitData(circleLaserShip);

    VECTOR generatePos = {};//�����ʒu
    FlyShip* flyship;
    VECTOR dir = VGet(1, 0, 0);//�����@GeneratePos���v�Z����̂Ɏg��
    float temp = 0;
    temp = 360 / param.unitNum;
    //firstPos���͂ނ悤�ɔz�u
    for (int i = 0; i < param.unitNum; i++)
    {
        dir = VNorm(OriginalMath::GetYRotateVector(dir, temp));
        generatePos = VAdd(firstPos, VScale(dir, param.unitBetween));
        flyship = new CircleLaserFlyShip(generatePos, firstPos);
        actorList.push_back(flyship);
    }
}