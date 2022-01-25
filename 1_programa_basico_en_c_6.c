/*
Este programa resuelve el problema del tiro parabolico para un proyectil 
con una altura inicial h y con velocidad inicial sobre la vertical, el proyectil 
se detiene cuando cae al suelo. El proposito de este programa es mostrar 
el uso de algunas funciones de C.

ultima edicion : 03 de abril de 2018

*/

// Librerias basicas de C
#include<stdio.h> 
#include<stdlib.h>
#include<math.h> 

// MACROS AND DEFINES

// Variables globales
double g=9.8;
FILE *fEnergiaRutina; // archivo como variable global

/*
1 - prototipo
void rutina_chequeo_energia(double t, double energia_ini, double masa, double vx, double vy, double altura);
2 - tipo de retorno  
3 - definición
*/
// Rutinas y funciones
void rutina_chequeo_energia(double , double , double , double , double , double ); // prototipo

double funcion_chequeo_energia(double t, double masa, double vx, double vy, double altura)
{
  
  double energia, v2;
  
  v2 = vx*vx+vy*vy; 
  
  energia = 0.5*masa*v2 + masa*g*altura;

return energia;

}

// Funcion principal del programa
int main(void)
{ 
  
  // declaracion de variables
  int i, numero_puntos;

  double altura, vel_ini; // no usar mas de 31 caracteres para nombrar una variable.
  double energia, energia_inicial, error_energia, masa, x, y, vx, vy, t, dt;
  double tiempo_caida;  
  /*
  printf("Inserte el valor de la altura inicial:\n");
  scanf("%lf",&altura); 
  printf("altura = %lf\n",altura);
  
  printf("Inserte el valor de la velocidad inicial:\n");
  scanf("%lf",&vel_ini); 
  printf("velocidad inicial = %lf\n",vel_ini);
  
  printf("Inserte el valor de la masa:\n");
  scanf("%lf",&masa); 
  printf("velocidad inicial = %lf\n",masa);
  */

  // inicializacion de variables
  x = 0.0;
  y = altura = 10.0;
  vx = vel_ini = 1.0;
  masa = 1.0;
  vy = 0.0;
  t = 0.0;
  energia  = energia_inicial = 0.5*masa*(vx*vx+vy*vy) + masa*g*altura;
  tiempo_caida = sqrt( 2.0*altura / g );
  printf("tiempo de caida estimado = %lf\n",tiempo_caida);
  printf("energia_inicial = %lf\n",energia_inicial);

  // uso de Switch
  printf("Inserte el numero de puntos:\n");
  scanf("%d",&numero_puntos); 
  printf("Numero de puntos esperados = %d\n",numero_puntos);
  
  dt = tiempo_caida / numero_puntos;

  switch (numero_puntos)
    {
    case 20:
      printf("Integracion con presicion baja\n");
      printf("dt = %lf\n",dt);
      break;
      
    case 100:
      printf("Integracion con presicion intermedia\n");
      printf("dt = %lf\n",dt);
      break;
      
    case 1000000:
      printf("Integracion con presicion alta\n");
      printf("dt = %lf\n",dt);
      break;

    case 10000000:
      printf("Integracion con presicion alta\n");
      printf("dt = %lf\n",dt);
      break;

    default:
      printf("ningun caso es valido\n");
      dt = tiempo_caida/1000;
      printf("dt = %lf\n",dt);
      printf("Integracion con presicion aceptable usando 1000 puntos\n");
      break;
    }

  // Salida de datos a un archivo
  FILE *pf = fopen("parabolico.dat","w");
  fprintf(pf,"%lf\t%lf\t%lf\t%lf\t%lf\n", t, x , y, vy, energia);
  fEnergiaRutina = fopen("parabolico_energia_rutina.dat","w");

  FILE *fEnergiaFuncion = fopen("parabolico_energia_funcion.dat","w");
  energia = funcion_chequeo_energia(t, masa, vx, vy, y);
  error_energia = ( fabs(energia-energia_inicial) ) / energia_inicial;
  fprintf(fEnergiaFuncion,"%lf %lf %lf\n",t,energia,error_energia);

  // Integracion
  rutina_chequeo_energia(t, energia_inicial, masa, vx, vy, y);
  for( t=dt; t<=tiempo_caida; t += dt ) 
    {
     
      vy = vy - g*dt;

      x = x + vx*dt;
      y = y + vy*dt;
      
      if( y>=0.0 )
	{
	  rutina_chequeo_energia(t, energia_inicial, masa, vx, vy, y);
	  energia = funcion_chequeo_energia(t, masa, vx, vy, y);
	  error_energia = ( fabs(energia-energia_inicial) ) / energia_inicial;
	  fprintf(fEnergiaFuncion,"%lf %lf %lf\n",t,energia,error_energia);
	  fprintf(pf,"%lf\t%lf\t%lf\t%lf\t%lf\n", t, x , y, vy, energia);
	}
      else
	break;

    }

  fclose(pf);
  fclose(fEnergiaRutina);
  fclose(fEnergiaFuncion);

  return 0;

}  // fin

// NOTA: - Obervar el tiempo de computo y el tamaño del archivo de salida aumentando dt con el switch
//            - Hablar de estudios de resolucion
//            - Hablar de los ceros que aparecen en los resultados de la energia y el dt por el formato de salida

void rutina_chequeo_energia(double t, double energia_ini, double masa, double vx, double vy, double altura)
{

  double energia, v2, error_energia;

  v2 = vx*vx+vy*vy; 

  energia = 0.5*masa*v2 + masa*g*altura;

  error_energia = ( fabs( energia - energia_ini ) ) / energia_ini;

  fprintf(fEnergiaRutina,"%.12lf %.12lf %.12lf\n",t,energia,error_energia);

}
