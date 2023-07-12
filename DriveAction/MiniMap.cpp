#include "MiniMap.h"
#include "UIManager.h"
#include "OriginalMath.h"
#include "ObjectObserver.h"
#include "Object.h"
#include "Utility.h"
//自機のIconの大きさ
const int MiniMap::iconSize;
//ミニマップの画像の横幅
int MiniMap::mapGraphWidth;
//ミニマップの画像の縦幅
int MiniMap::mapGraphHeight;
//マップの大きさ
const float MiniMap::mapSize = 420;
//収集物の位置の縮尺
const float MiniMap::collectBetween = 0.3f;
//マップの大きさの係数
float MiniMap::mapSizeCoefficient = 0;
//ミニマップに表示する点
std::list<ObjectObserver*> MiniMap::markerObserverList;
//ミニマップのデータ
UIData MiniMap::miniMap;
/// <summary>
/// 収集アイテムとかを描画するための奴
/// </summary>
MiniMap::MiniMap(std::weak_ptr<ObjectObserver> player)
{
    miniMap = UIManager::CreateUIData(radar);
    
    GetGraphSize(miniMap.dataHandle[0], &mapGraphWidth, &mapGraphHeight);
    //マップの大きさを一定にする
    mapSizeCoefficient = mapSize / mapGraphWidth;
    playerObserver = player;
}

MiniMap::~MiniMap()
{
    //描画するリストを全消し
    for (auto itr = markerObserverList.begin(); itr != markerObserverList.end(); itr++)
    {
        SAFE_DELETE((*itr));
    }
    markerObserverList.clear();
}
/// <summary>
/// 収集アイテムの位置を更新
/// </summary>
/// <param name="objInfo"></param>
void MiniMap::Update()
{
    mapRotate = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), playerObserver.lock()->GetSubjectDir()) * RAGE;
    //プレイヤーの車の向きに合わせる
    mapRotate = VCross(VGet(1, 0, 0), playerObserver.lock()->GetSubjectDir()).y < 0 ? -mapRotate : mapRotate;

    VECTOR playerPos = playerObserver.lock()->GetSubjectPos();
    playerPos.y = 0;
    drawPosList.clear();
    //収集アイテムのリストをマップに反映できるようにする
    for (auto ite = markerObserverList.begin(); ite != markerObserverList.end(); ite++)
    {
        //アクティブなオブジェクトをマップに反映
        if ((*ite)->GetSubjectState() == Object::active)
        {
            VECTOR pos = VScale(VSub((*ite)->GetSubjectPos(), playerPos), collectBetween);
            //マップの大きさに入っているなら
            if (VSize(pos) < mapGraphWidth)
            {
                OriginalMath::GetYRotateVector(pos, mapRotate);
                pos = ConvertPosition(pos);
                drawPosList.push_back(pos);
            }
        }
    }
}
/// <summary>
/// マップに表示する点とレーダーの枠
/// </summary>
void MiniMap::Draw()const
{
    //枠描画
    DrawRotaGraph(miniMap.x, miniMap.y, mapSizeCoefficient, 0, miniMap.dataHandle[0], true);
    //プレイヤーアイコンの描画
    DrawCircle(miniMap.x, miniMap.y, iconSize, playerColor, 1, 1);
    //収集アイテムの描画
    for (auto ite = drawPosList.begin(); ite != drawPosList.end(); ite++)
    {
        DrawCircle(static_cast<int>((*ite).x), static_cast<int>((*ite).y), iconSize + 1, GetColor(0,0,0), 0, 1);
        DrawCircle(static_cast<int>((*ite).x), static_cast<int>((*ite).y), iconSize, coinColor, 1, 1);
    }
}
/// <summary>
/// マップに反映させたいアイテムの追加
/// </summary>
/// <param name="obserber"></param>
void MiniMap::AddMarker(ObjectObserver* obserber)
{
    markerObserverList.push_back(obserber);
}

VECTOR MiniMap::ConvertPosition(VECTOR pos)
{
    VECTOR data;
    data.x = -pos.x * (mapGraphWidth / 2) / 6000 + miniMap.x;
    data.y = pos.z * (mapGraphHeight / 2) / 6000 + miniMap.y;
    return data;
}
