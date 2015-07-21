#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "chessboardmanager.h"
#include <QString>
#include <memory>

class ChessPiece
{
public:
    ChessPiece(const QString &type, const QString &color, const std::shared_ptr<Chessboard> chessboard
               , QQmlApplicationEngine *engine, QQuickItem *parent, int row, int column);
    virtual ~ChessPiece();

    const QString& type() const { return m_type; }
    const QString& color() const { return m_color; }
    QQuickItem *item() { return m_item; }

    virtual bool isMoveAvailable(int startRow, int startColumn, int endRow, int endColumn) const = 0;

protected:
    const QString m_type;
    const QString m_color;
    const std::shared_ptr<Chessboard> m_chessboard;
    QQuickItem *m_item;
};

#endif // CHESSPIECE_H
