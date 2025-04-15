#pragma once

#include <QMainWindow>
#include <QWebEngineView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(const QString &url, QWidget *parent = nullptr);

private slots:
    void startStream();
    void pauseStream();     // Not fully supported in WebView
    void stopStream();
    void refreshStream();
    void checkStreamStatus();

private:
    QString streamUrl;
    QWebEngineView *webView;
    QPushButton *startBtn, *pauseBtn, *stopBtn, *refreshBtn;
    QTimer *checkTimer;
    QString lastUrl;
};
