#include "MainWindow.h"
#include "SystemInfo.h"
#include "Parser.h"
#include "Executor.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QApplication>
#include <QScrollBar>

MainWindow::MainWindow(const AppConfig& config, QWidget *parent)
    : QMainWindow(parent), appConfig(config)
{
    setupUi();
}

void MainWindow::setupUi() {
    resize(800, 600);

    setWindowTitle(QString::fromStdString(SystemInfo::getWindowTitle()));

    userPrompt = SystemInfo::getUsername() + "@" + SystemInfo::getHostname() + ":~$ ";

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    historyArea = new QTextEdit(this);
    historyArea->setReadOnly(true);
    historyArea->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

    historyArea->append("Добро пожаловать в Shell Emulator [Этап 2]!");
    historyArea->append("Доступные команды: ls, cd, exit\n");

    inputField = new QLineEdit(this);
    inputField->setPlaceholderText("Введите команду...");

    mainLayout->addWidget(historyArea);
    mainLayout->addWidget(inputField);

    inputField->setFocus();

    connect(inputField, &QLineEdit::returnPressed, this, &MainWindow::onCommandEntered);
}

void MainWindow::onCommandEntered() {
    QString rawInputStr = inputField->text();
    std::string inputStr = rawInputStr.toStdString();

    if (inputStr.empty()) {
        return;
    }

    historyArea->append(QString::fromStdString(userPrompt + inputStr));
    inputField->clear();

    ParseResult parseResult = Parser::parse(inputStr);

    if (!parseResult.success) {
        historyArea->append("<font color='red'>" + QString::fromStdString(parseResult.errorMessage) + "</font>\n");
        return;
    }

    ExecutionResult execResult = Executor::execute(parseResult.tokens);

    if (!execResult.output.empty()) {
        if (execResult.isError) {
            historyArea->append("<font color='red'>" + QString::fromStdString(execResult.output) + "</font>\n");
        } else {
            historyArea->append(QString::fromStdString(execResult.output) + "\n");
        }
    }

    historyArea->verticalScrollBar()->setValue(historyArea->verticalScrollBar()->maximum());

    if (execResult.shouldExit) {
        QApplication::quit();
    }
}