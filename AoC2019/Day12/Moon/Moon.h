#pragma once

#include <string>
#include <vector>

class Moon {
private:
    std::vector<int> pos;
    std::vector<int> initPos;
    std::vector<int> vel;

public:
    Moon(int x, int y, int z);
    int GetEnergy();
    bool AtStart();
    bool AtStart(int dimension);
    void Move();
    void Move(int dimension);
    void UpdateVel(Moon& otherMoon);
    void UpdateVel(Moon& otherMoon, int dimension);
};