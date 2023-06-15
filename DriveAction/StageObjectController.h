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
    StageObjectController(FirstPositionGetter* firstPosGetter);
    ///model���f���[�g
    ~StageObjectController() override;
    /// <summary>
    /// �R�[�X�̃��f����`��
    /// </summary>
    void Draw()const override;
private:

    //�R�[�X�̊O����model�̃|�W�V����
    const float rockYPos = 20;
    //�n��
    int floorModelHandle;
    int skyDomeModelHandle;
};