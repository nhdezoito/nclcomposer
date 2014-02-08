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
#include "View.h"

View::View(QWidget* parent) :
    QStackedWidget(parent),
    gridVisibility(false)
{
  setWindowTitle("Qnly");

  createActions();
  createMenus();
  createConnections();

  nregions = 0;
  nregionbases = 0;

  selectedRegion = NULL;
  selectedRegionBase = NULL;
}

View::~View()
{

}

void View::createActions()
{
  // help action
  helpAction = new QAction(this);
  helpAction->setText(tr("Help"));

  helpAction->setEnabled(false);
  helpAction->setShortcut(QKeySequence("F1"));

  // undo action
  // undoAction = new QAction(this);
  // undoAction->setText(tr("Undo"));

  // undoAction->setEnabled(false);
  // undoAction->setShortcut(QKeySequence("Ctrl+Z"));

  // redo action
  redoAction = new QAction(this);
  redoAction->setText(tr("Redo"));

  redoAction->setEnabled(false);
  redoAction->setShortcut(QKeySequence("Ctrl+Shift+Z"));

  // cut action
  cutAction = new QAction(this);
  cutAction->setText(tr("Cut"));

  cutAction->setEnabled(false);
  cutAction->setShortcut(QKeySequence("Ctrl+X"));

  // copy action
  copyAction = new QAction(this);
  copyAction->setText(tr("Copy"));

  copyAction->setEnabled(false);
  copyAction->setShortcut(QKeySequence("Ctrl+C"));

  // paste action
  pasteAction = new QAction(this);
  pasteAction->setText(tr("Paste"));

  pasteAction->setEnabled(true);
  pasteAction->setShortcut(QKeySequence("Ctrl+V"));

  // delete action
  deleteAction = new QAction(this);
  deleteAction->setText(tr("Delete"));

  deleteAction->setEnabled(false);
  deleteAction->setShortcut(QKeySequence("Del"));

  // zoomin action
  zoominAction = new QAction(this);
  zoominAction->setText(tr("Zoom In"));

  zoominAction->setEnabled(false);
  zoominAction->setShortcut(QKeySequence("Ctrl++"));

  // zoomout action
  zoomoutAction = new QAction(this);
  zoomoutAction->setText(tr("Zoom Out"));

  zoomoutAction->setEnabled(false);
  zoomoutAction->setShortcut(QKeySequence("Ctrl+-"));

  // reset action
  zoomresetAction = new QAction(this);
  zoomresetAction->setText(tr("Reset"));

  zoomresetAction->setEnabled(false);
  zoomresetAction->setShortcut(QKeySequence("Ctrl+0"));

  // fullscreen action
  fullscreenAction = new QAction(this);
  fullscreenAction->setText(tr("Full Screen"));

  fullscreenAction->setEnabled(true);
  fullscreenAction->setShortcut(QKeySequence("F11"));

  // export action
  exportAction = new QAction(this);
  exportAction->setText(tr("Export..."));

  exportAction->setEnabled(false);

  // region action
  regionAction = new QAction(this);
  regionAction->setText(tr("Region"));

  regionAction->setEnabled(false);

  // regionbase action
  regionbaseAction = new QAction(this);
  regionbaseAction->setText(tr("Region Base"));

  regionbaseAction->setEnabled(true);

  // bring to front action
  bringfrontAction = new QAction(this);
  bringfrontAction->setText(tr("Bring to Front"));

  bringfrontAction->setEnabled(false);
  bringfrontAction->setShortcut(QKeySequence("Shift+Ctrl+]"));

  // bring forward action
  bringforwardAction = new QAction(this);
  bringforwardAction->setText(tr("Bring Forward"));

  bringforwardAction->setEnabled(false);
  bringforwardAction->setShortcut(QKeySequence("Ctrl+]"));

  // send backward action
  sendbackwardAction = new QAction(this);
  sendbackwardAction->setText(tr("Send Backward"));

  sendbackwardAction->setEnabled(false);
  sendbackwardAction->setShortcut(QKeySequence("Ctrl+["));

  // send to back action
  sendbackAction = new QAction(this);
  sendbackAction->setText(tr("Send to Back"));

  sendbackAction->setEnabled(false);
  sendbackAction->setShortcut(QKeySequence("Shift+Ctrl+["));

  // hide action
  hideAction = new QAction(this);
  hideAction->setText(tr("Hide"));

  hideAction->setEnabled(false);

  // properties action
  propertiesAction = new QAction(this);
  propertiesAction->setText(tr("Properties"));

  propertiesAction->setEnabled(false);

  regionbaseActionGroup = new QActionGroup(this);
  regionbaseActionGroup->setExclusive(true);

  setMouseTracking(true);
}

