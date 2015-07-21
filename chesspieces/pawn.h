#ifndef PAWN_H
#define PAWN_H

#include "chesspieces/chesspiece.h"

class Pawn : public ChessPiece
{
public:
    Pawn(const QString &color, const std::shared_ptr<Chessboard> chessboard
         , QQmlApplicationEngine *engine, QQuickItem *parentItem, int row, int column);
    ~Pawn();

    bool isMoveAvailable(int startRow, int startColumn, int endRow, int endColumn) const override;
};

#endif // PAWN_H
