#pragma once
namespace ObjectInit
{
    /// <summary>
    /// 初期化するオブジェクトの種類
    /// </summary>
    enum InitObjKind
    {
        //プレイヤー機
        player = 2,
        //小さい岩
        littleRock = 5,
        //中くらいの岩
        middleRock = 8,
        //大きい岩
        bigRock = 11,
        //回転丸鋸
        saw = 14,
        //爆撃機
        bomberShip = 17,
        //爆弾
        bomber = 20,
        //上下にレーザー撃つ飛行船
        upDownLaserShip = 23,
        //円状に並ぶ機体
        circleLaserShip = 26,
        //小回りレーザー
        littleRadiusLaser = 29,
        //大回りレーザー
        bigRadiusLaser = 32,
        //タイヤ
        wheel = 35,
        //コイン
        collect = 38,
        //床
        stageFloor = 41,
        //スカイドーム
        skyDome = 44,
        //ステージの外に出ないようにする壁
        wall = 47
    };
}