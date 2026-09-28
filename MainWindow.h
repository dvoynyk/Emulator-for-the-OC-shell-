#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <string>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private:
    void setupUi();

private slots:
    void onCommandEntered();

private:
    QTextEdit *historyArea;
    QLineEdit *inputField;
    std::string userPrompt;
};

#endif // MAINWINDOW_HPP