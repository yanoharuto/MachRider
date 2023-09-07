#include "DamageObjectController.h"
/// <summary>
/// 初期化
/// </summary>
/// <param name="kind">初期化したいオブジェクトの種類</param>
DamageObjectController::DamageObjectController(ObjectInit::InitObjKind kind)
    :ActorController(kind)
{
}