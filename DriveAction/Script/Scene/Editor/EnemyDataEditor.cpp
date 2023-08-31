#include "EnemyDataEditor.h"
#include "UserInput.h"
#include "EditorObject.h"
#include "Utility.h"
#include "EditorDrawModel.h"
#include "EditorCircleFlyShipDrawModel.h"
//�ǂݍ��ޔz�u���̃t�@�C���̃p�X
const std::string EnemyDataEditor::loadEditFilePath = "enemyData.csv";
/// <summary>
/// �G�̕ҏW�N���X
/// </summary>
EnemyDataEditor::EnemyDataEditor(InitObjKind enemyKind)
    :StageDataEditor(loadEditFilePath,enemyKind)
{
    //�~�`��s���N���X�͕`����@��ύX
    if (enemyKind == circleLaserShip)
    {
        SAFE_DELETE(drawer);
        drawer = new EditorCircleFlyShipDrawModel();
    }
}
