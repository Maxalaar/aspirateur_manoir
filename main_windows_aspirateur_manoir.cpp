#include "main_aspirateur_manoir.h"
#include "ui_main_aspirateur_manoir.h"

main_windows_aspirateur_manoir::main_windows_aspirateur_manoir(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::main_aspirateur_manoir)
{
    ui->setupUi(this);
}

main_windows_aspirateur_manoir::~main_windows_aspirateur_manoir()
{
    delete ui;
}

