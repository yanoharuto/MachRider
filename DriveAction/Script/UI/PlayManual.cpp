#include "PlayManual.h"
#include "UIDrawer.h"
/// <summary>
/// 各UIを読み込む
/// </summary>
PlayManual::PlayManual()
{
	using enum UIKind;
	//操作方法で出来ることが書いてある
    playManualUIData = UIManager::CreateUIData(manual);
	//操作方法で下に引いてある枠
    sheatUIData = UIManager::CreateUIData(playManualSheat);
	//左ボタン
	leftBUI.data = UIManager::CreateUIData(leftButton);
	//右ボタン
	rightBUI.data = UIManager::CreateUIData(rightButton);
	//ジョイパッドならUI変更
	downBUI.data = UIManager::CreateUIData((UserInput::IsInputPad()) ? xDownButton : downButton);
}
/// <summary>
/// UI削除
/// </summary>
PlayManual::~PlayManual()
{
	UIManager::DeleteUIGraph(&playManualUIData);
	UIManager::DeleteUIGraph(&sheatUIData);
	UIManager::DeleteUIGraph(&leftBUI.data);
	UIManager::DeleteUIGraph(&rightBUI.data);
	UIManager::DeleteUIGraph(&downBUI.data);
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

	UIKind nextUIKind = UIKind::manual;
	//下方向に入力するとターボ準備完了
	if (downBUI.push)
	{
		nextUIKind = UIKind::turboManual;
	}
	//表示するUIが変更されたらデータを持ってくる
	if (nextUIKind != nowUIKind)
	{
		playManualUIData= UIManager::CreateUIData(nextUIKind);
		nowUIKind = nextUIKind;
	}
}
/// <summary>
/// 操作説明の描画
/// </summary>
void PlayManual::Draw() const
{
	UIDrawer::DrawRotaUI(sheatUIData);
	UIDrawer::DrawRotaUI(playManualUIData);
	//ボタン押してたら押した状態のUIに変更
	UIDrawer::DrawRotaUI(leftBUI.data, leftBUI.push ? 1 : 0);
	UIDrawer::DrawRotaUI(rightBUI.data, rightBUI.push ? 1 : 0);
	UIDrawer::DrawRotaUI(downBUI.data, downBUI.push ? 1 : 0);
}