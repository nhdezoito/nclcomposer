/*
 * Copyright 2011 TeleMidia/PUC-Rio.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either 
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>. 
 */
#include "PropertiesViewPlugin.h"
#include "core/modules/LanguageControl.h"

namespace composer {
    namespace plugin {
        namespace property {

PropertiesViewPlugin::PropertiesViewPlugin()
{
    window = new PropertyEditor(0);
    project = NULL;
    currentEntity = NULL;

    connect(window, SIGNAL(propertyChanged(QString, QString)),
            this, SLOT(updateCurrentEntityAttr(QString, QString)));
}

PropertiesViewPlugin::~PropertiesViewPlugin()
{
    //delete window;
}

QWidget* PropertiesViewPlugin::getWidget()
{
    return window;
}

void PropertiesViewPlugin::onEntityAdded(QString pluginID, Entity *entity)
{
    QString line = "<" + entity->getType() + "> </" + entity->getType() + ">\n";
}

void PropertiesViewPlugin::errorMessage(QString error)
{
    qDebug() << "PropertiesViewPlugin::onEntityAddError(" << error << ")";
}

void PropertiesViewPlugin::onEntityChanged(QString pluginID, Entity * entity)
{
    QString line = "PLUGIN (" + pluginID + ") changed the Entity (" +
                   entity->getType() + " - " + entity->getUniqueId() +")";
}

void PropertiesViewPlugin::onEntityRemoved(QString pluginID, QString entityID)
{
    QString line = "PLUGIN (" + pluginID + ") removed Entity (" +
                   entityID + ")";
}

bool PropertiesViewPlugin::saveSubsession()
{
    //TODO: All
    return true;
}

void PropertiesViewPlugin::init()
{
    //TODO: All
}

void PropertiesViewPlugin::changeSelectedEntity(QString pluginID, void *param)
{
    QString *id = (QString*) param;
    if(id != NULL && *id != "") {
        currentEntity = project->getEntityById(*id);
    }

    if(currentEntity != NULL)
    {
        QString name;
        if( currentEntity->hasAttribute("id") )
            name = currentEntity->getAttribute("id");
        else if(currentEntity->hasAttribute("name"))
            name = currentEntity->getAttribute("name");
        else
            name = "Unknown";

        window->setTagname(currentEntity->getType(), name);

        QMap <QString, QString>::iterator begin, end, it;
        currentEntity->getAttributeIterator(begin, end);
        for (it = begin; it != end; ++it)
        {
            window->setAttributeValue(it.key(), it.value());
        }
    }
}

void PropertiesViewPlugin::updateCurrentEntityAttr(QString attr, QString value)
{
    if (currentEntity != NULL)
    {
        if(currentEntity->hasAttribute("attr") &&
           currentEntity->getAttribute("attr") == value)
        {
            //do nothing
            return;
        }
        else
        {
            QMap <QString, QString> attrs;
            QMap <QString, QString>::iterator begin, end, it;
            currentEntity->getAttributeIterator(begin, end);
            for (it = begin; it != end; ++it)
            {
                if(it.key() == attr)
                    attrs.insert(attr, value);
                else
                    attrs.insert(it.key(), it.value());
            }

            if(!attrs.contains(attr))
                attrs.insert(attr, value);

            emit setAttributes(currentEntity, attrs, false);
        }
    }
}

} } } //end namespace
