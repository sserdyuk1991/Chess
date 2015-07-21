#include "chessboardmanager.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/resources/qml/main.qml")));

    ChessboardManager chessboardManager(&engine);
    engine.rootContext()->setContextProperty("Engine", &chessboardManager);

    return app.exec();
}
