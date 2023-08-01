#include "Object.h"
#include "InitActor.h"
/// <summary>
/// オブジェクトの種類を渡して
/// </summary>
/// <param name="kind"></param>
Object::Object(ObjectInit::InitObjKind kind)
{
    InitParamater(kind);
}
Object::~Object()
{
 
}
/// <summary>
/// コンストラクタで呼ばれる処理
/// </summary>
void Object::InitParamater(ObjectInit::InitObjKind kind)
{
    ActorParameter initParam = InitActor::GetActorParamator(kind);
    //ポジション
    position.y = initParam.firstPosY;
    //向き
    direction = { 1,0,0 };
    //跳ね返り力
    bouncePower = initParam.setBouncePow;
    //半径
    radius = initParam.setRadius;
    //modelの大きさ
    modelSize = initParam.setModelSize;
}
/// <summary>
/// 位置や向きをVelocityに合わせて更新する
/// </summary>
void Object::ReflectsVelocity()
{
    // 力をかけ終わったベロシティの方向にディレクションを調整.
    if (VSize(velocity) != 0)
    {
        direction = VNorm(velocity);
    }
    // ポジションを更新.
    position = VAdd(position, velocity);
}
