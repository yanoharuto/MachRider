#pragma once
#include "RotatingLasers.h"

/// <summary>
/// ²‰ñ“]‚·‚é”¼Œa‚ª¬‚³‚¢ƒŒ[ƒU[
/// </summary>
class LittleRadiusLaser :
    public RotatingLasers
{
public:
    /// <summary>
/// ²‰ñ“]‚·‚é”¼Œa‚ª¬‚³‚¢ƒŒ[ƒU[
/// </summary>
    LittleRadiusLaser(std::unique_ptr<ObjectObserver> observer);
    /// <summary>
    /// ‰ñ“]
    /// </summary>
    void Update()override;
private:
    /// ‰ñ“]‘¬“x
    static const float rotaSpeed;
    
    /// ‰Šú‰»î•ñ
    static const InitParam initParam;
};

