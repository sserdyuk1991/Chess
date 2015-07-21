#ifndef CHESSBOARDMANAGER_H
#define CHESSBOARDMANAGER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <memory>

class ChessPiece;

using Chessboard = QVector<QVector<ChessPiece *>>;
using ChessboardModel = QVector<QVector<int>>;

class ChessboardManager : public QObject
{
    Q_OBJECT
public:
    explicit ChessboardManager(QQmlApplicationEngine *engine, QObject *parent = 0);
    ~ChessboardManager();

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void save(QUrl fileName);
    Q_INVOKABLE void load(QUrl fileName);
    Q_INVOKABLE void prev();
    Q_INVOKABLE void next();
    Q_INVOKABLE void move(int startX, int startY, int endX, int endY);
    Q_INVOKABLE void setSquareSize();

signals:

public slots:

private:
    void getGameStateFromModel();
    void clearChessboard();
    void createChessPieceById(int id, int row, int column);
    int getIndex(int coordinate) const;
    int getCoordinate(int index) const;
    void moveItem(QQuickItem *item, int row, int column);
    void performMove(QQuickItem *item, int startRow, int startColumn
                     , int endRow, int endColumn, const QString &color);

    std::shared_ptr<Chessboard> m_chessboard;
    ChessboardModel m_chessboardModel;
    QVector<ChessboardModel> m_gameHistory;
    QString m_lastMoveColor;
    int m_stateIndex;
    QQmlApplicationEngine *m_engine;
    QQuickItem *m_item;
    int m_squareSize;
};

#endif // CHESSBOARDMANAGER_H
