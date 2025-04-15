#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QString streamUrl;
    if (argc > 1) {
        streamUrl = QString::fromUtf8(argv[1]);
    }

    MainWindow window(streamUrl);
    window.show();
    return app.exec();
}
