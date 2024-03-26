#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include "plotwindow.h"
#include "point.h"

/**
  Creates a new Point object with coordinates x and y
  @param x int x coordinate
  @param y int y coordinate
*/
Point::Point(QColor color, const int x, const int y) {
  this->color_ = color;
  x_ = x;
  y_ = y;
}


void Point::changeColor(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event);

    qDebug() << "point clicked!";

    // Day 3, Task 2, Step 1
    // emit this signal when the user right-clicks on the point
    // you can compare the event()->button value to Qt::ModifierYouAreLookingFor
    if(event->button() == Qt::RightButton){
        emit PointSelected(this);
    }

    // Day 3, Task 1
    // Change the color of the point when the user clicks on it

    // change to a new color
    int r = QRandomGenerator::global()->generate() % 256;
    int g = QRandomGenerator::global()->generate() % 256;
    int b = QRandomGenerator::global()->generate() % 256;
    QColor c(r, g, b);
    color_ = c;
    qDebug() << "(" << r << "," << g << "," << b << ")";

    // need to make the point actually re-paint itself
    update();
}



//in point.cpp
void Point::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(PlotWindow::getDeleteMode()){
        emit deletePoint(this);
    }
    else{
        changeColor( event);
    }
}





// where is this object located
// always a rectangle, Qt uses this to know "where" the user
// would be interacting with this object
QRectF Point::boundingRect() const
{
    return QRectF(x_, y_, width_, width_);
}

// define the actual shape of the object
QPainterPath Point::shape() const
{
    QPainterPath path;
    path.addEllipse(x_, y_, width_, width_);
    return path;
}

// called by Qt to actually display the point
void Point::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);


    QBrush b = painter->brush();
    // update the line for setBrush to be this
    painter->setBrush(QBrush(color_));

    painter->drawEllipse(QRect(this->x_, this->y_, this->width_, this->width_));
    painter->setBrush(b);
}

/**
  Calculates the distance between this point and another Point.
  @param other Point object to calculate the distance to
*/
double Point::Distance(const Point &other) const {
  double distance = (x_ - other.get_x()) * (x_ - other.get_x());
  distance += (y_ - other.y_) * (y_ - other.y_);
  return sqrt(distance);
}


/**
  Makes it so the == operator will have the behavior that you
  expect when comparing points.
  You can overload pretty much any operator in c++
  @param first Point left hand side of the expression
  @param other Point right hand side of the expression
*/
bool operator==(const Point &first, const Point &other) {
  return first.x_ == other.x_ && first.y_ == other.y_;
}
