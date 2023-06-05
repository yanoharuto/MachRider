#include "Enemy.h"

Enemy::Enemy(CarInfomation carParam, int duplicateModelHandle)
{
    MV1SetScale(modelHandle, {scale,scale,scale});
}

Enemy::~Enemy()
{
}

void Enemy::Update(const  VECTOR playerPos, ItemInfo itemInfo)
{
}

void Enemy::Draw()
{
    MV1DrawModel(modelHandle);
}
