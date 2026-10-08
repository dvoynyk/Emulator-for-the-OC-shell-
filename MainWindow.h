#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <string>
#include <memory>
#include "ConfigParser.h"

class VFSManager;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(const AppConfig& config, QWidget *parent = nullptr);
    ~MainWindow() override = default;

private:
    void setupUi();

private slots:
    void onCommandEntered();

private:
    QTextEdit *historyArea;
    QLineEdit *inputField;
    std::string userPrompt;
    AppConfig appConfig;
    std::shared_ptr<VFSManager> vfsManager;
};

#endif // MAINWINDOW_HPP