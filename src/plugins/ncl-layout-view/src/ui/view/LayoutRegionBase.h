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
#ifndef QNLYGRAPHICSREGIONBASE_H
#define QNLYGRAPHICSREGIONBASE_H

#include <QMenu>
#include <QAction>
#include <QGraphicsScene>
#include <QDebug>
#include <QActionGroup>
#include <QGraphicsSceneContextMenuEvent>
#include <QObject>
#include <QMap>
#include <QGraphicsSceneMouseEvent>
#include <QFileDialog>

#include "LayoutRegion.h"
#include "LayoutGrid.h"

class LayoutRegion;

class LayoutRegionBase : public QGraphicsScene
{
  Q_OBJECT

public:
  explicit LayoutRegionBase(QObject* parent, QMenu* switchMenu);
  virtual ~LayoutRegionBase();

  QString getId() const;
  void setId(const QString &id);

  QString getUid() const;
  void setUid(const QString &uid);

  QString getRegion() const;
  void setRegion(const QString &region);

  QString getDevice() const;
  void setDevice(const QString &device);

  void addRegion(LayoutRegion* region,
                 LayoutRegion* parent,
                 const QMap<QString, QString> attributes);
  void changeRegion(LayoutRegion* region,
                    const QMap<QString, QString> attributes);
  void selectRegion(LayoutRegion* region);
  void hideRegion(LayoutRegion* region);
  void updateActionText(LayoutRegion *region);
  void removeRegion(LayoutRegion* region);

  QGraphicsItem* getBackgroundItem();

  void changeResolution(int w, int h);


  bool isGridVisible();
  void setGridVisible(bool active);
  void updateSafeAreaPos();
  bool isSafeAreaVisible();
  void setSafeAreaVisible(bool active);

public slots:
  void performRegion();
  void performDelete();
  void performExport();

signals:
  void regionAdditionRequested(const QString regionUID,
                               const QString parentUID,
                               const QString regionbaseUID,
                               QMap<QString, QString> attributes);

  void regionChangeRequested(const QString regionUID,
                             const QString regionbaseUID,
                             QMap<QString, QString> attributes);

  void regionSelectionRequested( const QString regionUID,
                                 const QString regionbaseUID);

  void regionDeletionRequested( const QString regionUID,
                                const QString regionbaseUID);

  void regionBaseDeletionRequested(const QString regionbaseUID);

  void regionBaseSelectionRequested(const QString regionbaseUID);

  void mediaOverRegion(const QString &mediaId, const QString &regionUID);

  void regionbasePerformed();

  void copyRequested(LayoutRegion *);
  void pasteRequested();

  void gridVisibilityChanged(bool visible);
  void safeAreaVisibilityChanged(bool visible);

protected:
  virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
  void mousePressEvent(QGraphicsSceneMouseEvent* event);
  void keyPressEvent( QKeyEvent * event );

  /*!
   * \brief createGrid creates the grid element that can be hide/unhide in the
   *  scene.
   */
  void createGrid();
  /*!
   * \brief createSafeArea creates the QGraphicsRectItem responsible to drawn
   *  safeArea information.
   *
   *  For more information about safe are you can look at: SMPTE ST 2046-1
   */
  void createSafeArea();
  /*!
   * \brief getSafeAreaRect returns a rect related that represents the safe area
   *  of a rectangle with size w x h.
   * \param w
   * \param h
   * \param w_perc
   * \param h_perc
   * \return
   */
  QRect getSafeAreaRect(int w, int h, double w_perc, double h_perc);

protected slots:
  void performShow(QAction* action);

  void requestAdditionRegion(LayoutRegion* parent);
  void requestRegionSelection(LayoutRegion* region);
  void requestRegionDeletion(LayoutRegion* region);
  void requestRegionChange(LayoutRegion* region,
                           QMap<QString, QString> attributes);
  void requestMediaOverRegionAction(QString mediaId,
                                    LayoutRegion* region);
  void performChangeResolution();
  void performGrid();
  void performSafeArea();

private:
  void createActions();
  void createMenus();
  void createConnections();

  QMenu* viewMenu;
  QMenu* showMenu;
  QMenu* arrangeMenu;
  QMenu* screensizeMenu;
  QMenu* switchMenu;
  QMenu* contextMenu;

  QAction* helpAction;
  QAction* undoAction;
  QAction* redoAction;
  QAction* cutAction;
  QAction* copyAction;
  QAction* pasteAction;
  QAction* deleteAction;
  QAction* zoominAction;
  QAction* zoomoutAction;
  QAction* zoomresetAction;
  QAction* hideAction;
  QAction* fullscreenAction;
  QAction* exportAction;
  QAction* regionAction;
  QAction* regionbaseAction;
  QAction* bringfrontAction;
  QAction* bringforwardAction;
  QAction* sendbackwardAction;
  QAction* sendbackAction;
  QAction* propertiesAction;
  QAction* gridAction;
  QAction* _safeAreaAction;
  QAction* action;

  /*! \todo This could be an array (and the user could also add its own size) */
  QAction* re640x480;
  QAction* re800x600;
  QAction* re1024x768;
  QAction* re854x480;
  QAction* re1280x720;
  QAction* re1920x1080;
  QAction* re320x400;

  QActionGroup* screensizeGroup;
  QActionGroup* regionActionGroup;

  QGraphicsTextItem *graphicsRegionBaseId;

  QString id;
  QString uid;
  QString region;
  QString device;

  QGraphicsRectItem* bgrect;
  QGraphicsRectItem* _safeActionAreaRect;
  QGraphicsTextItem* _safeActionAreaText;
  QGraphicsRectItem* _safeTitleAreaRect;
  QGraphicsTextItem* _safeTitleAreaText;

  LayoutGrid* _grid;

  LayoutRegion* selectedRegion;

  QMap<QString, QAction*> regionActions;
  QMap<QString, LayoutRegion*> regions;
};

#endif // QNLYGRAPHICSREGIONBASE_H
