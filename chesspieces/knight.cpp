#include "knight.h"

Knight::Knight(const QString &color, const std::shared_ptr<Chessboard> chessboard
               , QQmlApplicationEngine *engine, QQuickItem *parentItem, int row, int column)
    : ChessPiece("knight", color, chessboard, engine, parentItem, row, column) {}

Knight::~Knight() {}

bool Knight::isMoveAvailable(int startRow, int startColumn, int endRow, int endColumn) const
{
    if ((abs(endRow - startRow) == 2) && (abs(endColumn - startColumn) == 1))
        return true;
    if ((abs(endRow - startRow) == 1) && (abs(endColumn - startColumn) == 2))
        return true;
    return false;
}
