#pragma once
#include <vector>
#include <unordered_map>
#include "InitActor.h"

class ActorController;
using namespace ObjectInit;
/// <summary>
/// �G�@�̃}�l�[�W���[
/// </summary>
class EnemyGenerator
{
public:
    /// <summary>
/// �G�@�̏���������
/// </summary>
    EnemyGenerator() {};

    ~EnemyGenerator() {};
    std::vector<ActorController*> CreateActorController(InitObjKind kind,  std::unordered_map<int, std::vector<VECTOR>> generatePosMap);
    
private:

};