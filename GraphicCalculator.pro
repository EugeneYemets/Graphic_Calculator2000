QT += widgets
CONFIG += c++11

# Source files
SOURCES += main.cpp \
           mainwindow.cpp

# Header files
HEADERS += mainwindow.hpp  # Change from mainwindow.hpp to mainwindow.h (ensure consistency with actual file name)

# UI files created with Qt Designer
FORMS += mainwindow.ui

# Output file name
TARGET = GraphicCalculator

# Use += instead of = to avoid overwriting default libraries
LIBS += -lpthread
