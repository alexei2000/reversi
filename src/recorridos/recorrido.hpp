#ifndef RECORRIDO_H
#define RECORRIDO_H


#include <iostream>
#include <cstdio>
#include "../coordenadas/Coordenadas.hpp"

namespace recorrido {



	void recorridoPrincipal(int posicionesDeFichas[8][8], int jugadasPosibles[8][8], int turno);
	int recorridoIndividual(int posicionesDeFichas[8][8], Coordenadas coord, int turno);
	int recorridoDiagonal(int posicionesDeFichas[8][8], Coordenadas coBase, Coordenadas coAdyacente, int turno);
	int recorridoLineal(int posicionesDeFichas[8][8], Coordenadas coBase, Coordenadas coAdyacente, int turno);



	void recorridoPrincipal(int posicionesDeFichas[8][8], int jugadasPosibles[8][8], int turno) {


			Coordenadas tmpCoord;


			for(tmpCoord.x = 0; tmpCoord.x < 8; tmpCoord.x++) {

				for(tmpCoord.y = 0; tmpCoord.y < 8; tmpCoord.y++) {

					jugadasPosibles[tmpCoord.y][tmpCoord.x] = 0;

				}

			}


			for(tmpCoord.x = 0; tmpCoord.x < 8; tmpCoord.x++) {

				for(tmpCoord.y = 0; tmpCoord.y < 8; tmpCoord.y++) {

					if (posicionesDeFichas[tmpCoord.y][tmpCoord.x] == 0) {

						if(recorridoIndividual(posicionesDeFichas, tmpCoord, turno)) {

							jugadasPosibles[tmpCoord.y][tmpCoord.x] = 1;

						} else {

							continue;

						}

					}


				}

			}

		}



	int recorridoIndividual(int posicionesDeFichas[8][8], Coordenadas coBase, int turno) {

	    int band = 0;
	    Coordenadas coAdyacente;
	 
	    for(coAdyacente.x = coBase.x - 1; coAdyacente.x <= coBase.x + 1 && band == 0; coAdyacente.x++) {

	        for(coAdyacente.y = coBase.y - 1; coAdyacente.y <= coBase.y + 1 && band == 0; coAdyacente.y++) {

	            if( (coAdyacente.x >= 0 && coAdyacente.x < 7) && (coAdyacente.y >= 0 && coAdyacente.y < 7) ) { 
	 
	                if (posicionesDeFichas[coAdyacente.y][coAdyacente.x] == turno * -1) {

	                    

	                    if(	(coAdyacente.x < coBase.x && coAdyacente.y < coBase.y) ||
	                    	(coAdyacente.x > coBase.x && coAdyacente.y < coBase.y) ||
	                    	(coAdyacente.x < coBase.x && coAdyacente.y > coBase.y) ||
	                    	(coAdyacente.x > coBase.x && coAdyacente.y > coBase.y)) {

	                    	recorridoDiagonal(posicionesDeFichas, coBase, coAdyacente, turno) ? band = 1 : band = 0;


	                    } else if(	(coAdyacente.x == coBase.x && coAdyacente.y < coBase.y) ||
	                    			(coAdyacente.x == coBase.x && coAdyacente.y > coBase.y) ||
	                    			(coAdyacente.x < coBase.x && coAdyacente.y == coBase.y) ||
	                    			(coAdyacente.x > coBase.x && coAdyacente.y == coBase.y)) {

	                    	recorridoLineal(posicionesDeFichas, coBase, coAdyacente, turno) ? band = 1 : band = 0;



	                    }

	                }

	            }

	        }

	    }


	return (band);
	}



