#pragma once

//fps
#define FLAME 60
/// <summary>
/// �Q�[�����̎��Ԃ��X�V
/// </summary>
class Clock
{
public:
    Clock();
    ~Clock();
    /// <summary>
    /// �^�C�}�[���X�V����
    /// </summary>
    void Update();
    /// <summary>
    /// 1000m�b�𕁒ʂ̕b���ɂ��ēn��
    /// </summary>
    /// <returns></returns>
    static double GetNowGameTime();
private:
    //1000m�b
    double timeD;
    //���ʂ̌o�ߕb��
    static double gameTime;
};