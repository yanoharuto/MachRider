#include "GamePlayUI.h"
#include "Utility.h"
#include "MiniMap.h"
#include "TimerUI.h"
#include "Timer.h"
#include "NumUI.h"
#include "CollectController.h"
#include "ObjectObserver.h"
#include "EndCountDown.h"
#include "CollectSign.h"

/// <summary>
/// �V��ł���Ƃ���UI�@�������ԂƂ�
/// </summary>
/// <param name="setTimer"></param>
/// <param name="setFirstCoinNum"></param>
GamePlayUI::GamePlayUI(Timer* setTimer, std::weak_ptr<ObjectObserver> player)
{
    //�c�莞��
    gameTimerUI = new TimerUI(setTimer);
    //�~�j�}�b�v
    minimapUI = new MiniMap(player);
    manualData = UIManager::CreateUIData(manual);

    
    //�c��̎��W�A�C�e���̐��ƌ��ݎ������
    firstCoinNum = CollectController::GetTotalCollectNum();
    firstNumUI = new NumUI(allCollectItemNum);
    getNumUI = new NumUI(getCollectItemNum);
    remainingNumUI = new NumUI(remainingCollectItemNum);
    slashData = UIManager::CreateUIData(collectItemUI);
    remainingFraze = UIManager::CreateUIData(remainingCollectItemPhrase);

    //���W�A�C�e���̕������o��
    cSign = new CollectSign(player);

    playerObserver = player;
    countDown = new EndCountDown(setTimer);
    remainingNumDrawTimer = new Timer(remainingNumDrawTime);
}


GamePlayUI::~GamePlayUI()
{
    SAFE_DELETE(gameTimerUI);
    SAFE_DELETE(minimapUI);
    SAFE_DELETE(getNumUI);
    SAFE_DELETE(firstNumUI);
    SAFE_DELETE(remainingNumUI);
    SAFE_DELETE(countDown);
    SAFE_DELETE(cSign);
    SAFE_DELETE(remainingNumDrawTimer);
    playerObserver.reset();
}
/// <summary>
/// �~�j�}�b�v�̍X�V����W�A�C�e���̖������X�V
/// </summary>
void GamePlayUI::Update()
{
    int tempNum = nowGetCoinNum;
    nowGetCoinNum = playerObserver.lock()->GetSubjectHitCount(Object::ObjectTag::collect);
    //�Q�b�g�����A�C�e���̐�����������UI��\��
    if (nowGetCoinNum != tempNum)
    {
        isDrawGetNum = true;
        remainingNumDrawTimer->Init();
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
    cSign->Update();
}
/// <summary>
/// �`��
/// </summary>
void GamePlayUI::Draw()const
{
    //�������
    DrawRotaGraph(manualData.x, manualData.y, manualData.size, 0, manualData.dataHandle[0], true);
    if (isDrawGetNum)//���W�A�C�e��������Ă��΂炭�̊ԁA�c��̐����o��
    {
        int safeNum = 0;
        switch (firstCoinNum - nowGetCoinNum)//�c��̃A�C�e���̐��ɉ����Ď�������̃��b�Z�[�W��ς���
        {
        case 0:
            safeNum = 2;
            break;
        case 1:
            safeNum = 1;
            remainingNumUI->Draw(firstCoinNum - nowGetCoinNum);
            break;
        default:
            remainingNumUI->Draw(firstCoinNum - nowGetCoinNum);
            break;
        }
        safeNum %= remainingFraze.dataHandle.size();
        DrawRotaGraph(remainingFraze.x, remainingFraze.y,remainingFraze.size,0,remainingFraze.dataHandle[safeNum],true);
        
    }
    //���W�A�C�e���̐�����\��
    DrawRotaGraph(slashData.x, slashData.y, slashData.size, 0, slashData.dataHandle[0], true);
    firstNumUI->Draw(firstCoinNum);
    getNumUI->Draw(nowGetCoinNum);
    //�c�莞��
    gameTimerUI->Draw();
    //�~�j�}�b�v
    minimapUI->Draw();
    //�c�莞�Ԃ킸���ɂȂ�Ɠ����J�E���g�_�E��
    countDown->DrawUI();
}