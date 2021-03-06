#ifndef ROOK_H
#define ROOK_H

#include "chesspieces/chesspiece.h"

class Rook : virtual public ChessPiece
{
public:
    Rook(const QString &color, const std::shared_ptr<Chessboard> chessboard
         , QQmlApplicationEngine *engine, QQuickItem *parentItem, int row, int column);
    ~Rook();

    bool isMoveAvailable(int startRow, int startColumn, int endRow, int endColumn) const override;
};

#endif // ROOK_H
