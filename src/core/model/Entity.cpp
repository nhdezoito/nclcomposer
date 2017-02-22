/* Copyright (C) 2011-2017 PUC-Rio/TeleMídia Lab.

 NCL Composer is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published
 by the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 NCL Composer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU General Lesser Public License
 along with NCL Composer.  If not, see <http://www.gnu.org/licenses/>. */

#include "model/Entity.h"

#include <assert.h>

namespace composer {
    namespace core {
        namespace model {

Entity::Entity(QObject *parent) :
  QObject(parent)
{
  setUniqueID(QUuid::createUuid().toString());
  //    QMutexLocker locker(&lockParent);
  this->parent = (Entity*)parent;
  this->deleteChildren = true;
}

Entity::Entity(const QMap<QString,QString> &atts, QObject *parent) :
    QObject(parent)
{
  // QMutexLocker locker(&lockAtts);
  this->atts = atts;
  setUniqueID(QUuid::createUuid().toString());
  QMutexLocker lo(&lockParent);
  this->parent = (Entity*)parent;
  this->deleteChildren = true;
}

Entity::Entity( const QString &uniqueId,
                const QString &type,
                const QMap<QString, QString> &atts,
                QObject *parent ) :
  QObject(parent)
{
  //  QMutexLocker locker(&lockAtts);
  this->atts = atts;
  this->_id = uniqueId;
  QMutexLocker lo(&lockParent);
  this->parent = (Entity*)parent;
  this->deleteChildren = true;
  this->setType(type);
}

Entity::~Entity() {
  //  QMutexLocker locker(&lockChildren);
  if (deleteChildren)
  {
    while(children.size())
    {
      Entity *child = children.at(0);
      delete child;
      child = nullptr;
      children.pop_front();
    }
  }
}

void Entity::setAttribute(const QString &name,
                          const QString &value)
{
//    QMutexLocker locker(&lockAtts);
  atts[name] = value;
}

void Entity::setAtrributes(const QMap<QString,QString> &newatts)
{
//    QMutexLocker locker(&lockAtts);
  this->atts.clear(); // Should it??!
  for ( QMap<QString,QString>::const_iterator it = newatts.begin();
        it != newatts.end(); ++it)
  {
    this->atts[it.key()] = it.value();
  }
}

void Entity::setType(const QString &type)
{
//    QMutexLocker locker(&lockType);
  this->type = type;
}

void Entity::setUniqueID(const QString &uniqueId)
{
//    QMutexLocker locker(&lockID);
  this->_id = uniqueId;
}

void Entity::setParent(Entity *parent)
{
  this->parent = parent;
}

bool Entity::addChild(Entity *entity, int pos)
{
  assert(entity != nullptr);
  QMutexLocker locker(&lockChildren);
  QString _id = entity->getUniqueId();

  // Check if the entity is already children of this entity
  // TODO: THIS CAN BE IMPROVED!! Maybe checking if the parentUniqueID.
  for(int i = 0; i < children.size(); i++)
  {
    if(children.at(i)->getUniqueId() == _id )
      return false;
  }

  children.insert(pos >= 0 ? pos: children.size(), entity);
  entity->setParent(this);
  return true;
}

//! Deletes the child and its children in a recursive way
bool Entity::deleteChild(Entity *entity)
{
  assert(entity != nullptr);
//    QMutexLocker locker(&lockChildren);
  entity->setDeleteChildren(true);
  for(int i = 0; i < children.size(); i++)
  {
    if(children.at(i) == entity)
    {
      children.remove(i);
    }
  }

  delete entity;
  // entity = nullptr;

  return true;
}

QString Entity::getAttribute(const QString &name)
{
  QMutexLocker locker(&lockAtts);
  return atts.contains(name) ? atts[name] : "";
}

void Entity::getAttributeIterator (QMap<QString,QString>::iterator &begin,
                                   QMap<QString,QString>::iterator &end)
{
//    QMutexLocker locker(&lockAtts);
  begin = this->atts.begin();
  end = this->atts.end();
}

bool Entity::hasAttribute(const QString &name)
{
//    QMutexLocker locker(&lockAtts);
  return this->atts.contains(name);
}

QString Entity::getUniqueId() const
{
  return this->_id;
}

QString Entity::getType() const
{
//    QMutexLocker locker(&lockType);
  return this->type;
}

Entity* Entity::getParent() const
{
//    QMutexLocker locker(&lockParent);
  return parent;
}

QString Entity::getParentUniqueId() const
{
//    QMutexLocker loecker(&lockParent);
  return parent->getUniqueId();
}

void Entity::setDeleteChildren(bool _delete)
{
  this->deleteChildren = _delete;
}

QVector <Entity *> Entity::getChildren() const
{
  return this->children;
}

//! Removes the child and append his children to his parent
// Is it useful ??
bool Entity::removeChildAppendChildren(Entity *entity)
{
  assert(entity != nullptr);

  for(int i= 0; i < children.size(); i++)
  {
    Entity *child = children.at(i);
    child->setParent(this);
  }

  entity->setDeleteChildren(false);
  // delete entity;
  // entity = nullptr;

  return true;
}

//! Prints the Entity and its children
void Entity::print()
{
  for (int i = 0; i < children.size(); i++)
  {
    Entity *child = children.at(i);
    child->print();
  }
}

QString Entity::toString(int ntab, bool writeuid)
{
  QString out = "";
  for(int i = 0; i < ntab; i++)
    out += "\t";

  out += "<";
  out.append(getType().toLatin1());
  for(const QString &attr: atts.keys())
  {
    out += " ";
    out.append(attr);
    out += "=\"";
    out += atts.value(attr);
    out += "\"";
  }
  if(writeuid)
  {
    out += " uniqueEntityId=\"";
    out += getUniqueId();
    out += "\"";
  }
  out += ">\n";

  for (int i = 0; i < children.size(); i++)
  {
    Entity *child = children.at(i);
    out += child->toString(ntab+1, writeuid);
  }
  for(int i = 0; i < ntab; i++)
    out += "\t";
  out += "</";
  out += getType();
  out += ">\n";
  return out;
}

Entity *Entity::cloneEntity() const
{
  // QMap <QString, QString>::iterator begin, end, it;
  // QMap <QString, QString> attrs;
  //getAttributeIterator(begin, end);
  //for (it = begin; it != end; ++it)
  //    attrs[it.key()] = it.value();

  return new Entity(getUniqueId(), getType(), this->atts);
}

}}} //end namespace