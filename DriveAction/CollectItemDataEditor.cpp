#include "CollectItemDataEditor.h"
#include "EditorObject.h"
#include "UserInput.h"
#include "Utility.h"
#include "EditorDrawModel.h"
//読み込む配置情報の書いてあるファイルのパス
const std::string CollectItemDataEditor::loadEditFilePath = "collectData.csv";
/// <summary>
/// 収集アイテムの編集するクラス
/// </summary>
CollectItemDataEditor::CollectItemDataEditor()
    :StageDataEditor(loadEditFilePath,collect)
{
}
/// <summary>
/// 更新
/// </summary>
void CollectItemDataEditor::Update()
{
    StageDataEditor::Update();

    //収集アイテムの数を他のEditorにも反映
    if (!placementDataVec.empty())
    {
        collectNum = placementDataVec.size() - 1;
        collectNum = collectNum < 0 ? 0 : collectNum;
    }
}
/// <summary>
/// 編集中や編集し終えたオブジェクトの描画
/// </summary>
void CollectItemDataEditor::Draw() const
{
    StageDataEditor::Draw();
    
    //収集アイテムの数
    DrawString(0, drawCollectNumY, std::to_string(collectNum).c_str(), GetColor(0, 0, 0));
    //ミッションの数
    DrawString(0, drawEditedCollectNumY, std::to_string(getCollectNum).c_str(), GetColor(0, 0, 0));
}
 