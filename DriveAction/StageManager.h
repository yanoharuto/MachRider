#pragma once
#include <string>
class CircuitTrack;
class SkyDome;
class FirstPositionGetter;
/// <summary>
/// �R�[�X�̃��[�h��`��Ƃ������蔻��Ƃ�����
/// </summary>
class StageManager
{
public:
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    StageManager();
    ~StageManager();
    void Update();
    void Draw()const;
    
private:
    CircuitTrack* circuit;
    SkyDome* skyDome;
    FirstPositionGetter* firstPositionGeneratetor;

};