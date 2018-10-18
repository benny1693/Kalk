#include "../headers/menu.h"

menu::menu(){
  QAction *save = new QAction("&Save", this);

  QMenu *file;
  file = menuBar()->addMenu("&File");
  file->addAction(save);
}
