// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.cc
// -- implementación del objeto jerárquico de la práctica 3
//
// Autor: Pedro Domínguez López
//
// #############################################################################


#include "grafoparam.h"

// -----------------------------------------------------------------------------
// constructor: crea mallas indexadas en los nodos terminales del grafo

GrafoParam::GrafoParam(GLenum num_luz)
{
   cilindro = new Cilindro( 3, 14 );
   cubo     = new Cubo();
   esfera   = new Esfera(10,14);
   cono     = new Cono(20,14);

   numero_luz = num_luz;
}
// -----------------------------------------------------------------------------
// actualizar valor efectivo de un parámetro (a partir de su valor no acotado)

void GrafoParam::actualizarValorEfe( const unsigned iparam, const float valor_na )
{
   assert( iparam < num_parametros );

   using namespace std ;
   //cout << "GrafoParam::actualizarValorEfe( " << iparam << ", " << valor_na << " )" << endl ;

   constexpr float vp = 2.5 ;

   switch( iparam )
   {
      case 0:
         // angulo en grados de rotacion 1 de la pierna derecha y brazo derecho
         ag_rotacion_p1 = 30*sin( M_PI*valor_na) ;
         ag_rotacion_b1 = ag_rotacion_p1;
         break ;
      case 1:
         // ángulo en grados de rotacion 2 de la pierna izquierda y brazo izquierdo
         ag_rotacion_p2 = -30*sin( M_PI*valor_na);
         ag_rotacion_b2 = ag_rotacion_p2;
         break ;
      case 2:
         ag_rotacion_ca = 20*sin(M_PI*valor_na);
         break;
      case 3:
         movimiento_cuerpo = 5*sin(M_PI*valor_na);
         break;
   }
}

// -----------------------------------------------------------------------------
// visualización del objeto Jerárquico con OpenGL,
// mediante llamadas a los métodos 'draw' de los sub-objetos

void GrafoParam::draw( const int p_modo_vis, const bool p_usar_diferido )
{
   // asegurarnos que está inicializado ok

   assert( cubo     != nullptr );
   assert( cilindro != nullptr );
   assert( esfera   != nullptr );
   assert( cono     != nullptr );

   // guardar parametros de visualización para esta llamada a 'draw'
   // (modo de visualización, modo de envío)

   modo_vis      = p_modo_vis ;
   usar_diferido = p_usar_diferido ;

   // dibujar objetos

   constexpr float
      radio_p = 1; //como el cilindro tiene radio 0.5 al aplicar el escalado se
                   // quedaría igual por lo que el radio sería 0.5
      altura_p = 2;
      radio_c = 2.7;

   glTranslatef(movimiento_cuerpo,0,0);
   glRotatef(90,0,1,0); //rota el cuerpo completo para que se vea de lado
   glPushMatrix();
      glTranslatef(0,2,0.5);  //Se sube el cuerpo y la cabeza para unir los brazos
      glPushMatrix();         //Añade el cuerpo
         glTranslatef(0,-5.3,-0.5);//las baja y las centra en el origen
         glPushMatrix();      //dibuja las piernas
            glPushMatrix();   //Se añaden de forma simetrica de manera que el eje y quede centrado
               // primera pierna
               glTranslatef(-2,1.25,0);   //Se coloca en -x y se sube un poco
               glColor3f( 0.0, 0.6, 0.0 );
               pierna(altura_p,ag_rotacion_p1,radio_p);
            glPopMatrix();
            glPushMatrix();
               // segunda pierna
               glTranslatef(1,radio_p+0.25,0);//Se coloca en +x y se sube un poco
               glColor3f( 0.0, 0.6, 0.0 );
               pierna(altura_p,ag_rotacion_p2,radio_p);
            glPopMatrix();
         glPopMatrix();
         cuerpo(radio_c);
      glPopMatrix();
      glPushMatrix();         //Se añade la cabeza
         glColor3f( 0.0, 0.6, 0.0 );
         glRotatef(ag_rotacion_ca,0,1,0);
         cabeza();
      glPopMatrix();   
   glPopMatrix();
   glPushMatrix();   //Se añaden los dos con color verde
      glColor3f( 0.0, 0.6, 0.0 );
      glPushMatrix();//primer brazo
         glTranslatef(-0.7,-0.4,0);
         glRotatef(-50,0,0,1);
         glTranslatef(-1,0,0);
         brazo(ag_rotacion_b1);
      glPopMatrix();
      glPushMatrix();//segundo brazo
         glTranslatef(0.7,-0.4,0);
         glRotatef(50,0,0,1);
         brazo(ag_rotacion_b2);
      glPopMatrix();
   glPopMatrix();
}
// -----------------------------------------------------------------------------
// dibuja una pierna debajo del eje +x y pegando al eje -y

