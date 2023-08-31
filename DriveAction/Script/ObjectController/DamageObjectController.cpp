#include "DamageObjectController.h"
/// <summary>
/// ダメージ判定のあるオブジェクトの管理クラス
/// </summary>
/// <param name="kind">初期化する種類</param>
DamageObjectController::DamageObjectController(ObjectInit::InitObjKind kind)
    :ActorController(kind)
{
};