	int recorridoDiagonal(int posicionesDeFichas[8][8], Coordenadas coBase, Coordenadas coAdyacente, int turno) {

		int b, band;
		Coordenadas tmpCoord;


		if( (coAdyacente.x >= 0 && coAdyacente.x <= 7) && (coAdyacente.y >= 0 && coAdyacente.y <= 7) )  {

			//CASO 1 SUP DER

			if(coAdyacente.x < coBase.x && coAdyacente.y < coBase.y) {

				b = coBase.x - coBase.y;

				for(tmpCoord.x = coAdyacente.x-1, tmpCoord.y = -(b - tmpCoord.x), band = 0;
					tmpCoord.x >= 0 && posicionesDeFichas[tmpCoord.y][tmpCoord.x] != 0 && band == 0;
					tmpCoord.x--, tmpCoord.y = -(b - tmpCoord.x)) {


					if(posicionesDeFichas[tmpCoord.y][tmpCoord.x] != turno) {

						band = 0;

					} else {

						band = 1;

					}

				}


			//CASO 2 SUP IZQ

			} else if(coAdyacente.x > coBase.x && coAdyacente.y < coBase.y) {

				b = -coBase.x - coBase.y;

				for(tmpCoord.x = coAdyacente.x+1, tmpCoord.y = -(tmpCoord.x + b), band = 0;
					tmpCoord.x <= 7 && posicionesDeFichas[tmpCoord.y][tmpCoord.x] != 0 && band == 0;
					tmpCoord.x++, tmpCoord.y = -(tmpCoord.x + b)) {


					if(posicionesDeFichas[tmpCoord.y][tmpCoord.x] != turno) {

						band = 0;

					} else {

						band = 1;
					}

				}

			//CASO 3 INF DER


			} else if(coAdyacente.x < coBase.x && coAdyacente.y > coBase.y) {

				b = (-coBase.y) - coBase.x;

				for(tmpCoord.x = coAdyacente.x-1, tmpCoord.y = -(tmpCoord.x + b), band = 0;
					tmpCoord.x >= 0 && posicionesDeFichas[tmpCoord.y][tmpCoord.x] != 0 && band == 0;
					tmpCoord.x--, tmpCoord.y = -(tmpCoord.x + b)) {



					if(posicionesDeFichas[tmpCoord.y][tmpCoord.x] != turno) {

						band = 0;

					} else {

						band = 1;
					}

				}

			//CASO 4 INF IZQ


			} else if(coAdyacente.x > coBase.x && coAdyacente.y > coBase.y) {

				b = coBase.x - coBase.y;


				for(tmpCoord.x = coAdyacente.x+1, tmpCoord.y = -(b - tmpCoord.x), band = 0;
					tmpCoord.x <= 7 && posicionesDeFichas[tmpCoord.y][tmpCoord.x] != 0 && band == 0;
					tmpCoord.x++, tmpCoord.y = -(b - tmpCoord.x)) {


					if(posicionesDeFichas[tmpCoord.y][tmpCoord.x] != turno) {

						band = 0;

					} else {

						band = 1;
					}
					
				}


			}


			return band;

		} else {

			return 0;

		}

	}



	int recorridoLineal(int posicionesDeFichas[8][8], Coordenadas coBase, Coordenadas coAdyacente, int turno) {

		int band;
		Coordenadas tmpCoord;


		if( (coAdyacente.x >= 0 && coAdyacente.x <= 7) && (coAdyacente.y >= 0 && coAdyacente.y <= 7) )  {


			//CASO 1 VERTICAL SUP

			if(coAdyacente.x == coBase. x && coAdyacente.y < coBase. y) {


				for(tmpCoord.x = coAdyacente.x, tmpCoord.y = coAdyacente.y - 1, band = 0;
					tmpCoord.y >= 0 && posicionesDeFichas[tmpCoord.y][tmpCoord.x] != 0 && band == 0;
					tmpCoord.y--) {


					if(posicionesDeFichas[tmpCoord.y][tmpCoord.x] != turno) {

						band = 0;

					} else {

						band = 1;

					}

				}


			//CASO 2 VERTICAL INF

			} else if(coAdyacente.x == coBase. x && coAdyacente.y > coBase. y) {


				for(tmpCoord.x = coAdyacente.x, tmpCoord.y = coAdyacente.y + 1, band = 0;
					tmpCoord.y <= 7 && posicionesDeFichas[tmpCoord.y][tmpCoord.x] != 0 && band == 0;
					tmpCoord.y++) {


					if(posicionesDeFichas[tmpCoord.y][tmpCoord.x] != turno) {

						band = 0;

					} else {

						band = 1;
					}

				}

			//CASO 3 HORIZONTAL IZQ


			} else if(coAdyacente.x < coBase. x && coAdyacente.y == coBase. y) {


				for(tmpCoord.x = coAdyacente.x - 1, tmpCoord.y = coAdyacente.y, band = 0;
					tmpCoord.x >= 0 && posicionesDeFichas[tmpCoord.y][tmpCoord.x] != 0 && band == 0;
					tmpCoord.x--) {


					if(posicionesDeFichas[tmpCoord.y][tmpCoord.x] != turno) {

						band = 0;

					} else {

						band = 1;
					}

				}

			//CASO 4 HORIZONTAL DER


			} else if(coAdyacente.x > coBase. x && coAdyacente.y == coBase. y) {


				for(tmpCoord.x = coAdyacente.x + 1, tmpCoord.y = coAdyacente.y, band = 0;
					tmpCoord.x <= 7 && posicionesDeFichas[tmpCoord.y][tmpCoord.x] != 0 && band == 0;
					tmpCoord.x++) {


					if(posicionesDeFichas[tmpCoord.y][tmpCoord.x] != turno) {

						band = 0;

					} else {

						band = 1;
					}
					
				}


			}


			return band;

		} else {

			return 0;

		}


	}



}

#endif