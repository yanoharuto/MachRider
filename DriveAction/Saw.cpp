#include "Saw.h"
#include "InitObjKind.h"
#include "OriginalMath.h"
#include "SphereCollider.h"
#include "Utility.h"
#include "ConflictManager.h"
/// <summary>
/// 回転のこぎり
/// </summary>
/// <param name="arrangementData"></param>
Saw::Saw(EditArrangementData arrangementData)
    :Actor(saw)
{
    position.x = arrangementData.posX;
    position.z = arrangementData.posZ;
    collider = new SphereCollider(this);
    ConflictManager::AddHitChecker(collider);
    tag = damageObject;
    direction = VGet(arrangementData.dirX, 0, arrangementData.dirZ);
}
/// <summary>
/// 当たり判定消去
/// </summary>
Saw::~Saw()
{
    ConflictManager::EraceHitChecker(collider);
    SAFE_DELETE(collider);
}
/// <summary>
/// 回転する
/// </summary>
void Saw::Update()
{
    direction = VNorm(OriginalMath::GetYRotateVector(direction,addRotate));
}
