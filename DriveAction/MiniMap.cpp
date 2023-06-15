#include "MiniMap.h"
#include "UIManager.h"
#include "OriginalMath.h"
#include "ObjectObserver.h"

//���@��Icon�̑傫��
const int MiniMap::iconSize;
//�~�j�}�b�v�̉摜�̉���
int MiniMap::mapGraphWidth;
//�~�j�}�b�v�̉摜�̏c��
int MiniMap::mapGraphHeight;
//�}�b�v�̑傫��
const float MiniMap::mapSize = 420;
//���W���̈ʒu�̏k��
const float MiniMap::collectBetween = 0.3f;
//�}�b�v�̑傫���̌W��
float MiniMap::mapSizeCoefficient = 0;
std::list<VECTOR> MiniMap::posList;
UIData MiniMap::miniMap;
/// <summary>
/// ���W�A�C�e���Ƃ���`�悷�邽�߂̓z
/// </summary>
MiniMap::MiniMap(std::shared_ptr<ObjectObserver> player)
{
    miniMap = UIManager::CreateUIData(radar);
    
    GetGraphSize(miniMap.dataHandle[0], &mapGraphWidth, &mapGraphHeight);
    //�}�b�v�̑傫�������ɂ���
    mapSizeCoefficient = mapSize / mapGraphWidth;
    playerObserver = player;
}

MiniMap::~MiniMap()
{
}
/// <summary>
/// ���W�A�C�e���̈ʒu���X�V
/// </summary>
/// <param name="objInfo"></param>

void MiniMap::Update()
{
    mapRotate = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), playerObserver.lock()->GetSubjectDir()) * RAGE;
    //�v���C���[�̎Ԃ̌����ɍ��킹��
    mapRotate = VCross(VGet(1, 0, 0), playerObserver.lock()->GetSubjectDir()).y < 0 ? -mapRotate : mapRotate;

    VECTOR playerPos = playerObserver.lock()->GetSubjectPos();
    playerPos.y = 0;
    drawPosList.clear();
    //���W�A�C�e���̃��X�g���}�b�v�ɔ��f�ł���悤�ɂ���
    for (auto ite = posList.begin(); ite != posList.end(); ite++)
    {
        VECTOR pos = VScale(VSub(*ite, playerPos), collectBetween);        
        //�}�b�v�̑傫���ɓ����Ă���Ȃ�
        if (VSize(pos) < mapGraphWidth)
        {
            OriginalMath::GetYRotateVector(pos, mapRotate);
            pos = ConvertPosition(pos);
            drawPosList.push_back(pos);
        }
    }
    posList.clear();
}

void MiniMap::Draw()const
{
    //�g�`��
    DrawRotaGraph(miniMap.x, miniMap.y, mapSizeCoefficient, 0, miniMap.dataHandle[0], true);
    //�v���C���[�A�C�R���̕`��
    DrawCircle(miniMap.x, miniMap.y, iconSize, playerColor, 1, 1);
    //���W�A�C�e���̕`��
    for (auto ite = drawPosList.begin(); ite != drawPosList.end(); ite++)
    {
        DrawCircle(static_cast<int>((*ite).x), static_cast<int>((*ite).y), iconSize + 1, GetColor(0,0,0), 0, 1);
        DrawCircle(static_cast<int>((*ite).x), static_cast<int>((*ite).y), iconSize, coinColor, 1, 1);
    }
}

void MiniMap::AddMarker(ObjectObserver* obserber)
{
    VECTOR collectPos = obserber->GetSubjectPos();
    collectPos.y = 0;
    posList.push_back(collectPos);
}

VECTOR MiniMap::ConvertPosition(VECTOR pos)
{
    VECTOR data;
    data.x = -pos.x * (mapGraphWidth / 2) / 6000 + miniMap.x;
    data.y = pos.z * (mapGraphHeight / 2) / 6000 + miniMap.y;
    return data;
}
