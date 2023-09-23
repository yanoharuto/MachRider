#include "GamePlayUI.h"
#include "Utility.h"
#include "MiniMap.h"
#include "TimerUI.h"
#include "Timer.h"
#include "NumUI.h"
#include "CollectController.h"
#include "PlayerObserver.h"
#include "EndCountDown.h"
#include "CollectCompass.h"
#include "UIDrawer.h"
#include "PlayManual.h"
#include "ReusableTimer.h"
#include "CollectItemObserver.h"
/// <summary>
/// �v���C���[�␧�����ԁA���W�A�C�e���̐��Ȃǂ�\���ł���悤�ɂ���
/// </summary>
/// <param name="player">�v���C���[�̈ʒu</param>
/// <param name="timer">��������</param>
/// <param name="collectItemObserver">���W�A�C�e�����</param>
GamePlayUI::GamePlayUI(std::weak_ptr<PlayerObserver> player, std::weak_ptr<Timer> timer, std::shared_ptr<CollectItemObserver> collectItemObserver)
{
    using enum UIKind;
    //�c�莞��
    gameTimerUI = new TimerUI(timer);
    //�~�j�}�b�v
    minimapUI = new MiniMap(player);
    //�c��̎��W�A�C�e���̐�
    firstCoinNum = collectItemObserver->GetTotalItemNum();
    firstCollectNumUI = new NumUI(allCollectItemNum);
    //���ݎ������
    getNumUI = new NumUI(getCollectItemNum);
    remainingNumUI = new NumUI(remainingCollectItemNum);
    //���W�A�C�e���Ɋւ���UI�̘g
    frameUIData = UIManager::CreateUIData(collectItemFrameUI);
    //�c����W�A�C�e���ɂ��ẴR�����gUI
    remainingFrazeUIData = UIManager::CreateUIData(remainingCollectItemPhrase);
    //�v���C���[�̃A�C�e���������������Ă��炤
    playerObserver = player;
    //���W�A�C�e���̕������o��
    collectCompass = new CollectCompass(player,collectItemObserver);
    //�Q�[���I���J�E���g�_�E��
    countDown = new EndCountDown(timer);
    //�c�莞��
    remainingNumDrawTimer = new ReusableTimer(remainingNumDrawTime);
    //������@
    playManual = new PlayManual();
}

/// <summary>
/// �eUI���J��
/// </summary>
GamePlayUI::~GamePlayUI()
{
    SAFE_DELETE(gameTimerUI);
    SAFE_DELETE(minimapUI);
    SAFE_DELETE(getNumUI);
    SAFE_DELETE(firstCollectNumUI);
    SAFE_DELETE(remainingNumUI);
    SAFE_DELETE(countDown);
    SAFE_DELETE(collectCompass);
    SAFE_DELETE(remainingNumDrawTimer);
    SAFE_DELETE(playManual);
    playerObserver.reset();
    UIManager::DeleteUIGraph(&remainingFrazeUIData);
    UIManager::DeleteUIGraph(&frameUIData);
}
/// <summary>
/// �~�j�}�b�v�̍X�V����W�A�C�e���̖������X�V
/// </summary>
void GamePlayUI::Update()
{
    int tempNum = nowGetCoinNum;
    //���W�A�C�e���̐�
    nowGetCoinNum = playerObserver.lock()->GetCollectCount();
    //�Q�b�g�����A�C�e���̐�����������UI��\��
    if (nowGetCoinNum != tempNum)
    {
        isDrawGetNum = true;
        remainingNumDrawTimer->Reuse();
    }
    //�\������������false�ɂ���
    if (remainingNumDrawTimer->IsOverLimitTime())
    {
        isDrawGetNum = false;
    }
    //�Q�[���̎c�莞�Ԃ��Z���Ȃ����瓮��
    countDown->Update();
    //�~�j�}�b�v
    minimapUI->Update();
    //���W�A�C�e���̈ʒu�������Ă����
    collectCompass->Update();
    //������@�X�V
    playManual->Update();
}
/// <summary>
/// �`��
/// </summary>
void GamePlayUI::Draw()const
{
    if (isDrawGetNum)//���W�A�C�e��������Ă��΂炭�̊ԁA�c��̐����o��
    {
        int safeNum = 0;
        switch (firstCoinNum - nowGetCoinNum)//�c��̃A�C�e���̐��ɉ����Ď�������̃��b�Z�[�W��ς���
        {
        case 0:
            break;
        case 1:
            safeNum = 1;
            //�c��̎��W�A�C�e���ɂ��Ẵ��b�Z�[�W
            safeNum %= remainingFrazeUIData.dataHandle.size();
            UIDrawer::DrawRotaUI(remainingFrazeUIData, safeNum);
            break;
        default:
            //�c��̎��W�A�C�e���ɂ��Ẵ��b�Z�[�W
            safeNum %= remainingFrazeUIData.dataHandle.size();
            UIDrawer::DrawRotaUI(remainingFrazeUIData, safeNum);
            remainingNumUI->Draw(firstCoinNum - nowGetCoinNum);
            break;
        }
        
    }
    //���W�A�C�e���̐�����\��
    UIDrawer::DrawRotaUI(frameUIData);
    firstCollectNumUI->Draw(firstCoinNum);
    getNumUI->Draw(nowGetCoinNum);
    //�c�莞��
    gameTimerUI->Draw();
    //�~�j�}�b�v
    minimapUI->Draw();
    //�c�莞�Ԃ킸���ɂȂ�Ɠ����J�E���g�_�E��
    countDown->DrawUI();
    //������@�`��
    playManual->Draw();
}