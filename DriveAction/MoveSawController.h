#pragma once
#include "ActorController.h"
/// <summary>
/// ˆÚ“®‚·‚é‰ñ“]‚Ì‚±‚¬‚è‚ÌŠÇ—Ò
/// </summary>
class MoveSawController :
    public ActorController
{
public:
    /// <summary>
    /// ˆÚ“®‚·‚é‰ñ“]‚Ì‚±‚¬‚è‚ÌŠÇ—Ò
    /// </summary>
    MoveSawController();
    /// <summary>
    /// ˆÚ“®‚·‚é‰ñ“]‚Ì‚±‚¬‚è‚Ì’Ç‰Á
    /// </summary>
    /// <param name="editData"></param>
    void AddObject(std::vector<EditArrangementData> editData)override;

    void Update()override;
};

