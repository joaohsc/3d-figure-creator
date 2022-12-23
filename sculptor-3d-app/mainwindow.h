#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "sculptor.h"

#include <QActionGroup>

/**
 *  @brief a classe mainwindow representa a tela principal do programa
 *  @details a main window é a interface onde o usuário pode construir uma figura 3d por meio de pontos, cubos, elipses e elipsoides
 */

enum{
    sphere, voxel, box, ellipsoid, cVoxel, cSphere, cBox, cEllipsoid
};

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int dimX, dimY, dimZ;
    int r, g, b;
    int figuraAtual;
    void updateColor();
    Sculptor *escultor;
    QActionGroup *actionGroup;

public slots:
    /**
     *  @brief slot que fecha a interface
     */
    void quit();
    /**
     *  @brief slot que define o valor da váriavel r que é a cor vermelha no formato rgb
     */
    void setRed(int _r);

    /**
     *  @brief slot que define o valor da váriavel g que é a cor verde no formato rgb
     */
    void setGreen(int _g);

    /**
     *  @brief slot que define o valor da váriavel b que é a cor azul no formato rgb
     */
    void setBlue(int _b);


    /**
     *  @brief slot que únifica os métodos do sculptor e desenha a figura na tela
     */
    void draw3d(int, int);

    /**
     *  @brief slot atualiza os eixos de x y nos componetes de LCD
     */
    void updateAxis(int, int);

    /**
     *  @brief slot responsável por apresentar o dialog que define as dimensões do grid na tela, além disso o slot atualiza
     *  o objeto do sculptor com as dimensões registrads pelo usuário
     */
    void apresentaDialogo();

private slots:
    /**
     *  @brief slot que salva o objeto no formato .off
     */
    void save();

    /**
     *  @brief o slot é responsável por adicionar o enumerador voxel na variavel figuraAtual, o valor identifica que o método putVoxel será implementado
     */
    void putVoxel();
    /**
     *  @brief o slot é responsável por adicionar o enumerador box na variavel figuraAtual, o valor identifica que o método putBox será implementado
     */
    void putBox();
    /**
     *  @brief o slot é responsável por adicionar o enumerador sphere na variavel figuraAtual, o valor identifica que o método putSphere será implementado
     */
    void putSphere();
    /**
     *  @brief o slot é responsável por adicionar o enumerador ellipsoide na variavel figuraAtual, o valor identifica que o método putEllipsoide será implementado
     */
    void putEllipsoid();
    /**
     *  @brief o slot é responsável por adicionar o enumerador cVoxel na variavel figuraAtual, o valor identifica que o método cutVoxel será implementado
     */
    void cutVoxel();
    /**
     *  @brief o slot é responsável por adicionar o enumerador cBox na variavel figuraAtual, o valor identifica que o método cutBox será implementado
     */
    void cutBox();
    /**
     *  @brief o slot é responsável por adicionar o enumerador cSphere na variavel figuraAtual, o valor identifica que o método cutSphere será implementado
     */
    void cutSphere();
    /**
     *  @brief o slot é responsável por adicionar o enumerador do cEllipsoide na variavel figuraAtual, o valor identifica que o método cutEllipsoide será implementado
     */
    void cutEllipsoid();
    /**
     *  @brief o slot é responsável por definir o valor do plano z desejado pelo usuário
     */
    void set_Axis_z(int);
    /**
     *  @brief o slot é responsável por limpar todos os voxels ativos do grid
     */
    void limpar_voxel();
    /**
     *  @brief o slot define um limite no valor mínimo e máximo dos sliders para não serem maiores que o grid atual
     */
    void set_sliders_numbers();

};
#endif // MAINWINDOW_H
