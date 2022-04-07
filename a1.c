#include <stdio.h>
#include <math.h>


int x = 0;
int y = 0;
double lambda = 0;
double alpha = 0;
double deltaY = 0;
double deltaX = 0;
double p = 0;
double last_pump_y_pos = 0; // sorry for English variable names, my German is not so good :)
double last_pump_x_pos = 0;
double new_pump_y_pos = 0;
double new_pump_x_pos = 0;
double hohe = 0;

double reibungsverlust(int durchfluss);
double hangneigung(int hor, int ver);
double hoehendifferenz(double lamb, double alph);
double horiz_abstand(double dY, double alph);
double druckverlust(double dY, double lamb, double alph);
int flowrate();


int main(){
  int dfluss = 0;


  dfluss = flowrate();


   printf("Horizontale Distanz [m]: ");
   scanf("%d", &x);

   while (x <= 0){
     printf("Invalide Eingabe!\n");
     printf("Horizontale Distanz [m]: ");
     scanf("%d", &x);
   }

   printf("Vertikale Distanz [m]: ");
   scanf("%d", &y);

   while (y <= 0){
     printf("Invalide Eingabe!\n");
     printf("Vertikale Distanz [m]: ");
     scanf("%d", &y);
   }

   

   lambda = reibungsverlust(dfluss);

   alpha = hangneigung(x,y);

   deltaY = hoehendifferenz(lambda, alpha);
  


   deltaX = horiz_abstand(deltaY, alpha);


   printf("\nZiel: (%d, %d)\n", x, y);
   printf("Neigung [rad]: %.4f\n", alpha);
   printf("Durchfluss [l/min]: %d\n", dfluss);
   printf("Reibungsbeiwert [bar/m]: %.4f\n", lambda);

   hohe = y-last_pump_y_pos;
   p = druckverlust(hohe, lambda, alpha);
   int i = 1; // pump counter

   if (p < 6){
     while (p < 6){
       new_pump_x_pos = last_pump_x_pos + deltaX;
       new_pump_y_pos = last_pump_y_pos + deltaY;
     if (new_pump_x_pos > x){
       new_pump_x_pos = x;
       new_pump_y_pos = y;
     }
     printf("  Pumpe%d: (%.2f, %.2f)\n", i, new_pump_x_pos, new_pump_y_pos);
     last_pump_x_pos = new_pump_x_pos;
     last_pump_y_pos = new_pump_y_pos;
     hohe = y-last_pump_y_pos;
     p = druckverlust(hohe, lambda, alpha);
     i = i+1;
     }
   } else {
     printf("  Keine zusaetzliche Pumpe notwendig!\n");

   }
   
   printf("Austrittsdruck Zielpunkt [bar]: %.2f\n", p);



   return 0;
}


double reibungsverlust(int durchfluss){
    double rv = 0;

     if (durchfluss <= 200){
      rv = 0.001;
   } else if ((durchfluss >= 201)&&(durchfluss <= 400)){
      rv = 0.0025;
   } else if ((durchfluss >= 401)&&(durchfluss <= 600)){
      rv = 0.005;
   } else if ((durchfluss >= 601)&&(durchfluss <= 800)){
      rv = 0.01;
   } else if ((durchfluss >= 801)&&(durchfluss <= 1000)){
      rv = 0.015;
   } else if ((durchfluss >= 1001)&&(durchfluss <= 1200)){
      rv = 0.025;
   }

   return rv;

}

double hangneigung(int hor, int ver){
  double hn = 0;
  hn = atan((double)ver/(double)hor);
  return hn;
}

double hoehendifferenz(double lamb, double alph){
  double dY = 0;
  dY = 8.5/(0.1+lamb/sin(alph));
  return dY;
}

double horiz_abstand(double dY, double alph){
  double dX = 0;
  dX = dY/tan(alph);
  return dX;
}

double druckverlust(double dY, double lamb, double alph){
  double dv = 0;
  dv =  10 - (0.1*dY + lamb * (dY/sin(alph)));
  return dv;

}

int flowrate(){
  int flowrate = 0;
     printf("Erforderlicher Durchfluss [l/min]: ");
   scanf("%d", &flowrate);

   while ((flowrate < 100)||(flowrate > 1200)){
     printf("Invalide Eingabe! Der Durchfluss muss mindestens 100 l/min und maximal 1200 l/min betragen.\n");
     printf("Erforderlicher Durchfluss [l/min]: ");
     scanf("%d", &flowrate);
   }
   return flowrate;

}