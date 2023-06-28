#pragma once
#include <iostream>
#include<memory>
class ObjectObserver;
/// <summary>
/// ���𕷂��Ă���I�u�W�F�N�g�̏ꏊ���X�V
/// </summary>
class SoundListener
{
public:
    /// <summary>
    /// ���𕷂���̃|�C���^�[��Ⴄ
    /// </summary>
    /// <param name="listener"></param>
     SoundListener(std::weak_ptr<ObjectObserver> listener);
     ~SoundListener();
    /// <summary>
    /// ���X�i�[�̈ʒu�𔽉f
    /// </summary>
    void Update();
private:
    
    //���𕷂��Ă���I�u�W�F�N�g
    std::weak_ptr<ObjectObserver> listener;
};
