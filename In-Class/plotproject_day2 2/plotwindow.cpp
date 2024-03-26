#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QTime>

#include "plotwindow.h"
#include "ui_plotwindow.h"
#include "point.h"

// Name:
//
//

PlotWindow::PlotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotWindow)
{
    // we need to set up the ui before we draw on our scene
    ui->setupUi(this);

    // the QGraphicsView is the UI element that contains the
    // scene that we will actually get to draw on.
    QGraphicsView * view = ui->plotGraphicsView;

    // scene is a QGraphicsScene pointer field of the PlotWindow class
    // this makes our lives easier by letting us easily access it
    // from other functions in this class.
    scene = new QGraphicsScene;
    view->setScene(scene);

    // make the scene the same size as the view containing it
    view->setSceneRect(0,0,view->frameSize().width(),view->frameSize().height());

    // we'll want to generate random numbers later so we're
    // going to seed our random number generator once
    srand(static_cast<unsigned>(QTime::currentTime().msec()));

    //
    qDebug() << "Here's an example debugging statement";

    // Calculate the mid points
    int x_mid = view->frameSize().height() / 2;
    int y_mid = view->frameSize().width() / 2;

    // draw the axes
    scene->addLine(0, x_mid, view->frameSize().width(), x_mid, QPen(QColor(Qt::white)));
    scene->addLine(y_mid, 0, y_mid, view->frameSize().height(), QPen(QColor(Qt::white)));

    // connect a default signal with a custom slot
    connect(ui->randomButton, &QAbstractButton::pressed, this, &PlotWindow::SlotTest);
    connect(ui->addButton, &QAbstractButton::pressed, this, &PlotWindow::AddPointSlot);
    // @TODO: Write equations to calculate adjusted coordinates. See Canvas for help.

    // @TODO: Day 2, Task 3, Step 1 here
    // i. Instantiate a Point*. Go through the Point.h to figure out the expected parameters in the constructor.
    // QColor can be instantiated by giving integer values for R,G,B. example: QColor(255,255,255)

    int x_adj = -10 + (ui->plotGraphicsView->frameSize().width() /2 );
    int y_adj = (-1*8 + (ui->plotGraphicsView->frameSize().height() /2));

    Point * point = new Point(QColor(25.5, 41.2, 88.2) , x_adj, y_adj);
    scene->addItem(point);
    // ii. Add this point to the scene initialized above using scene->addItem() and passing your Point*.
    // You should be able to see this point on your UI when you run this application.
    // iii. Did the point appear in the correct quadrant? If not, make necessary adjustment to your Point's coordinates.


}

void PlotWindow::SlotTest() {
    qDebug() << "random button pressed custom slot!";
}


PlotWindow::~PlotWindow()
{
    delete ui;
}

void PlotWindow::on_randomButton_clicked()
{
    qDebug() << "random button clicked default slot!";
}

// Day 2, Task 4, Step 1&2 here.
// @TODO: A slot for the "click" event on the "Add Point" button will be created here (manually or default).
// If you are manually writing a slot, remember to connect it to the point that is being added to the scene in the constructor.
// Refer to the previous lecture code or look at the example in the constructor.
// Where does it show up in the .h file?
void PlotWindow::AddPointSLot(){
    qDebug()<< "add point button pressed ";
}


// @TODO: Add code in this slot that actually adds a Point to the graphics scene.
// Refer to Canvas to get started.



