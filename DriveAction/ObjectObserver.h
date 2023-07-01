#pragma once
#include "DxLib.h"
#include <string>
#include "Object.h"
class ObjectSubject;
class ObjectObserver
{
public:
    /// <summary>
    /// ŠÄ‹–ğ
    /// </summary>
    /// <param name="setSubject"></param>
    ObjectObserver(ObjectSubject* setSubject);
    ~ObjectObserver();
    /// <summary>
    /// ŠÄ‹‘ÎÛ‚ÌˆÊ’u‚ğ“n‚·
    /// </summary>
    /// <returns></returns>
    VECTOR GetSubjectPos() const;
    /// <summary>
    /// ŠÄ‹‘ÎÛ‚ÌŒü‚«
    /// </summary>
    /// <returns></returns>
    VECTOR GetSubjectDir() const;
    /// <summary>
    /// ŠÄ‹‘ÎÛ‚ªˆø”‚Ì‚à‚Ì‚É“–‚½‚Á‚½‰ñ”‚ğ•Ô‚·
    /// </summary>
    /// <param name="objTag"></param>
    /// <returns></returns>
    int GetSubjectHitCount(Object::ObjectTag objTag)const;
    /// <summary>
    /// ŠÄ‹‘ÎÛ‚Ìó‘Ô
    /// </summary>
    /// <returns></returns>
    Object::ObjectState GetSubjectState()const;
private:
    ObjectSubject* subject;
};

