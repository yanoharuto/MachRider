#include "PlayManual.h"
#include "UIDrawer.h"
/// <summary>
/// �eUI��ǂݍ���
/// </summary>
PlayManual::PlayManual()
{
	//������@�ŏo���邱�Ƃ������Ă���
    playManualData = UIManager::CreateUIData(manual);
	//������@�ŉ��Ɉ����Ă���g
    sheatData = UIManager::CreateUIData(playManualSheat);
	//���{�^��
	leftBUI.data = UIManager::CreateUIData(leftButton);
	//�E�{�^��
	rightBUI.data = UIManager::CreateUIData(rightButton);
	//�W���C�p�b�h�Ȃ�UI�ύX
	downBUI.data = UIManager::CreateUIData((UserInput::IsInputPad()) ? xDownButton : downButton);
}
/// <summary>
/// �v���C���[�̓��͂ɂ���đ��������ς���
/// </summary>
void PlayManual::Update()
{
	//�{�^�����͏�
	leftBUI.push = UserInput::GetInputState(Left) == Hold;
	rightBUI.push = UserInput::GetInputState(Right) == Hold;
	downBUI.push = UserInput::GetInputState((UserInput::IsInputPad()) ? Space : Down) == Hold;

	UIKind nextUIKind = manual;
	//�������ɓ��͂���ƃ^�[�{��������
	if (downBUI.push)
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