//
// Created by arshrow on 18-10-27.
//

#ifndef QTH3C_UTILS_H
#define QTH3C_UTILS_H

#include <QtGlobal>
#include <QStringList>

struct Utils {
    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

    enum class LogLevel {
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };
    static LogLevel logLevel;
};

#endif //QTH3C_UTILS_H
