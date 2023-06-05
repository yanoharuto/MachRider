#include <math.h>
#include "CPUCar.h"
#include "Wheels.h"
#include "Utility.h"
#include "InitActor.h"
CarInfomation setCarParam =
{
    120.0f,
    120.0f,
    5.0f,
    0.6f,
    6.0f,
    0.07f,
    3.5f,
};
/// <summary>
/// 初期化
/// </summary>
/// <returns></returns>
CPUCar::CPUCar()
{
}
CPUCar::CPUCar(VECTOR firstPos, VECTOR destinaTionPos)
    :Car(setCarParam,ObjectInit::player)
{
    position = firstPos;
    position.y = firstPosY;
    direction = VGet(1.0f, 0.0f, 0.0f);
    destinationPosition = destinaTionPos;
}
/// <summary>
/// modelとタイヤの後始末
/// </summary>
/// <returns></returns>
CPUCar::~CPUCar()
{
    SAFE_DELETE(wheels)
}
/// <summary>
/// 自動操縦。
/// </summary>
/// <param name="deltaTime">フレーム間差分</param>
/// <param nadme="outsideHitFlag">コース外に出たか</param>
void CPUCar::Update()
{}