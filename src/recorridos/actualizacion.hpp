#ifndef ACTUALIZACION_H
#define ACTUALIZACION_H


#include <iostream>
#include <cstdio>
#include "../coordenadas/Coordenadas.hpp"
#include "recorrido.hpp"

using namespace recorrido;


namespace actualizacion {


	void actualizacionIndividual(int posicionesDeFichas[8][8], Coordenadas coBase, int turno);
	void actualizacionDiagonal(int posicionesDeFichas[8][8], Coordenadas coBase, Coordenadas coAdyacente, int turno);
	void actualizacionLineal(int posicionesDeFichas[8][8], Coordenadas coBase, Coordenadas coAdyacente, int turno);




	void actualizacionIndividual(int posicionesDeFichas[8][8], Coordenadas coBase, int turno) {

	    Coordenadas coAdyacente;
	 
	    for(coAdyacente.x = coBase.x - 1; coAdyacente.x <= coBase.x + 1; coAdyacente.x++) {

	        for(coAdyacente.y = coBase.y - 1; coAdyacente.y <= coBase.y + 1; coAdyacente.y++) {

	            if( (coAdyacente.x >= 0 && coAdyacente.x < 7) && (coAdyacente.y >= 0 && coAdyacente.y < 7) ) { 
	 
	                if (posicionesDeFichas[coAdyacente.y][coAdyacente.x] == turno * -1) {

	                    

	                    if(	(coAdyacente.x < coBase.x && coAdyacente.y < coBase.y) ||
	                    	(coAdyacente.x > coBase.x && coAdyacente.y < coBase.y) ||
	                    	(coAdyacente.x < coBase.x && coAdyacente.y > coBase.y) ||
	                    	(coAdyacente.x > coBase.x && coAdyacente.y > coBase.y)) {

	                    	
	                    	if(recorridoDiagonal(posicionesDeFichas, coBase, coAdyacente, turno)) {

	                    		actualizacionDiagonal(posicionesDeFichas, coBase, coAdyacente, turno);

	                    	}


	                    } else if(	(coAdyacente.x == coBase.x && coAdyacente.y < coBase.y) ||
	                    			(coAdyacente.x == coBase.x && coAdyacente.y > coBase.y) ||
	                    			(coAdyacente.x < coBase.x && coAdyacente.y == coBase.y) ||
	                    			(coAdyacente.x > coBase.x && coAdyacente.y == coBase.y)) {

	                    	if (recorridoLineal(posicionesDeFichas, coBase, coAdyacente, turno)) {

	                    		actualizacionLineal(posicionesDeFichas, coBase, coAdyacente, turno);

	                    	}	


	                    }

	                }

	            }

	        }

	    }

	}



