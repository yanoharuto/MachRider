#include "SkyDome.h"
#include "OriginalMath.h"
/// <summary>
/// modelのロードとタグ付け
/// </summary>
/// <returns></returns>
SkyDome::SkyDome()
{
    modelHandle = MV1LoadModel("data/model/SkyDome/SkyDome.mv1");
    MV1SetPosition(modelHandle, position);
    MV1SetScale(modelHandle, VGet(setSize, setSize, setSize));
    tag = ObjectTag::stage;
}
//modelのデリート
SkyDome::~SkyDome()
{
    MV1DeleteModel(modelHandle);
}
void SkyDome::Update()
{
  
    
}
/// <summary>
/// modelの描画
/// </summary>
void SkyDome::Draw()
{

    SetUseLighting(false);
    MV1DrawModel(modelHandle);
    SetUseLighting(true);
}
