#pragma once
#include <iostream>
#include <memory>
class PlayerObserver;
class GamePlayUI;
class GameManager;
class StopTimer;
class Timer;
/// <summary>
/// �Q�[�����̏�����
/// </summary>
class PlayGameProcess
{
public:
    /// <summary>
    /// �v���C���[�̈ʒu��UI�ɓn��
    /// </summary>
    /// <param name="manager">UI�Ƀv���C���[�̈ʒu��n��</param>
    PlayGameProcess(std::weak_ptr<GameManager> const manager);
    /// <summary>
    /// UI�ƃ^�C�}�[�̉��
    /// </summary>
    ~PlayGameProcess();
    /// <summary>
    /// �V��ł���Ƃ��̍X�V
    /// </summary>
    /// <param name="manager">�Q�[��������Ƃ��ɕK�v�ȃI�u�W�F�N�g</param>
    void Update(std::weak_ptr<GameManager> const manager);
    /// <summary>
    /// �`��
    /// </summary>
    void Draw()const;
    /// <summary>
    /// �Q�[�������̏����̏I��
    /// </summary>
    /// <returns></returns>
    bool IsEndProcess()const
    {
        return isEndProcess;
    };
    /// <summary>
    /// �Q�[���̎c�莞�ԃ^�C�}�[��n��
    /// </summary>
    /// <returns> �Q�[���̎c�莞�ԃ^�C�}�[��n��</returns>
    std::shared_ptr<Timer> GetGameTimer();
    
private:
    //�������Ԃ̃^�C�}�[
    std::shared_ptr<StopTimer> timer;
    //�V��ł���Ƃ���UI
    GamePlayUI* playUI;
    //�����I���t���O
    bool isEndProcess;
};