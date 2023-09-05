#include "PlayScene.h"
#include "PlaySceneFlow.h"
#include "Utility.h"
#include "FadeInFadeOut.h"
#include "Clock.h"
#include "Menu.h"
/// <summary>
/// ���j���[��ʂƃQ�[���̗���̊m�ۂƉ������[�h
/// </summary>
PlayScene::PlayScene()
    :SceneBase(SceneType::PLAY)
{
    sceneFlow = new PlaySceneFlow();
    menu = new Menu();
}
/// <summary>
/// ���j���[�ƃQ�[���̊J���Ɖ����~�߂�
/// </summary>
PlayScene::~PlayScene()
{
    SAFE_DELETE(menu);
    SAFE_DELETE(sceneFlow);
}
/// <summary>
/// �Q�[����V��
/// </summary>
/// <returns></returns>
SceneType PlayScene::Update()
{
    //���j���[�Ńv���C���[������I�񂾂�
    menu->Update();
    MenuState menuState = menu->GetMenuState();
    
    //���j���[�̏�Ԃɂ���ĕύX
    switch (menuState)
    {
    case continueGame:
        //menu��ʂ��J���ĂȂ��Ȃ畁�ʂ̏���
        if (menu->IsMenuOpen() == false)
        {
            //�V�[�����Ƃ̏���
            sceneFlow->Update();
            //�������I�������
            if (sceneFlow->GetIsEndProcesss())
            {
                return sceneFlow->GetNextSceneType();
            }
        }
    break;
    //�Q�[������蒼��
    case retry:
        nowSceneType = SceneType::RELOAD;
        break;
        //�^�C�g���ɖ߂�
    case returnTitle:
        nowSceneType = SceneType::TITLE;
        break;
        //�Q�[���I��
    case exitGame:
        nowSceneType = SceneType::ESCAPE;
        break;
    default:
        break;
    }
    
    return nowSceneType;
}
/// <summary>
/// ���j���[���J���Ă��鎞�ƗV��ł���Ƃ��ŏ������Ⴄ
/// </summary>
void PlayScene::Draw()const
{
    if (Menu::IsMenuOpen())//���j���[���J���Ă����烁�j���[��ʂ�`��
    {
         menu->Draw();
    }
    else//�V��ł���Ƃ��̏�Ԃ�`��
    {
        sceneFlow->Draw();
    }
}