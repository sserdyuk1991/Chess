#include "queen.h"
#include "bishop.h"

Queen::Queen(const QString &color, const std::shared_ptr<Chessboard> chessboard
             , QQmlApplicationEngine *engine, QQuickItem *parent, int row, int column)
    : ChessPiece("queen", color, chessboard, engine, parent, row, column) {}

Queen::~Queen() {}

bool Queen::isMoveAvailable(int startRow, int startColumn, int endRow, int endColumn) const
{
    if (abs(endRow - startRow) == abs(endColumn - startColumn)) {
        int rStep = startRow < endRow ? 1 : -1;
        int cStep = startColumn < endColumn ? 1 : -1;
        for (int i = startRow + rStep, j = startColumn + cStep; i != endRow; i += rStep, j += cStep) {
            if ((*m_chessboard)[i][j] != nullptr) {
                return false;
            }
        }
        return true;
    }

    if (startRow == endRow) {
        int step = startColumn < endColumn ? 1 : -1;
        for (int i = startColumn + step; i != endColumn; i += step) {
            if ((*m_chessboard)[startRow][i] != nullptr) {
                return false;
            }
        }
        return true;
    }

    if (startColumn == endColumn) {
        int step = startRow < endRow ? 1 : -1;
        for (int i = startRow + step; i != endRow; i += step) {
            if ((*m_chessboard)[i][startColumn] != nullptr) {
                return false;
            }
        }
        return true;
    }

    return false;
}