void View::createMenus()
{
  // view menu
  viewMenu = new QMenu();
  viewMenu->setTitle(tr("View"));

  viewMenu->setEnabled(false);

  viewMenu->addAction(zoominAction);
  viewMenu->addAction(zoomoutAction);
  viewMenu->addAction(zoomresetAction);
  viewMenu->addSeparator();
  viewMenu->addAction(fullscreenAction);

  // insert menu
  insertMenu = new QMenu();
  insertMenu->setTitle(tr("Insert"));

  insertMenu->setEnabled(true);

  insertMenu->addAction(regionAction);
  insertMenu->addAction(regionbaseAction);

  showMenu = new QMenu();
  showMenu->setTitle(tr("Show"));

  showMenu->setEnabled(false);

  // arrange menu
  arrangeMenu = new QMenu();
  arrangeMenu->setTitle(tr("Arrange"));

  arrangeMenu->setEnabled(false);

  arrangeMenu->addAction(bringfrontAction);
  arrangeMenu->addAction(bringforwardAction);
  arrangeMenu->addAction(sendbackwardAction);
  arrangeMenu->addAction(sendbackAction);

  // switch menu
  switchMenu = new QMenu();
  switchMenu->setTitle(tr("Switch"));

  switchMenu->setEnabled(false);

  // context menu
  contextMenu = new QMenu();
  contextMenu->addAction(helpAction);
  //    contextMenu->addSeparator();
  //    contextMenu->addAction(undoAction);
  //    contextMenu->addAction(redoAction);
  //    contextMenu->addSeparator();
  //    contextMenu->addAction(cutAction);
  //    contextMenu->addAction(copyAction);
  contextMenu->addAction(pasteAction);
  contextMenu->addSeparator();
  contextMenu->addAction(deleteAction);
  contextMenu->addSeparator();
  contextMenu->addAction(exportAction);
  contextMenu->addSeparator();
  contextMenu->addMenu(viewMenu);
  contextMenu->addMenu(insertMenu);
  contextMenu->addMenu(showMenu);
  contextMenu->addMenu(arrangeMenu);
  contextMenu->addSeparator();
  contextMenu->addAction(hideAction);
  contextMenu->addSeparator();
  contextMenu->addMenu(switchMenu);
  contextMenu->addSeparator();
  contextMenu->addAction(propertiesAction);
}

void View::createConnections()
{
  connect(regionbaseActionGroup, SIGNAL(triggered(QAction*)),
          SLOT(performSwitch(QAction*)));

  connect(regionbaseAction, SIGNAL(triggered()),SLOT(performRegionBase()));

  connect(pasteAction, SIGNAL(triggered()), SLOT(performPaste()));
}

void View::requestRegionAddition(const QString regionUID,
                                     const QString parentUID,
                                     const QString regionbaseUID,
                                     QMap<QString, QString> attributes)
{
  // attributes["id"] = "rg" + QString::number(nregions+1);
  // attributes["id"] =

  emit regionAdded(regionUID, parentUID, regionbaseUID, attributes);
}

