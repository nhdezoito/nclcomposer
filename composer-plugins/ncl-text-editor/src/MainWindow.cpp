/****************************************************************************
**
** Copyright (C) 2004-2006 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** Licensees holding a valid Qt License Agreement may use this file in
** accordance with the rights, responsibilities and obligations
** contained therein.  Please consult your licensing agreement or
** contact sales@trolltech.com if any conditions of this licensing
** agreement are not clear to you.
**
** Further information about Qt licensing is available at:
** http://www.trolltech.com/products/qt/licensing.html or by
** contacting info@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include <QtGui>

#include <Qsci/qsciscintilla.h>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent):
        QMainWindow(parent)
{
    textEdit = new NCLTextEditor(this);
    setCentralWidget(textEdit);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createTreeView();

    readSettings();

    connect(textEdit, SIGNAL(textChanged()),
            this, SLOT(documentWasModified()));

    connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), SLOT(gotoLineOf(QTreeWidgetItem *, int)));

    setCurrentFile("");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::newFile()
{
    if (maybeSave()) {
        textEdit->clear();
        setCurrentFile("");
    }
}

void MainWindow::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Application"),
                       tr("The <b>Application</b> example demonstrates how to "
                          "write modern GUI applications using Qt, with a menu bar, "
                          "toolbars, and a status bar."));
}

void MainWindow::documentWasModified()
{
    setWindowModified(textEdit->isModified());
}

void MainWindow::createActions()
{
    newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAct->setShortcut(tr("Ctrl+N"));
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setShortcut(tr("Ctrl+S"));
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    cutAct->setShortcut(tr("Ctrl+X"));
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));

    copyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    copyAct->setShortcut(tr("Ctrl+C"));
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy()));

    pasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    pasteAct->setShortcut(tr("Ctrl+V"));
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    cutAct->setEnabled(false);
    copyAct->setEnabled(false);
    connect(textEdit, SIGNAL(copyAvailable(bool)),
            cutAct, SLOT(setEnabled(bool)));
    connect(textEdit, SIGNAL(copyAvailable(bool)),
            copyAct, SLOT(setEnabled(bool)));

    fullscreenAct = new QAction(QIcon(":/images/window_fullscreen.png"), tr("&FullScreen"), this);
    fullscreenAct->setShortcut(tr("F11"));
    fullscreenAct->setStatusTip(tr("Enable/disable fullscreen mode"));
    connect(fullscreenAct, SIGNAL(triggered()), this, SLOT(showInFullScreen()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(fullscreenAct);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createTreeView()
{
    treeWidget = new NCLTreeWidget(this);
    treeWidget->setColumnCount(1);
    treeWidget->setMaximumWidth(300);;
    treeWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);

    QTreeWidgetItem* item = new QTreeWidgetItem(0);
    item->setText(0, "hi");
    item->setFlags(Qt::ItemIsEnabled);
    treeWidget->insertTopLevelItem(0, item);

    dockTreeView = new QDockWidget("Outline", this);
    dockTreeView->setFeatures(QDockWidget::DockWidgetMovable |
                              QDockWidget::DockWidgetFloatable);
    dockTreeView->setAllowedAreas(Qt::LeftDockWidgetArea |
                                  Qt::RightDockWidgetArea);
    dockTreeView->setWidget(treeWidget);

    addDockWidget(Qt::LeftDockWidgetArea, dockTreeView);

    treeWidget->setContextMenuPolicy(Qt::ActionsContextMenu);

    nodeMenu = new QMenu(treeWidget);
    insertNodeChild = new QAction(QIcon(":/images/save.png"), tr("&Add child"), this);
    connect(insertNodeChild, SIGNAL(triggered()), this, SLOT(insertElement()));
    treeWidget->addAction(insertNodeChild);

}

void MainWindow::readSettings()
{
    QSettings settings("Trolltech", "Application Example");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    bool fullscreen = settings.value("fullscreen", true).toBool();
    resize(size);
    move(pos);

    if(fullscreen)
        showFullScreen();
}

void MainWindow::writeSettings()
{
    QSettings settings("Trolltech", "Application Example");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
    settings.setValue("fullscreen", isFullScreen());
}

bool MainWindow::maybeSave()
{
    if (textEdit->isModified()) {
        int ret = QMessageBox::warning(this, tr("Application"),
                                       tr("The document has been modified.\n"
                                          "Do you want to save your changes?"),
                                       QMessageBox::Yes | QMessageBox::Default,
                                       QMessageBox::No,
                                       QMessageBox::Cancel | QMessageBox::Escape);
        if (ret == QMessageBox::Yes)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    textEdit->setText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << textEdit->text();
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);

    treeWidget->updateFromText(textEdit->text());
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    textEdit->setModified(false);
    setWindowModified(false);

    QString shownName;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    else
        shownName = strippedName(curFile);

    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Application")));
    treeWidget->updateFromText(textEdit->text());
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::showInFullScreen(){
    if(!isFullScreen())
        showFullScreen();
    else
        showNormal();
}

void MainWindow::gotoLineOf(QTreeWidgetItem *item, int column)
{
    (void) column;

    bool ok;
    int line = item->text(2).toInt(&ok, 10);
    textEdit->setCursorPosition(line-1, 0);
    textEdit->ensureLineVisible(line-1);
    textEdit->SendScintilla(QsciScintilla::SCI_SETFOCUS, true);
}


//FIXME:    1. fix line element line numbers.
//          2. If element father is a start-closed tag in the same line, open it.
void MainWindow::insertElement(){
    bool ok;
    QList<QTreeWidgetItem*> selecteds = treeWidget->selectedItems ();
    QTreeWidgetItem *item = selecteds.at (0);
    int line = item->text(2).toInt ( &ok, 10 );
    QString tagname = item->text(0);

    QStringList strlist;
    map <QString, char> * children = NCLStructure::getInstance()->getChildren(tagname);

    if(children != NULL) {
        map <QString, char>::iterator it;
        for(it = children->begin(); it != children->end(); ++it){
            strlist << it->first;
        }
    }

    QString element = QInputDialog::getItem(this,
                                tr("Add child"),
                                tr("Element name:"),
                                strlist,
                                0,
                                true,
                                &ok);

    if(ok && !element.isEmpty()) {
        //Add new Element to TreeWidget
        treeWidget->addElement(item, 0, tagname, QString(""), line, 0);

        //Add new Element to texttWidget
        int endLine = textEdit->SendScintilla(QsciScintilla::SCI_GETLINEENDPOSITION, line-1);
        int beginLine = textEdit->SendScintilla(QsciScintilla::SCI_POSITIONFROMLINE, line-1);
        int end_element_column = item->text(3).toInt(&ok, 10);
        bool fix_next_line_indentation = false;

        //find if we are in a "<tagname/>" then open this tag
        char ch = textEdit->SendScintilla(QsciScintilla::SCI_GETCHARAT, beginLine + end_element_column-1);
        qDebug() << ch;
        if (ch == '/') {
            QString endtag = ">";
            endtag += "<";
            textEdit->insertAt(tagname, line-1, end_element_column);
            textEdit->insertAt(endtag,  line-1, end_element_column-1);
        }

        //put all the required attributes
        //TODO: remove from here (create a function)
        map <QString, bool> *attributes = NCLStructure::getInstance()->getAttributes(element);
        if(attributes != NULL) {
            map <QString, bool>::iterator it;
            for(it = attributes->begin(); it != attributes->end(); ++it){
                if(it->second) {
                    element += " ";
                    element += it->first + "=\"\"";
                }
            }
        }

        element.prepend("<");
        element.append("/>");
        if(end_element_column != endLine-beginLine) {
            fix_next_line_indentation = true;
            element.append("\n");
        }

        element.prepend("\n");

        qDebug() << line << " " << beginLine << " " << endLine << " " << end_element_column << " ";

        textEdit->insertAt(element, line-1, end_element_column);

        //fix indentation
        int lineident = textEdit->SendScintilla(QsciScintilla::SCI_GETLINEINDENTATION, line-1);
        textEdit->SendScintilla(QsciScintilla::SCI_GETLINEINDENTATION, line-1);

        if(fix_next_line_indentation)
            textEdit->SendScintilla(QsciScintilla::SCI_SETLINEINDENTATION, line+1, lineident);

        textEdit->SendScintilla(QsciScintilla::SCI_SETLINEINDENTATION, line, lineident+8);

        textEdit->setCursorPosition(line, 0);
        textEdit->ensureLineVisible(line);
        textEdit->SendScintilla(QsciScintilla::SCI_SETFOCUS, true);
    }

}
