#pragma once
#include "AssetManager.h"
#include <string>
class AddObjectDataLoader final:public AssetManager
{
public:
    enum class AddData;
    AddObjectDataLoader(AddData loadData);
    std::string GetLoadData();
    enum class AddData
    {
        circleFlyShip,
        upDownFlyShip,
        bomberShip,
        moveSaw,
        playerSpeed
    };
};