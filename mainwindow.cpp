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
    setWindowIcon(QIcon(":/icons/icons/icon_main.png"));

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

    // Toolbar setup
    QToolBar *toolBar = new QToolBar("Controls", this);
    toolBar->setMovable(false);
    toolBar->setIconSize(QSize(24, 24));

    // Create a QPushButton instead of QAction for custom styling
    QPushButton *refreshButton = new QPushButton(QIcon(":/icons/icons/icon_update.png"), "Refresh", this);

    // Apply the dark gradient style with more pronounced gradient
    refreshButton->setStyleSheet(
        "QPushButton {"
        "  min-width: 80px;"
        "  min-height: 24px;"
        "  border-radius: 6px;"
        "  padding: 2px 10px;"
        "  color: white;"
        "  background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "    stop:0 #666666, stop:0.5 #333333, stop:1 #000000);"  // More pronounced gradient
        "  border: 1px solid #777777;"                            // Lighter border
        "  font-family: Arial;"
        "  font-size: 9pt;"
        "  font-weight: bold;"
        "  letter-spacing: 0.5px;"
        "}"
        "QPushButton:hover {"
        "  background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "    stop:0 #777777, stop:0.5 #444444, stop:1 #111111);"  // Lighter hover gradient
        "}"
        "QPushButton:pressed {"
        "  background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "    stop:0 #000000, stop:0.5 #222222, stop:1 #444444);"  // Inverted pressed gradient
        "}"
        "QPushButton:disabled {"
        "  color: #888888;"
        "  background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "    stop:0 #444444, stop:1 #222222);"
        "}"
        );

    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::refreshStream);

    // Add the button to the toolbar
    toolBar->addWidget(refreshButton);
    addToolBar(Qt::TopToolBarArea, toolBar);
    setCentralWidget(webView);
}

void MainWindow::refreshStream()
{
    webView->reload();
}
