/*
Este programa resuelve el problema del tiro parabolico para un proyectil 
con una altura inicial h y con velocidad inicial sobre la vertical, el proyectil 
se detiene cuando cae al suelo. El proposito de este programa es mostrar 
el uso de algunas funciones de C.

ultima edicion : 06 de Marzo de 2020

 */

// Librerias basicas de C
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

// Funcion principal del programa
int main(void)
{ 
  
  // declaracion de variables
  int i, numero_puntos;

  double altura, vel_ini, g=9.8; // no usar mas de 31 caracteres para nombrar una variable.
  double energia, masa, x, y, vx, vy, t, dt;
  double tiempo_caida;  

  printf("Inserte el valor de la altura inicial:\n");
  //scanf("%lf",&altura); 
  printf("altura = %lf\n",altura);
  
  printf("Inserte el valor de la velocidad inicial:\n");
  //scanf("%lf",&vel_ini); 
  printf("velocidad inicial = %lf\n",vel_ini);
  
  printf("Inserte el valor de la masa:\n");
  //scanf("%lf",&masa); 
  printf("velocidad inicial = %lf\n",masa);
  

  // inicializacion de variables
  x = 0.0;
  y = altura = 10.0;
  vx = vel_ini = 1.0;
  vy = 0.0;
  t = 0.0;
  masa = 1.0;
  energia  = masa * g * altura;
  tiempo_caida = sqrt( 2.0*altura / g );
  printf("tiempo de caida estimado = %lf\n",tiempo_caida);

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
      printf("dt = %.10lf\n",dt);
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
  printf("%lf\n",y);

  FILE *teo = fopen("parabolico_teo.dat","w");
  fprintf(teo,"%lf\t%lf\t%lf\t%lf\t%lf\n", t, x , y, vy, energia);
  
  // Integracion
  for( t=0.0; t<=tiempo_caida; t += dt ) 
    {
      
      vy = vy - g*dt;
      
      x = x + vx*dt;
      y = y + vy*dt;
      
      if( y>=0.0 )
	fprintf(pf,"%lf\t%lf\t%lf\t%lf\t%lf\n", t, x , y, vy, energia);
      else
	break;
    }

  for (t=0.0; t<=tiempo_caida;t +=dt){

    x= vel_ini * t;
    y =10 - 0.5 * g * pow(t,2);
    
    if( y>=0.0 )
      fprintf(teo,"%lf\t%lf\t%lf\t%lf\t%lf\n", t, x , y, vy, energia);
    else
      break;
  }
    
    fclose(pf);
    fclose(teo);
  
  return 0;
  
}  // fin

// NOTA: - Obervar el tiempo de computo y el tamaño del archivo de salida aumentando dt con el switch
//            - Hablar de estudios de resolucion
