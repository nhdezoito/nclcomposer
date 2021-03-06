/*
 * Copyright 2011-2013 TeleMidia/PUC-Rio.
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
#ifndef MEDIAPREVIEWFACTORY_H
#define MEDIAPREVIEWFACTORY_H

#include "MediaPreviewPlugin.h"
#include <extensions/IPluginFactory.h>
using namespace cpr::core;

/*!
 * \brief Handles the creation and deletion of MediaPreview objects.
 */
class MediaPreviewFactory : public QObject, public IPluginFactory
{
  Q_OBJECT
  Q_INTERFACES(IPluginFactory)

public:
  /*!
   * \brief Constructor.
   */
  explicit MediaPreviewFactory();
  /*!
   * \brief Destructor.
   */
  ~MediaPreviewFactory();
  /*!
   * \brief Creates an MediaPreviewPlugin instance.
   * \return IPlugin* One NEW instance of MediaPreviewPlugin.
   */
  virtual IPlugin* createPluginInstance()
  {
    return new MediaPreviewPlugin();
  }

  /*!
   * \brief Destroy an instance of MediaPreviewPlugin.
   * \param IPlugin* the instance that must be destroyed.
   */
  virtual void releasePluginInstance(IPlugin *mediaPlug)
  {
    delete mediaPlug;
  }

  /*!
   * \brief
   * \return QString
   */
  virtual QString id() const { return "br.puc-rio.telemidia.MediaPreview"; }

#if QT_VERSION < 0x050000
  /*!
   * \brief
   * \return QString
   */
  virtual QString name() { return "Media Preview"; }
  /*!
   * \brief Returns the version of Media Preview implementation.
   * \return QString the version number as string.
   */
  QString version() { return NCLCOMPOSER_PLUGINS_VERSION; }
  /*!
   * \brief Returns the core version that is compatible with this plugin.
   *
   * \return QString the core version that is compatible with this plugin
   *    as a string.
   */
  QString compatVersion() {return "0.1";}
  /*!
   * \brief Returns the vendor of Media Preview (i.e. Telemidia Lab).
   *
   * \return QString the name of the vendor of MediaPreview.
   */
  QString vendor() {return "Telemidia Lab";}
  /*!
   * \brief Returns the copyright of Media Preview.
   *
   * \return QString the copyright of Media Preview.
   */
  QString copyright() {return "Telemidia/PUC-Rio";}
  /*!
   * \brief Returns the license of Media Preview plugin (i.e. GPLv3).
   *
   * \todo The complete license description.
   *
   * \return QString the license of Property View.
   */
  QString license() {return "LGPL";}

  /*!
   * \brief Returns a description of the Property View
   *
   * \return QString the description of Property View.
   */
  QString description() {return tr("Media Pre-view displays a media player "
                                   "of a current selected entity and "
                                   "enables the user have to a pre-view "
                                   "of the media object selected.");}

  /*!
   * \brief url
   * \return
   */
  QString url() {return "http://composer.telemidia.puc-rio.br/debug";}

  /*!
   * \brief category
   * \return
   */
  QString category() {return "NCL";}
#endif

};

#endif // MEDIAPREVIEWFACTORY_H
