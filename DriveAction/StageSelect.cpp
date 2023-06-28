#include "StageSelect.h"
#include "UserInput.h"
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
}
/// <summary>
/// 遊ぶステージ変更するときに使う
/// </summary>
/// <param name="next">次のステージTrue前のステージかfalse</param>
void StageSelect::Update()
{
    //上下に押したら変更
    if (UserInput::GetInputState(Up) == Push)
    {
        stageNum++;
        if (stageNum >= dataLoader.size())
        {
            stageNum = 0;
        }
    }
    else if (UserInput::GetInputState(Down) == Push)
    {
        stageNum--;
        if (stageNum < 0)
        {
            stageNum = dataLoader.size() - 1;
        }
    }
    fileAddres = dataLoader[stageNum];
}
/// <summary>
/// 現在選んでいるステージを表示
/// </summary>
void StageSelect::Draw() const
{
    DrawGraph(stageNameData.x, stageNameData.y, stageNameData.dataHandle[stageNum], true);
}
