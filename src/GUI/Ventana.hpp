#ifndef VENTANA_H
#define VENTANA_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "../conversor/Conversor.hpp"
#include "../tablero/Tablero.hpp"
#include "Opciones.hpp"
#include "../bot/Bot.hpp"

using namespace sf;

class Ventana{

    private:
        RenderWindow window;
        Texture tableroTexture,fichaBlancaTexture,fichaNegraTexture,jugadaPosibleTexture;
        Sprite tableroSprite,fichaBlancaSprite,fichaNegraSprite,jugadaPosibleSprite;
        Cursor cursor;
        Tablero tablero;
        Font font;
        string modo;
        BotPlayer *bot;
        int opcion;
        bool bloqueoDeEventos;
        void menuLoop();
        void gameLoop();
        void renderMenu(bool circleVisible=true, int posY=0);
        void renderTablero();
        void renderFichas();
        void renderJugadasPosibles();
        void renderMarcoDejugadores();
        void event();
        void eventWindowClose(Event e);
        void eventCursorHand(Event e);
        void eventClick(Event e);
        void eventMenu(int &pos);
        void delay(float delayTime);
        void jugadaDeBot();

    public:
        Ventana();
        void iniciar();
};

Ventana::Ventana(){

    opcion=OPCION::Menu;
    bloqueoDeEventos=true;

    window.create(VideoMode(830,630), "Reversi",Style::Titlebar | Style::Close);

    font.loadFromFile("font/Roboto-Medium.ttf");

    tableroTexture.loadFromFile("Texturas/tablero.png");
    fichaBlancaTexture.loadFromFile("Texturas/ficha blanca.png");
    fichaNegraTexture.loadFromFile("Texturas/ficha negra.png");
    jugadaPosibleTexture.loadFromFile("Texturas/jugadaPosible.png");

    tableroSprite.setTexture(tableroTexture);
    fichaBlancaSprite.setTexture(fichaBlancaTexture);
    fichaNegraSprite.setTexture(fichaNegraTexture);
    jugadaPosibleSprite.setTexture(jugadaPosibleTexture);

    tableroSprite.setPosition(0,0);
}

void Ventana::iniciar(){
    menuLoop();
    gameLoop();
}

void Ventana::menuLoop(){
    Clock clock;
    float timer=0;
    float time;
    int posY=0;
    bool circleVisible=true;

    while(window.isOpen() && opcion==OPCION::Menu){
        time=clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        if(timer>=0.3){
            circleVisible=!circleVisible;
            renderMenu(circleVisible,posY);
            timer=0;
        }
        eventMenu(posY);
    }
    if(opcion==0){
        modo="Player vs Player";
    }
    else if(opcion==1){
        modo="Player vs Bot";
        bot = new BotPlayer(&tablero);
    }
    else if(opcion==2){
        modo="Bot vs Bot";
        bot = new BotPlayer(&tablero);
    }
    tablero.setOpcion(opcion);
}

void Ventana::gameLoop(){

    renderTablero();
    while(window.isOpen()){
        if(opcion==OPCION::JugadorVsJugador || opcion==OPCION::JugadorVsBot){
            event();
        }
        else if(opcion==OPCION::BotVsBot){
            jugadaDeBot();
            jugadaDeBot();
            event();
        }
    }
}

