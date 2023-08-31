#include "UIDrawer.h"
#include "DxLib.h"
#include "Utility.h"

//����
 int UIDrawer::screenWidth = SCREEN_WIDTH;
//�c��
 int UIDrawer::screenHeight = SCREEN_HEIGHT;
//�����䗦
 float UIDrawer:: widthRaito = 0.0f;
//�c���䗦
 float UIDrawer:: heightRaito = 0.0f;
 //��ʂ̑傫���䗦
 float UIDrawer::UIDrawer::screenSizeRaito = 1.0f;
 /// <summary>
 /// drawRotaGraph����ʂ̃T�C�Y�ɍ��킹�ďo����悤�ɂ���
 /// </summary>
 /// <param name="data">�`�悵����UI</param>
 /// <param name="gHIndex">�`�悵����UI�̓Y����</param>
 /// <param name="angle">UI���X����</param>
 /// <param name="trans">�����x�L���t���O</param>
 /// <returns>���s�����false</returns>
bool UIDrawer::DrawRotaUI(UIData data, int gHIndex, float angle, bool trans)
{
    gHIndex = gHIndex % data.dataHandle.size();
   int success = DrawRotaGraph(data.x * widthRaito, data.y * heightRaito, data.size * screenSizeRaito, angle, data.dataHandle[gHIndex], trans);
   return success != -1;
}
/// <summary>
/// �X�N���[���̑z��̑傫���Ƃ̍���{���œn��
/// </summary>
/// <returns></returns>
float UIDrawer::GetScreenRaito()
{
    return screenSizeRaito;
}
/// <summary>
/// ��ʃT�C�Y��������
/// </summary>
UIDrawer::UIDrawer()
{
    int color;
    //��ʃT�C�Y
    GetScreenState(&screenWidth, &screenHeight, &color);
    //�����䗦
    widthRaito = screenWidth / SCREEN_WIDTH;
    //�c���䗦
    heightRaito = screenHeight / SCREEN_HEIGHT;
    //HD�̑傫���Ɣ�r�����傫��
    screenSizeRaito = (screenWidth + screenHeight) / (SCREEN_WIDTH + SCREEN_HEIGHT);
}