#include "StructuralBind.h"

StructuralBind::StructuralBind(StructuralEntity* parent)
  : StructuralEdge(parent)
{
  setStructuralCategory(Structural::Edge);
  setStructuralType(Structural::Bind);

  link = NULL;
}

StructuralBind::~StructuralBind()
{
}

void StructuralBind::setType(StructuralRole type)
{
  this->_name = type;

  switch(type)
  {
    //ACTIONS
    case Structural::Start:
      this->icon = ":/icon/start";
      break;

    case Structural::Stop:
      this->icon = ":/icon/stop";
      break;

    case Structural::Resume:
      this->icon = ":/icon/resume";
      break;

    case Structural::Pause:
      this->icon = ":/icon/pause";
      break;

    case Structural::Set:
      this->icon = ":/icon/set";
      break;

    //CONDITIONS
    case Structural::onBegin:
      this->icon = ":/icon/onbegin";
      break;

    case Structural::onEnd:
      this->icon = ":/icon/onend";
      break;

    case Structural::onResume:
      this->icon = ":/icon/onresume";
      break;

    case Structural::onPause:
      this->icon = ":/icon/onpause";
      break;

    case Structural::onSelection:
      this->icon = ":/icon/onselection";
      break;

    default:
      this->icon = "";
      break;
  }
}


void StructuralBind::setLocalProperty(const QString &name, const QString &value)
{/*
  if (name == "LOCAL:BIND")
  {
    setType((StructuralR) value.toInt());
    setRole(StructuralUtil::getStrFromStructuralRole(getType()));
  }

  StructuralEdge::setLocalProperty(name, value);*/
}

StructuralRole StructuralBind::getType()
{
  return _name;
}

QString StructuralBind::getIcon()
{
  return icon;
}

void StructuralBind::adjust(bool avoidCollision, bool rec)
{
  StructuralEdge::adjust(avoidCollision, rec);

  // Adjusting properties...
  QString tip = "";
  QString name = (getStructuralId() != "" ? getStructuralId() : "?");

  tip += "Bind ("+name+")";

  setToolTip(tip);

  // Adjusting position...
  if(isCondition())
    adjust_condition();
   else
  adjust_action();
}

void StructuralBind::adjust_action()
{
  if (getTail() != NULL && getHead() != NULL)
  {
    QLineF line = QLineF(QPointF(getTail()->getLeft() + getTail()->getWidth()/2,
                                 getTail()->getTop() + getTail()->getHeight()/2),
                         QPointF(getHead()->getLeft() + getHead()->getWidth()/2,
                                 getHead()->getTop() + getHead()->getHeight()/2));

    if (getTail()->getStructuralCategory() == Structural::Interface)
    {
      line.setP1(getStructuralParent()->mapFromItem(getTail()->getStructuralParent(), line.p1()));
    }

    if (getHead()->getStructuralCategory() == Structural::Interface)
    {
      line.setP2(getStructuralParent()->mapFromItem(getHead()->getStructuralParent(), line.p2()));
    }

    globlalPointA = line.p1();
    globlalPointB = line.p2();

    adjustBox(line);

    getHead()->setSelectable(false);

    qreal index;

    if (globlalPointA != globlalPointB)
    {
      index = 1.0;

      int n = 0;

      adjustExtreme(getHead(), line, 1.0, -0.01, getAngle());

//      globlalPointB.setX(getLeft() + STR_DEFAULT_PADDING);
//      globlalPointB.setY(getTop() + STR_DEFAULT_PADDING);


//      while(getHead()->collidesWithItem(this))
//      {
//        index -= 0.01;

//        globlalPointB = getPointAt(line, getAngle(), index);

//        adjustBox(globlalPointA, globlalPointB);

//        if (++n > 100){ // avoiding infinity loop
//          break;
//        }
//      }

    }

    getHead()->setSelectable(true);

    if (scene() != NULL)
      scene()->update();
  }
}

