#pragma once
#include "DxLib.h"
#include "InitObjKind.h"
#include <list>
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
    enum FlyShipParamator
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
using namespace FlyShipInit;
/// <summary>
/// 空を飛ぶ船のまとめ役
/// </summary>
class FlyShipController abstract : public AddableObjectController
{
public:
    /// <summary>
    /// 初期化するために必要なデータを所得
    /// </summary>
    /// <param name="kind">初期化したいFlyShipの種類</param>
    FlyShipController(ObjectInit::InitObjKind kind);
protected:
    /// <summary>
    /// 初期化するために必要なデータを所得
    /// </summary>
    /// <param name="kind">初期化したいFlyShipの種類</param>
    /// <returns>初期化データ</returns>
    InitFlyShipParamator GetInitData(ObjectInit::InitObjKind kind);
    //初期化情報
    InitFlyShipParamator param = {};
};

