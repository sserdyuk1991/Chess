#ifndef QUEEN_H
#define QUEEN_H

#include "chesspieces/chesspiece.h"

class Queen : public ChessPiece
{
public:
    Queen(const QString &color, const std::shared_ptr<Chessboard> chessboard
          , QQmlApplicationEngine *engine, QQuickItem *parent, int row, int column);
    ~Queen();

    bool isMoveAvailable(int startRow, int startColumn, int endRow, int endColumn) const override;
};

#endif // QUEEN_H
