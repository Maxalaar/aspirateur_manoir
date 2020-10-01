#ifndef MAIN_ASPIRATEUR_MANOIR_H
#define MAIN_ASPIRATEUR_MANOIR_H

#include <QMainWindow>
#include <QVector>
#include <QDebug>
#include <QApplication>
#include <QRandomGenerator>
//#include <QObject>
//#include <QThread>

#include "environement_manoir.h"
#include "fenetre_affichage_manoir.h"
#include "aspirateur_agent.h"
#include "deplacement_thread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class main_aspirateur_manoir; }
QT_END_NAMESPACE

class main_windows_aspirateur_manoir : public QMainWindow
{
    Q_OBJECT

public:
    main_windows_aspirateur_manoir(QWidget *parent = nullptr);
    ~main_windows_aspirateur_manoir();

private:
    Ui::main_aspirateur_manoir *ui;
};
#endif // MAIN_ASPIRATEUR_MANOIR_H
