#include "CircleFlyShipController.h"
#include "InitActor.h"
#include "ListUtility.h"
#include "FirstPositionGetter.h"
#include "CircleLaserFlyShip.h"
#include "OriginalMath.h"
#include "DrawModel.h"
/// <summary>
/// �ւɂȂ��Ă��郌�[�U�[�Ǝˋ@�̍X�V�Ƃ�����
/// </summary>
CircleFlyShipController::CircleFlyShipController()
    :FlyShipController(circleLaserShip)
{
    drawModel = new DrawModel(circleLaserShip);
}
/// <summary>
/// �ւɂȂ��Ă��郌�[�U�[�Ǝˋ@�̔z�u�ƒǉ�
/// </summary>
void CircleFlyShipController::AddObject(std::vector<PlacementData> editData)
{
    if (!editData.empty())
    {
        for (int i = 0; i < editData.size(); i++)
        {
            //������ނȂ�ǉ�
            if (editData[i].objKind == controllObjKind)
            {
                AddObject(editData[i]);
            }
        }
    }

}
/// <summary>
/// �ւɂȂ��Ă��郌�[�U�[�Ǝˋ@�̔z�u�ƒǉ�
/// </summary>
void CircleFlyShipController::AddObject(PlacementData arrangementData)
{
    //�@�̂��͂�ł��钆�S���W
    VECTOR centerPos = VGet(arrangementData.posX, 0, arrangementData.posZ);
    //�����ʒu
    VECTOR generatePos = {};
    //�����@GeneratePos���v�Z����̂Ɏg��
    VECTOR dir = VGet(arrangementData.dirX, 0, arrangementData.dirZ);
    //���x��dir���Ȃ���p�x
    float tempRota = static_cast<float>(360 / param.unitNum);
    //firstPos���͂ނ悤�ɔz�u
    for (int i = 0; i < param.unitNum; i++)
    {
        //��������
        dir = VNorm(OriginalMath::GetYRotateVector(dir, tempRota));
        //�����ʒu��dir�̕�����between�����ꂽ��
        generatePos = VAdd(centerPos, VScale(dir, param.unitBetween));
        //�@�̐����ʒu�Ƌ@�̂������ʒu
        actorList.push_back(new CircleLaserFlyShip(generatePos, centerPos));
    }
}
