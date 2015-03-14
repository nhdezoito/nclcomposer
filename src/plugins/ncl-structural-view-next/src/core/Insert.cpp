#include "Insert.h"

Insert::Insert(QString uid, QString parent, QMap<QString, QString> properties, QMap<QString, QString> settings)
{
  this->_uid = uid;
  this->_parent = parent;
  this->_properties = properties;

  this->_settings = settings;
}

Insert::~Insert()
{

}

void Insert::undo()
{
  _settings["UNDO"] = "0";
  _settings["NOTIFY"] = "1";

  emit remove(_uid, _settings);
}

void Insert::redo()
{
  _settings["UNDO"] = "0";

  emit insert(_uid, _parent, _properties, _settings);
}