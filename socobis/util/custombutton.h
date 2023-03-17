#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class CustomButton : public QPushButton

{
    Q_OBJECT
public:
    CustomButton(QWidget* parent=nullptr);
    void setData(int data);
    int getData();
private :
    int data;

signals:
    void btnClicked(int);
    void rightClicked(CustomButton*,QPoint);
protected:
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // CUSTOMBUTTON_H
