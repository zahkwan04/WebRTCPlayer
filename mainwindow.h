#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString &url, QWidget *parent = nullptr);

private slots:
    void refreshStream();

private:
    QWebEngineView *webView;
    QString streamUrl;
};

#endif // MAINWINDOW_H
