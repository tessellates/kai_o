#pragma once

#include "PieceData.hpp"

class PieceDataManager {
public:
    PieceDataManager() = default;
    int createPiece(PieceType type, Coordinate coordinate)
    {
        pieces.push_back({type, coordinate});
        return pieces.size() - 1;
    };

public:
    std::vector<PieceData> pieces;
    std::vector<int> modifiedIndexes;

};
