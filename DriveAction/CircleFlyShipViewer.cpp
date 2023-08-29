#include "CircleFlyShipViewer.h"
#include "CSVFileLoader.h"
#include "OriginalMath.h"
#include "DxLib.h"
#include "InitObjKind.h"
#include "FlyShipController.h"
#include "EditorDrawModel.h"
CircleFlyShipDrawer::CircleFlyShipDrawer()
    :EditorDrawModel(ObjectInit::circleLaserShip)
{
    Init();
}
/// <summary>
/// ���ʂɉ~������Ă���@�̂�`��
/// </summary>
/// <param name="data"></param>
void CircleFlyShipDrawer::Draw(PlacementData data) const
{
    VECTOR dataDir = VGet(data.dirX, 0, data.dirZ);
    VECTOR dataPos = VGet(data.posX, 0, data.posZ);
    for (int i = 0; i < uniNum; i++)
    {
        dataDir = VNorm(OriginalMath::GetYRotateVector(dataDir, uniDirRota)); 
        //�`�悷�郂�f�����Ȃ��Ȃ�I��
        if (modelHandle == -1)return;
        //������ς���
        ModelSetMatrix(VGet(data.dirX, 0, data.dirZ));
        // �RD���f���̃|�W�V�����ݒ�
        MV1SetPosition(modelHandle, VAdd(dataPos,VScale(dataDir,uniBetween)));
        MV1DrawModel(modelHandle);
    }
}
/// <summary>
/// �኱���ɕ`�悷��
/// </summary>
/// <param name="data"></param>
void CircleFlyShipDrawer::SelectDraw(PlacementData data) const
{
    VECTOR dataDir = VGet(data.dirX, 0, data.dirZ);
    VECTOR dataPos = VGet(data.posX, selectPosY, data.posZ);
    for (int i = 0; i < uniNum; i++)
    {
        dataDir = VNorm(OriginalMath::GetYRotateVector(dataDir, uniDirRota));
        //�`�悷�郂�f�����Ȃ��Ȃ�I��
        if (modelHandle == -1)return;
        //������ς���
        ModelSetMatrix(VGet(data.dirX, 0, data.dirZ));
        // �RD���f���̃|�W�V�����ݒ�
        MV1SetPosition(modelHandle, VAdd(dataPos, VScale(dataDir, uniBetween)));
        MV1DrawModel(modelHandle);
    }
}
/// <summary>
/// �~����邽�߂ɕK�v�ȏ�������
/// </summary>
void CircleFlyShipDrawer::Init()
{
    //�z�u�ɕK�v�ȏ��
    using namespace FlyShipInit;
    //FlyShip�p�̃f�[�^�����[�h
    CSVFileLoader* addDataLoader = new CSVFileLoader(InitActor::GetAddDataPass(circleLaserShip));
    auto addData = addDataLoader->GetLoadCharData();
    uniNum = atof(addData[unitNum]);
    uniBetween = atof(addData[unitBetween]);
    //�@�̂̐���������
    
    uniDirRota = 360.0f / uniNum;
}