void Ventana::renderMarcoDejugadores(){
    RectangleShape marco(Vector2f(198,626));
    marco.setPosition(630,2);
    marco.setFillColor(Color(13,31,8,255));
    marco.setOutlineColor(Color(7,16,4,255));
    marco.setOutlineThickness(2);

    RectangleShape turnoMarco(Vector2f(140,140));
    turnoMarco.setPosition(660,290);
    turnoMarco.setFillColor(Color(24,56,15,255));
    turnoMarco.setOutlineColor(Color(7,16,4,255));
    turnoMarco.setOutlineThickness(2);

    Text modoText(modo,font,20);
    modoText.setStyle(sf::Text::Regular);
    modoText.setFillColor(Color::White);
    modoText.setPosition(658,25);

    Text turnoText("Turno:",font,20);
    turnoText.setStyle(sf::Text::Regular);
    turnoText.setFillColor(Color::White);
    turnoText.setPosition(695,150);

    Text jugadorText;
    jugadorText.setFont(font);
    jugadorText.setCharacterSize(15);
    jugadorText.setStyle(sf::Text::Regular);
    jugadorText.setFillColor(Color::White);
    jugadorText.setPosition(700,250);


    window.draw(marco);
    window.draw(turnoMarco);
    window.draw(modoText);
    window.draw(turnoText);

    if(tablero.getTurno()==-1){
        jugadorText.setString(tablero.getJugador(0));
        window.draw(jugadorText);

        fichaNegraSprite.setPosition(695,325);
        window.draw(fichaNegraSprite);
    }
    else{
        jugadorText.setString(tablero.getJugador(1));
        window.draw(jugadorText);

        fichaBlancaSprite.setPosition(695,325);
        window.draw(fichaBlancaSprite);
    }
    if(tablero.getFinDelJuego()){
        Text ganadorText;
        ganadorText.setFont(font);
        ganadorText.setCharacterSize(15);
        ganadorText.setStyle(sf::Text::Regular);
        ganadorText.setFillColor(Color::White);
        ganadorText.setPosition(655,500);

        if(tablero.getGanador()==0){
            ganadorText.setString("Ha ganado "+tablero.getJugador(0));
        }
        else if(tablero.getGanador()==1){
            ganadorText.setString("Ha ganado "+tablero.getJugador(1));
        }
        else if(tablero.getGanador()==2){
            ganadorText.setString("El juego es empate");
        }
        window.draw(ganadorText);
    }
}

void Ventana::renderMenu(bool circleVisible, int posY){

    Text reversiText("REVERSI",font,103);
    reversiText.setStyle(sf::Text::Regular);
    reversiText.setFillColor(Color::White);
    reversiText.setPosition(103*2,25);

    Text opcion1Text("Jugador contra Jugador",font,20);
    opcion1Text.setStyle(sf::Text::Regular);
    opcion1Text.setFillColor(Color::Green);
    opcion1Text.setPosition(103*2+50,250);

    Text opcion2Text("Jugador contra Bot",font,20);
    opcion2Text.setStyle(sf::Text::Regular);
    opcion2Text.setFillColor(Color::Green);
    opcion2Text.setPosition(103*2+50,325);

    Text opcion3Text("Bot contra Bot",font,20);
    opcion3Text.setStyle(sf::Text::Regular);
    opcion3Text.setFillColor(Color::Green);
    opcion3Text.setPosition(103*2+50,400);

    CircleShape circulo(5);
    circulo.setFillColor(Color::White);
    circulo.setPosition(103*2+20,250+(75*posY)+5);

    window.clear();
    if(circleVisible){
        window.draw(circulo);
    }
    window.draw(reversiText);
    window.draw(opcion1Text);
    window.draw(opcion2Text);
    window.draw(opcion3Text);
    window.display();

}

void Ventana::renderTablero(){
    window.clear();
    window.draw(tableroSprite);
    renderMarcoDejugadores();
    renderFichas();
    renderJugadasPosibles();
    window.display();
}

void Ventana::renderFichas(){

    Conversor conversor;

    for(int y=0; y<tablero.getLength(); y++){
        for(int x=0; x<tablero.getLength(); x++){
            if(tablero.getPosicionFicha(x,y)!=0){

                conversor.setPosicion(x,y);
                conversor.decodificar();

                Coordenadas posicion = conversor.getPosicion();

                if(tablero.getPosicionFicha(x,y)==-1){

                    fichaNegraSprite.setPosition(posicion.x,posicion.y);
                    window.draw(fichaNegraSprite);
                }
                else if(tablero.getPosicionFicha(x,y)==1){

                    fichaBlancaSprite.setPosition(posicion.x,posicion.y);
                    window.draw(fichaBlancaSprite);
                }
            }
        }
    }
}

