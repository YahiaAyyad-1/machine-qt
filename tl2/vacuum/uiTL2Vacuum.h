#ifndef UITL2VACUUM_H
#define UITL2VACUUM_H

#include <QMainWindow>
#include <qepicspv.h>

#include "general/valves_window.h"
#include "qepicspv.h"
#include "client.h"

namespace Ui {
class uiTL2Vacuum;
}

class uiTL2Vacuum : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiTL2Vacuum(QWidget *parent = 0);
    ~uiTL2Vacuum();

private slots:
    void on_btnValves_clicked();

    void onStatusChanged();

    void on_btnReset_clicked();

private:
    Ui::uiTL2Vacuum *ui;
    ValvesWindow* valves;

    QEpicsPV* pvStatus[8];

    QString pvs[24] = {"TL1-VA-GV1"  , "TL1-VA-GV2"  , "BOC02-VA-GV1", "BOC03-VA-GV1", "BOC05-VA-GV1", "TL2-VA-GV1"  , "TL2-VA-GV2", "TL2-VA-SH1",
                       "SRC01-VA-GV1", "SRC01-VA-GV2", "SRC03-VA-GV1", "SRC03-VA-GV2", "SRC05-VA-GV1", "SRC05-VA-GV2",
                       "SRC07-VA-GV1", "SRC07-VA-GV2", "SRC09-VA-GV1", "SRC09-VA-GV2", "SRC11-VA-GV1", "SRC11-VA-GV2",
                       "SRC13-VA-GV1", "SRC13-VA-GV2", "SRC15-VA-GV1", "SRC15-VA-GV2"};
};

#endif // UITL2VACUUM_H
