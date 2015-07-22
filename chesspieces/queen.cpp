#include "queen.h"
#include "bishop.h"

Queen::Queen(const QString &color, const std::shared_ptr<Chessboard> chessboard
             , QQmlApplicationEngine *engine, QQuickItem *parentItem, int row, int column)
    : Bishop(color, chessboard, engine, parentItem, row, column)
    , Rook(color, chessboard, engine, parentItem, row, column)
    , ChessPiece("queen", color, chessboard, engine, parentItem, row, column) {}

Queen::~Queen() {}

bool Queen::isMoveAvailable(int startRow, int startColumn, int endRow, int endColumn) const
{
    return Bishop::isMoveAvailable(startRow, startColumn, endRow, endColumn)
            || Rook::isMoveAvailable(startRow, startColumn, endRow, endColumn);
}
