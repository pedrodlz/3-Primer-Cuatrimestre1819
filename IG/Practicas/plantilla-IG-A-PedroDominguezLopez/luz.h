// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luz.h
// -- declaraciones de clase para el objeto luz de la práctica 4
//
// Autor: Pedro Domínguez López
//
// #############################################################################

#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz{
private:
	GLenum indice;	//Numero de la luz
	Tupla4f posicion, ambiente, difusa, especular;	//Componentes de la luz
	int alfa = 0;	//Valor para la rotacion de la luz
	void dibujar_luz();
public:
	Luz(GLenum ind, Tupla4f pos, Tupla4f amb, Tupla4f dif, Tupla4f esp);
	void act_desact(GLenum ind, bool act);
	void animar();
};

#endif