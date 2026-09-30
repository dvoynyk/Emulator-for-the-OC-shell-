#include <QApplication>
#include "MainWindow.h"
#include "ConfigParser.h"
#include "ScriptExecutor.h"
#include <windows.h>

int main(int argc, char *argv[]) {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    QApplication app(argc, argv);

    ConfigParser configParser;
    AppConfig config = configParser.parse(argc, argv);

    configParser.printConfig(config);

    MainWindow window(config);
    window.show();

    if (config.hasScript)
    {
        ScriptExecutor scriptExecutor;

        if (scriptExecutor.loadScript(config.pathStartScript))
        {
            scriptExecutor.executeScript();
        }
    }

    return app.exec();
}