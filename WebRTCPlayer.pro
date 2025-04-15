QT += core gui widgets webenginewidgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h

RESOURCES +=

# Optional: Increase WebEngine cache if needed
QMAKE_CXXFLAGS += -Wall
