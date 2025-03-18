#pragma once

class Shooter;

class Weapon {
public:
    virtual ~Weapon() = default;
    virtual void Fire(Shooter& shooter) = 0;
};