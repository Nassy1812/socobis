#ifndef RIGHTCLICKBUTTON_H
#define RIGHTCLICKBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class RightClickButton: public QPushButton{
public:
    RightClickButton(QWidget *parent = nullptr) : QPushButton(parent){};
protected:
    void mousePressEvent(QMouseEvent *event) override{
        if(event->button() == Qt::RightButton){
            emit rightClicked(event->pos());
        }else{
            QPushButton::mousePressEvent(event);
        }
    }
signals:
    void rightClicked(const QPoint& pos);

};

#endif // RIGHTCLICKBUTTON_H
