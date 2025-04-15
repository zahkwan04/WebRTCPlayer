#include "MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(const QString &url, QWidget *parent)
    : QMainWindow(parent), streamUrl("http://10.12.49.100/showStream?workflowId=teststream") {

    webView = new QWebEngineView(this);

    startBtn = new QPushButton("Start");
    pauseBtn = new QPushButton("Pause");
    stopBtn = new QPushButton("Stop");
    refreshBtn = new QPushButton("Refresh");

    connect(startBtn, &QPushButton::clicked, this, &MainWindow::startStream);
    connect(pauseBtn, &QPushButton::clicked, this, &MainWindow::pauseStream);
    connect(stopBtn, &QPushButton::clicked, this, &MainWindow::stopStream);
    connect(refreshBtn, &QPushButton::clicked, this, &MainWindow::refreshStream);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(webView);
    layout->addWidget(startBtn);
    layout->addWidget(pauseBtn);
    layout->addWidget(stopBtn);
    layout->addWidget(refreshBtn);

    QWidget *central = new QWidget(this);
    central->setLayout(layout);
    setCentralWidget(central);

    resize(700, 700);

    if (!streamUrl.isEmpty()) {
        startStream();
    }

    checkTimer = new QTimer(this);
    connect(checkTimer, &QTimer::timeout, this, &MainWindow::checkStreamStatus);
    checkTimer->start(10000);  // 10 seconds for example
}

void MainWindow::startStream() {
    if (!streamUrl.isEmpty()) {
        webView->load(QUrl(streamUrl));
        lastUrl = streamUrl;
    }
}

void MainWindow::pauseStream() {
    // Not directly supported in WebView — you could inject JS to pause video if needed
    qDebug() << "Pause not supported in QWebEngineView directly.";
}

void MainWindow::stopStream() {
    webView->setHtml("<html><body><p>Stream stopped.</p></body></html>");
}

void MainWindow::refreshStream() {
    if (!lastUrl.isEmpty()) {
        webView->reload();
    }
}

void MainWindow::checkStreamStatus() {
    // Basic mechanism: if blank page is detected, refresh
    webView->page()->toPlainText([this](const QString &text) {
        if (text.trimmed().isEmpty()) {
            qDebug() << "No stream data, attempting auto-refresh...";
            refreshStream();
        }
    });
}
