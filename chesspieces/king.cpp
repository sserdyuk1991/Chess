#include "king.h"

King::King(const QString &color, const std::shared_ptr<Chessboard> chessboard
           , QQmlApplicationEngine *engine, QQuickItem *parent, int row, int column)
    : ChessPiece("king", color, chessboard, engine, parent, row, column) {}

King::~King() {}

bool King::isMoveAvailable(int startRow, int startColumn, int endRow, int endColumn) const
{
    if ((abs(endRow - startRow) <= 1) && (abs(endColumn - startColumn) <= 1))
        return true;
    return false;
}
