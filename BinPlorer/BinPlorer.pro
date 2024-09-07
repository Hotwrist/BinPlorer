QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#LIBS += -L"C:/msys64/mingw64/lib" -lbfd -lz -liberty -lssp -lopcodes -lintl -liconv -lctf -lzstd
LIBS += -L/usr/lib -lbfd
INCLUDEPATH += /usr/include

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    binary.cpp \
    main.cpp \
    binplorer.cpp \
    section.cpp \
    symbol.cpp

HEADERS += \
    binary.h \
    binplorer.h \
    section.h \
    symbol.h

FORMS += \
    binplorer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    bp_icon.qrc
