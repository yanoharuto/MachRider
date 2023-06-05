#include "MiniMap.h"
#include "UIManager.h"
#include "CourceDataLoader.h"
#include "OriginalMath.h"
#include "ObjectObserver.h"
#include "RacerManager.h"
#include "ObjectObserver.h"
/// <summary>
/// ���W�A�C�e���Ƃ���`�悷�邽�߂̓z
/// </summary>
MiniMap::MiniMap(RacerManager* racerManager)
{
    miniMap = UIManager::CreateUIData(radar);
    
    GetGraphSize(miniMap.dataHandle[0], &mapGraphWidth, &mapGraphHeight);
    //�}�b�v�̑傫�������ɂ���
    mapSizeCoefficient = mapSize / mapGraphWidth;
    playerObserver = new ObjectObserver(racerManager->GetPlayerSubject(0));
}

MiniMap::~MiniMap()
{
}
/// <summary>
/// ���W�A�C�e���̈ʒu���X�V
/// </summary>
/// <param name="objInfo"></param>
/// <param name="setCollectPos"></param>
void MiniMap::Update( std::list<VECTOR> setCollectPos)
{
    mapRotate = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), playerObserver->GetSubDir()) * RAGE;
    //�v���C���[�̎Ԃ̌����ɍ��킹��
    mapRotate = VCross(VGet(1, 0, 0), playerObserver->GetSubDir()).y < 0 ? -mapRotate: mapRotate;
    coinPosList.clear();
    //���W�A�C�e�����~�j�}�b�v�ɔ��f
    for (auto ite = setCollectPos.begin(); ite != setCollectPos.end(); ite++)
    {
        VECTOR collectPos = *ite;
        collectPos.y = 0;

        VECTOR playerPos = playerObserver->GetSubPos();
        playerPos.y = 0;
        collectPos = VScale(VSub(collectPos, playerPos),collectBetween);
        //�}�b�v�̑傫���ɓ����Ă���Ȃ�
        if (VSize(collectPos) < mapGraphWidth)
        {
            OriginalMath::GetYRotateVector(collectPos, mapRotate);
            collectPos = ConvertPosition(collectPos);
            coinPosList.push_back(collectPos);
        }
    }
}

void MiniMap::Draw()
{
    //�g�`��
    DrawRotaGraph(miniMap.x, miniMap.y, mapSizeCoefficient, 0, miniMap.dataHandle[0], true);
    //�v���C���[�A�C�R���̕`��
    DrawCircle(miniMap.x, miniMap.y, iconSize, playerColor, 1, 1);
    //���W�A�C�e���̕`��
    for (auto ite = coinPosList.begin(); ite != coinPosList.end(); ite++)
    {
        DrawCircle(static_cast<int>((*ite).x), static_cast<int>((*ite).y), iconSize + 1, GetColor(0,0,0), 0, 1);
        DrawCircle(static_cast<int>((*ite).x), static_cast<int>((*ite).y), iconSize, coinColor, 1, 1);
    }
}

VECTOR MiniMap::ConvertPosition(VECTOR pos)
{
    VECTOR data;
    data.x = -pos.x * (mapGraphWidth / 2) / 6000 + miniMap.x;
    data.y = pos.z * (mapGraphHeight / 2) / 6000 + miniMap.y;
    return data;
}
