#include <QCoreApplication>
#include <QCommandLineParser>
#include <QtH3C>
#include <signal.h>
#include <iostream>
#include "client.h"
#include "utils.h"

using namespace QH3C;

static void onSIGINT_TREM(int sig)
{
    if (SIGINT == sig || SIGTERM == sig)
        qApp->quit();
}

Utils::LogLevel stringToLogLevel(const QString& str)
{
    if (str.compare("DEBUG", Qt::CaseInsensitive) == 0) {
        return Utils::LogLevel::DEBUG;
    } else if (str.compare("INFO", Qt::CaseInsensitive) == 0) {
        return Utils::LogLevel::INFO;
    } else if (str.compare("WARN", Qt::CaseInsensitive) == 0) {
        return Utils::LogLevel::WARN;
    } else if (str.compare("ERROR", Qt::CaseInsensitive) == 0) {
        return Utils::LogLevel::ERROR;
    } else if (str.compare("FATAL", Qt::CaseInsensitive) == 0) {
        return Utils::LogLevel::FATAL;
    }
    std::cerr << "Log level " << str.toStdString()
              << " is not recognised, default to INFO" << std::endl;
    return Utils::LogLevel::INFO;
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(Utils::messageHandler);

    QCoreApplication a(argc, argv);
    a.setApplicationName("QtH3C");
    a.setApplicationVersion(Common::version());

    signal(SIGINT, onSIGINT_TREM);
    signal(SIGTERM, onSIGINT_TREM);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption configFile("c",
            "specify config.json file",
            "config_file",
            "config.json");
    QCommandLineOption eitf("e",
            "the network interface to use",
            "either_interface");
    QCommandLineOption userId("i",
            "specify user ID for identify",
            "id");
    QCommandLineOption userPwd("p",
            "specify user password",
            "password");
    QCommandLineOption daemon(
            QStringList() << "d" << "daemon",
            "run as daemon process");
    QCommandLineOption log("L",
            "logging level. Valid levels are: debug, info, warn, error, fatal. default:\"info\"",
            "log_level",
            "info");
    parser.addOption(configFile);
    parser.addOption(eitf);
    parser.addOption(userId);
    parser.addOption(userPwd);
    parser.addOption(daemon);
    parser.addOption(log);
    parser.process(a);

    Utils::logLevel = stringToLogLevel(parser.value(log));
    Client c;
    if (!c.readConfig(parser.value(configFile))) {
        if (1 == argc) {
            parser.showHelp();
        }

        QDebug(QtMsgType::QtInfoMsg).noquote() << "Ues Argument From Console";
        c.setup(parser.value(eitf),
                parser.value(userId),
                parser.value(userPwd),
                parser.isSet(daemon));
    }

    c.start();
    return a.exec();
}
