#ifndef QUEEN_H
#define QUEEN_H

#include "chesspieces/bishop.h"
#include "chesspieces/rook.h"

class Queen : public Bishop, public Rook
{
public:
    Queen(const QString &color, const std::shared_ptr<Chessboard> chessboard
          , QQmlApplicationEngine *engine, QQuickItem *parentItem, int row, int column);
    ~Queen();

    bool isMoveAvailable(int startRow, int startColumn, int endRow, int endColumn) const override;
};

#endif // QUEEN_H