void StructuralBind::adjust_condition()
{
  if (getTail() != NULL && getHead() != NULL)
  {
    QLineF line = QLineF(QPointF(getTail()->getLeft() + getTail()->getWidth()/2,
                                 getTail()->getTop() + getTail()->getHeight()/2),
                         QPointF(getHead()->getLeft() + getHead()->getWidth()/2,
                                 getHead()->getTop() + getHead()->getHeight()/2));

    if (getTail()->getStructuralCategory() == Structural::Interface)
    {
      line.setP1(getStructuralParent()->mapFromItem(getTail()->getStructuralParent(), line.p1()));
    }

    if (getHead()->getStructuralCategory() == Structural::Interface)
    {
      line.setP2(getStructuralParent()->mapFromItem(getHead()->getStructuralParent(), line.p2()));
    }

    globlalPointA = line.p1();
    globlalPointB = line.p2();

    adjustBox(line);

    getTail()->setSelectable(false);

    qreal index;

    if (globlalPointA != globlalPointB){

      index = 0;

      int n = 0;

      adjustExtreme(getTail(), line, 0.0, 0.01, getAngle());

//      globlalPointA.setX(getLeft() + STR_DEFAULT_PADDING);
//      globlalPointA.setY(getTop() + STR_DEFAULT_PADDING);

//      while(getTail()->collidesWithItem(this))
//      {
//        index += 0.01;


//        globlalPointA = getPointAt(line, getAngle(), index, true);



//        adjustBox(globlalPointA, globlalPointB);

//        if (++n > 100) // avoiding infinity loop
//          break;
//      }

    }

    getTail()->setSelectable(true);

    if (scene() != NULL)
      scene()->update();
  }
}

void StructuralBind::draw(QPainter* painter)
{
   if(isCondition())
    draw_condition(painter);
   else
    draw_action(painter);

  drawMouseHoverHighlight(painter); // This should not be HERE!!


}

