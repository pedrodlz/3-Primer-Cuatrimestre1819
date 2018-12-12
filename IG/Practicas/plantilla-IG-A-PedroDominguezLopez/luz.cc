// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luz.cc
// -- implementación del objeto luz de la práctica 4
//
// Autor: Pedro Domínguez López
//
// #############################################################################

#include "luz.h"

Luz::Luz(GLenum ind, Tupla4f pos, Tupla4f amb, Tupla4f dif, Tupla4f esp)
{
	indice = ind;
	for (int i=0;i<4;i++){
		posicion[i] = pos[i];
		ambiente[i] = amb[i];
		difusa[i] = dif[i];
		especular[i] = esp[i];
	}
}

void Luz::act_desact(GLenum ind, bool act)
{
	if(act){
		dibujar_luz();
		glEnable(GL_LIGHTING);
		glEnable(ind);

	}
	else{
		glDisable(ind);
		glDisable(GL_LIGHTING);
	}
}

void Luz::dibujar_luz()
{
	//glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );

	std::cout<< "Ambiente= {" << ambiente[0] << "," << ambiente[1] << "," << 
	ambiente[2] << "," << ambiente[3] << "}" << std::endl;
	std::cout<< "difusa= {" << difusa[0] << "," << difusa[1] << "," << 
	difusa[2] << "," << difusa[3] << "}" << std::endl;
	std::cout<< "especular= {" << especular[0] << "," << especular[1] << "," << 
	especular[2] << "," << especular[3] << "}" << std::endl;
	std::cout<< "posicion= {" << posicion[0] << "," << posicion[1] << "," << 
	posicion[2] << "," << posicion[3] << "}" << std::endl;


	glLightfv( indice, GL_AMBIENT, ambiente );
	glLightfv( indice, GL_DIFFUSE, difusa );
	glLightfv( indice, GL_SPECULAR, especular );
	glLightfv( indice, GL_POSITION, posicion );
}

void Luz::animar()
{
	Tupla4f nueva_pos;

	nueva_pos(0) = 6*cos( 0.01*(2.0*M_PI*alfa) );
    nueva_pos(1) = posicion(1);
    nueva_pos(2) = 6*sin( 0.01*(2.0*M_PI*alfa) );
    nueva_pos(3) = posicion(3);

    alfa = (alfa+1)%1000;

    posicion = nueva_pos;

	dibujar_luz();

}