//-----------------------------------------------------------------------------
//
// KDE HTML Bookmarks
//
// (c) Martin R. Jones 1996
//

#ifndef __BOOKMARK_H__
#define __BOOKMARK_H__

#include "html.h"
#include <qtstream.h>

class KBookmark
{
public:
	enum { URL, Folder };

	KBookmark();
	KBookmark( const char *_text, const char *_url );

	void clear();

	void setText( const char *_text )	{	text = _text; }
	void setURL( const char *_url )	{	url = _url; }
	void setType( int _type )	{	type = _type; }

	const char *getText()	{	return text; }
	const char *getURL()	{	return url; }
	int getType()	{	return type; }

	QList<KBookmark> &getChildren() 	{ return children; }

private:
	QString text;
	QString url;
	int type;
	QList<KBookmark> children;
};

class KBookmarkManager : public QObject
{
	Q_OBJECT
public:
	KBookmarkManager();

	void setTitle( const char *t )
		{	title = t; }

	void read( const char *filename );
	void write( const char *filename );

	void add( const char *_text, const char *_url );
	// rich
	bool remove(int);
	bool moveUp(int);
	bool moveDown(int);
	void reread();
	void rename(int, const char *);
	/**
	 * Overloaded to reread the last file loaded
	 */
	void write();

	KBookmark *getBookmark( int id );
	KBookmark *getRoot()	{	return &root; }

private:
	const char *parse( HTMLTokenizer *ht, KBookmark *parent, const char *_end);
	void	writeFolder( QTextStream &stream, KBookmark *parent );
	KBookmark *findBookmark( KBookmark *parent, int id, int &currId );

signals:
	void changed();

private:
	KBookmark root;
	QString title;
	// rich
        QString myFilename;
};

#endif	// __BOOKMARK_H__

