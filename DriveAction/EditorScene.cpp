#include "EditorScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "EditorSceneFlow.h"
/// <summary>
/// �ҏW�V�[���̗����New
/// </summary>
EditorScene::EditorScene()
    :SceneBase(SceneType::EDITOR)
{
    sceneFlow = new EditorSceneFlow();
}
