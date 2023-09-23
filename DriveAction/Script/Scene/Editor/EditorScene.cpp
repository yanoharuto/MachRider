#include "EditorScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "Menu.h"
#include "EditorManager.h"
#include "UserInput.h"
#include "EditorCamera.h"
#include "EditorEffect.h"
#include "EditManual.h"
#include "CameraObserver.h"
/// <summary>
/// ���j���[��ʂ�J�����A�ҏW�N���X�Ȃǂ��m��
/// </summary>
EditorScene::EditorScene()
    :SceneBase(SceneType::editor)
{
    //�J����
    camera = std::make_shared<EditorCamera>();
    cameraObserver = std::make_unique<CameraObserver>(camera);
    //�ҏW�I�u�W�F�N�g�̎�ނ�ύX����N���X
    editManager = new EditorManager();
    //���j���[���
    menu = new Menu();
    //�����������
    manual = new EditManual();
    //�G�t�F�N�g
    editorEffect = new EditorEffect();
}
/// <summary>
/// �R���X�g���N�^�Ŋm�ۂ��������J��
/// </summary>
EditorScene::~EditorScene()
{
    SAFE_DELETE(menu);
    SAFE_DELETE(editManager);
    camera.reset();
    SAFE_DELETE(manual);
    SAFE_DELETE(editorEffect);
}
/// <summary>
/// ���j���[��Editor�̍X�V
/// </summary>
/// <returns>�^�C�g���ɖ߂�����Q�[�����I��������Editor���ēǂݍ��݂����肷��</returns>
SceneType EditorScene::Update()
{
    menu->Update();//���j���[��ʂ̍X�V

    using enum Menu::MenuOptions;
    switch (menu->GetMenuState())
    {
        //���j���[UI�̑I�����ƂɃV�[����V�����ǂݍ���
    case retry:
        return SceneType::reload;//�ēǂݍ���
        break;
    case returnTitle:
        return SceneType::title;//�^�C�g��
        break;
    case exitGame:
        return SceneType::escape;//�Q�[���I��
        break;
    }
    //���j���[��ʊJ���ĂȂ�������
    if (!menu->IsMenuOpen())
    {
        if (UserInput::GetInputState(AKey) == Hold)
        {
            camera->UpdateDirectionAndTargetBetween();
        }
        else
        {
            //�V�[�����Ƃ̏���
            editManager->Update(cameraObserver);
        }

        //�J�����̍X�V
        camera->UpdatePositionAndTarget(editManager->GetNowEditObjPlaceData());
        //�G�t�F�N�g�X�V
        editorEffect->Update(editManager->GetNowEditObjPlaceData());
    }
    return nowSceneType;
}
/// <summary>
/// ���j���[��ʂ�Editor�̕`��
/// </summary>
void EditorScene::Draw() const
{
    //���j���[��ʂ��J���Ă�����
    if (menu->IsMenuOpen())
    {
        menu->Draw();
    }
    else
    {
        editManager->Draw(cameraObserver);
        //���ҏW���Ă���ғ����ő�������ύX
        if(editManager->IsNowEdit())
        {
            //�������
            manual->DrawEditManualString();
        }
        else
        {
            manual->DrawSelectManualString();
        }
    }
}
