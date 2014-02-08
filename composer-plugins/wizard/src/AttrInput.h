#ifndef ATTRINPUT_H
#define ATTRINPUT_H

#include <QWidget>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>

class AttrInput : public QWidget
{

  Q_OBJECT

protected:
  QString _name;
  QString _type;
  QString _value;
  QString _question;


public:
  explicit AttrInput (QWidget *parent = 0) : QWidget (parent) {}

  explicit AttrInput(QString getQuestion, QString name, QString getType,
                     QString getValue, QWidget *parent = 0);

  inline QString getName () const { return _name; }
  inline QString getType () const { return _type; }
  inline QString getValue () const { return _value; }
  inline QString getQuestion () const { return _question; }

  virtual QString getAnswer () const = 0;
  virtual void setAnswer (QString) = 0;
  virtual AttrInput * clone () const = 0;
  //    virtual void computeAnswer () = 0;

  /* inline void paintEvent(QPaintEvent *)
  {
      QStyleOption opt;
      opt.init(this);
      QPainter p(this);
      style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
  } */
};

#endif // ATTRINPUT_H