QT       += core gui
QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aspirateur_agent.cpp \
    aspiration_thread.cpp \
    deplacement_thread.cpp \
    entite_simulation.cpp \
    environement_manoir.cpp \
    exploration_non_informees_thread.cpp \
    fenetre_affichage_manoir.cpp \
    main_aspirateur_manoir.cpp \
    main_windows_aspirateur_manoir.cpp \
    ramassage_thread.cpp \
    salle_manoir.cpp \
    vision_thread.cpp

HEADERS += \
    aspirateur_agent.h \
    aspiration_thread.h \
    deplacement_thread.h \
    entite_simulation.h \
    environement_manoir.h \
    exploration_non_informees_thread.h \
    fenetre_affichage_manoir.h \
    main_aspirateur_manoir.h \
    ramassage_thread.h \
    salle_manoir.h \
    vision_thread.h

FORMS += \
    main_aspirateur_manoir.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
