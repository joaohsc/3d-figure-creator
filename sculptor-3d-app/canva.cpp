#include "canva.h"
#include <QPainter>
#include <QSize>
#include <QPen>
#include <QBrush>
#include <QPoint>
#include <QMouseEvent>
#include <QGradient>
#include <cmath>
#include <iostream>
#include <sculptor.h>
#include <qdebug.h>

Canva::Canva(QWidget *parent)
    : QWidget{parent}
{
    nl = 10;
    nc = 10;

    pressed = false;
    widthScreen = rect().width();
    heightScreen = rect().height();
    widthCel = widthScreen/nc;
    heightCel = heightScreen/nl;
    if (heightCel > widthCel){
        tamCel = widthCel;
    }else{
        tamCel = heightCel;
    }
    setSize(nl,nc);
}

void Canva::paintEvent(QPaintEvent *e)
{

    QPen pen;
    QPainter p(this);
    QBrush brush;

    pen.setWidth(2);

    widthScreen = width();
    heightScreen = height();

    widthCel = widthScreen/nc;
    heightCel = heightScreen/nl;

    if (heightCel > widthCel){
        tamCel = widthCel;
    }else{
        tamCel = heightCel;
    }
    gridH = (widthScreen - nc*tamCel)/2;
    gridV = (heightScreen - nl*tamCel)/2;



    for(int i = 0; i < nl; i++){
        for(int j = 0; j < nc; j++){
            if(v[i][j].isOn == true){
                p.save();
                p.translate(j*tamCel+gridH+tamCel/2,
                            i*tamCel+gridV+tamCel/2);
                p.setPen(Qt::NoPen);
                brush.setColor(QColor::fromRgb(v[i][j].r, v[i][j].g, v[i][j].b));
                brush.setStyle(Qt::SolidPattern);
                p.setBrush(brush);
                p.drawRect(-tamCel/2+1, -tamCel/2+1, tamCel-1, tamCel-1);
                p.restore();
            }else{
                brush.setColor(QColor(255,255,255,0));
                p.setBrush(brush);
                p.drawRect(j*tamCel+gridH,i*tamCel+gridV,tamCel, tamCel);
            }
        }
    }

}

void Canva::setSize(int _nl, int _nc)
{
    nl = _nl;
    nc = _nc;
    repaint();
}

void Canva::mousePressEvent(QMouseEvent *event)
{
    int h, v;
    QRect ret;
    ret = rect();
    pressed = true;
    ret.adjust(gridH, gridV, -gridH, -gridV);
    if(ret.contains(event->pos())){
        h = (event->pos().x()-gridH)*nc/ret.width();
        v = (event->pos().y()-gridV)*nl/ret.height();
        emit enviaPosicao(h, v);
    }

}

void Canva::mouseMoveEvent(QMouseEvent *event)
{
    int h, v;
    QRect ret;
    ret = rect();
    ret.adjust(gridH, gridV, -gridH, -gridV);
    if(ret.contains(event->pos())&& pressed == true){
        h = (event->pos().x()-gridH)*nc/ret.width();
        v = (event->pos().y()-gridV)*nl/ret.height();
        emit enviaPosicao(h, v);
    }

}

void Canva::mouseReleaseEvent(QMouseEvent *event)
{
    pressed = false;
}

void Canva::imprimirFigura(vector<vector<Voxel> > m)
{
    nl = m.size();
    nc = m[0].size();
    v = m;
    repaint();
}

