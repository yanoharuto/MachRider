#include "CollectController.h"
#include "FirstPositionGetter.h"
#include "Coin.h"
#include "MiniMap.h"
#include "ObjectObserver.h"
#include "ObjectSubject.h"
/// <summary>
/// ƒRƒCƒ“‚Ìİ’u
/// </summary>
CollectController::CollectController(VECTOR generatePos)
{
    Coin* newCoin = new Coin(generatePos);
    actorList.push_back(newCoin);
    subject = new ObjectSubject(newCoin);
}

void CollectController::Update()
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->Update();
    }
    MiniMap::AddMarker(new ObjectObserver(subject));
}
