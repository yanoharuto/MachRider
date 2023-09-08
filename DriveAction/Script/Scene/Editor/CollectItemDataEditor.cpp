#include "CollectItemDataEditor.h"
#include "EditorObject.h"
#include "UserInput.h"
#include "Utility.h"
#include "EditorDrawModel.h"
#include "EditorCameraObserver.h"
//�ǂݍ��ޔz�u���̏����Ă���t�@�C���̃p�X
const std::string CollectItemDataEditor::loadEditFilePath = "collectData.csv";
/// <summary>
/// ���W�A�C�e���̕ҏW����N���X
/// </summary>
CollectItemDataEditor::CollectItemDataEditor()
    :StageDataEditor(loadEditFilePath,collect)
{
}
/// <summary>
/// �e�N���X�Ɠ����X�V�Ǝ��W�A�C�e���̐����X�V����
/// </summary>
void CollectItemDataEditor::Update(std::weak_ptr<EditorCameraObserver> cameraObserever)
{
    //�e�N���X�Ɠ����X�V
    StageDataEditor::Update(cameraObserever);

    //���W�A�C�e���̐��𑼂�Editor�ɂ����f
    if (!placementDataVec.empty())
    {
        collectNum = placementDataVec.size() - 1;
        collectNum = collectNum < 0 ? 0 : collectNum;
    }
}
/// <summary>
/// �ҏW����ҏW���I�����I�u�W�F�N�g�̕`��
/// </summary>
void CollectItemDataEditor::Draw() const
{
    StageDataEditor::Draw();
    
    //���W�A�C�e���̐�
    DrawString(0, drawCollectNumY, std::to_string(collectNum).c_str(), GetColor(0, 0, 0));
    //�~�b�V�����̐�
    DrawString(0, drawEditedCollectNumY, std::to_string(getCollectNum).c_str(), GetColor(0, 0, 0));
}
 