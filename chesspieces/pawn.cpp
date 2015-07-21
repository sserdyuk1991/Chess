#include "pawn.h"

Pawn::Pawn(const QString &color, const std::shared_ptr<Chessboard> chessboard
           , QQmlApplicationEngine *engine, QQuickItem *parent, int row, int column)
    : ChessPiece("pawn", color, chessboard, engine, parent, row, column) {}

Pawn::~Pawn() {}

bool Pawn::isMoveAvailable(int startRow, int startColumn, int endRow, int endColumn) const
{
    const QString &color = (*m_chessboard)[startRow][startColumn]->color();
    int step = ((color == "white") ? -1 : 1);

    if (startColumn == endColumn) {
        if ((*m_chessboard)[startRow + step][startColumn] != nullptr) {
            return false;
        } else {
            if (startRow + step == endRow) {
                return true;
            } else {
                bool isPawnInStart = (((color == "white") && (startRow == 6))
                                      || ((color == "black") && (startRow == 1)));
                if (isPawnInStart && (startRow + 2 * step == endRow) &&
                        (*m_chessboard)[endRow][endColumn] == nullptr) {
                    return true;
                }
            }
        }
    } else {
        if ((abs(startColumn - endColumn) == 1) && (startRow + step == endRow)
                && ((*m_chessboard)[endRow][endColumn] != nullptr)
                && ((*m_chessboard)[endRow][endColumn]->color() != color)) {
            return true;
        }
    }

    return false;
}
