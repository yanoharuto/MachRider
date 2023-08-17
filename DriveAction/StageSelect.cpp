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
    stageNum = 0;
    stageNameData = UIManager::CreateUIData(stageName);
    selectButtonData = UIManager::CreateUIData(stageSelectButton);
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
        stageNum++;
        //ステージ数の限界に来たら0に
        if (stageNum >= StageDataManager::GetStageTotalNumber())
        {
            stageNum = 0;
        }
    }
    else if (UserInput::GetInputState(Up) == Push)
    {
        stageNum--;
        //ステージ数の最低に来たら最大値に
        if (stageNum < 0)
        {
            stageNum = StageDataManager::GetStageTotalNumber() - 1;
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
    UIData data = stageNameData;
    for (int i = 0; i < data.dataHandle.size(); i++)
    {
        if (i == stageNum)//現在のステージは大きくちょっとずらして表示
        {
            data.x -= data.width / 2;
            data.size *= selectSizeCoefficient;
        }
        else
        {
            data.x = stageNameData.x;
            data.size = stageNameData.size;
        }
        UIDrawer::DrawRotaUI(data, i);
        data.y += data.height;
    }
    UIDrawer::DrawRotaUI(selectButtonData);
}
/// <summary>
/// ステージの番号
/// </summary>
/// <returns></returns>
int StageSelect::GetStageNum()const
{
    return stageNum;
}
