//AUTOR: Pedro Domínguez López 3ºA

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    glEnable(GL_CULL_FACE);

    Front_plane = 0.1;
    Back_plane = 2000.0;
    Observer_distance = 2.0;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de las prácticas: Mallas o Jerárquicos....
    //cubo = new Cubo();
    //tetraedro = new Tetraedro();
    /*obj_ply = new ObjPLY("./plys/beethoven.ply");
    obj_rev1 = new ObjRevolucion("./plys/peon.ply",0);
    obj_rev2 = new ObjRevolucion("./plys/lata-pcue.ply",0);
    obj_rev3 = new ObjRevolucion("./plys/lata-psup.ply",0);
    cilindro = new Cilindro(4,20);
    cono = new Cono(4,20);
    esfera = new Esfera(30,20);*/
    objetojerarquico = new ObjJerarquico();

    num_objetos = 1 ; // se usa al pulsar la tecla 'O' (rotar objeto actual)
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	redimensionar( UI_window_width, UI_window_height );
}

// **************************************************************************
// Funcion que dibuja el objeto activo actual, usando su método 'draw'
// (llamada desde Escena::dibujar)
// ***************************************************************************

void Escena::dibujar_objeto_actual()
{
   using namespace std ;

   // (1) configurar OpenGL para el modo actual (puntos/lineas/sólido)
   //    llamar glPolygonMode, glColor... (y alguna cosas más), según dicho modo
   // .........completar (práctica 1)

   glColor3f(0,0,0);
   glPointSize(3);

   // (2) dibujar el objeto actual usando método 'draw' del objeto asociado al
   // valor entero en 'objeto_actual'

   switch( objeto_actual )
   {
       case 0:
            if ( objetojerarquico != nullptr ){
                objetojerarquico->draw(modo,usar_diferido);
            }
            break ;
      /*case 0:
           if ( obj_ply != nullptr ){
               obj_ply->draw(modo,usar_diferido);
           }
           break ;
      case 1:
          if ( obj_rev1 != nullptr ){
              obj_rev1->draw(modo,usar_diferido);
          }
          break ;
      case 2:
          if ( obj_rev2 != nullptr ){
              obj_rev2->draw(modo,usar_diferido);
          }
          break;
      case 3:
          if ( obj_rev3 != nullptr ){
              obj_rev3->draw(modo,usar_diferido);
          }
          break;
      case 4:
          if ( cilindro != nullptr ){
              cilindro->draw(modo,usar_diferido);
          }
          break;
      case 5:
          if ( cono != nullptr ){
            cono->draw(modo,usar_diferido);
          }
          break;
      case 6:
          if ( esfera != nullptr ){
              esfera->draw(modo,usar_diferido);
          }
          break;*/
      default:
         cout << "draw_object: el número de objeto actual (" << objeto_actual << ") es incorrecto." << endl ;
         break ;
   }
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
   ejes.draw();
	dibujar_objeto_actual();
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;

    switch( toupper(tecla) )
    {
        case 'M' :
            //Cambiar de modo
            modo = (modo+1) % 4 ;
            cout << "modo actual == " << modo << endl ;
            break ;
        case 'O' :
            // activar siguiente objeto
            objeto_actual = (objeto_actual+1) % num_objetos ;
            cout << "objeto actual == " << objeto_actual << endl ;
            break;
        case 'V' :
            //Cambiar modo draw
            usar_diferido = !usar_diferido;
            break ;
        case 'P' :
            // activar el parámetro siguiente al actual
            objetojerarquico->siguienteParametro();
            break ;
        case 'A' :
            // activa o desactiva las animaciones
            conmutarAnimaciones();
            break ;
        case 'Z' :
            // incrementa el valor del parámetro actual del objeto jerárquico
            if(!anima_activ) objetojerarquico->incrementaParamAct();
            break ;
        case 'X' :
            // decrementa el valor del parámetro actual del objeto jerárquico
            if(!anima_activ) objetojerarquico->decrementaParamAct();
            break ;
        case '>' :
            // incrementar el valor de incremento/decremento usado para las animaciones
            objetojerarquico->acelerar();
            break ;
        case '<' :
            // decrementar el valor de incremento/decremento usado para las animaciones
            objetojerarquico->decelerar();
            break ;
        case 'Q' :
            // salir
            return true ;
            break ;
    }
    return false ;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wy = 0.84*Front_plane,
   wx = ratio_xy*wy ;
   glFrustum( -wx, +wx, -wy, +wy, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
    Width = newWidth;
    Height = newHeight;
    change_projection( float(Width)/float(Height) );
    glViewport( 0, 0, Width, Height );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_x, 1.0 ,0.0, 0.0 );
   glRotatef( Observer_angle_y, 0.0, 1.0, 0.0 );
}

//**************************************************************************
// Funcion encargada de activar/desactivar las animaciones
//***************************************************************************

void Escena::conmutarAnimaciones()
{
    anima_activ = !anima_activ;

    if(anima_activ){
        objetojerarquico->inicioAnimaciones();
        glutIdleFunc( funcion_desocupado );
    }
    else glutIdleFunc( nullptr );
}

//**************************************************************************
// Funcion encargada de actualizar el estado de los parámetros del objeto jerárquico
//***************************************************************************

void Escena::mgeDesocupado()
{
    objetojerarquico->actualizarEstado();
    glutPostRedisplay();
}
