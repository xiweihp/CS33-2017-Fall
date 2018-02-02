#include "func.h"
#include "util.h"

void func0(double *weights, double *arrayX, double *arrayY, int xr, int yr, int n)
{
  int i;
  int thread_Num = 28;
  double weightsn = 1/((double)(n));
  
  omp_set_num_threads(thread_Num);
#pragma omp parallel for private(i) firstprivate(n, weights, arrayX, arrayY, xr, yr, weightsn)
	for(i = 0; i < n; i++){
	  weights[i] = weightsn;
		arrayX[i] = xr;
		arrayY[i] = yr;
	}
}

void func1(int *seed, int *array, double *arrayX, double *arrayY,
			double *probability, double *objxy, int *index,
			int Ones, int iter, int X, int Y, int Z, int n)
{
	int i, j;
   	int index_X, index_Y;
	int max_size = X*Y*Z;
	int thread_Num = 28;
	omp_set_num_threads(thread_Num);
        #pragma omp parallel for private(i) firstprivate(n, arrayX, arrayY, seed)
   	for(i = 0; i < n; i++){
   		arrayX[i] += 1 + 5*rand2(seed, i);
   		arrayY[i] += -2 + 2*rand2(seed, i);
   	}

	int a,b;
	//	omp_set_num_threads(thread_Num);
        #pragma omp parallel for private(i,j, index_X, index_Y) firstprivate(n, Ones,  arrayX, arrayY, objxy, Y, Z, iter, max_size, probability, index, array)

   	for(i = 0; i<n; i++){
	  a = i * Ones;
	  for(j = 0; j < Ones; j++)
	    {
	      b = j*2;
	      index_X = round(arrayX[i]) + objxy[b + 1];
   	      index_Y = round(arrayY[i]) + objxy[b];
   	      index[a + j] = fabs(index_X*Y*Z + index_Y*Z + iter);
   	      if(index[a + j] >= max_size)
		index[a + j] = 0;
   	     }
   		probability[i] = 0;

   		for(j = 0; j < Ones; j++) {
   			probability[i] += (pow((array[index[a + j]] - 100),2) -
   			pow((array[index[a + j]]-228),2))/50.0;
   		}
   		probability[i] = probability[i]/((double) Ones);
   	}
}

void func2(double *weights, double *probability, int n)
{
   int i;
  double sumWeights=0;
  double save;

  int thread_Num = 28;
  omp_set_num_threads(thread_Num);
  #pragma omp parallel for private(i, save) firstprivate(n, weights, probability) reduction(+:sumWeights)



  for(i = 0; i < n; i++)
    {
      save = weights[i] * exp(probability[i]);
      weights[i] = save;
      sumWeights += save;
    }
  #pragma omp parallel for private(i) firstprivate(n, weights,sumWeights)
  for(i = 0; i < n; i++)
    weights[i] = weights[i]/sumWeights;


}

void func3(double *arrayX, double *arrayY, double *weights, double *x_e, double *y_e, int n)
{
	double estimate_x=0.0;
	double estimate_y=0.0;
	int i;

	int thread_Num = 28;
        omp_set_num_threads(thread_Num);
        #pragma omp parallel for private(i) firstprivate(n, arrayX, arrayY, weights) reduction(+:estimate_x, estimate_y)	
	for(i = 0; i < n; i++){
   		estimate_x += arrayX[i] * weights[i];
   		estimate_y += arrayY[i] * weights[i];
   	}

	*x_e = estimate_x;
	*y_e = estimate_y;

}

void func4(double *u, double u1, int n)
{
	int i;

	for(i = 0; i < n; i++){
	  u[i] = u1 + i/((double)(n));
   	}
}

void func5(double *x_j, double *y_j, double *arrayX, double *arrayY, double *weights, double *cfd, double *u, int n)
{
	int i, j;
	int thread_Num = 28;
	int minus = n-1;
	
	omp_set_num_threads(thread_Num);
        #pragma omp parallel for private(j, i) firstprivate(n, cfd, u, arrayX, arrayY, x_j, y_j,minus)
	for(j = 0; j < n; j++){
   		//i = findIndex(cfd, n, u[j]);
   		i = findIndexBin(cfd, 0, n, u[j]);
   		if(i == -1)
   			i = minus;
   		x_j[j] = arrayX[i];
   		y_j[j] = arrayY[i];

   	}

       	//omp_set_num_threads(thread_Num);
        #pragma omp parallel for private(i) firstprivate(n, arrayX, arrayY, weights, x_j, y_j)
	for(i = 0; i < n; i++){
		arrayX[i] = x_j[i];
		arrayY[i] = y_j[i];
		weights[i] = 1/((double)(n));
	}
}