void StructuralBind::draw_action(QPainter* painter)
{
  if (getTail() != NULL && getHead() != NULL)
  {
    if (icon.isEmpty())
      icon = ":/icon/noaction";

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);

    QLineF line = QLineF(QPointF(getTail()->getLeft() + getTail()->getWidth()/2,
                                 getTail()->getTop() + getTail()->getHeight()/2),
                         QPointF(getHead()->getLeft() + getHead()->getWidth()/2,
                                 getHead()->getTop() + getHead()->getHeight()/2));

    if (getTail()->getStructuralCategory() == Structural::Interface)
    {
      line.setP1(getStructuralParent()->mapFromItem(getTail()->getStructuralParent(), line.p1()));
    }

    if (getHead()->getStructuralCategory() == Structural::Interface)
    {
      line.setP2(getStructuralParent()->mapFromItem(getHead()->getStructuralParent(), line.p2()));
    }

    QPointF pointa = QPointF(getTailLeft(), getTailTop());
    QPointF pointb =  QPointF(getHeadLeft(), getHeadTop());

//    if (!isInvalid() && !hasError)
      painter->setPen(QPen(QBrush(QColor("#000000")), 1));
//    else
//      painter->setPen(QPen(QBrush(QColor(255,0,0,200)), 1, Qt::DashLine));


    if (pointa.x() <= pointb.x() && pointa.y() <= pointb.y())
    {
      if (getAngle() != 0)
      {
        qreal drawangle = getAlfa();

        QLineF localline(4+4,4+4, 4+8+getWidth()-16, 4+8+getHeight()-16);

        if (drawangle < 0)
        {
          drawangle = -drawangle;
        }

        qreal R = localline.length()/(::sin(((drawangle/2)*PI)/180)*2);

        qreal delta = (180-drawangle)/2 + (360 - localline.angle());

        QPointF center_a(localline.p2().x() - ::cos((180-delta-drawangle)*PI/180)*R,
                         localline.p2().y() + ::sin((180-delta-drawangle)*PI/180)*R);

        QPointF center_b(localline.p1().x() + ::cos((180-delta-drawangle)*PI/180)*R,
                         localline.p1().y() - ::sin((180-delta-drawangle)*PI/180)*R);




        if (getAlfa() < 0)
        {
          painter->drawArc(center_b.x()-R,center_b.y()-R,2*R,2*R,
                           16*((180-delta-drawangle)+180),16*drawangle);
        }
        else
        {
          painter->drawArc(center_a.x()-R,center_a.y()-R,2*R,2*R
                           ,16*(180-delta-drawangle),16*drawangle);
        }
      }
      else
      {
        painter->drawLine(4+4,4+4, 4+8+getWidth()-16, 4+8+getHeight()-16);
      }

      painter->setPen(Qt::NoPen);

      painter->drawPixmap(4+getWidth()-16, 4+getHeight()-16, 16, 16, QPixmap(icon));

//      if (!isInvalid() && !hasError)
//      {
        painter->setBrush(QBrush(QColor("#000000")));
//      }
//      else
//      {
//        painter->setBrush(QBrush(QColor(255,0,0,75)));
//        painter->drawEllipse(3+getWidth()-16, 3+getHeight()-16, 18, 18);
//      }
    }
    else if (pointa.x() > pointb.x() && pointa.y() <= pointb.y())
    {
      if (getAngle() != 0)
      {
        qreal drawangle = getAlfa();

        QLineF localline(4+4+getWidth()-8,4+4, 4+8, 4+8+getHeight()-16);

        if (drawangle < 0)
        {
          drawangle = -drawangle;
        }

        qreal R = localline.length()/(::sin(((drawangle/2)*PI)/180)*2);

        qreal delta = (180-drawangle)/2 + (360 - localline.angle());

        QPointF center_a(localline.p2().x() - ::cos(((2*localline.angle() - drawangle - 540)/2)*PI/180)*R,
                         localline.p2().y() + ::sin(((2*localline.angle() - drawangle - 540)/2)*PI/180)*R);

        QPointF center_b(localline.p1().x() + ::cos(((2*localline.angle() - drawangle - 540)/2)*PI/180)*R,
                         localline.p1().y() - ::sin(((2*localline.angle() - drawangle - 540)/2)*PI/180)*R);


        if (getAlfa() < 0)
        {
          painter->drawArc(center_b.x()-R,center_b.y()-R,2*R,2*R,
                           16*((180-delta-drawangle)+180),16*drawangle);
        }
        else
        {
          painter->drawArc(center_a.x()-R,center_a.y()-R,2*R,2*R
                           ,16*(180-delta-drawangle),16*drawangle);
        }
      }
      else
      {
        painter->drawLine(4+4+getWidth()-8,4+4, 4+8, 4+8+getHeight()-16);
      }


      painter->setPen(Qt::NoPen);

      painter->drawPixmap(4, 4+getHeight()-16, 16, 16, QPixmap(icon));

//      painter->setBrush(QBrush(QColor(255,0,0,75)));

//      if (!isInvalid() && !hasError)
//      {
        painter->setBrush(QBrush(QColor("#000000")));
//      }
//      else
//      {
//        painter->setBrush(QBrush(QColor(255,0,0,75)));
//        painter->drawEllipse(3, 3+getHeight()-16, 18, 18);
//      }
    }
    else if (pointa.x() <= pointb.x() && pointa.y() > pointb.y())
    {
      if (getAngle() != 0)
      {
        qreal drawangle = getAlfa();

        QLineF localline(4+4, 4+4+getHeight()-8, 4+8+getWidth()-16, 4+8);

        if (drawangle < 0)
        {
          drawangle = -drawangle;
        }

        qreal R = localline.length()/(::sin(((drawangle/2)*PI)/180)*2);

        qreal delta = (180-drawangle)/2 + (360 - localline.angle());

        QPointF center_a(localline.p2().x() - ::cos((180-delta-drawangle)*PI/180)*R,
                         localline.p2().y() + ::sin((180-delta-drawangle)*PI/180)*R);

        QPointF center_b(localline.p1().x() + ::cos((180-delta-drawangle)*PI/180)*R,
                         localline.p1().y() - ::sin((180-delta-drawangle)*PI/180)*R);

        if (getAlfa() < 0)
        {
          painter->drawArc(center_b.x()-R,center_b.y()-R,2*R,2*R,
                           16*((180-delta-drawangle)+180),16*drawangle);
        }
        else
        {
          painter->drawArc(center_a.x()-R,center_a.y()-R,2*R,2*R
                           ,16*(180-delta-drawangle),16*drawangle);
        }
      }
      else
      {
        painter->drawLine(4+4, 4+4+getHeight()-8, 4+8+getWidth()-16, 4+8);
      }

      painter->setPen(Qt::NoPen);

      painter->drawPixmap(4+getWidth()-16,4,16,16, QPixmap(icon));

//      if (!isInvalid() && !hasError)
//      {
        painter->setBrush(QBrush(QColor("#000000")));
//      }
//      else
//      {
//        painter->setBrush(QBrush(QColor(255,0,0,75)));
//        painter->drawEllipse(3+getWidth()-16,3,18,18);
//      }
    }
    else if (pointa.x() > pointb.x() && pointa.y() > pointb.y())
    {
      if (getAngle() != 0){
        qreal drawangle = getAlfa();

        QLineF localline(4+4+getWidth()-8, 4+4+getHeight()-8, 4+8, 4+8);

        if (drawangle < 0)
        {
          drawangle = -drawangle;
        }

        qreal R = localline.length()/(::sin(((drawangle/2)*PI)/180)*2);

        qreal delta = (180-drawangle)/2 + (360 - localline.angle());

        QPointF center_a(localline.p2().x() - ::cos((180-delta-drawangle)*PI/180)*R,
                         localline.p2().y() + ::sin((180-delta-drawangle)*PI/180)*R);

        QPointF center_b(localline.p1().x() + ::cos((180-delta-drawangle)*PI/180)*R,
                         localline.p1().y() - ::sin((180-delta-drawangle)*PI/180)*R);

        if (getAlfa() < 0)
        {
          painter->drawArc(center_b.x()-R,center_b.y()-R,2*R,2*R,
                           16*((180-delta-drawangle)+180),16*drawangle);
        }
        else
        {
          painter->drawArc(center_a.x()-R,center_a.y()-R,2*R,2*R
                           ,16*(180-delta-drawangle),16*drawangle);
        }
      }
      else
      {
        painter->drawLine(4+4+getWidth()-8, 4+4+getHeight()-8, 4+8, 4+8);
      }

      painter->setPen(Qt::NoPen);

      painter->drawPixmap(4,4,16,16, QPixmap(icon));

//      if (!isInvalid() && !hasError)
//      {
        painter->setBrush(QBrush(QColor("#000000")));
//      }
//      else
//      {
//        painter->setBrush(QBrush(QColor(255,0,0,75)));
//        painter->drawEllipse(3,3,18,18);
//      }
    }
  }
}

