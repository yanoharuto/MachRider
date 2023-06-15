#pragma once
#include <vector>
#include <string>
#include <unordered_map>

namespace UIInit
{
    //UI�̎��
    enum UIKind
    {
        //�Q�[���̖ڕW
        gamePurose = 2,
        //�J�E���g�_�E��
        countDownUI = 5,
        //�R���N�g�A�C�e���̎c�萔�Ȃǂ�UI
        collectItemUI = 8,
        //���W���̃X�R�A�̕���
        collectScore = 11,
        //���W���̃X�R�A
        collectScoreNum = 14,
        //�_���[�W���󂯂�ƌ�������X�R�A�̕���
        damageScore = 17,
        //�_���[�W���󂯂�ƌ�������X�R�A
        damageScoreNum = 20,
        //�������
        manual = 26,
        //�����_
        point = 29,
        //���[�_�[
        radar = 32,
        //�^�C�g�����S
        tilteLogo = 35,
        //�^�C�}�[�̘g
        timerFrame = 38,
        //�c�莞�ԃX�R�A�̕���
        timeScore = 41,
        //�c�莞�Ԃ̃X�R�A
        timeScoreNum = 44,
        //���v�X�R�A�̕���
        totalScore = 47,
        //���v�X�R�A
        totalScoreNum = 50,
        //���W�A�C�e���̍ŏ��̐��ɂ��Ă�UI
        allCollectItemNum = 23,
        //���W�A�C�e���̂����Q�b�g�������ɂ���
        getCollectItemNum = 53,
        //�c�莞��
        timeNum = 56,
        //���j���[��ʂ̘g
        menuFrame = 59,
        //�v���C���s
        playUI = 62,
        //���g���C
        retryUI = 65,
        //���j���[��ʂ̃J�[�\��
        menuCursor = 68,
        //�Q�[���I��UI
        exitUI = 71,
        //�^�C�g����ʂŃX�e�[�W�I��������Ƃ��Ɏg��
        stageName = 74
    };
    /// <summary>
    /// UI�̏��������@�����͓ǂݍ��ݒi��
    /// </summary>
    enum InitUIData
    {
        //�`��ꏊX
        drawX = 1,
        //Y
        drawY = 3,
        //�摜����
        width = 5,
        //�摜�c��
        height = 7,
        //����������
        xNum = 9,
        //�c������
        yNum = 11,
        //�摜�̑��΃p�X
        graphPass = 13,
        //�傫��
        UISize = 15,
        //�������Ă���ꍇ�̃R�}����X�s�[�h
        frameSpeed = 17
    };
    /// <summary>
    /// UI�Ŏ��ۂɎg�����
    /// </summary>
    struct  UIData
    {
        //�`��ꏊX
        int x = 0;
        //�`��ꏊY
        int y = 0;
        //������̉摜����
        int width = 0;
        //������̉摜�c��
        int height = 0;
        //�摜�n���h��
        std::vector<int> dataHandle;
        //�傫��
        float size = 0.0f;
        //�R�}���葬�x
        float frameSpeed = 0.0f;
    };
}
using namespace UIInit;
/// <summary>
/// UI��Z�߂�}�l�[�W���[
/// </summary>
class UIManager
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <returns></returns>
    UIManager();
    ~UIManager();
    static UIData CreateUIData(UIKind uiKind);
    static UIData CreateUIData(int kindNum);
 private:
    static std::vector<std::string> initDataVec;
    static std::unordered_map<int,int*> loadGraphs;
    const std::string initUIDataPassFile = "data/UI/InitUIPass.csv";
};