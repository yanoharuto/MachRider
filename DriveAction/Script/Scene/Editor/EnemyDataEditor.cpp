#include "EnemyDataEditor.h"
#include "UserInput.h"
#include "EditorObject.h"
#include "Utility.h"
#include "EditorDrawModel.h"
#include "EditorCircleFlyShipDrawModel.h"
//読み込む配置情報のファイルのパス
const std::string EnemyDataEditor::loadEditFilePath = "enemyData.csv";
/// <summary>
/// 敵の編集クラス
/// </summary>
EnemyDataEditor::EnemyDataEditor(InitObjKind enemyKind)
    :StageDataEditor(loadEditFilePath,enemyKind)
{
    //円形飛行艇クラスは描画方法を変更
    if (enemyKind == circleLaserShip)
    {
        SAFE_DELETE(drawer);
        drawer = new EditorCircleFlyShipDrawModel();
    }
}
