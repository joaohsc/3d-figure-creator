#include <iostream>
#include <iomanip>
#include <fstream>
#include "sculptor.h"

Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
    nx = _nx;
    ny = _ny;
    nz = _nz;

    v = new Voxel**[nx];

    for (int i = 0; i < nx; i++)
    {
        v[i] = new Voxel*[ny];
        for (int j = 0; j < ny; j++) {
            v[i][j] = new Voxel[nz];
        }
    }


    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                v[i][j][k].isOn=false;
            }
        }
    }

}

Sculptor::~Sculptor()
{
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            delete[] v[i][j];
        }
        delete[] v[i];
    }

    delete[] v;
    nx = 0;
    ny = 0;
    nz = 0;
}

void Sculptor::setColor(float r, float g, float b, float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void Sculptor::putVoxel(int x, int y, int z)
{
    v[x][y][z].isOn = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
}

void Sculptor::cutVoxel(int x, int y, int z)
{
    v[x][y][z].isOn =false;
}

void Sculptor:: putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for (int i = x0; i <= x1; i++)
    {
        for (int j = y0; j <= y1; j++)
        {
            for (int k = z0; k <= z1; k++)
            {
                putVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for (int i = x0; i <= x1; i++)
    {
        for (int j = y0; j <= y1; j++)
        {
            for (int k = z0; k <= z1; k++)
            {
                cutVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius)
{


    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                int p1= i - xcenter;
                int p2= j - ycenter;
                int p3= k - zcenter;
                float equation = ((p1*p1) + (p2*p2) + (p3*p3));

                if (equation <= radius*radius)
                {
                    putVoxel(i,j,k);
                }
            }
        }
    }
}
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                int p1= i - xcenter;
                int p2= j - ycenter;
                int p3= k - zcenter;

                float equation = ((p1*p1) + (p2*p2) + (p3*p3));

                if (equation <= radius*radius)
                {
                    cutVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    for (int i = 0; i <= nx; i++)
    {
        for (int j = 0; j <= ny; j++)
        {
            for (int k = 0; k <= nz; k++)
            {

                int p1= i - xcenter;
                int p2= j - ycenter;
                int p3= k - zcenter;

                float conta = ((float)(p1*p1)/(rx*rx)) + ((float)(p2*p2)/(ry*ry)) + ((float)(p3*p3) / (rz*rz));
                if (conta <= 1)
                {
                    putVoxel(i,j,k);
                }
            }
        }
    }
}


void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    for (int i = 0; i <= nx; i++)
    {
        for (int j = 0; j <= ny; j++)
        {
            for (int k = 0; k <= nz; k++)
            {
                int p1= i - xcenter;
                int p2= j - ycenter;
                int p3= k - zcenter;

                float conta = ((float)(p1*p1)/(rx*rx)) + ((float)(p2*p2)/(ry*ry)) + ((float)(p3*p3) / (rz*rz));
                if (conta <= 1)
                {
                    cutVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::writeOFF(const char* filename)
{
    std::ofstream file;

    int nv = 0;
    int nf = 0;


    file.open(filename);

    if(!file.is_open()){
        exit(1);
    }

    file << "OFF" << std::endl;

    for (int px = 0; px < nx; px++)
    {
        for (int py = 0; py < ny; py++)
        {
            for (int pz = 0; pz < nz; pz++)
            {
                if (v[px][py][pz].isOn)
                {
                    nv += 8;
                    nf += 6;
                }
            }
        }
    }

    file << nv << ' ' << nf << ' ' << 0 << std::endl;

    file << std::fixed;
    file << std::setprecision(2);

    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                if (v[i][j][k].isOn)
                {
                    file << (i - 0.5) << ' ' << (j + 0.5) << ' ' << (k - 0.5) << std::endl;
                    file << (i - 0.5) << ' ' << (j - 0.5) << ' ' << (k - 0.5) << std::endl;
                    file << (i + 0.5) << ' ' << (j - 0.5) << ' ' << (k - 0.5) << std::endl;
                    file << (i + 0.5) << ' ' << (j + 0.5) << ' ' << (k - 0.5) << std::endl;
                    file << (i - 0.5) << ' ' << (j + 0.5) << ' ' << (k + 0.5) << std::endl;
                    file << (i - 0.5) << ' ' << (j - 0.5) << ' ' << (k + 0.5) << std::endl;
                    file << (i + 0.5) << ' ' << (j - 0.5) << ' ' << (k + 0.5) << std::endl;
                    file << (i + 0.5) << ' ' << (j + 0.5) << ' ' << (k + 0.5) << std::endl;
                }
            }
        }
    }

    int count = 0;
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                if (v[i][j][k].isOn)
                {
                    int red = v[i][j][k].r;
                    int green = v[i][j][k].g;
                    int blue = v[i][j][k].b;
                    int alpha = v[i][j][k].a;

                    file << 4 << ' ' << count + 0 << ' ' << count + 3 << ' ' << count + 2 << ' ' << count + 1 << ' ';
                    file << red << ' ' << green << ' ' << blue << ' ' << alpha<< std::endl;

                    file << 4 << ' ' << count + 4 << ' ' << count + 5 << ' ' << count + 6 << ' ' << count + 7 << ' ';
                    file << red << ' ' << green << ' ' << blue << ' ' << alpha << std::endl;

                    file << 4 << ' ' << count + 0 << ' ' << count + 1 << ' ' << count + 5 << ' ' << count + 4 << ' ';
                    file << red << ' ' << green << ' ' << blue << ' ' << alpha << std::endl;

                    file << 4 << ' ' << count + 0 << ' ' << count + 4 << ' ' << count + 7 << ' ' << count + 3 << ' ';
                    file << red << ' ' << green << ' ' << blue << ' ' << alpha << std::endl;

                    file << 4 << ' ' << count + 3 << ' ' << count + 7 << ' ' << count + 6 << ' ' << count + 2 << ' ';
                    file << red << ' ' << green << ' ' << blue << ' ' << alpha << std::endl;

                    file << 4 << ' ' << count + 1 << ' ' << count + 2 << ' ' << count + 6 << ' ' << count + 5 << ' ';
                    file << red << ' ' << green << ' ' << blue << ' ' << alpha << std::endl;



                    count += 8;
                }
            }
        }
    }

    file.close();
    std::cout <<"Arquivo criado!" << std::endl;
}

void Sculptor::limparVoxel()
{
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                v[i][j][k].isOn=false;
            }
        }
    }
}

vector<vector<Voxel> > Sculptor::getPlano(int i)
{
    vector< vector<Voxel> > retorno;
    vector<Voxel> linha;
    linha.resize(ny);
    for(int x=0; x<nx; x++){
        for(int y=0; y<ny; y++){
            linha[y].r = v[x][y][i].r;
            linha[y].g = v[x][y][i].g;
            linha[y].b = v[x][y][i].b;
            linha[y].isOn = v[x][y][i].isOn;
        }
        retorno.push_back(linha);
    }
    return retorno;
}
