#include "custombutton.h"
#include <QMouseEvent>
CustomButton::CustomButton(QWidget* parent) : QPushButton(parent)
{

}

void CustomButton::setData(int data){
    this->data = data;
}

int CustomButton::getData(){
    return this->data;
}

void CustomButton::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton){
        emit btnClicked(this->data);
    }
    if(event->button() == Qt::RightButton){
        emit rightClicked(this,event->pos());
    }
}
