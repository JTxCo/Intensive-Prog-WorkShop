#include "mainwindow.h"
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include "exprtk.hpp"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), display(new QLineEdit(this)), historyDisplay(new QTextEdit(this))
{
    createButtons();

    QWidget *centralWidget = new QWidget(this);
    QGridLayout *layout = new QGridLayout(centralWidget);

    layout->addWidget(display, 0, 0, 1, 4);

    // Numbers 1-9 in a 3x3 grid
    for(int i = 1; i <= 9; i++) {
        layout->addWidget(buttons[i], ((i-1) / 3) + 1, ((i-1) % 3));
    }

    // Operation buttons beside 3, 6, 9
    layout->addWidget(buttons[10], 1, 3); // '+'
    layout->addWidget(buttons[11], 2, 3); // '-'
    layout->addWidget(buttons[12], 3, 3); // '*'

    // Bottom row: 0, and '/'
    layout->addWidget(buttons[0], 4, 1);
    layout->addWidget(buttons[13], 4, 3); // '/'

    // Add equals button, clear history button, and clear display button
    QPushButton *buttonEquals = new QPushButton("=", this);
    connect(buttonEquals, &QPushButton::clicked, this, &MainWindow::calculate);
    layout->addWidget(buttonEquals, 5, 0);

    QPushButton *buttonClear = new QPushButton("Clear History", this);
    connect(buttonClear, &QPushButton::clicked, this, &MainWindow::clearHistory);
    layout->addWidget(buttonClear, 5, 1);

    QPushButton *displayClear = new QPushButton("Clear Display", this);
    connect(displayClear, &QPushButton::clicked, this, &MainWindow::clearDisplay);
    layout->addWidget(displayClear, 5, 2);
    layout->addWidget(historyDisplay, 6, 0, 1, 4);
    setCentralWidget(centralWidget);
}

void MainWindow::createButtons()
{
    for(int i = 0; i <= 9; i++) {
        buttons[i] = new QPushButton(QString::number(i), this);
        connect(buttons[i], &QPushButton::clicked, this, &MainWindow::buttonClicked);
    }

    buttons[10] = new QPushButton(QString("+"), this);
    connect(buttons[10], &QPushButton::clicked, this, &MainWindow::buttonClickedForPlus);
    buttons[11] = new QPushButton(QString("-"), this);
    connect(buttons[11], &QPushButton::clicked, this, &MainWindow::buttonClickedForMinus);
    buttons[12] = new QPushButton(QString("*"), this);
    connect(buttons[12], &QPushButton::clicked, this, &MainWindow::buttonClickedForMultiplication);
    buttons[13] = new QPushButton(QString("/"), this);
    connect(buttons[13], &QPushButton::clicked, this, &MainWindow::buttonClickedForDivision);


    display->setReadOnly(true);
    historyDisplay->setReadOnly(true);
}

void MainWindow::buttonClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString clickedText = clickedButton->text();

    // Add the button text to the QLineEdit display and history.
    display->setText(display->text() + clickedText);
}


void MainWindow::buttonClickedForPlus()
{
    QString currentText = display->text();
    currentText += "+";  // append "+" to the current text
    display->setText(currentText);
}

void MainWindow::buttonClickedForMinus()
{
    QString currentText = display->text();
    currentText += "-";  // append "-" to the current text
    display->setText(currentText);
}

void MainWindow::buttonClickedForMultiplication()
{
    QString currentText = display->text();
    currentText += "*";  // append "*" to the current text
    display->setText(currentText);
}

void MainWindow::buttonClickedForDivision()
{
    QString currentText = display->text();
    currentText += "/";  // append "/" to the current text
    display->setText(currentText);
}
void MainWindow::calculate() {
    //using the exprtk to parse and do the operations
    QString qstringExpression = display->text();
    std::string expression = qstringExpression.toStdString();

    using parser_t = exprtk::parser<double>;
    parser_t parser;
    exprtk::expression<double> expressionToEvaluate;
    if(parser.compile(expression, expressionToEvaluate)) {
        double result = expressionToEvaluate.value();
        // Display the result
        qstringExpression += "= " + QString::number(result);
        addToHistory(qstringExpression);
        display->setText(QString::number(result));
    } else {
        // Error handling for parse failure
        display->setText("error");
    }

}

void MainWindow::clearHistory() {
    historyDisplay->clear();
}
void MainWindow::clearDisplay(){
    display->clear();
}

void MainWindow::addToHistory(const QString &item) {
    historyDisplay->append(item);
}

MainWindow::~MainWindow()
{
    delete display;
    for(int i = 0; i <= 16; i++) {
        delete buttons[i];
    }
}
