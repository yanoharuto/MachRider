#pragma once
#include<memory>
#include<iostream>
#include <list>
#include "DxLib.h"
#include "InitObjKind.h"
#include "InitActor.h"
#include "AddableObjectController.h"
namespace FlyShipInit
{
    /// <summary>
    /// 空を飛ぶ船の初期化情報
    /// </summary>
    struct InitFlyShipParamator
    {
        //大きさとかmodelのパスとか当たり判定の大きさとか
        ActorParameter actorParam;
        //生存時間
        float setAliveTime;
        //移動速度
        float moveSpeed;
        //発射のクールタイム
        float setCoolTime;
        //ユニット同士の距離
        float unitBetween;
        //団体行動する場合の構成数
        int unitNum;
    };
    /// <summary>
    /// 空を飛ぶ船のパラメータ情報
    /// </summary>
    enum class FlyShipParamator
    {
        //生存時間
        aliveTime = 2,

        //移動速度
        moveSpeed = 5,

        //何かしら発射する時間
        coolTime = 8,

        //構成数
        unitNum = 11,

        //攻勢ユニット同士の距離
        unitBetween = 14
    };
}
class FlyShip;
class DamageObjectGenerator;
using namespace FlyShipInit;
/// <summary>
/// 空を飛ぶ船のまとめ役
/// </summary>
class FlyShipController abstract : public AddableObjectController
{
public:
    /// <summary>
    /// 纏める飛行船の初期化するために必要なデータを所得 
    /// 飛行船が発射する物を生成できるdamageObjGeneratorを所得
    /// </summary>
    /// <param name="kind">初期化したいFlyShipの種類</param>
    /// <param name="damageObjGenerator">レーザーや爆弾を発射するのに使う</param>
    FlyShipController(ObjectInit::InitObjKind kind, std::shared_ptr<DamageObjectGenerator> damageObjGenerator);
    /// <summary>
    /// actorListとDrawModelとdamageObjectGeneratorの解放
    /// </summary>
    ~FlyShipController()override;
protected:
    /// <summary>
    /// 初期化するために必要なデータを所得
    /// </summary>
    /// <param name="kind">初期化したいFlyShipの種類</param>
    /// <returns>初期化データ</returns>
    InitFlyShipParamator GetInitData(ObjectInit::InitObjKind kind);
    //初期化情報
    InitFlyShipParamator param = {};
    //レーザーや爆弾を発射するのに使う
    std::shared_ptr<DamageObjectGenerator> damageObjectGenerator;
};