void StructuralBind::draw_condition(QPainter* painter)
{
  if (getTail() != NULL && getHead() != NULL)
  {
    if (icon.isEmpty())
      icon = ":/icon/nocondition";

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);

    QLineF line = QLineF(QPointF(getTail()->getLeft() + getTail()->getWidth()/2,
                                 getTail()->getTop() + getTail()->getHeight()/2),
                         QPointF(getHead()->getLeft() + getHead()->getWidth()/2,
                                 getHead()->getTop() + getHead()->getHeight()/2));

    if (getTail()->getStructuralCategory() == Structural::Interface)
    {
      line.setP1(getStructuralParent()->mapFromItem(getTail()->getStructuralParent(), line.p1()));
    }

    if (getHead()->getStructuralCategory() == Structural::Interface)
    {
      line.setP2(getStructuralParent()->mapFromItem(getHead()->getStructuralParent(), line.p2()));
    }

    QPointF pointa = QPointF(getTailLeft(), getTailTop());
    QPointF pointb =  QPointF(getHeadLeft(), getHeadTop());

    qDebug() << "----";
    qDebug() << "----" << getLeft() << getTop() << getWidth() << getHeight();
    qDebug() << "----" << line;
    qDebug() << "----" << pointa << pointb;
    qDebug() << "----";

//    if (!isInvalid() && !hasError)
      painter->setPen(QPen(QBrush(QColor("#000000")), 1));
//    else
//      painter->setPen(QPen(QBrush(QColor(255,0,0,200)), 1, Qt::DashLine));

    if (pointa.x() <= pointb.x() && pointa.y() <= pointb.y())
    {
      if (getAngle() != 0)
      {
        qreal drawangle = getAlfa();

        QLineF localline(4+8,4+8, 4+getWidth()-4, 4+getHeight()-4);

        if (drawangle < 0)
        {
          drawangle = -drawangle;
        }

        qreal R = localline.length()/(::sin(((drawangle/2)*PI)/180)*2);

        qreal delta = (180-drawangle)/2 + (360 - localline.angle());

        QPointF center_a(localline.p2().x() - ::cos((180-delta-drawangle)*PI/180)*R,
                         localline.p2().y() + ::sin((180-delta-drawangle)*PI/180)*R);

        QPointF center_b(localline.p1().x() + ::cos((180-delta-drawangle)*PI/180)*R,
                         localline.p1().y() - ::sin((180-delta-drawangle)*PI/180)*R);

        if (getAlfa() < 0)
        {
          painter->drawArc(center_b.x()-R,center_b.y()-R,2*R,2*R,
                           16*((180-delta-drawangle)+180),16*drawangle);
        }
        else
        {
          painter->drawArc(center_a.x()-R,center_a.y()-R,2*R,2*R
                           ,16*(180-delta-drawangle),16*drawangle);
        }
      }
      else
      {
        painter->drawLine(4+8,4+8, 4+getWidth()-4, 4+getHeight()-4);
      }

      painter->setPen(Qt::NoPen);

      painter->drawPixmap(4,4,16,16, QPixmap(icon));

//      if (!isInvalid() && !hasError)
//      {
        painter->setBrush(QBrush(QColor("#000000")));
//      }
//      else
//      {
//        painter->setBrush(QBrush(QColor(255,0,0,75)));
//        painter->drawEllipse(3,3, 18, 18);
//      }
    }
    else if (pointa.x() >= pointb.x() && pointa.y() <= pointb.y())
    {
      if (getAngle() != 0)
      {
        qreal drawangle = getAlfa();

        QLineF localline(4+getWidth()-8,4+8, 4+4, 4+getHeight()-4);

        if (drawangle < 0)
        {
          drawangle = -drawangle;
        }

        qreal R = localline.length()/(::sin(((drawangle/2)*PI)/180)*2);

        qreal delta = (180-drawangle)/2 + (360 - localline.angle());

        QPointF center_a(localline.p2().x() - ::cos((180-delta-drawangle)*PI/180)*R,
                         localline.p2().y() + ::sin((180-delta-drawangle)*PI/180)*R);

        QPointF center_b(localline.p1().x() + ::cos((180-delta-drawangle)*PI/180)*R,
                         localline.p1().y() - ::sin((180-delta-drawangle)*PI/180)*R);

        if (getAlfa() < 0)
        {
          painter->drawArc(center_b.x()-R,center_b.y()-R,2*R,2*R,
                           16*((180-delta-drawangle)+180),16*drawangle);
        }
        else
        {
          painter->drawArc(center_a.x()-R,center_a.y()-R,2*R,2*R
                           ,16*(180-delta-drawangle),16*drawangle);
        }
      }
      else
      {
        painter->drawLine(4+getWidth()-8,4+8, 4+4, 4+getHeight()-4);
      }

      painter->setPen(Qt::NoPen);

      painter->drawPixmap(4+getWidth()-16,4,16,16, QPixmap(icon));

//      if (!isInvalid() && !hasError)
//      {
        painter->setBrush(QBrush(QColor("#000000")));
//      }
//      else
//      {
//        painter->setBrush(QBrush(QColor(255,0,0,75)));
//        painter->drawEllipse(3+getWidth()-16,3, 18, 18);
//      }
    }
    else if (pointa.x() < pointb.x() && pointa.y() > pointb.y())
    {
      if (getAngle() != 0)
      {
        qreal drawangle = getAlfa();
        QLineF localline(4+8, 4+getHeight()-8, 4+getWidth()-4, 4+4);

        if (drawangle < 0)
        {
          drawangle = -drawangle;
        }

        qreal R = localline.length()/(::sin(((drawangle/2)*PI)/180)*2);

        qreal delta = (180-drawangle)/2 + (360 - localline.angle());

        QPointF center_a(localline.p2().x() - ::cos((180-delta-drawangle)*PI/180)*R,
                         localline.p2().y() + ::sin((180-delta-drawangle)*PI/180)*R);

        QPointF center_b(localline.p1().x() + ::cos((180-delta-drawangle)*PI/180)*R,
                         localline.p1().y() - ::sin((180-delta-drawangle)*PI/180)*R);

        if (getAlfa() < 0)
        {
          painter->drawArc(center_b.x()-R,center_b.y()-R,2*R,2*R,
                           16*((180-delta-drawangle)+180),16*drawangle);
        }
        else
        {
          painter->drawArc(center_a.x()-R,center_a.y()-R,2*R,2*R
                           ,16*(180-delta-drawangle),16*drawangle);
        }
      }
      else
      {
        painter->drawLine(4+8, 4+getHeight()-8, 4+getWidth()-4, 4+4);
      }

      painter->setPen(Qt::NoPen);

      painter->drawPixmap(4, 4+getHeight()-16, 16, 16, QPixmap(icon));

//      if (!isInvalid() && !hasError)
//      {
        painter->setBrush(QBrush(QColor("#000000")));
//      }
//      else
//      {
//        painter->setBrush(QBrush(QColor(255,0,0,75)));
//        painter->drawEllipse(3, 3+getHeight()-16, 18, 18);
//      }
    }
    else if (pointa.x() > pointb.x() && pointa.y() > pointb.y())
    {
      if (getAngle() != 0)
      {
        qreal drawangle = getAlfa();

        QLineF localline(4+getWidth()-8, 4+getHeight()-8, 4+4, 4+4);

        if (drawangle < 0)
        {
          drawangle = -drawangle;
        }

        qreal R = localline.length()/(::sin(((drawangle/2)*PI)/180)*2);

        qreal delta = (180-drawangle)/2 + (360 - localline.angle());

        QPointF center_a(localline.p2().x() - ::cos((180-delta-drawangle)*PI/180)*R,
                         localline.p2().y() + ::sin((180-delta-drawangle)*PI/180)*R);

        QPointF center_b(localline.p1().x() + ::cos((180-delta-drawangle)*PI/180)*R,
                         localline.p1().y() - ::sin((180-delta-drawangle)*PI/180)*R);

        if (getAlfa() < 0)
        {
          painter->drawArc(center_b.x()-R,center_b.y()-R,2*R,2*R,
                           16*((180-delta-drawangle)+180),16*drawangle);
        }
        else
        {
          painter->drawArc(center_a.x()-R,center_a.y()-R,2*R,2*R
                           ,16*(180-delta-drawangle),16*drawangle);
        }
      }
      else
      {
        painter->drawLine(4+getWidth()-8, 4+getHeight()-8, 4+4, 4+4);
      }

      painter->setPen(Qt::NoPen);

      painter->drawPixmap(4+getWidth()-16, 4+getHeight()-16, 16, 16, QPixmap(icon));

//      if (!isInvalid() && !hasError)
//      {
        painter->setBrush(QBrush(QColor("#000000")));
//      }
//      else
//      {
//        painter->setBrush(QBrush(QColor(255,0,0,75)));
//        painter->drawEllipse(3+getWidth()-16, 3+getHeight()-16, 18, 18);
//      }
    }
  }
}

