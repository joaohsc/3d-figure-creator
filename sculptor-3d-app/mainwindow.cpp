#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sculptor.h"
#include <QString>
#include <QDebug>
#include <QFileDialog>
#include "dialognewproject.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dimX = 20;
    dimY = 20;
    dimZ = 20;
    r=0;
    g=0;
    b=0;

    escultor = new Sculptor(dimX,dimY,dimZ);
    escultor->limparVoxel();

    set_sliders_numbers();

    ui->widget->imprimirFigura(escultor->getPlano(ui->horizontalSlider_z->value()));

    actionGroup = new QActionGroup(this);
    actionGroup->addAction(ui->actionputVoxel);
    actionGroup->addAction(ui->actionputSphere);
    actionGroup->addAction(ui->actionputBox);
    actionGroup->addAction(ui->actionputEllipsoid);
    actionGroup->addAction(ui->actioncutVoxel);
    actionGroup->addAction(ui->actioncutSphere);
    actionGroup->addAction(ui->actioncutBox);
    actionGroup->addAction(ui->actioncutEllipsoid);
    ui->actionputVoxel->setChecked(true);

    connect(ui->actionNovo_Projeto, SIGNAL(triggered(bool)),this,SLOT(apresentaDialogo()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::quit()
{
    exit(0);
}

void MainWindow::setRed(int _r)
{
    r = _r;
    updateColor();
}

void MainWindow::setGreen(int _g)
{
    g = _g;
    updateColor();
}

void MainWindow::setBlue(int _b)
{
    b = _b;
    updateColor();
}

void MainWindow::draw3d(int hClick, int vClick)
{
    int x0,x1,y0,y1,z0,z1;
    switch(figuraAtual){
    case(sphere):
        escultor->putSphere(vClick,hClick,ui->horizontalSlider_z->value(),ui->sliderRadiusSphere->value());
        ui->widget->imprimirFigura(escultor->getPlano(ui->horizontalSlider_z->value()));
        break;
    case(voxel):
        escultor->putVoxel(vClick,hClick,ui->horizontalSlider_z->value());
        ui->widget->imprimirFigura(escultor->getPlano(ui->horizontalSlider_z->value()));
        break;
    case(box):
        x0=vClick - ui->horizontalSlider_BX->value()/2;
        x1=vClick + ui->horizontalSlider_BX->value()/2;

        y0=hClick - ui->horizontalSlider_BY->value()/2;
        y1=hClick + ui->horizontalSlider_BY->value()/2;

        z0=ui->horizontalSlider_z->value()-ui->horizontalSlider_BZ->value()/2;
        z1=ui->horizontalSlider_z->value()+ui->horizontalSlider_BZ->value()/2;

        escultor->putBox(x0,x1,y0,y1,z0,z1);

        ui->widget->imprimirFigura(escultor->getPlano(ui->horizontalSlider_z->value()));
        break;
    case(ellipsoid):
        escultor->putEllipsoid(vClick,hClick,ui->horizontalSlider_z->value(),ui->horizontalSlider_RX->value(),ui->horizontalSlider_RY->value(),ui->horizontalSlider_RZ->value());
        ui->widget->imprimirFigura(escultor->getPlano(ui->horizontalSlider_z->value()));
        break;

    case(cVoxel):
        escultor->cutVoxel(vClick,hClick,ui->horizontalSlider_z->value());
        ui->widget->imprimirFigura(escultor->getPlano(ui->horizontalSlider_z->value()));
        break;

    case(cSphere):

        escultor->cutSphere(vClick,hClick,ui->horizontalSlider_z->value(),ui->sliderRadiusSphere->value());
        ui->widget->imprimirFigura(escultor->getPlano(ui->horizontalSlider_z->value()));
        break;

    case(cBox):
        x0=vClick - ui->horizontalSlider_BX->value()/2;
        x1=vClick + ui->horizontalSlider_BX->value()/2;

        y0=hClick - ui->horizontalSlider_BY->value()/2;
        y1=hClick + ui->horizontalSlider_BY->value()/2;

        z0=ui->horizontalSlider_z->value()-ui->horizontalSlider_BZ->value()/2;
        z1=ui->horizontalSlider_z->value()+ui->horizontalSlider_BZ->value()/2;

        escultor->cutBox(x0,x1,y0,y1,z0,z1);

        ui->widget->imprimirFigura(escultor->getPlano(ui->horizontalSlider_z->value()));
        break;

    case(cEllipsoid):
        escultor->cutEllipsoid(vClick,hClick,ui->horizontalSlider_z->value(),ui->horizontalSlider_RX->value(),ui->horizontalSlider_RY->value(),ui->horizontalSlider_RZ->value());
        ui->widget->imprimirFigura(escultor->getPlano(ui->horizontalSlider_z->value()));
        break;
    }
}

void MainWindow::updateAxis(int hClick, int vClick)
{
    ui->lcdNumber_x->display(vClick);
    ui->lcdNumber_y->display(hClick);
}

void MainWindow::apresentaDialogo()
{
    DialogNewProject d;
    if(d.exec() == QDialog::Accepted){
        dimX = d.get_x_dialog().toInt();
        dimY = d.get_y_dialog().toInt();
        dimZ = d.get_z_dialog().toInt();

        if(escultor != NULL)
            delete escultor;
        escultor = new Sculptor(dimX,dimY,dimZ);

        set_sliders_numbers();

        ui->widget->imprimirFigura(escultor->getPlano(ui->horizontalSlider_z->value()));



    }
}

void MainWindow::save()
{
    QFileDialog dialog;
    QString selectedFilter;
    QString filename = dialog.getSaveFileName(this,tr("Salvar"),
                                              QDir::currentPath(),
                                              tr("Arquivo OFF(*.off)"),
                                              &selectedFilter);
    if(filename.isNull()){
        return;
    }

    escultor->writeOFF(filename.toStdString().c_str());
}



void MainWindow::putVoxel()
{
    figuraAtual = voxel;
}

void MainWindow::putBox()
{
    figuraAtual = box;
}

void MainWindow::putSphere()
{
    figuraAtual = sphere;
}

void MainWindow::putEllipsoid()
{
    figuraAtual = ellipsoid;
}

void MainWindow::cutVoxel()
{
    figuraAtual = cVoxel;
}

void MainWindow::cutBox()
{
    figuraAtual = cBox;
}

void MainWindow::cutSphere()
{
    figuraAtual = cSphere;
}

void MainWindow::cutEllipsoid()
{
    figuraAtual = cEllipsoid;
}

void MainWindow::set_Axis_z(int value)
{
    ui->widget->imprimirFigura(escultor->getPlano(value));
}

void MainWindow::limpar_voxel()
{
    escultor->limparVoxel();
    ui->widget->imprimirFigura(escultor->getPlano(ui->horizontalSlider_z->value()));
}

void MainWindow::set_sliders_numbers()
{
    ui->horizontalSlider_z->setMaximum(dimZ-1);

    ui->horizontalSlider_BX->setMinimum(1);
    ui->horizontalSlider_BY->setMinimum(1);
    ui->horizontalSlider_BZ->setMinimum(1);
    ui->horizontalSlider_BX->setMaximum(dimZ);
    ui->horizontalSlider_BY->setMaximum(dimZ);
    ui->horizontalSlider_BZ->setMaximum(dimZ);

    ui->horizontalSlider_RX->setMinimum(1);
    ui->horizontalSlider_RY->setMinimum(1);
    ui->horizontalSlider_RZ->setMinimum(1);
    ui->horizontalSlider_RX->setMaximum(dimZ);
    ui->horizontalSlider_RY->setMaximum(dimZ);
    ui->horizontalSlider_RZ->setMaximum(dimZ);

    ui->sliderRadiusSphere->setMinimum(1);
    ui->sliderRadiusSphere->setMaximum(dimZ-1);
}

void MainWindow::updateColor()
{
    QString color;

    // mudar se der pau
    color = "background-color: rgb(" +
            QString().setNum(r) + "," +
            QString().setNum(g) + "," +
            QString().setNum(b) + ");";
    ui->pushButton_color_preview->setStyleSheet(color);
    escultor->setColor(r,g,b,1);
}



