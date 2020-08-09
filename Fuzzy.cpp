/*
***********************Libreria creada por Elmer Meneses *******************************
***********************Ingeniero Mecatronico Universidad de Pamplona********************
***********************  5 de Julio de 2020             *******************************
*/
#include <Arduino.h>
#include "Fuzzy.h"

Fuzzy::Fuzzy(){ //Este metodo se usa para colocar el vector en ceros
  for(int i=0; i<resolution; i++){
      B[i] = 0;
  }
}
void Fuzzy::regla_simple(float in[],float Uin[],float err,float V[], float UV[]){
  int t=0,date=0;
  float r=0.0;
  while(date==0){
      if(in[t]=='T' || in[t]=='t' || in[t]=='R' || in[t]=='r'){
        date=1;
        t=t-1;
        }
      t=t+1;
    }
    if(t ==3){
      r = triangular(Uin,in,err);
    }
    else if(t ==4){
      r = trapezoidal(Uin,in,err);
    }
    inferencia_mamdani2(r,V,UV); // Se Hace la primera regla
}

/*
void Fuzzy::regla_compuesta2(float in1[],float in2[],float U1[],float U2[],float c1,float c2, float V[], float UV[], float B[], int tam){
  int t1=0,date = 0,t2 =0,date1=0;
  float r1 = 0, r2 = 0,res =0;
  while(date ==0){
    while(date1==0){
      if(in2[t2]=='T' || in2[t2]=='t' || in2[t2]=='R' || in2[t2]=='r'){
        date1=1;
        t2=t2-1;
        }
      t2=t2+1;
    }
    if(in1[t1]=='T' || in1[t1]=='t' || in1[t1]=='R' || in1[t1]=='r'){
        date=1;
        t1=t1-1;
        }
      t1=t1+1;//aqui defino el tamaño de in1 e in2 
  }
  if(t1==3){
    r1 = triangular(U1,in1,c1);
  }
    else if(t1==4){
      r1 = trapezoidal(U1,in1,c1);
    }
   if(t2==3){
    r2 = triangular(U2,in2,c2);
  }
    else if(t2 ==4){
      r2 = trapezoidal(U2,in2,c2);
    }
res = min(r1,r2);
inferencia_mamdani2(B,res,V,UV,tam);
}
void Fuzzy::regla_compuesta3(float in1[],float in2[],float in3[],float U1[],float U2[],float U3[],float c1,float c2,float c3, float V[], float UV[], float B[], int tam){
  int t1=0,date = 0,t2 =0,t3 =0,date1=0,date2 =0;
  float r1 = 0, r2 = 0,r3 =0,res =0;
  while(date ==0){
    while(date1==0){
      while(date2==0){
      if(in3[t3]=='T' || in3[t3]=='t' || in3[t2]=='R' || in3[t3]=='r'){
        date2=1;
        t3=t3-1;
        }
      t3=t3+1; //Aqui defino el tamaño de in3
      }
    if(in2[t2]=='T' || in2[t2]=='t' || in2[t2]=='R' || in2[t2]=='r'){
        date1=1;
        t2=t2-1;
        }
      t2=t2+1;//aqui defino el tamaño de in2
    }
    if(in1[t1]=='T' || in1[t1]=='t' || in1[t1]=='R' || in1[t1]=='r'){
        date=1;
        t1=t1-1;
        }
      t1=t1+1;//aqui defino el tamaño de in1 
  }////////////////////////////////Aqui defino el tamaño de los vectores ingresados
  if(t1==3){
    r1 = triangular(U1,in1,c1);
  }
    else if(t1==4){
      r1 = trapezoidal(U1,in1,c1);
    }
  if(t2==3){
    r2 = triangular(U2,in2,c2);
  }
    else if(t2 ==4){
      r2 = trapezoidal(U2,in2,c2);
    }
  if(t3==3){
    r3 = triangular(U3,in3,c3);
  }
    else if(t3 ==4){
      r3 = trapezoidal(U3,in3,c3);
    }
res = min(r1,r2);
res = min(r3,res);
inferencia_mamdani2(B,res,V,UV,tam);
}

*/

