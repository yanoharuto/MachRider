#include "CollectSign.h"
#include "UIManager.h"
#include "CollectController.h"
#include "ObjectObserver.h"
#include "DxLib.h"
#include "Timer.h"
#include "OriginalMath.h"
CollectSign::CollectSign(std::weak_ptr<ObjectObserver> player)
{
    collectSignData = UIManager::CreateUIData(collectSign);
    signScale = collectSignData.width / 2 * collectSignData.size;
    markerAllowData = UIManager::CreateUIData(markerAllow);
    signTimer = new Timer(collectSignData.frameSpeed);
    playerObserver = player;
}

void CollectSign::Update()
{
    degree = CollectController::GetCollectItemDegreeDifference(playerObserver);
    
    if (degree > 45 || degree < -45)
    {
        VECTOR dir = VNorm(OriginalMath::GetYRotateVector({ 1,0,0 }, degree));
        dir = VScale(dir, signScale);
        markerAllowData.x = collectSignData.x + dir.x;
        markerAllowData.y = collectSignData.y + dir.y;
        
        degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), dir) * RAGE;
        printfDx("%f\n", degree);
        if (signTimer->IsOverLimitTime())
        {
            drawIcon = !drawIcon;
            signTimer->Init();
        }
    }
    else
    {
        drawIcon = false;
    }

}

void CollectSign::Draw() const
{
    if (drawIcon)
    {
        DrawRotaGraph(collectSignData.x, collectSignData.y, collectSignData.size,0,collectSignData.dataHandle[0], true);
        DrawRotaGraph(markerAllowData.x, markerAllowData.y, markerAllowData.size, degree, markerAllowData.dataHandle[0], true);
    }
}
