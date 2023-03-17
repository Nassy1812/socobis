QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Form/addpiecedialog.cpp \
    controller/machinecontroller.cpp \
    controller/panneanalysecontroller.cpp \
    controller/pannehistoriquecontroller.cpp \
    controller/personnelcontroller.cpp \
    controller/stockcontroller.cpp \
    form/addensembledialog.cpp \
    form/addsousensembledialog.cpp \
    logger.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    models/machine.cpp \
    controller/tableaubordcontroller.cpp \
    repository/CoupureElectriciteRepository.cpp \
    repository/EnsembleRepository.cpp \
    repository/EquipeRepository.cpp \
    repository/InterventionRepository.cpp \
    repository/MarchandiseRepository.cpp \
    repository/PanneRepository.cpp \
    repository/PieceRepository.cpp \
    repository/machinerepository.cpp \
    repository/personnelrepository.cpp \
    repository/sousEnsembleRepository.cpp \
    util/custombutton.cpp

HEADERS += \
    Form/addpiecedialog.h \
    controller/machinecontroller.h \
    controller/panneanalysecontroller.h \
    controller/pannehistoriquecontroller.h \
    controller/personnelcontroller.h \
    controller/stockcontroller.h \
    form/addensembledialog.h \
    form/addsousensembledialog.h \
    logger.h \
    mainwindow.h \
    model.h \
    models/coupureElectricite.h \
    models/ensemble.h \
    models/equipe.h \
    models/intervention.h \
    models/machine.h \
    models/marchandise.h \
    models/panne.h \
    models/personnel.h \
    models/piece.h \
    models/sous_ensemble.h \
    models/stock.h \
    repository/CoupureElectriciteRepository.h \
    repository/EnsembleRepository.h \
    repository/EquipeRepository.h \
    repository/InterventionRepository.h \
    repository/MarchandiseRepository.h \
    repository/PanneRepository.h \
    repository/PieceRepository.h \
    repository/machinerepository.h \
    repository/personnelrepository.h \
    repository/sousEnsembleRepository.h \
    controller/tableaubordcontroller.h \
    util/custombutton.h

FORMS += \
    Form/addpiecedialog.ui \
    controller/machinecontroller.ui \
    controller/panneanalysecontroller.ui \
    controller/pannehistoriquecontroller.ui \
    controller/personnelcontroller.ui \
    controller/stockcontroller.ui \
    form/addensembledialog.ui \
    form/addsousensembledialog.ui \
    mainwindow.ui \
    controller/tableaubordcontroller.ui\


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    socobis.qrc\

RC_ICONS = socobis.ico
