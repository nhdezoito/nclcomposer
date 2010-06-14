#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QCheckBox>
#include <QDesktopWidget>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
   // ui->setupUi(this);
    screenResolution = QApplication::desktop()->screenGeometry();

    width = 700;
    height = 500;

    setWindowTitle("LayoutView");

    tree = new QTreeWidget;
    tree->setHeaderLabel("RegionBase");
    tree->header()->setResizeMode(0, QHeaderView::Stretch);


    scroll = new QScrollArea;

    att = new Attributes;

    area = new ScribbleArea;
    area->resize(width, height);


    createActions ();
    
    connect (createRegion, SIGNAL (triggered()),
             area, SLOT (Accept()));

    connect (clearAction, SIGNAL (triggered()),
            area, SLOT (clear()));

    connect (deleteRegion, SIGNAL (triggered()),
            this, SLOT (removeRegion()));

    connect (area, SIGNAL (regionSelected (NCLRegion *)),
             this, SLOT (selectRegion(NCLRegion *)));


    connect (area, SIGNAL (regionAdded(NCLRegion*)),
             this, SLOT (addNodeTreeView(NCLRegion*)));

    connect (tree, SIGNAL (itemSelectionChanged()),
             this, SLOT (selectRegion()));

    connect (area, SIGNAL (regionSelected(NCLRegion*)),
             this, SLOT (performChanges(NCLRegion*)));

    connect (area, SIGNAL (regionChanged(NCLRegion*)),
             att, SLOT (fillFields(NCLRegion*)));

    connect (area, SIGNAL (regionSelected(NCLRegion*)),
             att, SLOT (fillFields(NCLRegion*)));

    connect (att, SIGNAL (IdChanged(QString,QString)),
             this, SLOT (changeIdRegion (QString,QString)));

    connect (att, SIGNAL (LeftChanged(QString,QString)),
             this, SLOT (changeLeftRegion (QString,QString)));

    connect (att, SIGNAL (RightChanged(QString,QString)),
             this, SLOT (changeRightRegion (QString,QString)));

    connect (att, SIGNAL (TopChanged(QString,QString)),
             this, SLOT (changeTopRegion (QString,QString)));

    connect (att, SIGNAL (BottomChanged(QString,QString)),
             this, SLOT (changeBottomRegion (QString,QString)));

    connect (att, SIGNAL (ZIndexChanged(QString,QString)),
             this, SLOT (changeZIndexRegion (QString,QString)));

    connect (att, SIGNAL (TitleChanged(QString,QString)),
             this, SLOT (changeTitleRegion (QString,QString)));

    connect (att, SIGNAL (WidthChanged(QString,QString)),
             this, SLOT (changeWidthRegion (QString,QString)));

    connect (att, SIGNAL (HeightChanged(QString,QString)),
             this, SLOT (changeLeftRegion (QString,QString)));


    QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout *rightLayout = new QVBoxLayout;
    QGridLayout *bottomLayout = new QGridLayout;


    QCheckBox *check = new QCheckBox (tr("PreView"));

    bottomLayout->addWidget(att, 0, 0);
    bottomLayout->setColumnMinimumWidth(0, 700);
    bottomLayout->addWidget(check, 0, 1);

    rightLayout->addWidget(area);
    rightLayout->addLayout(bottomLayout);

    mainLayout->addWidget(tree);
    mainLayout->addLayout(rightLayout);

    createContextMenu();

    QWidget *widget = new QWidget;
    widget->setLayout(mainLayout);
    setCentralWidget(widget);
    //setLayout(layout);

    resize(sizeHint());
}

void MainWindow::changeBottomRegion(QString id, QString newValue)
{

}

void MainWindow::changeIdRegion(QString id, QString newValue)
{
    //region->setId (newValue);
}

void MainWindow::changeLeftRegion(QString id, QString newValue)
{
    bool ok;
    int left = newValue.toInt(&ok, 10);
    //std::cout<<left << std::endl;
    double p = (double) left/screenResolution.width();
    //std::cout<< width * p << std::endl;

    area->modify (id, "left", width * p);
}

void MainWindow::changeRightRegion(QString id, QString newValue)
{

}

void MainWindow::changeTopRegion(QString id, QString newValue)
{

}

void MainWindow::changeWidthRegion(QString id, QString newValue)
{

}

void MainWindow::changeHeightRegion(QString id, QString newValue)
{

}

void MainWindow::changeTitleRegion(QString id, QString newValue)
{

}

void MainWindow::changeZIndexRegion(QString id, QString newValue)
{

}

void MainWindow::addNodeTreeView(NCLRegion *region)
{
    if (region == NULL) return;
    QTreeWidgetItem *item = new QTreeWidgetItem;
    QTreeWidgetItem *parent;

    item->setText(0, region->getId());
    itens [region] = item;
    inverse [item] = region;

    if (region->getParent() != NULL){
        itens.at(region->getParent())->addChild (item);
        return;
    }

    tree->addTopLevelItem(item);
}

void MainWindow::selectRegion()
{
    QList <QTreeWidgetItem *> list = tree->selectedItems();
    NCLRegion *regions;
    if (list.size())
        regions = inverse[list[0]];
    else
        regions = NULL;
    area->setSelectedList(regions);
    if (regions!=NULL)
        att->fillFields(regions);
}

void MainWindow::performChanges(NCLRegion *region)
{
    if (region == NULL) return;
    QList <QTreeWidgetItem *> list = tree->selectedItems();
    for (int i=0; i < list.size(); i++) list[i]->setSelected(false);
    QTreeWidgetItem *item = itens[region];
    item->setSelected(true);

    att->fillFields(region);
    
}

void MainWindow::createContextMenu ()
{
    area->addAction(createRegion);
    area->addAction(clearAction);
    area->addAction(deleteRegion);
    area->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createActions ()
{
    createRegion = new QAction (tr("Create New &Region"), this);
    createRegion->setShortcut(tr("Ctrl+R"));
    createRegion->setToolTip(tr("Habilita a criacao de nova regiao"));

    clearAction = new QAction (tr("C&lear"), this);
    clearAction->setShortcut(tr("Ctrl+l"));
    clearAction->setToolTip(tr("Limpa as regioes desenhadas"));

    deleteRegion = new QAction (tr("&Delete Region"), this);
    deleteRegion->setShortcut(tr("delete"));

}

void MainWindow::selectRegion(NCLRegion *region)
{
    if (region == NULL) return;
    currentNCLRegion = region;
}

void MainWindow::removeRegion()
{
    if (currentNCLRegion == NULL) return;
    std::cout << tree->indexOfTopLevelItem( itens[currentNCLRegion] ) << std::endl;
    QTreeWidgetItem * item =  itens[currentNCLRegion] ;
    for (int i=0; i < item->childCount(); i++)
        item->removeChild(item->child(i));
    QTreeWidgetItem * parent = item->parent();
    if (parent != NULL)
        parent->removeChild(item);
    tree->takeTopLevelItem (tree->indexOfTopLevelItem( itens[currentNCLRegion] ));
    area->Delete(currentNCLRegion);
    currentNCLRegion = NULL;
    att->fillFields(currentNCLRegion);
}

void MainWindow::fillFields(NCLRegion *region)
{
    //TODO
}

MainWindow::~MainWindow()
{
    delete ui;
}
