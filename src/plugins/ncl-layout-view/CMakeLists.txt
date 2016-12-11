cmake_minimum_required (VERSION 3.5)
project(ncl_layout_view)

set (CMAKE_INCLUDE_CURRENTDIR ON)
set (CMAKE_AUTOMOC ON)

include_directories(
  .
  src
  src/ui
  src/ui/view
  "${CMAKE_SOURCE_DIR}/src/plugins/ncl-profile"
  "${CMAKE_SOURCE_DIR}/src/core/src"
  "${CMAKE_BINARY_DIR}/src/plugins/ncl-layout-view"
  ${nclcomposer_core_SOURCE_DIR}
)

find_package (Qt5Xml REQUIRED)
find_package (Qt5Widgets REQUIRED)

set (NCL_LAYOUT_VIEW_SOURCES
  src/LayoutViewPlugin.cpp
  src/LayoutViewFactory.cpp
  src/ui/view/LayoutView.cpp
  src/ui/view/LayoutRegion.cpp
  src/ui/view/LayoutRegionBase.cpp
  src/ui/view/LayoutGrid.cpp
  src/ui/view/LayoutCanvas.cpp
  src/ui/LayoutWindow.cpp

  src/LayoutViewPlugin.h
  src/LayoutViewFactory.h
  src/ui/view/LayoutCanvas.h
  src/ui/view/LayoutGrid.h
  src/ui/view/LayoutRegion.h
  src/ui/view/LayoutRegionBase.h
  src/ui/view/LayoutView.h
  src/ui/LayoutWindow.h
)

qt5_wrap_ui (UI_GENERATED_HEADERS
  ui/LayoutWindow.ui
)

add_library (ncl_layout_view
  SHARED
  ${NCL_LAYOUT_VIEW_SOURCES}
  ${UI_GENERATED_HEADERS}
)

target_link_libraries (ncl_layout_view
  nclcomposer_core
  nclprofile
  Qt5::Xml
  Qt5::Widgets
)

install (TARGETS ncl_layout_view DESTINATION plugins)