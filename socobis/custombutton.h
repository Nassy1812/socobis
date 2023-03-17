#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class CustomButton : public QPushButton
{
public:
    CustomButton(QWidget *parent=nullptr);
    signals:
        void rightClicked(QPoint pos);

protected:
    void mousePressEvent(QMouseEvent *event) override{
        if(event->button() == Qt::RightButton){
            emit CustomButton::rightClicked(event->pos());
        }else{
            QPushButton::mousePressEvent(event);
        }
    }
};

#endif // CUSTOMBUTTON_H
