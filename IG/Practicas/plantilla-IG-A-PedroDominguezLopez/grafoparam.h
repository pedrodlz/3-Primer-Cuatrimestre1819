// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.h
// -- declaraciones de clase para el objeto jerárquico de la práctica 3
//
// Autor: Pedro Domínguez López
//
// #############################################################################

#ifndef GRAFOPARAM_H_INCLUDED
#define GRAFOPARAM_H_INCLUDED

#include "malla.h" // añadir .h de cualquier objetos malla indexada usados....

constexpr int num_parametros = 4 ; // número de parámetros o grados de libertad
                                   // de este modelo

class GrafoParam
{
   public:

   // crea mallas indexadas (nodos terminales del grafo)
   GrafoParam(GLenum numero_luz);

   // función principal de visualización
   void draw( const int p_modo_vis, const bool p_usar_diferido );

   // actualizar valor efectivo de un parámetro (a partir de su valor no acotado)
   void actualizarValorEfe( const unsigned iparam, const float valor_na );

   // devuelve el número de parámetros
   unsigned numParametros() { return num_parametros ; }

   private:

   // métodos de dibujo de subgrafos
   void pierna( const float altura, const float ag_rotacion,
                             const float radio_cil );
   void cuerpo( const float altura);
   void cabeza();
   void ojo();
   void brazo( const float ag_rotacion);

   // objetos tipo malla indexada (nodos terminales)

   Cilindro * cilindro = nullptr ;
   Cubo *     cubo     = nullptr ;
   Esfera *   esfera   = nullptr ;
   Cono *     cono     = nullptr ;

   // parámetros de la llamada actual (o última) a 'draw'
   int modo_vis ;      // modo de visualización
   bool    usar_diferido ; // modo de envío (true -> diferido, false -> inmediato)


   // valores efectivos de los parámetros (angulos, distancias, factores de
   // escala, etc.....) calculados a partir de los valores no acotados

   float altura_p,       // altura de la primera columna
         radio_p,         // radio de la pierna
         ag_rotacion_p1,  // ángulo en grados de rotación pierna derecha
         ag_rotacion_p2,  // ángulo en grados de rotación pierna izquierda
         radio_c,          // Radio del cuerpo
         ag_rotacion_b1,   // ángulo en grados de rotación brazo derecho
         ag_rotacion_b2,   // ángulo en grados de rotación brazo izquierdo
         ag_rotacion_ca,   // ángulo en grados de rotación cabeza
         movimiento_cuerpo;// distancia a la que se mueve

   GLenum numero_luz;

} ;

#endif
