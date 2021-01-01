#ifndef TABLERO_H
#define TABLERO_H

#include <string>
#include "../coordenadas/Coordenadas.hpp"
#include "../recorridos/recorrido.hpp"
#include "../recorridos/actualizacion.hpp"

using namespace std;

class Tablero{
    private:
        int posicionesDeFichas[8][8];
        int jugadasPosibles[8][8];
        string jugador[2];
        int ganador;
        int length;
        int turno;
        int contadorDeJugadasNulas;
        int opcion;
        bool finDelJuego;
        void inicializarPosicionesDeFichas();
        void actualizarPosicionesDeFichas(Coordenadas jugada);
        void crearJugadasPosibles();
        void cambiarTurno();
        void contabilizarJugadaNula();
        void establecerGanador();

    public:
        Tablero();
        void realizarJugada(Coordenadas jugada);
        bool getFinDelJuego();
        bool esUnaJugadaPosible(Coordenadas jugada);
        void setOpcion(int op);
        int getLength();
        int getPosicionFicha(int x, int y);
        int getJugadaPosible(int x, int y);
        int getTurno();
        int getGanador();
        int getContadorDeJugadasNulas();
        string getJugador(int i);

};

Tablero::Tablero(){
    length=8;
    turno=-1;
    contadorDeJugadasNulas=0;
    finDelJuego=false;
    inicializarPosicionesDeFichas();
    crearJugadasPosibles();
}

void Tablero::setOpcion(int op){
    switch (op){
        case 0: jugador[0]="Player1"; jugador[1]="Player2"; break;
        case 1: jugador[0]="Player1"; jugador[1]="Bot"; break;
        case 2: jugador[0]="Bot1"; jugador[1]="Bot2"; break;
    }
    opcion=op;
}

void Tablero::realizarJugada(Coordenadas jugada){
    if(esUnaJugadaPosible(jugada)){
        actualizarPosicionesDeFichas(jugada);
        cambiarTurno();
        crearJugadasPosibles();
        contabilizarJugadaNula();
    }
}

void Tablero::actualizarPosicionesDeFichas(Coordenadas jugada){
    actualizacion::actualizacionIndividual(posicionesDeFichas,jugada,turno);
}

void Tablero::inicializarPosicionesDeFichas(){
    for(int y=0; y<length; y++){
        for(int x=0; x<length; x++){
            posicionesDeFichas[y][x]=0;
        }
    }

    posicionesDeFichas[4][3]=-1;
    posicionesDeFichas[3][4]=-1;
    posicionesDeFichas[3][3]=1;
    posicionesDeFichas[4][4]=1;
}

bool Tablero::esUnaJugadaPosible(Coordenadas jugada){
    if(jugadasPosibles[jugada.y][jugada.x]==1){
        return true;
    }
    else{
        return false;
    }
}

void Tablero::crearJugadasPosibles(){
    recorrido::recorridoPrincipal(posicionesDeFichas,jugadasPosibles,turno);
}

void Tablero::cambiarTurno(){
    if(turno==-1){
        turno=1;
    }
    else{
        turno=-1;
    }
}

void Tablero::contabilizarJugadaNula(){

    bool band=false;
    for(int y=0; y<length && !band; y++){
        for(int x=0; x<length && !band; x++){
            if(jugadasPosibles[y][x]==1){
                band=true;
                contadorDeJugadasNulas=0;
            }
        }
    }
    if(!band){
        contadorDeJugadasNulas++;
        if(contadorDeJugadasNulas<2){
            cambiarTurno();
            crearJugadasPosibles();
            contabilizarJugadaNula();
        }
        else{
            finDelJuego=true;
            establecerGanador();
        }
    }
}

void Tablero::establecerGanador(){
    int cont1=0,cont2=0;
    for(int y=0;y<length;y++){
        for(int x=0;x<length;x++){
            if(posicionesDeFichas[y][x]==-1){
                cont1++;
            }
            if(posicionesDeFichas[y][x]==1){
                cont2++;
            }
        }
    }

    if(cont1>cont2){
        ganador=0;
    }
    else if(cont2>cont1){
        ganador=1;
    }
    else if(cont1==cont2){
        ganador=2;
    }

}

string Tablero::getJugador(int i){
    return jugador[i];
}

int Tablero::getContadorDeJugadasNulas(){
    return contadorDeJugadasNulas;
}

int Tablero::getGanador(){
    return ganador;
}

int Tablero::getTurno(){
    return turno;
}

bool Tablero::getFinDelJuego(){
    return finDelJuego;
}

int Tablero::getLength(){
    return length;
}

int Tablero::getPosicionFicha(int x, int y){
    return posicionesDeFichas[y][x];
}

int Tablero::getJugadaPosible(int x, int y){
    return jugadasPosibles[y][x];
}



#endif