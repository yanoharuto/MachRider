#include "MiniMap.h"
#include "UIManager.h"
#include "CourceDataLoader.h"
#include "OriginalMath.h"
#include "ObjectObserver.h"
#include "RacerManager.h"
#include "ObjectObserver.h"
/// <summary>
/// 収集アイテムとかを描画するための奴
/// </summary>
MiniMap::MiniMap(RacerManager* racerManager)
{
    miniMap = UIManager::CreateUIData(radar);
    
    GetGraphSize(miniMap.dataHandle[0], &mapGraphWidth, &mapGraphHeight);
    //マップの大きさを一定にする
    mapSizeCoefficient = mapSize / mapGraphWidth;
    playerObserver = new ObjectObserver(racerManager->GetPlayerSubject(0));
}

MiniMap::~MiniMap()
{
}
/// <summary>
/// 収集アイテムの位置を更新
/// </summary>
/// <param name="objInfo"></param>
/// <param name="setCollectPos"></param>
void MiniMap::Update( std::list<VECTOR> setCollectPos)
{
    mapRotate = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), playerObserver->GetSubDir()) * RAGE;
    //プレイヤーの車の向きに合わせる
    mapRotate = VCross(VGet(1, 0, 0), playerObserver->GetSubDir()).y < 0 ? -mapRotate: mapRotate;
    coinPosList.clear();
    //収集アイテムをミニマップに反映
    for (auto ite = setCollectPos.begin(); ite != setCollectPos.end(); ite++)
    {
        VECTOR collectPos = *ite;
        collectPos.y = 0;

        VECTOR playerPos = playerObserver->GetSubPos();
        playerPos.y = 0;
        collectPos = VScale(VSub(collectPos, playerPos),collectBetween);
        //マップの大きさに入っているなら
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
    //枠描画
    DrawRotaGraph(miniMap.x, miniMap.y, mapSizeCoefficient, 0, miniMap.dataHandle[0], true);
    //プレイヤーアイコンの描画
    DrawCircle(miniMap.x, miniMap.y, iconSize, playerColor, 1, 1);
    //収集アイテムの描画
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