void StructuralBind::delineate(QPainterPath* painter) const
{
   if(isCondition())
    delineate_condition(painter);
   else
  delineate_action(painter);
}

void StructuralBind::delineate_action(QPainterPath* painter) const
{
  if (getTail() != NULL && getHead() != NULL)
  {
    QLineF line = QLineF(QPointF(getTail()->getLeft() + getTail()->getWidth()/2,
                                 getTail()->getTop() + getTail()->getHeight()/2),
                         QPointF(getHead()->getLeft() + getHead()->getWidth()/2,
                                 getHead()->getTop() + getHead()->getHeight()/2));

    if (getTail()->getStructuralCategory() == Structural::Interface)
    {
      line.setP1(getStructuralParent()->mapFromItem(getTail()->getStructuralParent(), line.p1()));
    }

    if (getHead()->getStructuralCategory() == Structural::Interface)
    {
      line.setP2(getStructuralParent()->mapFromItem(getHead()->getStructuralParent(), line.p2()));
    }

    QPointF pointa = line.p1();
    QPointF pointb = line.p2();

    if (pointa.x() <= pointb.x() && pointa.y() <= pointb.y())
    {
      painter->addEllipse(4+getWidth()-16, 4+getHeight()-16, 16, 16);
    }
    else if (pointa.x() > pointb.x() && pointa.y() < pointb.y())
    {
      painter->addEllipse(4, 4+getHeight()-16, 16, 16);
    }
    else if (pointa.x() < pointb.x() && pointa.y() > pointb.y())
    {
      painter->addEllipse(4+getWidth()-16,4,16,16);
    }
    else if (pointa.x() > pointb.x() && pointa.y() > pointb.y())
    {
      painter->addEllipse(4,4,16,16);
    }
  }
}