float Fuzzy::triangular(float x[],float params[],float date){/////////////////////////////////////////////////////////////////////////////
  float y;
  if(date < params[0]){ // Se rellena con ceros a la izquierda
    y = 0;
  }
  if(date > params[2]){ // Se rellena con ceros a la derecha
    y = 0;
  }
  if (params[0]<=date && date<= params[1]){ // Primera Pendiente
    float p = 1/(params[1]-params[0]);
    y = (p*(date-params[1])+1); 
  }
  if (params[1]<=date && date<= params[2]){ // Segunda Pendiente
    float p = -1/(params[2]-params[1]);
    y = (p*(date-params[1])+1);
  }
  if(params[0] <x[0] || params[2] >x[1]){
    y = 0;
  }
  if((date == params[0]&& date ==params[1])|| (date == params[1]&& date ==params[2])){
    y = 1;
  }
  return y;
}//////////////////////////////////////////////////////////////////////////////////////////////////////
float Fuzzy::trapezoidal(float x[],float params[],float date){
  float y;
  if(date < params[0]){ // Se rellena con ceros a la izquierda
    y = 0;
  }
  if(date > params[2]){ // Se rellena con ceros a la derecha
    y = 0;
  }
  if (params[0]<=date && date<= params[1]){ // Primera Pendiente
    float p = 1/(params[1]-params[0]);
    y = (p*(date-params[1])+1); 
  }
  if(params[1]<date && date<= params[2]){ // Región Constante
    y = 1;
  }
  if (params[2]<=date && date<= params[3]){ // Segunda Pendiente
    float p = -1/(params[3]-params[2]);
    y = (p*(date-params[2])+1);
  }
  if(params[0] <x[0] || params[2] >x[1]){
    y = 0;
  }
  if((date == params[2]&& date ==params[3])|| (date == params[0]&& date ==params[1])|| (date == params[1]&& date ==params[2])){
    y = 1;
  }
  return y;
}/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Fuzzy::inferencia_mamdani2(float c,float stru[],float U_VOL[]){ //Hacemos inferencia mamdani
  
  int t=0,date = 0; //Declaracion de t para determinar si es trapezoidal o triangualar
  float factor = (U_VOL[1] - U_VOL[0]) /resolution; //Calculo factor de crecimiento para eje x del vector B
  float x = U_VOL[0];
  while(date == 0){
    if(stru[t]=='T' || stru[t]=='t' || stru[t]=='R' || stru[t]=='r'){
      date=1;
    }else{
    t=t+1;
    }
    if(t > 5){ //Quiere decir que hay algo mal en estruc....
      date =1;
      t = 4;
    }
  }
  if(t == 4 ){ //Para una funcion en el conjunto de salida tipo trapezoidal
    for(int i =0;i<resolution;i++){
      if(x < stru[0] || x == stru[0]){
        float y=0;
        if(y>B[i]){
          B[i]=y;
        }
      }
      if(stru[0] <= x && x <= stru[1]){ //Primera Pendiente
        float p= 1/(stru[1]-stru[0]);
        float y = (p*(x-stru[1]))+1;
        if(y >= c){
          y=c;
        }
        if(y > B[i]){
          B[i]=y;
        }
      }
      if(stru[1] <= x && x <= stru[2]){ //zona constante
        float y = c;
        if(y > B[i]){
          B[i]= y;
        }
      }
      if(stru[2] <= x && x <= stru[3]){ //Segunda pendiente
        float p= -1/(stru[3]-stru[2]);
        float y= (p*(x-stru[2]))+1;
        if(y >= c){ //Cortamos a la altura de c1
          y = c;
        }
        if(y > B[i]){
          B[i] = y;
        }
      }
      if(x==stru[2] && x==stru[3]){ //ultimos puntos iguales
        float y=c;
        if(y>B[i]){
          B[i]=y;
        }
      }
      if(x>stru[3]){
        float y=0;
        if(y>B[i]){
          B[i]=0;
        }
      }
      x += factor;
    }//////////////////////////////////////Se acaba el ciclo for
  }
  if(t ==3){ //Significa que tenemos solo una funcion triangular
    for(int i =0;i<300;i++){
      if(stru[0] <= x && x <= stru[1]){ //Primera Pendiente
        float p= 1/(stru[1]-stru[0]);
        float y = (p*(x-stru[1]))+1;
        if(y >= c){
          y=c;
        }
        if(y > B[i]){
          B[i]=y;
        }
      }
      if(stru[1] <= x && x <= stru[2]){ //Segunda pendiente
        float p= -1/(stru[2]-stru[1]);
        float y= (p*(x-stru[1]))+1;
        if(y >= c){ //Cortamos a la altura de c1
          y = c;
        }
        if(y > B[i]){
          B[i] = y;
        }
      }
      x += factor;
    }//////////////////////////////////////Se acaba ciclo for
  }
}///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float Fuzzy::defusi(float U_VOL[]){ //Metodo para defusificar el conjunto final B[]
  float x=U_VOL[0];
  float factor = (U_VOL[1] - U_VOL[0]) /resolution; //Define la resolucion del conjunto difuso
  float y0,area=0,res1=0;
  for(int i=0; i <resolution;i++){
    area= area+B[i];
    res1= res1+(B[i]*x);
    x += factor;
    B[i] = 0; 
  }
  if(area == 0){
    y0 = 0;
  }
  else{
  y0 = res1/area;
  }
  return y0;
}////////////////////////////////////////////////////
