#pragma once

#include "Coordinate.hpp"

enum PieceType
{
    Dirt,
    Ball,
    LightBall,
    Gem,
    Player,
    Bomb,
    HardWall,
    WeakWall,
    VictoryClosed,
    VictoryOpen,
    Explosion,
    LeverOn,
    LeverOff,
    LaserOn,
    LaserOff,
    Beam,
    Elevator,
    Gate
};

struct PieceData
{
public:

    PieceType type;
    Coordinate coordinate;
};