void StructuralBind::delineate_condition(QPainterPath* painter) const
{
  if (getTail() != NULL && getHead() != NULL)
  {
    QLineF line = QLineF(QPointF(getTail()->getLeft() + getTail()->getWidth()/2,
                                 getTail()->getTop() + getTail()->getHeight()/2),
                         QPointF(getHead()->getLeft() + getHead()->getWidth()/2,
                                 getHead()->getTop() + getHead()->getHeight()/2));

    if (getTail()->getStructuralCategory() == Structural::Interface)
    {
      line.setP1(getStructuralParent()->mapFromItem(getTail()->getStructuralParent(), line.p1()));
    }

    if (getHead()->getStructuralCategory() == Structural::Interface)
    {
      line.setP2(getStructuralParent()->mapFromItem(getHead()->getStructuralParent(), line.p2()));
    }

    QPointF pointa = line.p1();
    QPointF pointb = line.p2();

    if (pointa.x() <= pointb.x() && pointa.y() <= pointb.y())
    {
      //        painter->drawLine(4+4,4+4, 4+4+getWidth()-8-2, 4+4+getHeight()-8-2);

      painter->addEllipse(4,4,16,16);

    }
    else if (pointa.x() > pointb.x() && pointa.y() < pointb.y())
    {
      //        painter->drawLine(4+4+getWidth()-8,4+4, 4+4, 4+4+getHeight()-8);

      painter->addEllipse(4+getWidth()-16,4,16,16);


    }
    else if (pointa.x() < pointb.x() && pointa.y() > pointb.y())
    {
      //        painter->drawLine(4+4, 4+4+getHeight()-8, 4+4+getWidth()-8, 4+4);

      painter->addEllipse(4, 4+getHeight()-16, 16, 16);

    }
    else if (pointa.x() > pointb.x() && pointa.y() > pointb.y())
    {
      //        painter->drawLine(4+4+getWidth()-8, 4+4+getHeight()-8, 4+4, 4+4);

      painter->addEllipse(4+getWidth()-16, 4+getHeight()-16, 16, 16);
    }
  }
}

