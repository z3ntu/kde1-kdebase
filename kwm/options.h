/*
 * main.h. Part of the KDE project.
 *
 * Copyright (C) 1997 Matthias Ettrich
 *
 */

#include <qpixmap.h>

#ifndef OPTIONS_H
#define OPTIONS_H

#define BORDER     4
#define TITLEWINDOW_SEPARATION  2
#define BUTTON_SIZE    20
#define TITLEBAR_HEIGHT 20


enum WINDOW_MOVE_TYPE {
  TRANSPARENT,
  OPAQUE
};

enum FOCUS_POLICY {
  CLICK_TO_FOCUS,
  FOCUS_FOLLOW_MOUSE
};

enum TITLEBAR_LOOK{
  PLAIN,
  SHADED,
  PIXMAP
};

enum BUTTON_FUNCTIONS {
 MAXIMIZE,
 ICONIFY,
 CLOSE,
 STICKY,
 MENU,
 NOFUNC,
 UNDEFINED
};


struct kwmOptions {

  WINDOW_MOVE_TYPE WindowMoveType;
  FOCUS_POLICY FocusPolicy;
  TITLEBAR_LOOK TitlebarLook;
  bool ResizeAnimation;
  bool MaximizeOnlyVertically;
  int TitleAnimation;
  int AutoRaise;
  bool ControlTab;
  bool Button3Grab;

  const char* rstart;

  BUTTON_FUNCTIONS buttons[6];

  QPixmap* titlebarPixmapActive;
  QPixmap* titlebarPixmapInactive;

};

extern kwmOptions options;


#endif // OPTIONS_H

