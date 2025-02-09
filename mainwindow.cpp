#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), firstOperand(0) {
    ui->setupUi(this);

    // Apply a blue color theme
    QString style = R"(
        QMainWindow {
            background-color: #1E90FF;  /* DodgerBlue background */
        }
        QLineEdit {
            background-color: white;
            color: black;
            font-size: 20px;
            border: 2px solid #4682B4; /* SteelBlue border */
            border-radius: 5px;
            padding: 5px;
        }
        QPushButton {
            background-color: #4682B4; /* SteelBlue buttons */
            color: white;
            font-size: 16px;
            border: none;
            padding: 10px;
            border-radius: 5px;
        }
        QPushButton:hover {
            background-color: #5B9BD5; /* Lighter blue on hover */
        }
        QPushButton:pressed {
            background-color: #1C6EA4; /* Darker blue when pressed */
        }
    )";

    this->setStyleSheet(style);

    // Connect number buttons (0-9) and operations
    QList<QPushButton*> buttons = this->findChildren<QPushButton*>();
    for (QPushButton* button : buttons) {
        connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onButtonClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString buttonText = button->text();

    if (buttonText == "C") {
        currentInput.clear();
        firstOperand = 0;
        operation.clear();
        ui->display->setText("0");
    } else if (buttonText == "+" || buttonText == "-" || buttonText == "*" || buttonText == "/") {
        firstOperand = currentInput.toDouble();
        operation = buttonText;
        currentInput.clear();
    } else if (buttonText == "=") {
        double secondOperand = currentInput.toDouble();
        double result = 0;

        if (operation == "+") result = firstOperand + secondOperand;
        else if (operation == "-") result = firstOperand - secondOperand;
        else if (operation == "*") result = firstOperand * secondOperand;
        else if (operation == "/") result = secondOperand != 0 ? firstOperand / secondOperand : 0;

        ui->display->setText(QString::number(result));
        currentInput = QString::number(result);
        operation.clear();
    } else { // Numbers
        currentInput += buttonText;
        ui->display->setText(currentInput);
    }
}
