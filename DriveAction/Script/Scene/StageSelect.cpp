#include "StageSelect.h"
#include "UserInput.h"
#include "UIDrawer.h"
#include "Utility.h"
#include "StageDataManager.h"
/// <summary>
/// ステージごとに必要なアセットのアドレスが
/// 書いてあるファイルの
/// アドレスが書いてあるファイルを読み込む
/// </summary>
/// <returns></returns>
StageSelect::StageSelect()
{
    selectStageNum = 0;
    StageDataManager::ChangeStageData(this);
    stageNameUI = UIManager::CreateUIData(stageName);
    selectButtonUI = UIManager::CreateUIData(stageSelectButton);
}
/// <summary>
/// 遊ぶステージ変更するときに使う
/// </summary>
/// <param name="next">次のステージTrue前のステージかfalse</param>
void StageSelect::Update()
{
    //上下に押したら変更
    if (UserInput::GetInputState(Down) == Push)
    {
        selectStageNum++;
        //ステージ数の限界に来たら0に
        if (selectStageNum >= StageDataManager::GetStageTotalNumber())
        {
            selectStageNum = 0;
        }
    }
    else if (UserInput::GetInputState(Up) == Push)
    {
        selectStageNum--;
        //ステージ数の最低に来たら最大値に
        if (selectStageNum < 0)
        {
            selectStageNum = StageDataManager::GetStageTotalNumber() - 1;
        }
    }
    //変更したことを伝える
    StageDataManager::ChangeStageData(this);
}
/// <summary>
/// ステージ一覧を表示
/// </summary>
void StageSelect::Draw() const
{
    //stageNameUIのCopy
    UIData stageNameData = stageNameUI;
    for (int i = 0; i < stageNameData.dataHandle.size(); i++)
    {
        if (i == selectStageNum)//現在選んでいるステージは大きくちょっとずらして表示
        {
            stageNameData.x -= stageNameData.width / 2;
            stageNameData.size *= selectSizeCoefficient;
        }
        else
        {
            stageNameData.x = stageNameUI.x;
            stageNameData.size = stageNameUI.size;
        }
        //各ステージの選択UIを描画
        UIDrawer::DrawRotaUI(stageNameData, i);
        stageNameData.y += stageNameData.height;
    }
    //選択するときのボタンを表示
    UIDrawer::DrawRotaUI(selectButtonUI);
}
/// <summary>
/// ステージの番号所得
/// </summary>
/// <returns>今選択しているステージの番号</returns>
int StageSelect::GetSelectStageNum()const
{
    return selectStageNum;
}
