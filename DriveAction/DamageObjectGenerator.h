#pragma once
#include <list>

class ObjectSubject;
class DamageObject;
class ActorController;
class ActorControllerManager;
/// <summary>
/// 投擲アイテムなどのダメージがあるオブジェクトを生成する
/// </summary>
class DamageObjectGenerator
{
public:
    /// <summary>
    /// ダメージ判定のある物の種類
    /// </summary>
    enum DamageObjectKind
    {
        bomber,
        littleRadLaser,
        bigRadLaser
    };
    /// <summary>
    /// デフォルトコンストラクタ
    /// </summary>
    DamageObjectGenerator();
    ~DamageObjectGenerator();
    /// <summary>
    /// ダメージを与えるオブジェクトを生成
    /// </summary>
    /// <param name="itemTag"></param>
    /// <param name="sub">発射した人の情報を渡す</param>
    /// <returns></returns>
    static void GenerateDamageObject(DamageObjectKind itemTag,ObjectSubject* sub);
    /// <summary>
    /// 生成されたオブジェクトをcontrollerManagerに追加
    /// </summary>
    /// <param name="controllerManager"></param>
    void MoveControllerList(ActorControllerManager* controllerManager);
private:
    //作成したコントローラークラス。GetControllerListが呼ばれると初期化される
    static std::list<ActorController*> createDamageObject;
};