TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

LIBS += -lcrypto -lssl

LIBS += \
       -lboost_system\

LIBS += -Wl,--no-as-needed -lpthread

QMAKE_CXXFLAGS += -std=c++11 -pthread -Wpedantic -Wextra
LIBS += -lpthread
