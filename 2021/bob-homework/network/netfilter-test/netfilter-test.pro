TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ip.cpp \
        iphdr.cpp \
        main.cpp \
        tcphdr.cpp

HEADERS += \
    ip.h \
    iphdr.h \
    tcphdr.h

LIBS += -lnetfilter_queue
