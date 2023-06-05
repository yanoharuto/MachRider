#pragma once
#include <list>
#include <unordered_map>
#include "ObjectObserver.h"
class Timer;
class FlyShipCommander;
class RacerManager;
/// <summary>
/// �G�@�̃}�l�[�W���[
/// </summary>
class FlyShipManager
{
public:
    /// <summary>
    /// �G�@�̏���������
    /// </summary>
    FlyShipManager(RacerManager* racerManager);

    ~FlyShipManager();
    /// <summary>
    /// �G�@�����̍X�V
    /// </summary>
    /// <param name="infoCenter"></param>
    void Update();
    /// <summary>
    /// �`��
    /// </summary>
    void Draw();
private:
    //�G�@�̃}�b�v
    std::unordered_map<int, std::list<FlyShipCommander*>> commanderMap;
    //�����@�ė��p�̃^�C�}�[
    Timer* bomberFlyShipGoTimer;
    //�v���C���[�̈ʒu
    ObjectObserver* playerObserver;
};