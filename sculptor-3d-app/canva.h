#ifndef CANVA_H
#define CANVA_H

#include <QWidget>
#include <vector>
#include <QVector>
#include "sculptor.h"

/**
 *  @brief a classe canva desenha o grid na tela
 *  @details a classe é responsavel por detectar o click do usuário no grid e emitir um sinal com a posição x e y do click
 */

using namespace std;

class Canva : public QWidget
{
    Q_OBJECT

private:

    int nl, nc;
    vector <vector<Voxel>> v;
    int gridV, gridH;
    int tamCel;
    int widthScreen, heightScreen;
    int widthCel, heightCel;
    bool pressed;

public:
    /**
     *  @brief construtor do qwidget denominado canva
     */
    explicit Canva(QWidget *parent = nullptr);

    /**
     *  @brief método de evento de paint event
     */
    void paintEvent(QPaintEvent *e);

    /**
     *  @brief método que define o valor das variáveis de número de linhas e colinas
     *  @param nl é o número de linhas
     *  @param nc é o número de colunas
     */
    void setSize(int _nl, int _nc);

    /**
     *  @brief método que define o evento de mouse press event responsável por pegar o clik do mouse
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     *  @brief método que define o evento de mouse move event responsável por pegar o movimento do mouse
     */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     *  @brief método que define o evento de mouse release event responsável por pegar a ação de soltar o mouse
     */
    void mouseReleaseEvent(QMouseEvent *event);

    /**
     *  @brief método que imprime a figura no grid
     */
    void imprimirFigura(vector <vector <Voxel> > m);

signals:
    /**
     *  @brief sinal que envia a posição x e y do click no grid
     */
    void enviaPosicao(int,int);


};

#endif // CANVA_H
