#ifndef LOGGER_H
#define LOGGER_H

#include <QMessageBox>

namespace Logger{
    void showInformationMessage(QWidget *parent, QString title);
    void showFailMessage(QWidget *parent, QString title);
}

#endif // LOGGER_H
