#pragma once
#include "ActorController.h"
#include "DxLib.h"
class Coin;
class ObjectSubject;
/// <summary>
/// �ʒu���~�j�}�b�v�ɋ������肷��
/// </summary>
class CollectController final:public ActorController
{
public:
    /// <summary>
    /// �R�C���̐ݒu
    /// </summary>
    CollectController(VECTOR generatePos);
    void Update()override;

private:
    ObjectSubject* subject;
};