	void actualizacionDiagonal(int posicionesDeFichas[8][8], Coordenadas coBase, Coordenadas coAdyacente, int turno) {

		int b, band;
		Coordenadas tmpCoord;


		if( (coAdyacente.x >= 0 && coAdyacente.x <= 7) && (coAdyacente.y >= 0 && coAdyacente.y <= 7) )  {

			posicionesDeFichas[coBase.y][coBase.x] = turno;

			//CASO 1 SUP IZQ

			if(coAdyacente.x < coBase.x && coAdyacente.y < coBase.y) {

				b = coBase.x - coBase.y;

				for(tmpCoord.x = coAdyacente.x-1, tmpCoord.y = -(b - tmpCoord.x), band = 0;
					tmpCoord.x >= 0 && posicionesDeFichas[tmpCoord.y][tmpCoord.x] != 0 && band == 0;
					tmpCoord.x--, tmpCoord.y = -(b - tmpCoord.x)) {

					
					posicionesDeFichas[coAdyacente.y][coAdyacente.x] = turno;

					if(posicionesDeFichas[tmpCoord.y][tmpCoord.x] != turno) {

						band = 0;
						posicionesDeFichas[tmpCoord.y][tmpCoord.x] = turno;


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


					posicionesDeFichas[coAdyacente.y][coAdyacente.x] = turno;

					if(posicionesDeFichas[tmpCoord.y][tmpCoord.x] != turno) {

						band = 0;

						posicionesDeFichas[tmpCoord.y][tmpCoord.x] = turno;

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

					posicionesDeFichas[coAdyacente.y][coAdyacente.x] = turno;


					if(posicionesDeFichas[tmpCoord.y][tmpCoord.x] != turno) {

						band = 0;

						posicionesDeFichas[tmpCoord.y][tmpCoord.x] = turno;

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

					posicionesDeFichas[coAdyacente.y][coAdyacente.x] = turno;


					if(posicionesDeFichas[tmpCoord.y][tmpCoord.x] != turno) {

						band = 0;

						posicionesDeFichas[tmpCoord.y][tmpCoord.x] = turno;

					} else {

						band = 1;
					}
					
				}


			}

		}

	}



	void actualizacionLineal(int posicionesDeFichas[8][8], Coordenadas coBase, Coordenadas coAdyacente, int turno) {

		int band;
		Coordenadas tmpCoord;


		if( (coAdyacente.x >= 0 && coAdyacente.x <= 7) && (coAdyacente.y >= 0 && coAdyacente.y <= 7) )  {

			posicionesDeFichas[coBase.y][coBase.x] = turno;


			//CASO 1 VERTICAL SUP

			if(coAdyacente.x == coBase. x && coAdyacente.y < coBase. y) {


				for(tmpCoord.x = coAdyacente.x, tmpCoord.y = coAdyacente.y - 1, band = 0;
					tmpCoord.y >= 0 && posicionesDeFichas[tmpCoord.y][tmpCoord.x] != 0 && band == 0;
					tmpCoord.y--) {

					posicionesDeFichas[coAdyacente.y][coAdyacente.x] = turno;


					if(posicionesDeFichas[tmpCoord.y][tmpCoord.x] != turno) {

						band = 0;

						posicionesDeFichas[tmpCoord.y][tmpCoord.x] = turno;

					} else {

						band = 1;

					}

				}


			//CASO 2 VERTICAL INF

			} else if(coAdyacente.x == coBase. x && coAdyacente.y > coBase. y) {


				for(tmpCoord.x = coAdyacente.x, tmpCoord.y = coAdyacente.y + 1, band = 0;
					tmpCoord.y <= 7 && posicionesDeFichas[tmpCoord.y][tmpCoord.x] != 0 && band == 0;
					tmpCoord.y++) {

					posicionesDeFichas[coAdyacente.y][coAdyacente.x] = turno;


					if(posicionesDeFichas[tmpCoord.y][tmpCoord.x] != turno) {

						band = 0;

						posicionesDeFichas[tmpCoord.y][tmpCoord.x] = turno;

					} else {

						band = 1;
					}

				}

			//CASO 3 HORIZONTAL IZQ


			} else if(coAdyacente.x < coBase. x && coAdyacente.y == coBase. y) {


				for(tmpCoord.x = coAdyacente.x - 1, tmpCoord.y = coAdyacente.y, band = 0;
					tmpCoord.x >= 0 && posicionesDeFichas[tmpCoord.y][tmpCoord.x] != 0 && band == 0;
					tmpCoord.x--) {

					posicionesDeFichas[coAdyacente.y][coAdyacente.x] = turno;


					if(posicionesDeFichas[tmpCoord.y][tmpCoord.x] != turno) {

						band = 0;

						posicionesDeFichas[tmpCoord.y][tmpCoord.x] = turno;

					} else {

						band = 1;
					}

				}

			//CASO 4 HORIZONTAL DER


			} else if(coAdyacente.x > coBase. x && coAdyacente.y == coBase. y) {


				for(tmpCoord.x = coAdyacente.x + 1, tmpCoord.y = coAdyacente.y, band = 0;
					tmpCoord.x <= 7 && posicionesDeFichas[tmpCoord.y][tmpCoord.x] != 0 && band == 0;
					tmpCoord.x++) {

					posicionesDeFichas[coAdyacente.y][coAdyacente.x] = turno;


					if(posicionesDeFichas[tmpCoord.y][tmpCoord.x] != turno) {

						band = 0;
						posicionesDeFichas[tmpCoord.y][tmpCoord.x] = turno;

					} else {

						band = 1;
					}
					
				}


			}

		} 

	}

}

#endif

