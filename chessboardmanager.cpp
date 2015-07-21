#include "chessboardmanager.h"
#include "chesspieces/chesspiece.h"
#include "chesspieces/king.h"
#include "chesspieces/queen.h"
#include "chesspieces/rook.h"
#include "chesspieces/bishop.h"
#include "chesspieces/knight.h"
#include "chesspieces/pawn.h"
#include <QQuickWindow>
#include <QFile>
#include <QTextStream>

ChessboardManager::ChessboardManager(QQmlApplicationEngine *engine, QObject *parent)
    : m_engine(engine), QObject(parent)
{
    m_chessboard = std::make_shared<Chessboard>(Chessboard(8, QVector<ChessPiece *>(8, nullptr)));

    QQuickWindow *mainWindow = qobject_cast<QQuickWindow *>(m_engine->rootObjects().first());
    m_item = mainWindow->findChild<QQuickItem *>("gameField");
}

ChessboardManager::~ChessboardManager()
{
    clearChessboard();
}

void ChessboardManager::start()
{
    m_chessboardModel = ChessboardModel(8, QVector<int>(8, 0));

    m_chessboardModel[0][0] = -4;
    m_chessboardModel[0][1] = -2;
    m_chessboardModel[0][2] = -3;
    m_chessboardModel[0][3] = -5;
    m_chessboardModel[0][4] = -6;
    m_chessboardModel[0][5] = -3;
    m_chessboardModel[0][6] = -2;
    m_chessboardModel[0][7] = -4;

    m_chessboardModel[1][0] = -1;
    m_chessboardModel[1][1] = -1;
    m_chessboardModel[1][2] = -1;
    m_chessboardModel[1][3] = -1;
    m_chessboardModel[1][4] = -1;
    m_chessboardModel[1][5] = -1;
    m_chessboardModel[1][6] = -1;
    m_chessboardModel[1][7] = -1;

    m_chessboardModel[7][0] = 4;
    m_chessboardModel[7][1] = 2;
    m_chessboardModel[7][2] = 3;
    m_chessboardModel[7][3] = 5;
    m_chessboardModel[7][4] = 6;
    m_chessboardModel[7][5] = 3;
    m_chessboardModel[7][6] = 2;
    m_chessboardModel[7][7] = 4;

    m_chessboardModel[6][0] = 1;
    m_chessboardModel[6][1] = 1;
    m_chessboardModel[6][2] = 1;
    m_chessboardModel[6][3] = 1;
    m_chessboardModel[6][4] = 1;
    m_chessboardModel[6][5] = 1;
    m_chessboardModel[6][6] = 1;
    m_chessboardModel[6][7] = 1;

    m_gameHistory.clear();
    m_gameHistory << m_chessboardModel;

    m_lastMoveColor = "black";

    getGameStateFromModel();
}

void ChessboardManager::stop()
{
    clearChessboard();
}

void ChessboardManager::save(QUrl fileName)
{
    QFile file(fileName.toLocalFile());
    if (!file.open(QIODevice::WriteOnly))
        return;

    QTextStream out(&file);
    out.setFieldWidth(3);
    for (const auto &gameState : m_gameHistory) {
        for (const auto &row : gameState) {
            for (const auto &cell : row)
                out << cell;
            out << '\n';
        }
        out << '\n';
    }
}

void ChessboardManager::load(QUrl fileName)
{
    QFile file(fileName.toLocalFile());
    if (!file.open(QIODevice::ReadOnly))
        return;

    QTextStream in(&file);
    m_gameHistory.clear();
    QVector<QVector<int>> gameState;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList sl = line.split(" ");
        QVector<int> row;

        for (const auto &str : sl) {
            if (str != "")
                row << str.toInt();
        }

        if (gameState.size() != 8) {
            gameState << row;
        } else {
            m_gameHistory << gameState;
            gameState.clear();
        }
    }

    m_chessboardModel = m_gameHistory.last();
    m_stateIndex = m_gameHistory.length() - 1;
    getGameStateFromModel();
}

