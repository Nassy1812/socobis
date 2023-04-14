#include "mainwindow.h"
#include "model.h"

#include <QApplication>
#include <QFile>
#include <QLocale>
#include <QMessageBox>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QLocale locale(QLocale::French,QLocale::Madagascar);
    QLocale::setDefault(locale);

    if(!model::initDb()){
        QMessageBox::critical(nullptr,
                                       "Socobis",
                                       "Le fichier socobis.db est introuvale, "
                                       "Réinstaller le logiciel peut corriger cette erreur");
        return -1;

    }

//    QFile f(":/assets/qss/pagefold.qss");

//    if (!f.exists())   {
//        printf("Unable to set stylesheet, file not found\n");
//    }
//    else   {
//        f.open(QFile::ReadOnly | QFile::Text);
//        QTextStream ts(&f);
//        a.setStyleSheet(ts.readAll());
//    }

//    QApplication::setStyle(QStyleFactory::create("Fusion"));
    MainWindow w;
    w.hide();

    return a.exec();
}
