#include "bishop.h"

Bishop::Bishop(const QString &color, const std::shared_ptr<Chessboard> chessboard
               , QQmlApplicationEngine *engine, QQuickItem *parent, int row, int column)
    : ChessPiece("bishop", color, chessboard, engine, parent, row, column) {}

Bishop::~Bishop() {}

bool Bishop::isMoveAvailable(int startRow, int startColumn, int endRow, int endColumn) const
{
    if (abs(endRow - startRow) == abs(endColumn - startColumn)) {
        int rStep = startRow < endRow ? 1 : -1;
        int cStep = startColumn < endColumn ? 1 : -1;
        for (int i = startRow + rStep, j = startColumn + cStep; i != endRow; i += rStep, j += cStep) {
            if ((*m_chessboard)[i][j] != nullptr)
                return false;
        }
        return true;
    }
    return false;
}
