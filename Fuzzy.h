/*
***********************Librería creada por Elmer Meneses *******************************
***********************Ingeniero Mecatrónico Universidad de Pamplona********************
***********************  9 de Agosto de 2019             *******************************
*/
#ifndef Fuzzy_h
#define Fuzzy_h
#include <arduino.h>
class Fuzzy
{
	public:
		Fuzzy();
		int resolution = 300;
		float B[300];
		float triangular(float x[],float params[],float date);
		float trapezoidal(float x[],float params[],float date);
		void inferencia_mamdani2(float c,float stru[],float U_VOL[]);
		float defusi(float U_VOL[]);
		//void regla_compuesta2(float in1[],float in2[],float U1[],float U2[],float c1,float c2,float V[],float UV[],float B[],int tam);
		//void regla_compuesta3(float in1[],float in2[],float in3[],float U1[],float U2[],float U3[],float c1,float c2,float c3, float V[], float UV[], float B[], int tam);
		void regla_simple(float in[],float Uin[],float err,float V[], float UV[]);
		void borrar();
};
#endif