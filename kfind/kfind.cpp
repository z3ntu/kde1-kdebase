/***********************************************************************
 *
 *  Kfind.cpp
 *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <qapp.h>
#include <qwidget.h>
#include <qpushbt.h>
#include <qcolor.h>
#include <stdio.h>
#include <qevent.h>
#include <qstring.h>
#include <qdir.h>

#include <kmsgbox.h>
#include <kprocess.h>

#include "kftabdlg.h"
#include "kfwin.h"
#include "kfind.h"

Kfind::Kfind( QWidget *parent, const char *name, const char *searchPath = 0 )
    : QWidget( parent, name )
  {
    //create tabdialog
    tabDialog = new KfindTabDialog(this,"dialog",searchPath);

    //prepare window for find results
    win = new KfindWindow(this,"window");
    win->hide();  //and hide it firstly    
    winsize=1;

    connect(win ,SIGNAL(resultSelected(bool)),
	    this,SIGNAL(resultSelected(bool)));
    connect(win ,SIGNAL(statusChanged(const char *)),
	    this,SIGNAL(statusChanged(const char *)));
    connect(this,SIGNAL(deleteFile()),
	    win,SLOT(deleteFiles()));
    connect(this,SIGNAL(properties()),
	    win,SLOT(fileProperties()));
    connect(this,SIGNAL(openFolder()),
	    win,SLOT(openFolder()));
    connect(this,SIGNAL(saveResults()),
	    win,SLOT(saveResults()));
    connect(this,SIGNAL(addToArchive()),
	    win,SLOT(addToArchive()));
    connect(this,SIGNAL(open()),
	    win,SLOT(openBinding()));
    connect(&findProcess,SIGNAL(processExited(KProcess *)),
	    this,SLOT(processResults()));

    emit haveResults(false);
    resize(tabDialog->sizeHint()+QSize(0,5));
  };

void Kfind::resizeEvent( QResizeEvent *e)
  {
    QWidget::resizeEvent(e);

    tabDialog->setGeometry(5,5,
			   width()-10,(tabDialog->sizeHint()).height());
    //printf("------------------------------\n");
    //printf("Win height1 = %d\n",win->height());
    //printf("Kfind height1 = %d\n",height());
    //printf("tabDialog height1 = %d\n",(tabDialog->sizeHint()).height());

    win->setGeometry(0,5+(tabDialog->sizeHint()).height()+5,width(),
    		     height()-tabDialog->height()-10);

    //printf("Win height2 = %d\n",win->height());
    //printf("------------------------------\n");
  };
    
void Kfind::startSearch()
  {
    QString buffer,pom;
    int pos;
    buffer = tabDialog->createQuery();

    //if ( winsize==1)
    //  winsize=300;
    emit haveResults(false);
    emit resultSelected(false);
    win->clearList();

    if (!buffer.isNull())
      {
	enableSearchButton(false);

	findProcess.setExecutable("find");
	findProcess.clearArguments ();

        int t = time( 0L ); 
        outFile.sprintf( "/tmp/kfindout%i", t );

	buffer.append(pom.sprintf(" -fprint %s",outFile.data()));
        buffer=buffer.simplifyWhiteSpace();

	while( !buffer.isEmpty() )
	  {
	    pos = buffer.find(" ");
	    pom = buffer.left(pos);

	    findProcess << pom.data();

	    if (pos==-1) 
	      pos = buffer.length();
	    buffer = buffer.remove(0,pos+1);
	  };

	findProcess.start();
      };
  };

void Kfind::stopSearch()
  {
    //    printf("Stoping Search\n");
    
    enableSearchButton(true);

    findProcess.kill();
  };

void Kfind::newSearch()
  {
    //    printf("Prepare for New Search\n");
    win->hide();
    win->clearList();
    //    winsize=1;

    tabDialog->setDefaults();

    emit enableStatusBar(false);
    emit haveResults(false);
    emit resultSelected(false);
     
    stopSearch();
 };

void Kfind::processResults()
  {
    win->updateResults( outFile.data() );
    win->show();
    
    emit haveResults(true);
    emit enableStatusBar(true);

    unlink( outFile.data() );
    
    enableSearchButton(true);
  };

QSize Kfind::sizeHint()
  {
    return (tabDialog->sizeHint());//+QSize(0,winsize-1));
  };

