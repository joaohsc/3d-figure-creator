#ifndef GRID_H
#define GRID_H

#include <QWidget>
#include <vector>
#include <QVector>
#include "sculptor.h"

using namespace std;

class Grid : public QWidget
{
    Q_OBJECT
public:
    explicit Grid(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *e);

    void setTamanho(int _nl, int _nc);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void imprimirFigura(vector <vector <Voxel> > m);

private:
    int nl, nc;
    vector <vector <Voxel> > v;
    int borderv, borderh;
    int dimCelula;
    int larguraTela, alturaTela;
    int larguraCelula, alturaCelula;
    bool pressed;

signals:
    void enviaPosicao(int,int);

};

#endif // GRID_H