void StructuralBind::addParam(const QString &uid, const QString &name, const QString &value)
{
  if (name != "")
  {
    params[name] = value;
    names_uids[name] = uid;

    emit bindParamUpdated(getStructuralId(), params, names_uids);
  }
}

void StructuralBind::setParam(const QString &name, const QString &value)
{
  if (name != "")
  {
    params[name] = value;

    emit bindParamUpdated(getStructuralId(), params, names_uids);
  }
}

void StructuralBind::removeUId(const QString &uid)
{
  QString name = names_uids.key(uid);

  if (params.contains(name))
  {
    params.remove(name);
    names_uids.remove(name);

    emit bindParamUpdated(getStructuralId(), params, names_uids);
  }
}

void StructuralBind::removeParam(const QString &name)
{
  if(name != "")
  {
    params.remove(name);
    names_uids.remove(name);

    emit bindParamUpdated(getStructuralId(), params, names_uids);
  }
}

void StructuralBind::setParams(const QMap<QString, QString> &params)
{
  this->params = params;
}

void StructuralBind::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
  StructuralEdge::mouseDoubleClickEvent(event);

  setMoving(false);
  update();

  emit showEditBindDialog(this);
}

bool StructuralBind::isCondition() const
{
    return (_name == Structural::onBegin ||
            _name == Structural::onBeginAttribution ||
            _name == Structural::onEnd ||
            _name == Structural::onEndAttribution ||
            _name == Structural::onPause ||
            _name == Structural::onPauseAttribution ||
            _name == Structural::onResume ||
            _name == Structural::onResumeAttribution ||
            _name == Structural::onSelection);
}

