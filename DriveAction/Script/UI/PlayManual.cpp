#include "PlayManual.h"
#include "UIDrawer.h"
/// <summary>
/// 各UIを読み込む
/// </summary>
PlayManual::PlayManual()
{
	//操作方法で出来ることが書いてある
    playManualData = UIManager::CreateUIData(manual);
	//操作方法で下に引いてある枠
    sheatData = UIManager::CreateUIData(playManualSheat);
	//左ボタン
	leftBUI.data = UIManager::CreateUIData(leftButton);
	//右ボタン
	rightBUI.data = UIManager::CreateUIData(rightButton);
	//ジョイパッドならUI変更
	downBUI.data = UIManager::CreateUIData((UserInput::IsInputPad()) ? xDownButton : downButton);
}
/// <summary>
/// プレイヤーの入力によって操作説明を変える
/// </summary>
void PlayManual::Update()
{
	//ボタン入力状況
	leftBUI.push = UserInput::GetInputState(Left) == Hold;
	rightBUI.push = UserInput::GetInputState(Right) == Hold;
	downBUI.push = UserInput::GetInputState((UserInput::IsInputPad()) ? Space : Down) == Hold;

	UIKind nextUIKind = manual;
	//下方向に入力するとターボ準備完了
	if (downBUI.push)
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