#include "chesspiece.h"

ChessPiece::ChessPiece(const QString &type, const QString &color, const std::shared_ptr<Chessboard> chessboard
                       , QQmlApplicationEngine *engine, QQuickItem *parentItem, int row, int column)
    : m_type(type), m_color(color), m_chessboard(chessboard)
{
    QQmlComponent component(engine, QUrl(QStringLiteral("qrc:/qml/resources/qml/ChessPiece.qml")));
    m_item = qobject_cast<QQuickItem *>(component.create());

    m_item->setParent(parentItem);
    m_item->setParentItem(parentItem);

    int squareSize = parentItem->property("squareSize").toInt();
    m_item->setProperty("width", squareSize);
    m_item->setProperty("x", column * squareSize);
    m_item->setProperty("y", row * squareSize);
    QString source = "/images/resources/images/" + m_color + "_" + m_type + ".svg";
    m_item->setProperty("src", source);
}

ChessPiece::~ChessPiece()
{
    m_item->deleteLater();
}