bool StructuralBind::isAction() const
{
  return (!isCondition() && _name != Structural::NoRole);
}

QString StructuralBind::getRole() const
{
  return role;
}

void StructuralBind::setRole(const QString &role)
{
  this->role = role;
}

QString StructuralBind::getComponent() const
{
  return component;
}

void StructuralBind::setComponent(const QString &component)
{
  this->component = component;
}

QString StructuralBind::getComponentUid() const
{
  return componentUID;
}

void StructuralBind::setComponentUid(const QString &componentUID)
{
  this->componentUID = componentUID;
}

QString StructuralBind::getInterface() const
{
  return interface;
}

void StructuralBind::setInterface(const QString &interface)
{
  this->interface = interface;
}

QString StructuralBind::getInterfaceUid() const
{
  return interfaceUID;
}

void StructuralBind::setInterfaceUid(const QString &interfaceUID)
{
  this->interfaceUID = interfaceUID;
}

QMap<QString, QString> StructuralBind::getParams()
{
  return params;
}

QMap<QString, QString> StructuralBind::getNameUIDs()
{
  return names_uids;
}

void StructuralBind::setNamesUIDs(const QMap<QString, QString> &names_uids)
{
  this->names_uids = names_uids;
}

void StructuralBind::setLink(StructuralLink *link)
{
  this->link = link;
  setTail(link);
}

StructuralLink* StructuralBind::getLink()
{
  return this->link;
}

void StructuralBind::setTarget(StructuralEntity *target)
{
  setHead(target);
}

StructuralEntity *StructuralBind::getTarget()
{
  return getHead();
}

void StructuralBind::updateToolTip()
{
  StructuralEntity* comp = NULL;

  if (isCondition())
  {
    comp = getTail();
  }
  else
  {
    comp = getHead();
  }


  QString tip = getRole() + " (";

  if (comp->getStructuralCategory() == Structural::Interface)
  {
    StructuralEntity* parent = comp->getStructuralParent();
    tip += parent->getStructuralId() +  "#" + comp->getStructuralId();
  }
  else
  {
    tip += comp->getStructuralId();
  }

  tip += ")";

  setToolTip(tip);
}
