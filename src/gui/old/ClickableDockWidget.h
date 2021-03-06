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

#ifndef CLICKABLEDOCKWIDGET_H
#define CLICKABLEDOCKWIDGET_H

#include <QEvent>
#include <QFrame>
#include <QPushButton>
#include <QDockWidget>

namespace composer {
  namespace gui {

/*!
* \brief A DockWidget that emit signals when clicked.
*/
class ClickableQDockWidget : public QDockWidget
{
  Q_OBJECT

public:
  /*!
   * \brief Constructor.
   */
  ClickableQDockWidget (const QString &title, QWidget *parent = 0,
                        Qt::WindowFlags flags = 0);

signals:
  void clicked();
  void refreshPressed();

protected:
  bool event(QEvent *event);

private:
  void createTitlebar(const QString &title);
  void addButtonToDockTitleBar( QFrame *titleBar,
                                QPushButton *button);
private slots:
  void visibilityHasChange(bool visible);
  void topLevelHasChanged(bool a);

};

} }

#endif // CLICKABLEDOCKWIDGET_H
