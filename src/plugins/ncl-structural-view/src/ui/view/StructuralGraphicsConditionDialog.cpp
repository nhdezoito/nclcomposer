#include "StructuralGraphicsConditionDialog.h"

StructuralGraphicsConditionDialog::StructuralGraphicsConditionDialog(QWidget* parent)
  : QDialog(parent)
{
  form.setupUi(this);
}

StructuralGraphicsConditionDialog::~StructuralGraphicsConditionDialog()
{

}

void StructuralGraphicsConditionDialog::init(QMap<QString, StructuralConnector*> connectors,
                                       StructuralGraphicsLink* link)
{
  this->connectors = connectors;
  this->link = link;

  form.cbConnector->clear();
  form.cbConnector->setEnabled(false);

  if (link != NULL)
    form.cbConnector->addItem(link->getxConnector());
  else
    form.cbConnector->addItem("New...");

  form.cbLink->clear();
  form.cbLink->setEnabled(false);

  if (link != NULL)
    form.cbLink->addItem(link->getnstId());
  else
    form.cbLink->addItem("New...");

  form.cbCondition->setEnabled(true);
  form.cbCondition->clear();

  StructuralConnector* conn;
  if (link != NULL && connectors.contains(link->getxConnector()))
    conn = connectors[link->getxConnector()];
  else
    conn = NULL;

  if (conn != NULL)
  {
    if (conn->getName() == form.cbConnector->currentText())
    {
      foreach(QString name, conn->getConditions().values())
      {
        form.cbCondition->addItem(name);
      }
    }
  }
  else
  {
    form.cbCondition->addItem("onBegin");
    form.cbCondition->addItem("onEnd");
    form.cbCondition->addItem("onSelection");
    form.cbCondition->addItem("onResume");
    form.cbCondition->addItem("onPause");
  }
}