void View::requestRegionChange(const QString regionUID,
                                   const QString regionbaseUID,
                                   QMap<QString, QString> attributes)
{

  emit regionChanged(regionUID,
                     regionbaseUID,
                     attributes);
}

void View::performSwitch(QAction* action)
{
  emit regionBaseSelected(regionbaseActions.key(action));
}

void View::performRegionBase()
{
  QMap<QString, QString> attributes;

  attributes["id"] = "rgbase" + QString::number(++nregionbases);

  emit regionBaseAdded(QUuid::createUuid().toString(), attributes);
}

void View::addRegion(const QString regionUID,
                         const QString parentUID,
                         const QString regionbaseUID,
                         const QMap<QString, QString> attributes)
{
  if (!regions.contains(regionUID) &&
      regionbases.contains(regionbaseUID))
  {
    Region* region = new Region(switchMenu);

    if (regionUID.isEmpty())
      region->setUid(QUuid::createUuid().toString());
    else
      region->setUid(regionUID);

    Region* parent = NULL;

    if (regions.contains(parentUID))
      parent = regions[parentUID];

    RegionBase* regionbase = regionbases[regionbaseUID];

    nregions++;

    addRegion(region, parent, regionbase, attributes);
  }
}

void View::performCopy(Region *region)
{  
  // setting
  QMap<QString, QString> attr = region->getAttributes();

  copiedRegionAttrs.clear();
  foreach(QString key, attr.keys())
  {
    if(key != "id")
      copiedRegionAttrs[key] = attr[key];
  }
}

void View::performPaste()
{ 
  QString selectedRegionUId = "";
  if(selectedRegion != NULL)
    selectedRegionUId = selectedRegion->getUid();

  qDebug() << "Perform paste inside: " << selectedRegionUId;

  QString selectedRegionBaseUId = "";
  if(selectedRegionBase != NULL)
    selectedRegionBaseUId = selectedRegionBase->getUid();

  requestRegionAddition("",
                        selectedRegionUId,
                        selectedRegionBaseUId,
                        copiedRegionAttrs);
}

void View::removeRegion(const QString regionUID,
                            const QString regionbaseUID)
{
  if (regions.contains(regionUID) && regionbases.contains(regionbaseUID))
  {
    removeRegion(regions[regionUID],
                 regionbases[regionbaseUID]);
  }
}

void View::changeRegion(const QString regionUID,
                            const QString regionbaseUID,
                            const QMap<QString, QString> attributes)
{
  if (regions.contains(regionUID) && regionbases.contains(regionbaseUID))
  {
    changeRegion(regions[regionUID],
                 regionbases[regionbaseUID],
                 attributes);
  }
}

void View::selectRegion(const QString regionUID,
                            const QString regionbaseUID)
{
  if (regions.contains(regionUID) && regionbases.contains(regionbaseUID))
  {
    selectRegion(regions[regionUID],
                 regionbases[regionbaseUID]);
  }
}

void View::addRegionBase(const QString regionbaseUID,
                             const QMap<QString, QString> attributes)
{
  if (!regionbases.contains(regionbaseUID))
  {
    Canvas* canvas = new Canvas(this);

    RegionBase* regionbase =
        new RegionBase(canvas, switchMenu);

    regionbase->setParent(canvas);

    canvas->setScene(regionbase);

    if (regionbaseUID.isEmpty())
    {
      regionbase->setUid(QUuid::createUuid().toString());
    }
    else{
      regionbase->setUid(regionbaseUID);
    }

    addRegionBase(regionbase, attributes);
  }
}

void View::removeRegionBase(const QString regionbaseUID)
{
  if (regionbases.contains(regionbaseUID))
  {
    removeRegionBase(regionbases[regionbaseUID]);
  }
}

