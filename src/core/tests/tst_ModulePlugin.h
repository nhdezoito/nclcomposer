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

#ifndef TST_MODULEPLUGIN_H
#define TST_MODULEPLUGIN_H

#include <QObject>
#include <QTest>

#include "modules/PluginControl.h"
#include "modules/LanguageControl.h"
using namespace composer::core;

class tst_ModulePlugin : public QObject
{
  Q_OBJECT

public:
  void setBenchmark(bool isBench) { isBenchmark = isBench; }

private:
  PluginControl *pgControl;
  QString pluginDir;
  bool isBenchmark;

private slots:
  void initTestCase();
  void loadPluginDir();
  void pluginName_data();
  void pluginName();
  void pluginLoadBenchmark_data();
  void pluginLoadBenchmark();
  void cleanupTestCase();

};

#endif // TST_MODULEPLUGIN_H
