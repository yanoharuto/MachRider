#include "MiniMap.h"
#include "UIManager.h"
#include "OriginalMath.h"
#include "Object.h"
#include "Utility.h"
#include "UIDrawer.h"
#include "StageWall.h"
//自機のIconの大きさ
const int MiniMap::iconSize;
//ミニマップの画像の横幅
int MiniMap::mapGraphWidth;
//ミニマップの画像の縦幅
int MiniMap::mapGraphLength;

//ミニマップに表示する点
std::list<std::unique_ptr<ObjectObserver>> MiniMap::markerObserverList;
//ミニマップのデータ
UIData MiniMap::miniMap;
/// <summary>
/// 収集アイテムとかを描画するための奴
/// </summary>
MiniMap::MiniMap(std::weak_ptr<ObjectObserver> player)
{
    miniMap = UIManager::CreateUIData(radar);
    
    GetGraphSize(miniMap.dataHandle[0], &mapGraphWidth, &mapGraphLength);

    playerObserver = player;

    betweenSize = mapGraphWidth / StageWall::GetStageWidth() * betweenSize;
}

MiniMap::~MiniMap()
{
    //描画するリストを全消し
    for (auto itr = markerObserverList.begin(); itr != markerObserverList.end(); itr++)
    {
        (*itr).reset();
    }
    markerObserverList.clear();
}
/// <summary>
/// 収集アイテムの位置を更新
/// </summary>
/// <param name="objInfo"></param>
void MiniMap::Update()
{
    //プレイヤーがマップの中心になるようにする
    VECTOR playerPos = playerObserver.lock()->GetSubjectPos();
    playerPos.y = 0;
    //今動いている収集アイテムだけマップに反映
    drawPosList.clear();
    for (auto ite = markerObserverList.begin(); ite != markerObserverList.end(); ite++)
    {
        //アクティブなオブジェクトをマップに反映
        if ((*ite)->GetSubjectState() == Object::active)
        {
            VECTOR itePos = (*ite)->GetSubjectPos();
            VECTOR distance = VSub(itePos, playerPos);
            distance.y = 0;
            //距離がマップに反映可能な大きさなら
            if (VSize(distance) * betweenSize < miniMap.width / 2 * miniMap.size)
            {
                distance = ConvertPosition(distance);
                
                drawPosList.push_back(distance);
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
    UIDrawer::DrawRotaUI(miniMap);
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
void MiniMap::AddMarker(std::unique_ptr<ObjectObserver> obserber)
{
    markerObserverList.push_back(std::move(obserber));
}
/// <summary>
/// ミニマップの大きさに変換する
/// </summary>
/// <param name="between">中央のアイテムからの距離</param>
/// <returns></returns>
VECTOR MiniMap::ConvertPosition(VECTOR between)
{
    //マップの中央物の向きとマーカーの位置の角度差
    float rotate = OriginalMath::GetDegreeMisalignment(between, playerObserver.lock()->GetSubjectDir());
    //右側か左側か
    rotate = VCross(between, playerObserver.lock()->GetSubjectDir()).y < 0 ? -rotate : rotate ;
    //角度分曲がっている行列で距離を曲げる
    MATRIX pM = MGetRotY(-rotate * RAGE);
    between = VTransform(VGet(0, 0, -VSize(between)), pM);
    //ミニマップの大きさに変換
    VECTOR data;
    data.x = -between.x * betweenSize + miniMap.x;
    data.y = between.z * betweenSize + miniMap.y;
    return data;
}
