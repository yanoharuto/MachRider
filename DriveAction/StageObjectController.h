#pragma once
#include <string>
#include <vector>
#include "ActorController.h"
class StageWall;
class Rock;
class FirstPositionGetter;
/// <summary>
/// ����ꏊ
/// </summary>
class StageObjectController final:public ActorController
{
public:
    /// <summary>
    /// ������
    /// </summary>
    StageObjectController();
    ///model���f���[�g
    ~StageObjectController() override;
    /// <summary>
    /// �R�[�X�̃��f����`��
    /// </summary>
    void Draw()const override;
    /// <summary>
    /// �V�[�����؂�ւ���܂ł͂����Ƃ���
    /// </summary>
    /// <returns></returns>
    bool IsAlive()const override;
private:
    //�n��
    int floorModelHandle;
    //��
    int skyDomeModelHandle;
    //��
    StageWall* stageWall;
};