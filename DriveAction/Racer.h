#pragma once
class Car;
/// <summary>
/// ���[�T�[�@
/// </summary>
class Racer abstract
{
public:
    Racer();
    virtual ~Racer();
    /// <summary>
    /// �Ԃ𑖂点����A�C�e�����g�����肷��
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <param name="outsideHitFlag"></param>
    /// <param name="damageObj"></param>
    virtual void Update();
    /// <summary>
    /// �`�悷��
    /// </summary>
    void Draw();
    /// <summary>
    /// ���i�O�ɏ㉺�ɓ���
    /// </summary>
    void UpDown();
    
protected:
    //��
    Car* car;
};

