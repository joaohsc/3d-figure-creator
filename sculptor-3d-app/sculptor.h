#ifndef SCULPTOR_H
#define SCULPTOR_H

#include "voxel.h"
#include <vector>
#include <string>

/**
 *  @brief a classe sculptor monta os voxels em uma matriz 3d
 *  @details na classe definimos os métodos utilizados para configurar a forma e cor da figura 3d
 */

using namespace std;

class Sculptor {
private:
    Voxel ***v; // 3D matrix
    int nx,ny,nz; // Dimensions
    float r,g,b,a; // Current drawing color
public:
    /**
     *  @brief o construtor faz a alocação dinâmica do "v"
     *  @param nx representa o eixo X
     *  @param ny representa o eixo Y
     *  @param nz representa o eixo Z
     */
    Sculptor(int _nx, int _ny, int _nz);
    /**
     *  @brief o destrutor libera espaço alocado
     */
    ~Sculptor();
    /**
     *  @brief setColor é o método para definir qual a cor do voxel no formato RGBA
     *  @param r representa a cor vermelho no formato RGBA
     *  @param g representa a cor verde no formato RGBA
     *  @param b representa a cor azul no formato RGBA
     *  @param a representa a transparência no formato RGBA
     */
    void setColor(float r, float g, float b, float a);
    /**
     *  @brief putVoxel adiciona um voxel nos eixos configurados
     *  @param x representa o eixo X
     *  @param y representa o eixo Y
     *  @param z representa o eixo Z
     */
    void putVoxel(int x, int y, int z);
    /**
     *  @brief cutVoxel remove um voxel nos eixos configurados
     *  @param x representa o eixo X
     *  @param y representa o eixo Y
     *  @param z representa o eixo Z
     */
    void cutVoxel(int x, int y, int z);
    /**
     *  @brief putBox adiciona voxels nos eixos configurados no formato de um cubo(box)
     *  @param x0 representa o eixo x inicial
     *  @param x1 representa o eixo x final
     *  @param y0 representa o eixo y inicial
     *  @param y1 representa o eixo y final
     *  @param z0 representa o eixo z inicial
     *  @param z1 representa o eixo z final
     */
    void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
    /**
     *  @brief cutBox remove voxels nos eixos configurados no formato de um cubo(box)
     *  @param x0 representa o eixo x inicial
     *  @param x1 representa o eixo x final
     *  @param y0 representa o eixo y inicial
     *  @param y1 representa o eixo y final
     *  @param z0 representa o eixo z inicial
     *  @param z1 representa o eixo z final
     */
    void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
    /**
     *  @brief putSphere adiciona voxels nos eixos configurados no formato de uma esfera
     *  @param xcenter representa centro da esfera no eixo x
     *  @param ycenter representa centro da esfera no eixo y
     *  @param zcenter representa centro da esfera no eixo z
     *  @param radius é presenta o raio da esfera
     */
    void putSphere(int xcenter, int ycenter, int zcenter, int radius);
    /**
     *  @brief cutSphere remove voxels nos eixos configurados no formato de uma esfera
     *  @param xcenter representa centro da esfera no eixo x
     *  @param ycenter representa centro da esfera no eixo y
     *  @param zcenter representa centro da esfera no eixo z
     *  @param radius é presenta o raio da esfera
     */
    void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
    /**
     *  @brief putEllipsoid adiciona voxels nos eixos configurados no formato de uma elipsoide
     *  @param xcenter representa centro do elipsoide no eixo x
     *  @param ycenter representa centro do elipsoide no eixo y
     *  @param zcenter representa centro do elipsoide no eixo z
     *  @param rx representa o raio da esfera no eixo x
     *  @param ry representa o raio da esfera no eixo y
     *  @param rz representa o raio da esfera no eixo z
     */
    void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    /**
     *  @brief cutEllipsoid remove voxels nos eixos configurados no formato de uma elipsoide
     *  @param xcenter representa centro do elipsoide no eixo x
     *  @param ycenter representa centro do elipsoide no eixo y
     *  @param zcenter representa centro do elipsoide no eixo z
     *  @param rx representa o raio da esfera no eixo x
     *  @param ry representa o raio da esfera no eixo y
     *  @param rz representa o raio da esfera no eixo z
     */
    void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    /**
     *  @brief writeOFF é um método que cria/edita um documento em formato .OFF
     */
    void writeOFF(const char* filename);

    void limparVoxel();

    vector< vector<Voxel> > getPlano(int i);

};

#endif // SCULPTOR_H
