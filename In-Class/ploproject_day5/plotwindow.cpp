#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QTime>

#include "plotwindow.h"
#include "ui_plotwindow.h"
#include "point.h"
#include <QMessageBox>
#include <QLayout>
// Name:
//
//
int PlotWindow::addPoints()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Dialog Title");


    QVBoxLayout layout(&dialog);

    // Create a label
    QLabel label("Please enter you details:", &dialog);
    layout.addWidget(&label);


    QLineEdit lineEdit(&dialog);
    lineEdit.setPlaceholderText("Here");
    layout.addWidget(&lineEdit);

    // Create an OK button
    QPushButton okButton("OK", &dialog);
    layout.addWidget(&okButton);
    connect(&okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    // Make the dialog modal and execute it
    dialog.exec();
    return lineEdit.text().toInt();
}



void PlotWindow::randomPoints(int numPoints)
{
    srand(static_cast<unsigned>(QTime::currentTime().msec()));

    for (int i = 0; i < numPoints; ++i) {
        // Generate random coordinates and color values
        int x = rand() % ui->plotGraphicsView->frameSize().width();
        int y = rand() % ui->plotGraphicsView->frameSize().height();
        QColor color(rand() % 256, rand() % 256, rand() % 256);

        // Random adjustment
        x -= Point::get_width() / 2;
        y -= Point::get_width() / 2;

        // Instantiate a point with random color at random position
        Point *p = new Point(color, x, y);

        // Add point to the scene
        scene->addItem(p);

        // Connect the custom signals to the custom slots
        connect(p, &Point::PointSelected, this, &PlotWindow::PointSelectedSlot);
        connect(p, &Point::DeletePoint, this, &PlotWindow::DeletePointSlot);
        connect(p, &Point::DrawLine, this, &PlotWindow::DrawLineSlot);
    }
}


PlotWindow::PlotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotWindow)
{
    // we need to set up the ui before we draw on our scene
    ui->setupUi(this);
    int inputtedNums = this->addPoints();
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


    qDebug() << "Here's an example debugging statement";

    // Calculate the mid points
    int x_mid = view->frameSize().height() / 2;
    int y_mid = view->frameSize().width() / 2;
    // draw the axes
    // this is the horizontal line
    QPen pen(QColor(255, 25, 255));
    scene->addLine(0, x_mid, view->frameSize().width(), x_mid, pen);
    // this is the vertical line
    scene->addLine(y_mid, 0, y_mid, view->frameSize().height(), pen);

    connect(ui->randomButton, &QAbstractButton::pressed, this, &PlotWindow::SlotTest);

    // equations to calculate adjusted coordinates
    //int x_adj = x + (ui->plotGraphicsView->frameSize().width() / 2);
    //int y_adj = (-1 * y + (ui->plotGraphicsView->frameSize().height() / 2));


    // Slots & signals
    // 1) default signal + default slot (on_randomButton_clicked)
    // 2) default signal + custom slot (SlotTest)
    //      make sure to connect the signal to the slot
    // 3) custom signal + custom slot
    //      define the signal & the slot (matching parameters)
    //      emit the signal
    //      connect the signal to the slot
    // the sender is a point, so wherever you are instantiating points (not within the Point constructor)
    // is where you want to call connect
    randomPoints(inputtedNums);

    // needs to be "clicked" and not "click" to be a signal!
    connect(ui->addButton, &QAbstractButton::clicked, this, &PlotWindow::AddPoint);

    first_point_ = nullptr;
    prev_point_ = nullptr;
    delete_mode_ = false;
}

void PlotWindow::AddHelper() {
   bool safe = false;
   int x = ui->xCoord->text().toInt(&safe);
   if (!safe) {
       return;
   }
   // do the same thing for the y coordinate
   int y = ui->yCoord->text().toInt(&safe);
   if (!safe) {
       return;
   }

     // then create your point and add it to the scene!
   QColor c(0, 0, 155);
   int x_adj = x + (ui->plotGraphicsView->frameSize().width() / 2);
   // account for the width of the point
   x_adj = x_adj - Point::get_width() / 2;
   int y_adj = (-1 * y + (ui->plotGraphicsView->frameSize().height() / 2));
   // account for the height of the point (which is the same as the width because it's a circle)
   y_adj = y_adj - Point::get_width() / 2;
   Point * p = new Point(c, x_adj, y_adj);
   scene->addItem(p);
   connect(p, &Point::PointSelected, this, &PlotWindow::PointSelectedSlot);
   connect(p, &Point::DeletePoint, this, &PlotWindow::DeletePointSlot);
   connect(p, &Point::DrawLine, this, &PlotWindow::DrawLineSlot);
}

// (option 1, default slot)
//void PlotWindow::on_addButton_clicked() {
//    this->AddHelper();
//}

// (option 2, custom slot) -> you can see the connect statement in the constructor
void PlotWindow::AddPoint() {
    this->AddHelper();
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

// Day 3, task 2, step 2
// Modify this slot to display the coordinates under the Point 1 Label when the user right-clicks on the point
// you can use the setText() method for labels that takes in QString as a parameter

// Day 3, task 2, step 3
// Now display the coordinates under the Point 2 label and then display the distance in the distance label
// You may need to track some information across calls to this slot.
// Hint: Using additional field(s) may help you accomplish this task
void PlotWindow::PointSelectedSlot(Point *p) {
    if(first_point_){
        std::string text = "Point 2: ("+ std::to_string(p->get_x()) + "," + std::to_string(p->get_y()) + ")";
        ui->point2Label->setText(text.c_str());

        double distance = p->Distance(*first_point_);
        std::string dist_text = "Distance: " + std::to_string(distance);
        ui->distanceLabel->setText(dist_text.c_str());

        first_point_ = nullptr;
    }
    else{
        first_point_ = p;
        std::string text = "Point 1: ("+ std::to_string(p->get_x()) + "," + std::to_string(p->get_y()) + ")";
        ui->point1Label->setText(text.c_str());

        ui->distanceLabel->setText(QString("Distance: "));
        ui->point2Label->setText(QString("Point 2: "));
    }

}

// Day 3, Task 3, Step 2
// In the slot (default or custom) add code to flip the value in the delete_mode_ boolean
// Add code to change the cursor when the user is in delete_mode_
    // you can use ui->centralWidget->setCursor() method for this
// Remember to change it back when the user is no longer in delete mode

void PlotWindow::on_deletePoints_clicked()
{
    delete_mode_ = !delete_mode_;
    if(delete_mode_){
        ui->centralWidget->setCursor(Qt::CrossCursor);
    }
    else{
        ui->centralWidget->setCursor(Qt::ArrowCursor);
    }
}

void PlotWindow::DeletePointSlot(Point *p){
    if(delete_mode_){
        scene->removeItem(p);
    }
}

void PlotWindow::DrawLineSlot(Point *p){
    if(!prev_point_){
        prev_point_ = p;
    }
    else{
        int width = Point::get_width()/2;
        scene->addLine(prev_point_->get_x() + width, prev_point_->get_y() + width, p->get_x() + width, p->get_y() + width, QPen(QColor(255,255,255)));
        prev_point_ = p;
    }
}

