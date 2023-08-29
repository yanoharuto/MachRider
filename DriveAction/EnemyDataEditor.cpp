#include "EnemyDataEditor.h"
#include "UserInput.h"
#include "EditorObject.h"
#include "Utility.h"
#include "EditorDrawModel.h"
#include "CircleFlyShipViewer.h"
const std::string EnemyDataEditor::loadEditFilePath = "enemyData.csv";
/// <summary>
/// ìGÇÃï“èWÉNÉâÉX
/// </summary>
EnemyDataEditor::EnemyDataEditor(InitObjKind enemyKind)
    :StageDataEditor(loadEditFilePath,enemyKind)
{
    if (enemyKind == circleLaserShip)
    {
        SAFE_DELETE(drawer);
        drawer = new CircleFlyShipDrawer();
    }
}
