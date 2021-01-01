#ifndef BOT_H
#define BOT_H

#include "../coordenadas/Coordenadas.hpp"
#include "../tablero/Tablero.hpp"
#include <iostream> 

class BotPlayer{

	private:
        Tablero *tablero;
		Coordenadas mejorJugada;
		int length;
		int turno;
        int contadorDeMejorJugada;
		int contadorDeFichaActual;

        void setTurno();

        void recorridoDiagonalSuperiorIzquierdo(Coordenadas posicionCentral);
        void recorridoDiagonalSuperiorDerecho(Coordenadas posicionCentral);

        void recorridoDiagonalInferiorIzquierdo(Coordenadas posicionCentral);
        void recorridoDiagonalInferiorDerecho(Coordenadas posicionCentral);

        void recorridoVerticalSuperior(Coordenadas posicionCentral);
        void recorridoVerticalInferior(Coordenadas posicionCentral);

        void recorridoHorizontalIzquierdo(Coordenadas posicionCentral);
        void recorridoHorizontalDerecho(Coordenadas posicionCentral);


	public:
		BotPlayer(Tablero *tab);
        Coordenadas getMejorJugada();
		void crearMejorJugada();
};

BotPlayer::BotPlayer(Tablero *tab){
	length=8;
    tablero = tab;
}

void BotPlayer::setTurno(){
    turno=tablero->getTurno();
}

Coordenadas BotPlayer::getMejorJugada(){
    return mejorJugada;
}

void BotPlayer::crearMejorJugada(){
    Coordenadas posicion;
    mejorJugada.x=0;
    mejorJugada.y=0;
    contadorDeFichaActual=0;
    contadorDeMejorJugada=0;
    setTurno();

    for(int y=0;y<length;y++){
        for(int x=0; x<length; x++){
            if(tablero->getJugadaPosible(x,y)==1){

                posicion.x=x;
                posicion.y=y;

                recorridoDiagonalSuperiorIzquierdo(posicion);
                recorridoDiagonalSuperiorDerecho(posicion);

                recorridoDiagonalInferiorIzquierdo(posicion);
                recorridoDiagonalInferiorDerecho(posicion);

                recorridoVerticalSuperior(posicion);
                recorridoVerticalInferior(posicion);


                recorridoHorizontalIzquierdo(posicion);
                recorridoHorizontalDerecho(posicion);

                if(contadorDeFichaActual>contadorDeMejorJugada){
                    contadorDeMejorJugada=contadorDeFichaActual;
                    mejorJugada=posicion;
                }

                contadorDeFichaActual=0;

            }
        }
    }

}

void BotPlayer::recorridoDiagonalSuperiorIzquierdo(Coordenadas posicionCentral){
    for(int y=posicionCentral.y-1, x=posicionCentral.x-1; y>=0 && x>=0 ;y--,x--){
        if(tablero->getPosicionFicha(x,y) == turno*(-1)){
            contadorDeFichaActual++;
        }
        else{
            break;
        }
    }
}

void BotPlayer::recorridoDiagonalSuperiorDerecho(Coordenadas posicionCentral){
    for(int y=posicionCentral.y-1, x=posicionCentral.x+1; y>=0 && x<length ;y--,x++){
        if(tablero->getPosicionFicha(x,y) == turno*(-1)){
            contadorDeFichaActual++;
        }
        else{
            break;
        }
    }
}

void BotPlayer::recorridoDiagonalInferiorIzquierdo(Coordenadas posicionCentral){
    for(int y=posicionCentral.y+1, x=posicionCentral.x-1; y<length && x>=0 ;y++,x--){
        if(tablero->getPosicionFicha(x,y) == turno*(-1)){
            contadorDeFichaActual++;
        }
        else{
            break;
        }
    }
}

void BotPlayer::recorridoDiagonalInferiorDerecho(Coordenadas posicionCentral){
    for(int y=posicionCentral.y+1, x=posicionCentral.x+1; y<length && x<length ;y++,x++){
        if(tablero->getPosicionFicha(x,y) == turno*(-1)){
            contadorDeFichaActual++;
        }
        else{
            break;
        }
    }
}

void BotPlayer::recorridoVerticalSuperior(Coordenadas posicionCentral){
    for(int y=posicionCentral.y-1, x=posicionCentral.x; y>=0 ;y--){
        if(tablero->getPosicionFicha(x,y) == turno*(-1)){
            contadorDeFichaActual++;
        }
        else{
            break;
        }
    }
}

void BotPlayer::recorridoVerticalInferior(Coordenadas posicionCentral){
    for(int y=posicionCentral.y+1, x=posicionCentral.x; y<length ;y++){
        if(tablero->getPosicionFicha(x,y) == turno*(-1)){
            contadorDeFichaActual++;
        }
        else{
            break;
        }
    }
}

void BotPlayer::recorridoHorizontalIzquierdo(Coordenadas posicionCentral){
    for(int y=posicionCentral.y, x=posicionCentral.x-1; x>=0 ;x--){
        if(tablero->getPosicionFicha(x,y) == turno*(-1)){
            contadorDeFichaActual++;
        }
        else{
            break;
        }
    }
}

void BotPlayer::recorridoHorizontalDerecho(Coordenadas posicionCentral){
    for(int y=posicionCentral.y, x=posicionCentral.x+1; x<length ;x++){
        if(tablero->getPosicionFicha(x,y) == turno*(-1)){
            contadorDeFichaActual++;
        }
        else{
            break;
        }
    }
}


#endif