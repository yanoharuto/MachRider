#include "EditorScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "EditorSceneFlow.h"
#include "UserInput.h"
/// <summary>
/// �ҏW�V�[���̗����New
/// </summary>
EditorScene::EditorScene()
    :SceneBase(SceneType::EDITOR)
{
    sceneFlow = new EditorSceneFlow();
    menu = new Menu();
}
/// <summary>
/// ���j���[��Editor�̍X�V
/// </summary>
/// <returns>�^�C�g���ɖ߂�����Q�[�����I��������Editor���ēǂݍ��݂����肷��</returns>
SceneType EditorScene::Update()
{
    menu->Update();
    switch (menu->GetMenuState())
    {
    case continueGame:
        //���j���[��ʊJ���ĂȂ�������
        if (!menu->IsMenuOpen())
        {
            //�V�[�����Ƃ̏���
            sceneFlow->Update();
        }
        break;
        //���j���[UI�̑I�����ƂɕύX
    case retry:
        return SceneType::RELOAD;//�ēǂݍ���
        break;
    case returnTitle:
        return SceneType::TITLE;//�^�C�g��
        break;
    case exitGame:
        return SceneType::ESCAPE;//�Q�[���I��
        break;
    default:
        break;
    }
    return nowSceneType;
}
/// <summary>
/// ���j���[��ʂ�Editor�̕`��
/// </summary>
void EditorScene::Draw() const
{
    if (menu->IsMenuOpen())
    {
        menu->Draw();
    }
    else
    {
        sceneFlow->Draw();
    }
}
