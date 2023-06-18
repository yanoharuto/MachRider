#pragma once
#include <iostream>
#include <memory>
#include <list>
#include "ActorController.h"
#include "DxLib.h"
class Coin;
class ObjectSubject;
class ObjectObserver;
/// <summary>
/// �ʒu���~�j�}�b�v�ɋ������肷��
/// </summary>
class CollectController final:public ActorController
{
public:
    /// <summary>
    /// �R�C���̐ݒu
    /// </summary>
    CollectController();
    void Update()override;
    void Draw()const override;
    /// <summary>
    /// ������Vector�Ƃ̃N���X�ς�Y����
    /// </summary>
    /// <param name="vec"></param>
    /// <returns></returns>
    static float GetCollectItemDegreeDifference(std::weak_ptr<ObjectObserver> observer);
private:
    std::list<ObjectSubject*> subjectList;
    static VECTOR nowActiveCollectItemPos;
};
