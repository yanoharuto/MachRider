#include "SoundListener.h"
#include "ObjectObserver.h"
#include "Utility.h"
/// <summary>
/// 音を聞くやつのポインターを貰う
/// </summary>
/// <param name="listener"></param>
SoundListener::SoundListener(std::weak_ptr<ObjectObserver> setListener)
{
    listener = setListener;
}
SoundListener::~SoundListener()
{
}
/// <summary>
/// リスナーの位置を反映
/// </summary>
void SoundListener::Update()
{
    if (listener.expired())//リスナーが活きてたら
    {
        VECTOR position = listener.lock()->GetSubjectPos();
        Set3DSoundListenerPosAndFrontPos_UpVecY(position, VAdd(position, listener.lock()->GetSubjectDir()));
    }
}
