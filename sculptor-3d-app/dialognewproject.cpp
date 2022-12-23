#include "dialognewproject.h"
#include "ui_dialognewproject.h"

#include <string>
using namespace std;

DialogNewProject::DialogNewProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewProject)
{
    ui->setupUi(this);
}

DialogNewProject::~DialogNewProject()
{
    delete ui;
}

QString DialogNewProject::get_x_dialog()
{
    return ui->lineEdit_x->text();
}

QString DialogNewProject::get_y_dialog()
{
    return ui->lineEdit_y->text();
}

QString DialogNewProject::get_z_dialog()
{
    return ui->lineEdit_z->text();
}
