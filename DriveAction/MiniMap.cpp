#include "MiniMap.h"
#include "UIManager.h"
#include "OriginalMath.h"
#include "ObjectObserver.h"
#include "Object.h"
#include "Utility.h"
#include "UIDrawer.h"
#include "StageWall.h"
//���@��Icon�̑傫��
const int MiniMap::iconSize;
//�~�j�}�b�v�̉摜�̉���
int MiniMap::mapGraphWidth;
//�~�j�}�b�v�̉摜�̏c��
int MiniMap::mapGraphLength;
//���W���̈ʒu�̏k��
const float MiniMap::betweenSize = 0.3f;

//�~�j�}�b�v�ɕ\������_
std::list<ObjectObserver*> MiniMap::markerObserverList;
//�~�j�}�b�v�̃f�[�^
UIData MiniMap::miniMap;
/// <summary>
/// ���W�A�C�e���Ƃ���`�悷�邽�߂̓z
/// </summary>
MiniMap::MiniMap(std::weak_ptr<ObjectObserver> player)
{
    miniMap = UIManager::CreateUIData(radar);
    
    GetGraphSize(miniMap.dataHandle[0], &mapGraphWidth, &mapGraphLength);

    playerObserver = player;
}

MiniMap::~MiniMap()
{
    //�`�悷�郊�X�g��S����
    for (auto itr = markerObserverList.begin(); itr != markerObserverList.end(); itr++)
    {
        SAFE_DELETE((*itr));
    }
    markerObserverList.clear();
}
/// <summary>
/// ���W�A�C�e���̈ʒu���X�V
/// </summary>
/// <param name="objInfo"></param>
void MiniMap::Update()
{
    //�v���C���[���}�b�v�̒��S�ɂȂ�悤�ɂ���
    VECTOR playerPos = playerObserver.lock()->GetSubjectPos();
    playerPos.y = 0;
    //�������Ă�����W�A�C�e�������}�b�v�ɔ��f
    drawPosList.clear();
    for (auto ite = markerObserverList.begin(); ite != markerObserverList.end(); ite++)
    {
        //�A�N�e�B�u�ȃI�u�W�F�N�g���}�b�v�ɔ��f
        if ((*ite)->GetSubjectState() == Object::active)
        {
            VECTOR itePos = (*ite)->GetSubjectPos();
            VECTOR distance = VSub(itePos, playerPos);
            distance.y = 0;

            if (VSize(distance) * betweenSize < miniMap.width * miniMap.size)
            {
                distance = ConvertPosition(distance);
                
                drawPosList.push_back(distance);
            }
        }
    }
}
/// <summary>
/// �}�b�v�ɕ\������_�ƃ��[�_�[�̘g
/// </summary>
void MiniMap::Draw()const
{
    //�g�`��
    UIDrawer::DrawRotaUI(miniMap);
    //�v���C���[�A�C�R���̕`��
    DrawCircle(miniMap.x, miniMap.y, iconSize, playerColor, 1, 1);
    //���W�A�C�e���̕`��
    for (auto ite = drawPosList.begin(); ite != drawPosList.end(); ite++)
    {
        DrawCircle(static_cast<int>((*ite).x), static_cast<int>((*ite).y), iconSize + 1, GetColor(0,0,0), 0, 1);
        DrawCircle(static_cast<int>((*ite).x), static_cast<int>((*ite).y), iconSize, coinColor, 1, 1);
    }
}
/// <summary>
/// �}�b�v�ɔ��f���������A�C�e���̒ǉ�
/// </summary>
/// <param name="obserber"></param>
void MiniMap::AddMarker(ObjectObserver* obserber)
{
    markerObserverList.push_back(obserber);
}
/// <summary>
/// �~�j�}�b�v�̑傫���ɕϊ�����
/// </summary>
/// <param name="between">�����̃A�C�e������̋���</param>
/// <returns></returns>
VECTOR MiniMap::ConvertPosition(VECTOR between)
{
    //�}�b�v�̒������̌����ƃ}�[�J�[�̈ʒu�̊p�x��
    float rotate = OriginalMath::GetDegreeMisalignment(between, playerObserver.lock()->GetSubjectDir());
    //�E����������
    rotate = VCross(between, playerObserver.lock()->GetSubjectDir()).y < 0 ? -rotate : rotate ;
    //�p�x���Ȃ����Ă���s��ŋ������Ȃ���
    MATRIX pM = MGetRotY(-rotate * RAGE);
    between = VTransform(VGet(0, 0, -VSize(between)), pM);
    //�~�j�}�b�v�̑傫���ɕϊ�
    float wSize = mapGraphWidth / StageWall::GetStageWidth();
    float lSize = mapGraphLength / StageWall::GetStageLength();
    VECTOR data;
    data.x = -between.x * wSize + miniMap.x;
    data.y = between.z * lSize + miniMap.y;
    return data;
}
