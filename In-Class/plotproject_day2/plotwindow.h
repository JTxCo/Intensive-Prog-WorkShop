#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace Ui {
class PlotWindow;
}

class PlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = 0);
    ~PlotWindow();


private slots:
    void on_randomButton_clicked();

    void SlotTest();

private:
    Ui::PlotWindow *ui;

    QGraphicsScene *scene;
};

#endif // PLOTWINDOW_H
