#ifndef BISHOP_H
#define BISHOP_H

#include "chesspieces/chesspiece.h"

class Bishop : public ChessPiece
{
public:
    Bishop(const QString &color, const std::shared_ptr<Chessboard> chessboard
           , QQmlApplicationEngine *engine, QQuickItem *parent, int row, int column);
    ~Bishop();

    bool isMoveAvailable(int startRow, int startColumn, int endRow, int endColumn) const override;
};

#endif // BISHOP_H