void ChessboardManager::prev()
{
    if (m_stateIndex > 0) {
        m_chessboardModel = m_gameHistory[--m_stateIndex];
        getGameStateFromModel();
    }
}

void ChessboardManager::next()
{
    if (m_stateIndex < m_gameHistory.length() - 1) {
        m_chessboardModel = m_gameHistory[++m_stateIndex];
        getGameStateFromModel();
    }
}

void ChessboardManager::move(int startX, int startY, int endX, int endY)
{
    int startRow = getIndex(startY);
    int startColumn = getIndex(startX);
    int endRow = getIndex(endY);
    int endColumn = getIndex(endX);

    auto &firstObject = (*m_chessboard)[startRow][startColumn];
    const QString &color = firstObject->color();
    auto item = firstObject->item();

    if (((startRow != endRow) || (startColumn != endColumn)) && (m_lastMoveColor != color)
            && firstObject->isMoveAvailable(startRow, startColumn, endRow, endColumn)) {
        auto &secondObject = (*m_chessboard)[endRow][endColumn];

        if (secondObject != nullptr) {
            if (color != secondObject->color()) {
                performMove(item, startRow, startColumn, endRow, endColumn, color);

                delete secondObject;
                secondObject = firstObject;
                firstObject = nullptr;
            } else {
                moveItem(item, startRow, startColumn);
            }
        } else {
            performMove(item, startRow, startColumn, endRow, endColumn, color);

            secondObject = firstObject;
            firstObject = nullptr;
        }
    } else {
        moveItem(item, startRow, startColumn);
    }
}

void ChessboardManager::getGameStateFromModel()
{
    setSquareSize();
    clearChessboard();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int id = m_chessboardModel[i][j];
            if (id != 0)
                createChessPieceById(id, i, j);
        }
    }
}

void ChessboardManager::setSquareSize()
{
    m_squareSize = m_item->property("squareSize").toInt();
}

void ChessboardManager::clearChessboard()
{
    for (auto &row : (*m_chessboard)) {
        for (auto &cell : row) {
            delete cell;
            cell = nullptr;
        }
    }
}

void ChessboardManager::createChessPieceById(int id, int row, int column)
{
    QString color = ((id < 0) ? "black" : "white");

    switch (abs(id)) {
    case 1:
        (*m_chessboard)[row][column] = new Pawn(color, m_chessboard, m_engine, m_item, row, column);
        break;
    case 2:
        (*m_chessboard)[row][column] = new Knight(color, m_chessboard, m_engine, m_item, row, column);
        break;
    case 3:
        (*m_chessboard)[row][column] = new Bishop(color, m_chessboard, m_engine, m_item, row, column);
        break;
    case 4:
        (*m_chessboard)[row][column] = new Rook(color, m_chessboard, m_engine, m_item, row, column);
        break;
    case 5:
        (*m_chessboard)[row][column] = new Queen(color, m_chessboard, m_engine, m_item, row, column);
        break;
    case 6:
        (*m_chessboard)[row][column] = new King(color, m_chessboard, m_engine, m_item, row, column);
        break;
    default:
        break;
    }
}

int ChessboardManager::getIndex(int coordinate) const
{
    return coordinate / m_squareSize;
}

int ChessboardManager::getCoordinate(int index) const
{
    return index * m_squareSize;
}

void ChessboardManager::moveItem(QQuickItem *item, int row, int column)
{
    item->setProperty("x", getCoordinate(column));
    item->setProperty("y", getCoordinate(row));
}

void ChessboardManager::performMove(QQuickItem *item, int startRow, int startColumn
                                    , int endRow, int endColumn, const QString &color)
{
    moveItem(item, endRow, endColumn);

    m_chessboardModel[endRow][endColumn] = m_chessboardModel[startRow][startColumn];
    m_chessboardModel[startRow][startColumn] = 0;
    m_gameHistory << m_chessboardModel;
    m_stateIndex = m_gameHistory.length() - 1;
    m_lastMoveColor = color;
}
