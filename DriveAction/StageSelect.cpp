#include "StageSelect.h"
#include "UserInput.h"
#include "UIDrawer.h"
#include "Utility.h"
/// <summary>
/// ステージごとに必要なアセットのアドレスが
/// 書いてあるファイルの
/// アドレスが書いてあるファイルを読み込む
/// </summary>
/// <returns></returns>
StageSelect::StageSelect()
    :StageDataPass()
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
        if (stageNum >= dataLoader.size())
        {
            stageNum = 0;
        }
    }
    else if (UserInput::GetInputState(Up) == Push)
    {
        stageNum--;
        if (stageNum < 0)
        {
            stageNum = dataLoader.size() - 1;
        }
    }
    //選んでいるステージのアドレスを保存
    fileAddres = dataLoader[stageNum];
}
/// <summary>
/// 現在選んでいるステージを表示
/// </summary>
void StageSelect::Draw() const
{
    UIData data = stageNameData;
    for (int i = 0; i < data.dataHandle.size(); i++)
    {
        if (i == stageNum)
        {
            data.x -= data.width / 2;
        }
        else
        {
            data.x = stageNameData.x;
        }
        UIDrawer::DrawRotaUI(data, i);
        data.y += data.height;
    }
    UIDrawer::DrawRotaUI(selectButtonData);
}
