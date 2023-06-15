#include "Saw.h"
#include "InitObjKind.h"
#include "OriginalMath.h"
#include "SphereCollider.h"
#include "Utility.h"
Saw::Saw()
    
{
}

Saw::Saw(VECTOR pos)
    :Actor(ObjectInit::saw)
{
    pos.y = position.y;
    position = pos;
    collider = new SphereCollider(this);
    tag = damageObject;
}

Saw::~Saw()
{
    SAFE_DELETE(collider);
}

void Saw::Update()
{
    direction = OriginalMath::GetYRotateVector(direction,addRotate);
}
