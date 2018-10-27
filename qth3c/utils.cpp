//
// Created by arshrow on 18-10-27.
//
#include <QDateTime>
#include <iostream>
#include "utils.h"

void Utils::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    const std::string timestamp =
            QDateTime::currentDateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz").toStdString();
    const std::string message = msg.toStdString();
    switch(type) {
        case QtDebugMsg:
            if (Utils::logLevel <= LogLevel::DEBUG) {
                std::cout << timestamp << " DEBUG: " << message << std::endl;
            }
            break;
        case QtInfoMsg:
            if (Utils::logLevel <= LogLevel::INFO) {
                std::cout << timestamp << " INFO: " << message << std::endl;
            }
            break;
        case QtWarningMsg:
            if (Utils::logLevel <= LogLevel::WARN) {
                std::cout << timestamp << " WARN: " << message << std::endl;
            }
            break;
        case QtCriticalMsg:
            if (Utils::logLevel <= LogLevel::ERROR) {
                std::cout << timestamp << " ERROR: " << message << std::endl;
            }
            break;
        case QtFatalMsg:
            // FATAL is not allowed to skip
            std::cerr << timestamp << " FATAL: " << message << std::endl;
            abort();
    }
}