void View::changeRegionBase(const QString regionbaseUID,
                                const QMap<QString, QString> attributes)
{
  if (regionbases.contains(regionbaseUID))
  {
    changeRegionBase(regionbases[regionbaseUID], attributes);
  }
}

void View::selectRegionBase(const QString regionbaseUID)
{
  if (regionbases.contains(regionbaseUID))
  {
    selectRegionBase(regionbases[regionbaseUID]);
  }
  else
    qWarning() << tr("It is not possible to select regionBase ")
               << regionbaseUID;
}

void View::addRegion(Region* region,
                         Region* parent,
                         RegionBase* regionBase,
                         const QMap<QString, QString> attributes)
{
  if (region != NULL && regionBase != NULL)
  {
    qDebug() << "Adding Region" << attributes;

    regions[region->getUid()] = region;

    regionBase->addRegion(region,
                          parent,
                          attributes);
  }
}

void View::removeRegion(Region* region,
                            RegionBase* regionBase)
{
  if (region != NULL && regionBase != NULL)
  {
    qDebug() << "Region Removed!";

    foreach(QGraphicsItem* item, region->childItems())
    {
      Region* child = dynamic_cast<Region*> (item);

      if(item != NULL)
        removeRegion(child, regionBase);
      else
        qWarning() << "Trying to remove an element that is not\
                      of the type QnlyGraphicsRegion " << __FILE__ << __LINE__;
    }

    regions.remove(region->getUid());

    regionBase->removeRegion(region);

    // delete(region);
  }
}

void View::changeRegion(Region* region,
                            RegionBase* regionBase,
                            const QMap<QString, QString> attributes)
{
  if (region != NULL && regionBase != NULL)
  {
    regionBase->changeRegion(region, attributes);
  }
}

void View::selectRegion(Region* region,
                            RegionBase* regionBase)
{
  if (region != NULL && regionBase != NULL)
  {
    if (selectedRegion != NULL)
    {
      selectedRegion->setSelected(false);
    }

    regionBase->selectRegion(region);

    selectedRegion = region;

    QWidget* parent = (QWidget*) regionBase->parent();

    setCurrentWidget(parent);
  }
}

void View::addRegionBase(RegionBase* regionBase,
                             const QMap<QString, QString> attributes)
{
  if (regionBase != NULL)
  {
    qDebug() << "RegionBase Added!";

    if (attributes.contains("id"))
      regionBase->setId(attributes["id"]);

    if (attributes.contains("region"))
      regionBase->setId(attributes["region"]);

    if (attributes.contains("device"))
      regionBase->setId(attributes["device"]);

    QWidget* parent = (QWidget*) regionBase->parent();

    addWidget(parent);
    setCurrentWidget(parent);

    regionbases[regionBase->getUid()] = regionBase;

    QAction* action = new QAction(this);
    action->setText(regionBase->getId());

    switchMenu->addAction(action);

    action->setCheckable(true);
    action->setEnabled(true);

    regionbaseActionGroup->addAction(action);

    action->trigger();

    regionbaseActions[regionBase->getUid()] = action;

    connect(regionBase, SIGNAL(regionbasePerformed()),
            SLOT(performRegionBase()));

    connect(regionBase,
            SIGNAL(regionAdditionRequested(QString,QString,QString
                                           ,QMap<QString,QString>)),
            SLOT(requestRegionAddition(QString,QString,QString
                                       ,QMap<QString,QString>)));

    connect(regionBase,
            SIGNAL(regionChangeRequested(QString,QString,QMap<QString,QString>)),
            SLOT(requestRegionChange(QString,QString,QMap<QString,QString>)));

    connect(regionBase,
            SIGNAL(regionSelectionRequested(QString,QString)),
            SIGNAL(regionSelected(QString,QString)));

    connect(regionBase,
            SIGNAL(regionBaseSelectionRequested(QString)),
            SIGNAL(regionBaseSelected(QString)));

    connect(regionBase,
            SIGNAL(regionBaseDeletionRequested(QString)),
            SIGNAL(regionBaseRemoved(QString)));

    connect(regionBase,
            SIGNAL(regionDeletionRequested(QString,QString)),
            SIGNAL(regionRemoved(QString,QString)));

    connect(regionBase,
            SIGNAL(mediaOverRegion(QString,QString)),
            SIGNAL(mediaOverRegionAction(QString,QString)));

    regionBase->setGridVisible(gridVisibility);
    connect(regionBase,
            SIGNAL(gridVisibilityChanged(bool)),
            SLOT(setGridVisible(bool)));

    connect(regionBase,
            SIGNAL(copyRequested(Region*)),
            SLOT(performCopy(Region *)));

    connect(regionBase,
            SIGNAL(pasteRequested()),
            SLOT(performPaste()));

    emit regionBaseSelected(regionBase->getUid());
  }
}

