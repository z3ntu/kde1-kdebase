//
//
// "Misc Options" Tab for KFM configuration
//
// (c) Martin R. Jones 1996
//
// Port to KControl
// (c) David Faure 1998

#ifndef __KFM_MISC_OPTIONS_H
#define __KFM_MISC_OPTIONS_H

#include <qtabdlg.h>
#include <qstrlist.h>
#include <qchkbox.h>
#include <kspinbox.h>
#include <kcolorbtn.h>

#include <kconfig.h>
#include <kcontrol.h>

extern KConfigBase *g_pConfig;

//-----------------------------------------------------------------------------
// The "Misc Options" Tab contains :

// Root Icons settings (gridwidth/height, transparent text, bg & fg color)
// ... should create a "Desktop Icons" tab.
// Misc settings (allow per-url settings, tree view follows navigation)

class KMiscOptions : public KConfigWidget
{
        Q_OBJECT
public:
        KMiscOptions( QWidget *parent = 0L, const char *name = 0L );
        virtual void loadSettings();
        virtual void saveSettings();
        virtual void applySettings();
        virtual void defaultSettings();
 
 private slots:
        void slotIconFgColorChanged(const QColor &);
        void slotIconBgColorChanged(const QColor &);
        void makeBgActive( bool );
 
private:
        QLabel * bgLabel;
        // Root Icons Settings
        KNumericSpinBox *hspin;
        KNumericSpinBox *vspin;
        QCheckBox *iconstylebox;
        KColorButton *fgColorBtn;
        KColorButton *bgColorBtn;

        QColor icon_fg;
        QColor icon_bg;

        // Misc Settings
        QCheckBox *urlpropsbox;
        QCheckBox *treefollowbox;
};

#endif // __KFM_MISC_OPTIONS_H