#include "SpaceKeyUI.h"
#include "Utility.h"
#include "DxLib.h"

SpaceKeyUI::SpaceKeyUI(int setX, int setY)
{
    pressKeyData = UIManager::CreateUIData(pressSpaceKey);
    pressKeyData.x = setX;
    pressKeyData.y = setY;
    aValue = lowtestAvalue;//最低値をセット
    isAValueIncrement = true;
}

SpaceKeyUI::~SpaceKeyUI()
{
}
/// <summary>
/// アルファ値の更新
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
/// 徐々に薄くなったり濃くなったりしながら描画
/// </summary>
void SpaceKeyUI::Draw() const
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, aValue);//α値をいじる
    DrawRotaGraph(pressKeyData.x, pressKeyData.y, pressKeyData.size, 0, pressKeyData.dataHandle[0], true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//元に戻す
}
