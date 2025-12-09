#include "Moon.h"

#include <cmath>
#include <sstream>

Moon::Moon(int x, int y, int z) {
    pos = { x,y,z };
    initPos = { x,y,z };
    vel = { 0,0,0 };
}

int Moon::GetEnergy() {
    return (std::abs(pos[0]) + std::abs(pos[1]) + std::abs(pos[2])) * (std::abs(vel[0]) + std::abs(vel[1]) + std::abs(vel[2]));
}

bool Moon::AtStart() {
    return AtStart(0) && AtStart(1) && AtStart(2);
}

bool Moon::AtStart(int dimension) {
    return vel[dimension] == 0 && pos[dimension] == initPos[dimension];
}

void Moon::Move() {
    for (int i = 0; i < 3; i++) {
        Move(i);
    }
}

void Moon::Move(int dimension) {
    pos[dimension] += vel[dimension];
}

void Moon::UpdateVel(Moon& otherMoon) {
    for (int i = 0; i < 3; i++) {
        UpdateVel(otherMoon, i);
    }
}

void Moon::UpdateVel(Moon& otherMoon, int dimension) {
    int delta = otherMoon.pos[dimension] - pos[dimension];
    int change = delta > 0 ? 1 : delta < 0 ? -1 : 0;
    vel[dimension] += change;
    otherMoon.vel[dimension] -= change;
}