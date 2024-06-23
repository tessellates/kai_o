#pragma once

#include "Coordinate.hpp"
#include "PieceDataManager.hpp"

int index(int x, int y, int xmax)
{
    return y*xmax + x;
}

inline void start()
{
    int x = 16;
    int y = 12;
    auto grid = std::vector<int>(x*y, -1);
    PieceDataManager manager;
    grid[index(1,1, x)] = manager.createPiece(PieceType::Player, {1,1});
    grid[index(1,2, x)] = manager.createPiece(PieceType::Dirt, {1,2});
    for (const auto& p : manager.pieces)
    {
        //std::cout << grid[index(p.coordinate.x, p.coordinate.y, x)] << std::endl;
    }

};