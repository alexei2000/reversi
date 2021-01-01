#ifndef CONVERSOR_H
#define CONVERSOR_H

#include "../coordenadas/Coordenadas.hpp"

class Conversor{
    private:
        int margen,escala;
        Coordenadas posicion;

    public:
        Conversor();
        void setPosicion(int x, int y);
        Coordenadas getPosicion();
        void decodificar();
        void codificar();
};

Conversor::Conversor(){
    margen=35;
    escala=70;
}
void Conversor::setPosicion(int x, int y){
    posicion.x=x;
    posicion.y=y;
}
Coordenadas Conversor::getPosicion(){
    return posicion;
}
void Conversor::decodificar(){
    posicion.x = posicion.x*escala + margen;
    posicion.y = posicion.y*escala + margen;
}
void Conversor::codificar(){
    posicion.x = (posicion.x-margen)/escala;
    posicion.y = (posicion.y-margen)/escala;
}

#endif