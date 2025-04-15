#include "MainWindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QToolBar>
#include <QAction>
#include <QUrlQuery>
#include <QTimer>
#include <QIcon>

MainWindow::MainWindow(const QString &url, QWidget *parent)
    : QMainWindow(parent), streamUrl(url)
{
    resize(640, 500);

    // Set app icon
    setWindowIcon(QIcon("icon_main.ico"));

    webView = new QWebEngineView(this);

    QUrl urlObj(streamUrl);
    webView->load(urlObj);

    connect(webView, &QWebEngineView::loadFinished, this, [=](bool ok) {
        if (!ok) {
            QTimer::singleShot(5000, this, &MainWindow::refreshStream);
        }
    });

    QUrlQuery query(urlObj);
    QString workflowId = query.queryItemValue("workflowId");

    if (!workflowId.isEmpty()) {
        setWindowTitle("GIRN Dispatcher - Streaming: " + workflowId);
    } else {
        setWindowTitle("GIRN Dispatcher - Streaming Viewer");
    }

    // Refresh Toolbar
    QToolBar *toolBar = new QToolBar("Controls", this);
    toolBar->setMovable(false);
    toolBar->setIconSize(QSize(24, 24));

    QAction *refreshAction = new QAction(QIcon("icon_update.ico"), "Refresh", this);
    refreshAction->setToolTip("Refresh Stream");

    connect(refreshAction, &QAction::triggered, this, &MainWindow::refreshStream);

    toolBar->addAction(refreshAction);
    addToolBar(Qt::TopToolBarArea, toolBar);

    setCentralWidget(webView);
}

void MainWindow::refreshStream()
{
    webView->reload();
}
