#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define PI 3.141592

/* gcc -fopenmp prueba1.c -lm  -o prueba1_c  , ./prueba1_c */

double* metropolis(int N, double mu, double sigma); 

int main()
{
	int N = 1000;
	double mu = 0.0; 
	double sigma = 1.0; 
	int n_cadenas = 8; 
    
  for ( int j = 0; j < n_cadenas; j++ ) 
  {
      FILE *out;
      char filename[128];
      
      sprintf(filename, "sample_%d.dat", j);
    
      if(!(out = fopen(filename, "w")))
      {
                fprintf(stderr, "Problema abriendo el archivo\n");
                exit(1);
        }
        
      for( int i = 0; i < N; i++ )
        {
                fprintf(out, "%f\n", metropolis(N, mu, sigma)[i]);
        }

        fclose(out);
  }
}

double normal(double x, int N, double sigma, double mu)
 {
    double y;
    int i;

    y = 1/(sigma * sqrt(2 * PI)) * exp( - pow ( (x-mu)/ (sqrt(2)*sigma),2));
 
    return y;
 }

double min(double a, double b)
{
    if( a < b )
    {
        return a;
    }
    else
    {
        return b;
    }
}

double* metropolis(int N, double mu, double sigma)
{
    float sigma_delta = 4.0;
    double* lista; 
	lista = malloc(sizeof(double *)*N);
    float propuesta;
    float r;
	float alpha; 
    
	#pragma omp parallel for shared(lista)
    for( int i = 0; i < N; i++ )
    {
        if( i == 0 )
        {
            lista[i] = drand48(); 
        }
        else
        {
            propuesta = lista[i-1] + 2*drand48() - 1;
            
            r = min(1, normal(propuesta, N, sigma, mu)/normal(lista[i-1], N, sigma, mu));
		
            alpha = drand48();

		if( alpha < r )
		{
			lista[i] = propuesta;
		}
		else
		{
			lista[i] = lista[i-1];
		}
        }
    }
    
    return lista;
}

