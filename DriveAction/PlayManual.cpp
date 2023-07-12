#include "PlayManual.h"
#include "UIDrawer.h"
PlayManual::PlayManual()
{
    playManualData = UIManager::CreateUIData(manual);
    sheatData = UIManager::CreateUIData(playManualSheat);
	UIKind nowUIKind = manual;
	leftBUI.data = UIManager::CreateUIData(leftButton);
	rightBUI.data = UIManager::CreateUIData(rightButton);
	downBUI.data = UIManager::CreateUIData(downButton);
}

PlayManual::~PlayManual()
{
}
/// <summary>
/// �v���C���[�̓��͂ɂ���đ��������ς���
/// </summary>
void PlayManual::Update()
{
	//�{�^�����͏�
	leftBUI.push = UserInput::GetInputState(Left) == Hold;
	rightBUI.push = UserInput::GetInputState(Right) == Hold;
	downBUI.push = UserInput::GetInputState(Down) == Hold;

	UIKind nextUIKind = manual;
	//�������ɓ��͂���ƃ^�[�{��������
	if (UserInput::GetInputState(Down) == Hold)
	{
		nextUIKind = turboManual;
	}
	//�\������UI���ύX���ꂽ��f�[�^�������Ă���
	if (nextUIKind != nowUIKind)
	{
		playManualData= UIManager::CreateUIData(nextUIKind);
		nowUIKind = nextUIKind;
	}
}
/// <summary>
/// ��������̕`��
/// </summary>
void PlayManual::Draw() const
{
	UIDrawer::DrawRotaUI(sheatData);
	UIDrawer::DrawRotaUI(playManualData);
	//�{�^�������Ă��牟������Ԃ�UI�ɕύX
	UIDrawer::DrawRotaUI(leftBUI.data, leftBUI.push ? 1 : 0);
	UIDrawer::DrawRotaUI(rightBUI.data, rightBUI.push ? 1 : 0);
	UIDrawer::DrawRotaUI(downBUI.data, downBUI.push ? 1 : 0);
}