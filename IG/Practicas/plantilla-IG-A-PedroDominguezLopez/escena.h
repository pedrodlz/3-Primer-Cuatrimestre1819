//AUTOR: Pedro Domínguez López 3ºA

#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "jerarquico.h"
#include "luz.h"
#include "camara.h"

enum EstadosRaton{
  MOVIENDO_CAMARA,
  CAMARA_QUIETA,
  ZOOM
};

class Escena
{
   private:

   Ejes ejes;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

   void clear_window();
	void dibujar_objeto_actual();

   // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();

   int objeto_actual = 0 , // objeto actual (el que se visualiza)
       modo = 0,           // modo actual -> 0:puntos 1:alambre 2:solido 3:ajedrez
       num_objetos   = 0 ; // número de objetos (actualizado al crear los objetos en el constructor)

   bool usar_diferido = true; //Si esta a true pinta la malla en modo diferido
                            // sino la pinta en modo inmediato

   bool anima_activ = false;

   // Objetos de la escena
   /*Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro = nullptr ;*/
   ObjPLY * obj_ply = nullptr;
   ObjRevolucion * obj_rev = nullptr;
   Cilindro * cilindro = nullptr;
   Cono * cono = nullptr;
   Esfera * esfera = nullptr;
   ObjJerarquico * objetojerarquico = nullptr;

   GLenum numero_luz1 = GL_LIGHT0, numero_luz2 = GL_LIGHT1;

   Luz * blanca = nullptr;
   Luz * puntual = nullptr;

   Cuadro * imagen = nullptr;

   //Camaras
   int camara_activa = 1;
   Camara * camaras[2] = {nullptr,nullptr};

   // Gestion de las animaciones
   void conmutarAnimaciones();

   void colorearId(const int ident );
   int obtenerId( int xpix, int ypix );


   public:

   Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

  // Actualizar el estado de los parámetros del objeto jerárquico
  void mgeDesocupado();

  EstadosRaton estado_raton = CAMARA_QUIETA;

  void zoom(float factor);

  //Gestion del raton
  void raton_movido(int x, int y);

  //Seleccion de objetos
  void dibujaSeleccion();
  void pick(GLint x, GLint y);
};
#endif
