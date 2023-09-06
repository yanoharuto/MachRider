#include "PlayGameProcess.h"
#include "ConflictManager.h"
#include "ActorControllerManager.h"
#include "GamePlayUI.h"
#include "CollectController.h"
#include "GameManager.h"
#include "SoundPlayer.h"
#include "PostGameEndStagingProcess.h"
#include "StageDataManager.h"
#include "Utility.h"
#include "StopTimer.h"
#include "Timer.h"
/// <summary>
/// �v���C���[�̈ʒu��UI�ɓn��
/// </summary>
/// <param name="manager">UI�Ƀv���C���[�̈ʒu��n��</param>
PlayGameProcess::PlayGameProcess(std::weak_ptr<GameManager> const manager)
{
	timer = StageDataManager::CreateGameTimer();
	playUI = new GamePlayUI(manager,timer);
	isEndProcess = false;
	SoundPlayer::LoadSound(playBGM);
}
/// <summary>
/// UI�ƃ^�C�}�[�̉��
/// </summary>
PlayGameProcess::~PlayGameProcess()
{
	SAFE_DELETE(playUI);
	timer.reset();
}
/// <summary>
/// �V��ł���Ƃ��̍X�V
/// </summary>
/// <param name="gameObject">�Q�[��������Ƃ��ɕK�v�ȃI�u�W�F�N�g</param>
void PlayGameProcess::Update(std::weak_ptr<GameManager> const gameObject)
{
	//���W�A�C�e����S��������Ȃ�
	if (CollectController::IsEndGame())
	{
		timer->Stop();
	}
	//���W�A�C�e�����S�������I�����,�������Ԃ̏I�������Ȃ�
	if (CollectController::IsDestroyAllItem()||timer->IsOverLimitTime())
	{
		isEndProcess = true;
	}
	//BGM�����ĂȂ�������Đ�
	if (!SoundPlayer::IsPlaySound(playBGM))
	{
		SoundPlayer::Play2DSE(playBGM);
	}
	gameObject.lock()->Update();
	playUI->Update();
}
/// <summary>
/// �`��
/// </summary>
void PlayGameProcess::Draw() const
{
	playUI->Draw();
}
/// <summary>
/// �Q�[���̎c�莞�ԃ^�C�}�[��n��
/// </summary>
/// <returns> �Q�[���̎c�莞�ԃ^�C�}�[��n��</returns>
std::shared_ptr<Timer> PlayGameProcess::GetGameTimer()
{
	return timer;
};
