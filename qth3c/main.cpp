#include <QCoreApplication>
#include <QCommandLineParser>
#include <QtH3C>
#include <signal.h>
#include <iostream>
#include <zconf.h>
#include "client.h"

using namespace QH3C;

static void onSIGINT_TREM(int sig)
{
    if (SIGINT == sig || SIGTERM == sig)
        qApp->quit();
}

int main(int argc, char *argv[])
{
    if (0 != getuid()) {
        std::cout << "Permission Denied! Please try to add \"sudo\"" << std::endl;
        exit(-1);
    }
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
    QCommandLineOption daemon("d",
            "whether to run as daemon process",
            "daemon");
    parser.addOption(configFile);
    parser.addOption(eitf);
    parser.addOption(userId);
    parser.addOption(userPwd);
    parser.addOption(daemon);
    parser.process(a);

    Client c;
    if (!c.readConfig(parser.value(configFile))) {
        c.setup(parser.value(eitf),
                parser.value(userId),
                parser.value(userPwd),
                parser.isSet(daemon));
    }
    c.start();
    return a.exec();
}