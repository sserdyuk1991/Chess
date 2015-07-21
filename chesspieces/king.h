#ifndef KING_H
#define KING_H

#include "chesspieces/chesspiece.h"

class King : public ChessPiece
{
public:
    King(const QString &color, const std::shared_ptr<Chessboard> chessboard
         , QQmlApplicationEngine *engine, QQuickItem *parent, int row, int column);
    ~King();

    bool isMoveAvailable(int startRow, int startColumn, int endRow, int endColumn) const override;
};

#endif // KING_H
