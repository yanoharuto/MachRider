#include "SpaceKeyUI.h"
#include "Utility.h"
#include "DxLib.h"

SpaceKeyUI::SpaceKeyUI(int setX, int setY)
{
    pressKeyData = UIManager::CreateUIData(pressSpaceKey);
    pressKeyData.x = setX;
    pressKeyData.y = setY;
    aValue = lowtestAvalue;//�Œ�l���Z�b�g
    isAValueIncrement = true;
}

SpaceKeyUI::~SpaceKeyUI()
{
}
/// <summary>
/// �A���t�@�l�̍X�V
/// </summary>
void SpaceKeyUI::Update()
{
    aValue += isAValueIncrement ? aSpeed : -aSpeed;
    if (aValue > MAX1BYTEVALUE)
    {
        isAValueIncrement = false;
    }
    else if (aValue < lowtestAvalue)
    {
        isAValueIncrement = true;
    }
}
/// <summary>
/// ���X�ɔ����Ȃ�����Z���Ȃ����肵�Ȃ���`��
/// </summary>
void SpaceKeyUI::Draw() const
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, aValue);//���l��������
    DrawRotaGraph(pressKeyData.x, pressKeyData.y, pressKeyData.size, 0, pressKeyData.dataHandle[0], true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//���ɖ߂�
}