void Ventana::renderJugadasPosibles(){

    Conversor conversor;

    for(int y=0; y<tablero.getLength(); y++){
        for(int x=0; x<tablero.getLength(); x++){

            if(tablero.getJugadaPosible(x,y)==1){

                conversor.setPosicion(x,y);
                conversor.decodificar();
                Coordenadas posicion = conversor.getPosicion();

                jugadaPosibleSprite.setPosition(posicion.x,posicion.y);
                window.draw(jugadaPosibleSprite);
            }
        }
    }
}

void Ventana::event(){

    Event e;
    while(window.pollEvent(e)){
        eventWindowClose(e);
        if(!tablero.getFinDelJuego() && !(opcion==OPCION::BotVsBot) && bloqueoDeEventos){
            eventCursorHand(e);
            eventClick(e);
        }
    }
    if(opcion==OPCION::JugadorVsBot){
        bloqueoDeEventos=true;
    }

}

void Ventana::eventMenu(int &pos){
    Event e;
    while(window.pollEvent(e)){
        if(e.type == Event::KeyPressed){
            if(e.key.code==Keyboard::Up){
                pos--;
                if(pos<0){
                    pos=2;
                }
                renderMenu(true,pos);
            }
            if(e.key.code==Keyboard::Down){
                pos++;
                if(pos>2){
                    pos=0;
                }
                renderMenu(true,pos);
            }
            if(e.key.code==Keyboard::Enter){
                opcion=pos;
            }
        }
        eventWindowClose(e);
    }
}

void Ventana::eventWindowClose(Event e){

    if(e.type == Event::Closed){
        window.close();
    }
}

void Ventana::eventCursorHand(Event e){

    Conversor conversor;

    if(e.type == Event::MouseMoved){
        if(e.mouseMove.x>=35 && e.mouseMove.x<=595 && e.mouseMove.y>=35 && e.mouseMove.y<=595){

            conversor.setPosicion(e.mouseMove.x, e.mouseMove.y);
            conversor.codificar();

            if(tablero.getJugadaPosible(conversor.getPosicion().x,conversor.getPosicion().y)==1){
                cursor.loadFromSystem(Cursor::Hand);
            }
            else{
                cursor.loadFromSystem(Cursor::Arrow);
            }
            window.setMouseCursor(cursor);
        }
    }

}

void Ventana::eventClick(Event e){

    Conversor conversor;
    if(e.type == Event::MouseButtonPressed){
        if(e.mouseButton.button==Mouse::Left){
            if((e.mouseButton.x>=35 && e.mouseButton.x<=595) && (e.mouseButton.y>=35 && e.mouseButton.y<=595)){

                conversor.setPosicion(e.mouseButton.x,e.mouseButton.y);
                conversor.codificar();
                Coordenadas posicion = conversor.getPosicion();

                if(tablero.esUnaJugadaPosible(posicion)){
                    if(!(opcion==OPCION::JugadorVsBot && tablero.getTurno()==1)){

                        tablero.realizarJugada(posicion);
                        renderTablero();

                        if(opcion==OPCION::JugadorVsBot){
                            cursor.loadFromSystem(Cursor::Arrow);
                            window.setMouseCursor(cursor);
                            bloqueoDeEventos=false;
                            jugadaDeBot();
                        }
                    }
                }
            }

        }
    }
}

void Ventana::delay(float delayTime){
    Clock clock;
    float timer=0;
    float time;
    do{
        event();
        time=clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
    }while(timer<delayTime);
}

void Ventana::jugadaDeBot(){
    delay(0.5);
    bot->crearMejorJugada();
    tablero.realizarJugada(bot->getMejorJugada());
    renderTablero();
    if(tablero.getTurno()==1 && !tablero.getFinDelJuego()){
        jugadaDeBot();
    }
}


#endif
