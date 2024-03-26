#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QPushButton;
class QLineEdit;
class QTextEdit;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void buttonClicked();
    void calculate();
    void clearDisplay();
    void clearHistory();
    void buttonClickedForPlus();
    void buttonClickedForMinus();
    void buttonClickedForMultiplication();
    void buttonClickedForDivision();

private:
    QLineEdit *display;
    QTextEdit *historyDisplay;
    QPushButton *buttons[16]; // 10 numbers, plus, minus, multiply, divide, equals, clear

    void createButtons();
    void addToHistory(const QString &item);
};
#endif // MAINWINDOW_H
