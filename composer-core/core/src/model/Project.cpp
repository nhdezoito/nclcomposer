#include "model/Project.h"

namespace composer {
    namespace core {
        namespace model {

Project::Project(QObject *parent) :
    Entity(parent)
{
    setType("document");
    entities[this->getUniqueId()] = this;
}

Project::Project(QMap<QString,QString> &atts, QObject *parent) :
    Entity(atts, parent)
{
    setType("document");
    entities[this->getUniqueId()] = this;
}

Project::~Project() {
    QMutexLocker locker(&lockEntities);
    entities.clear();
}

LanguageType Project::getProjectType()
{
    return this->projectType;
}

void Project::setProjectType(LanguageType type)
{
    this->projectType = type;
}

Entity* Project::getEntityBydId(QString _id) {
    QMutexLocker locker(&lockEntities);
    return entities.contains(_id) ? entities[_id] : NULL;
}

QList<Entity*> Project::getEntitiesbyType(QString _type) {
    QMutexLocker locker(&lockEntities);
    QMapIterator<QString, Entity*> it(entities);
    QList<Entity*> listRet;
    while(it.hasNext()){
        it.next();
        Entity* ent = it.value();
        if (ent->getType() == _type)
            listRet.append(ent);
    }
    return listRet;
}

QString Project::getLocation() {
    QMutexLocker locker(&lockLocation);
    return this->projectLocation;
}

void Project::setLocation(QString location) {
    QMutexLocker locker(&lockLocation);
    this->projectLocation = location;
}

void Project::setProjectId(QString _projectId)
{
    this->projectId = _projectId;
}

QString Project::getProjectId()
{
    return this->projectId;
}

bool Project::addEntity(Entity* entity, QString parentId)
    throw (EntityNotFound,ParentNotFound)
{
    QMutexLocker locker(&lockEntities);
    if (!entities.contains(parentId)) {
        throw ParentNotFound(entity->getType(),entity->getType(),
                                 parentId);
        return false;
    }
    if (entities.contains(entity->getUniqueId())) {
        throw EntityNotFound(entity->getType(),entity->getUniqueId());
        return false;
    }

    Entity *parent = entities[parentId];
    parent->addChild(entity);
    entities[entity->getUniqueId()] = entity;
}

bool Project::removeEntity(Entity* entity, bool appendChild)
     throw (EntityNotFound)
{
    QMutexLocker locker(&lockEntities);
    QString _id = entity->getUniqueId();

    if (entities.contains(entity->getUniqueId())) {
        Entity *parent = entity->getParent();
        if (parent) {
            if (appendChild)
                    parent->removeChildAppendChildren(entity);
            else parent->deleteChild(entity);
        } else { //does not have a parent, so dont append
            delete entity;
            entity = NULL;
            return true;
        }
    } else {
        throw EntityNotFound(entity->getType(),entity->getUniqueId());
        return false; // entity does not exist in the model
    }

    entities.remove(_id);
    return true;
}

/** \todo Save project to the hard disk. */
QString Project::toString()
{
   QMutexLocker locker(&lockEntities);
   QString result = "";
   result += "<project name=\"" + this->projectId + "\">\n";
   result += Entity::toString(0);

   QString key;
   foreach(key, pluginData.keys())
   {
       result += "<pluginData pluginID=\"" + key + "\">";
       result += pluginData[key];
       result += "</pluginData>\n";
   }
   result += "\n</project>";
   return result;
}

bool Project::setPluginData(QString pluginId, const QByteArray data)
{
    this->pluginData[pluginId] = data;
    return true;
}

QByteArray Project::getPluginData(QString pluginId)
{
    if(pluginData.contains(pluginId))
    {
        return this->pluginData[pluginId];
    }
    return QByteArray();
}

} } } //end namespace