#pragma once
#include <string>
#include <vector>
class StageWall;
class Rock;
class FirstPositionGetter;
/// <summary>
/// ����ꏊ
/// </summary>
class CircuitTrack final
{
public:
    /// <summary>
    /// ������
    /// </summary>
    CircuitTrack(FirstPositionGetter* firstPosGetter);
    ///model���f���[�g
    ~CircuitTrack();
    /// <summary>
    /// �R�[�X�̃��f����`��
    /// </summary>
    void Draw();
private:

    //�R�[�X�̊O����model�̃|�W�V����
    const float rockYPos = 20;
    //�n��
    int floorModelHandle;
    std::vector<Rock*> rocks;
    StageWall* stageWall;
};