#ifndef KNIGHT_H
#define KNIGHT_H

#include "chesspieces/chesspiece.h"

class Knight : public ChessPiece
{
public:
    Knight(const QString &color, const std::shared_ptr<Chessboard> chessboard
           , QQmlApplicationEngine *engine, QQuickItem *parentItem, int row, int column);
    ~Knight();

    bool isMoveAvailable(int startRow, int startColumn, int endRow, int endColumn) const override;
};

#endif // KNIGHT_H
