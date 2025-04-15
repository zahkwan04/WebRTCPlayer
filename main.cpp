#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString streamUrl;
    if (argc > 1) {
        streamUrl = argv[1];
    }

    MainWindow window(streamUrl);
    window.show();
    return app.exec();
}
