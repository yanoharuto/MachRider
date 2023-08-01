#pragma once
#include <list>
#include <unordered_map>
#include <memory>
#include <iostream>
class ObjectObserver;
class DamageObjectController;
class ActorControllerManager;
/// <summary>
/// 投擲アイテムなどのダメージがあるオブジェクトを生成する
/// </summary>
class DamageObjectGenerator final
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
    DamageObjectGenerator(ActorControllerManager* const controllerManager);
    ~DamageObjectGenerator();
    /// <summary>
    /// ダメージを与えるオブジェクトを生成
    /// </summary>
    /// <param name="itemTag"></param>
    /// <param name="sub">発射した人の情報を渡す</param>
    /// <returns></returns>
    static void GenerateDamageObject(DamageObjectKind itemTag, std::unique_ptr<ObjectObserver> sub);
private:
    //作成したコントローラークラス。GetControllerListが呼ばれると初期化される
    static std::unordered_map<DamageObjectKind, DamageObjectController*> controllerVec;
    
};