#include "session.h"

#include <qpushbutton.h>

TESession::TESession(KTMainWindow* main, TEWidget* te, const char* args[], const char* term)
{
  sh = new Shell();
  em = new VT102Emulation(te,term);

  this->term = strdup(term);

  { int i;
    for (i = 0; args[i]; i++);
    this->args = (char**)malloc(sizeof(char*)*(i+1));
    for (i = 0; args[i]; i++) this->args[i] = strdup(args[i]);
    this->args[i] = NULL;
  }

  sh->setSize(te->Lines(),te->Columns()); // not absolutely nessesary
  QObject::connect( sh,SIGNAL(block_in(const char*,int)),
                    em,SLOT(onRcvBlock(const char*,int)) );
  QObject::connect( em,SIGNAL(ImageSizeChanged(int,int)),
                    sh,SLOT(setSize(int,int)));
  QObject::connect( em,SIGNAL(ImageSizeChanged(int,int)),
                    main,SLOT(notifySize(int,int)));
  QObject::connect( em,SIGNAL(sndBlock(const char*,int)),
                    sh,SLOT(send_bytes(const char*,int)) );
  QObject::connect( em,SIGNAL(changeColumns(int)),
                    main,SLOT(changeColumns(int)) );
  QObject::connect( em,SIGNAL(changeTitle(int, char*)),
                    main,SLOT(changeTitle(int, char*)) );
  QObject::connect( this,SIGNAL(done(TESession*,int)),
                    main,SLOT(doneSession(TESession*,int)) );
  QObject::connect( sh,SIGNAL(done(int)), this,SLOT(done(int)) );
  //FIXME: note the right place
  QObject::connect( te,SIGNAL(configureRequest(TEWidget*,int,int,int)),
                    main,SLOT(configureRequest(TEWidget*,int,int,int)) );
}

void TESession::run()
{
  sh->run(args,term);
}

TESession::~TESession()
{ int i;
  free(term);
  for (i = 0; args[i]; i++) free(args[i]);
  free(args);
  delete em;
  delete sh;
}

void TESession::setConnect(bool c)
{
  em->setConnect(c);
}

void TESession::done(int status)
{
//setConnect(FALSE);
  emit done(this,status);
//delete this;
}

Emulation* TESession::getEmulation()
{
  return em;
}

// following interfaces might be misplaces ///

int TESession::schemaNo()
{
  return schema_no;
}

int TESession::fontNo()
{
  return font_no;
}

const char* TESession::emuName()
{
  return term;
}

void TESession::setSchemaNo(int sn)
{
  schema_no = sn;
}

void TESession::setFontNo(int fn)
{
  font_no = fn;
}

void TESession::setTitle(const char* title)
{
  this->title = title;
}

const char* TESession::Title()
{
  return title.data();
}


#include "session.moc"
