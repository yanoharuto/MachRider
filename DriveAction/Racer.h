#pragma once
class Car;
/// <summary>
/// レーサー　
/// </summary>
class Racer abstract
{
public:
    Racer();
    virtual ~Racer();
    /// <summary>
    /// 車を走らせたりアイテムを使ったりする
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <param name="outsideHitFlag"></param>
    /// <param name="damageObj"></param>
    virtual void Update();
    /// <summary>
    /// 描画する
    /// </summary>
    void Draw();
    /// <summary>
    /// 発進前に上下に動く
    /// </summary>
    void UpDown();
    
protected:
    //車
    Car* car;
};

