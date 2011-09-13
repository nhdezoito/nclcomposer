#include "qncgrectangleinterface.h"

QncgRectangleInterface::QncgRectangleInterface(QncgEntity* parent)
    : QncgInterface(parent)
{
}

QncgRectangleInterface::~QncgRectangleInterface()
{

}

void QncgRectangleInterface::draw(QPainter* painter)
{
    painter->setBrush(QColor("#0000FF"));
    //painter->setRenderHint(QPainter::Antialiasing,true);

    if (isSelected()){
        painter->setPen(QPen(QBrush(Qt::black), 0, Qt::DashLine));
        painter->drawEllipse(4, 4, getWidth()-1, getHeight()-1);
    }else{
//        painter->setPen(QPen(QBrush(Qt::black), 0));
        painter->drawEllipse(4, 4, getWidth()-1, getHeight()-1);
    }

    if (isMoving()){
        if (parentItem() != NULL){
            painter->setBrush(Qt::NoBrush);
            painter->setPen(QPen(QBrush(Qt::black), 0));            // 0px = cosmetic border
            painter->drawEllipse(getMoveLeft()+4-getLeft(),getMoveTop()+4-getTop(),getWidth()-1,getHeight()-1);
        }else{
            painter->setBrush(Qt::NoBrush);
            painter->setPen(QPen(QBrush(Qt::black), 0));            // 0px = cosmetic border
            painter->drawEllipse(getMoveLeft()+4-getLeft(),getMoveTop()+4-getTop(),getWidth()-1,getHeight()-1);
        }

    }else if (isResizing()){
        painter->setBrush(Qt::NoBrush);
        painter->setPen(QPen(QBrush(Qt::black), 0));                // 0px = cosmetic border
        painter->drawEllipse(getResizeLeft()+4-getLeft(),getResizeTop()+4-getTop(),getResizeWidth()-1,getResizeHeight()-1);

//        painter->setPen(QPen(QBrush(Qt::black), 0,Qt::DashLine));            // 0px = cosmetic border
//        painter->drawRect(getResizeLeft()+4-getLeft(),getResizeTop()+4-getTop(),getResizeWidth()-1,getResizeHeight()-1);
    }
}

void QncgRectangleInterface::delineate(QPainterPath* painter) const
{
    painter->addRect(4, 4, getWidth(), getHeight());
}