void View::removeRegionBase(RegionBase* regionBase)
{
  if (regionBase != NULL)
  {
    qWarning() << "RegionBase removed!";

    QAction* action = regionbaseActions[regionBase->getUid()];
    switchMenu->removeAction(action);

    regionbaseActionGroup->removeAction(action);

    // delete(action);

    foreach(QGraphicsItem* item, regionBase->items())
    {
      if (item != regionBase->getBackgroundItem()) {
        Region* child = dynamic_cast<Region *> (item);

        if (child != NULL)
        {
          regions.remove(child->getUid());
        }
        else
          qWarning() << "Trying to remove an element that is not of the\
                        type QnlyGraphicsRegion " << __FILE__ << __LINE__;
      }
    }

    //        delete (regionBase);


    QWidget* parent = (QWidget*) regionBase->parent();

    removeWidget(parent);

    regionbases.remove(regionBase->getUid());

    if (currentWidget() != NULL)
    {
      RegionBase* current =
          (RegionBase*) ((QGraphicsView*)currentWidget())->scene();

      emit regionBaseSelected(current->getUid());
    }
  }
}

void View::changeRegionBase(RegionBase* regionBase,
                                const QMap<QString, QString> attributes)
{
  if (regionBase != NULL)
  {
    if (attributes.contains("id"))
    {
      regionBase->setId(attributes["id"]);

      QAction* action = regionbaseActions[regionBase->getUid()];
      action->setText(attributes["id"]);
    }

    if (attributes.contains("region"))
      regionBase->setId(attributes["region"]);

    if (attributes.contains("device"))
      regionBase->setId(attributes["device"]);
  }
}

void View::selectRegionBase(RegionBase* regionBase)
{
  if (regionBase != NULL)
  {
    QWidget* parent = (QWidget*) regionBase->parent();

    setCurrentWidget(parent);

    QAction* action = regionbaseActions[regionBase->getUid()];
    action->setChecked(true);

    if (selectedRegion != NULL)
    {
      selectedRegion->setSelected(false);
      selectedRegion = NULL;
    }

    selectedRegionBase = regionBase;

    emit regionBaseSelected(selectedRegionBase->getUid());
  }
}

void View::setGridVisible(bool visible)
{
  if(this->gridVisibility != visible)
  {
    this->gridVisibility = visible;
    foreach(RegionBase *regionBase, regionbases.values())
    {
      regionBase->setGridVisible(visible);
    }

    emit gridVisibilityChanged(visible);
  }
}

RegionBase* View::getSelectedRegionBase()
{
  return selectedRegionBase;
}

Region* View::getSelectedRegion()
{
  return selectedRegion;
}

void View::contextMenuEvent(QContextMenuEvent *event)
{
  QStackedWidget::contextMenuEvent(event);

  if (!event->isAccepted())
  {
    contextMenu->exec(event->globalPos());

    event->accept();
  }
}

void View::snapshot()
{
  if(getSelectedRegionBase() != NULL)
      getSelectedRegionBase()->performExport();
}