#include "logger.h"


void Logger::showInformationMessage(QWidget *parent, QString text){
    QMessageBox::information(parent,"Socobis",text);
}

void Logger::showFailMessage(QWidget *parent, QString text){
    QMessageBox::critical(parent,"Socobis",text);
}
