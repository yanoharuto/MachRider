#pragma once
#include <vector>
#include <unordered_map>
#include "InitActor.h"

class ActorController;
using namespace ObjectInit;
/// <summary>
/// 敵機のマネージャー
/// </summary>
class EnemyGenerator
{
public:
    /// <summary>
/// 敵機の初期化する
/// </summary>
    EnemyGenerator() {};

    ~EnemyGenerator() {};
    std::vector<ActorController*> CreateActorController(InitObjKind kind,  std::unordered_map<int, std::vector<VECTOR>> generatePosMap);
    
private:

};