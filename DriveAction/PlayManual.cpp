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
/// プレイヤーの入力によって操作説明を変える
/// </summary>
void PlayManual::Update()
{
	//ボタン入力状況
	leftBUI.push = UserInput::GetInputState(Left) == Hold;
	rightBUI.push = UserInput::GetInputState(Right) == Hold;
	downBUI.push = UserInput::GetInputState(Down) == Hold;

	UIKind nextUIKind = manual;
	//下方向に入力するとターボ準備完了
	if (UserInput::GetInputState(Down) == Hold)
	{
		nextUIKind = turboManual;
	}
	//表示するUIが変更されたらデータを持ってくる
	if (nextUIKind != nowUIKind)
	{
		playManualData= UIManager::CreateUIData(nextUIKind);
		nowUIKind = nextUIKind;
	}
}
/// <summary>
/// 操作説明の描画
/// </summary>
void PlayManual::Draw() const
{
	UIDrawer::DrawRotaUI(sheatData);
	UIDrawer::DrawRotaUI(playManualData);
	//ボタン押してたら押した状態のUIに変更
	UIDrawer::DrawRotaUI(leftBUI.data, leftBUI.push ? 1 : 0);
	UIDrawer::DrawRotaUI(rightBUI.data, rightBUI.push ? 1 : 0);
	UIDrawer::DrawRotaUI(downBUI.data, downBUI.push ? 1 : 0);
}