void GrafoParam::pierna( const float altura, const float ag_rotacion,
                          const float radio_cil )
{
   glPushMatrix();
      glRotatef(ag_rotacion,1,0,0);
      glTranslatef(0.5,-altura,0);
      glPushMatrix();
         glScalef( radio_cil, altura, radio_cil );
         cilindro->draw( modo_vis, usar_diferido, numero_luz );
      glPopMatrix();
      glPushMatrix( );
         glTranslatef(0,-0.5,0.5);
         glColor3f( 1, 0.6, 0.0 );
         glScalef( 0.5, 0.5, 1 );
         cubo->draw( modo_vis, usar_diferido, numero_luz );
      glPopMatrix();
   glPopMatrix();
}

// -----------------------------------------------------------------------------
// dibuja el cuerpo casi completamente por encima del eje x

void GrafoParam::cuerpo( const float radio)
{
   glPushMatrix();
      //caparazon
      glPushMatrix();
         glTranslatef(0,radio,-1.1);
         glColor3f( 0.6, 0.0, 0.0 );
         glRotatef(40,1,0,0);
         glScalef(radio-0.5,radio-0.2,radio+0.5);
         esfera->draw(modo_vis,usar_diferido,numero_luz);
      glPopMatrix();
      //torso
      glColor3f( 0.0, 0.6, 0.0 );
      glPushMatrix();
         glTranslatef(0,radio-1.3,-0.4);
         glRotatef(10,1,0,0);
         glScalef(radio*1.5,radio*2,radio*1.5);
         cono->draw(modo_vis, usar_diferido,numero_luz);
      glPopMatrix();
      //cola
      glPushMatrix();
         glTranslatef(0,radio-1.23,-0.65);
         glRotatef(-83,1,0,0);
         glScalef(radio*1.2,radio*1.3,radio*1.2);
         cono->draw(modo_vis, usar_diferido,numero_luz);
      glPopMatrix();
      //culo
      glPushMatrix();
         glTranslatef(0,1.2,-0.4);
         glRotatef(15,1,0,0);
         glScalef(radio*1.6,radio,radio*1.5);
         esfera->draw(modo_vis,usar_diferido,numero_luz);
      glPopMatrix();
   glPopMatrix();
}

// -----------------------------------------------------------------------------
// dibuja la cabeza centrado el cuello en el origen
void GrafoParam::cabeza( )
{
   glPushMatrix();
      //hocico
      glPushMatrix();
         glTranslatef(0,0.8,2.5);
         glRotatef(90,1,0,0);
         glScalef(4.2,4.2,4);
         esfera->draw(modo_vis,usar_diferido,numero_luz);
      glPopMatrix();
      //cuello
      glPushMatrix();
         glScalef(4.3,3.6,3.5);
         esfera->draw(modo_vis,usar_diferido,numero_luz);
      glPopMatrix();
      //ojos
      glColor3f( 1, 1, 0.8 );
      glPushMatrix();
         glTranslatef(-0.5,0,0);
         ojo();
      glPopMatrix();
      glTranslatef(0.5,0,0);
      ojo();
   glPopMatrix();
}

// -----------------------------------------------------------------------------
// dibuja un ojo en y = 2 x=0 y z=0
void GrafoParam::ojo()
{
   glPushMatrix();
         glTranslatef(0,2,0);
         glScalef(1,2,0.9);
         esfera->draw(modo_vis,usar_diferido,numero_luz);
   glPopMatrix();
}

// -----------------------------------------------------------------------------
// dibuja un brazo
void GrafoParam::brazo(const float ag_rotacion)
{
   glPushMatrix();
      glRotatef(ag_rotacion,1,0,0);
      glTranslatef(0,-2,0);
      //brazo
      glPushMatrix();
         glTranslatef(0.5,0,0);
         glScalef( 0.8, 2.3, 0.8 );
         cilindro->draw( modo_vis, usar_diferido, numero_luz );
      glPopMatrix();
      //mano
      glPushMatrix();
            glTranslatef(0.5,-0.2,0);
            glScalef(0.9,1,1.4);
            esfera->draw(modo_vis,usar_diferido,numero_luz);
      glPopMatrix();
   glPopMatrix();
}