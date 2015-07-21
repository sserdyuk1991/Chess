#include "rook.h"

Rook::Rook(const QString &color, const std::shared_ptr<Chessboard> chessboard
           , QQmlApplicationEngine *engine, QQuickItem *parentItem, int row, int column)
    : ChessPiece("rook", color, chessboard, engine, parentItem, row, column) {}

Rook::~Rook() {}

bool Rook::isMoveAvailable(int startRow, int startColumn, int endRow, int endColumn) const
{
    if (startRow == endRow) {
        int step = startColumn < endColumn ? 1 : -1;
        for (int i = startColumn + step; i != endColumn; i += step) {
            if ((*m_chessboard)[startRow][i] != nullptr)
                return false;
        }
        return true;
    }

    if (startColumn == endColumn) {
        int step = startRow < endRow ? 1 : -1;
        for (int i = startRow + step; i != endRow; i += step) {
            if ((*m_chessboard)[i][startColumn] != nullptr)
                return false;
        }
        return true;
    }

    return false;
}
