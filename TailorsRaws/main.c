#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double Tailor_Sin(double *x, int *n);

double Geron_Sqrt(double *x, int *n);

double Gregory_Ln(double *x, int *n);



int main()
{
//---------------------Preambula------------------------------------------------  
 
 
  printf("Sum of Tailor Raw for sin(x), sqrt(x), ln(x) ver 0.1 \n\n"
  
         "Date of compilation - " __DATE__"   " __TIME__
         "\n(c)zorroxied\n \n");
         
         
         
         
  printf("Enter the value for x:\n");
  double  x=0;
  scanf("%lf",&x);
  
  
  
  printf("Enter the number of itterations):\n");
  int  n=0;
  scanf("%d",&n);
  printf("\n");
//------------------------------------------------------------------------------  
  


 
  double SinValue = Tailor_Sin(&x,&n);
  
  double GeronSqrt = Geron_Sqrt(&x,&n);
  
  double GregoryLn = Gregory_Ln(&x,&n);
  

  double ln = log(x);
  double Sin = sin(x);
  double Sqrt = sqrtf(x);

  printf("Sin(x) = %-10.6lf StdSin  = %-10.6lf\n\n",SinValue, Sin);
  
if (x>0) printf("ln(x)  = %-10.6lf StdLn   = %-10.6lf\n\n",GregoryLn, ln);
  else printf("Calculation of the ln is impossible. Sorry. You are stupid.\n");
  
if (x>=0)  printf("Sqrt(x)= %-10.6lf StdSqrt = %-10.6lf\n",GeronSqrt, Sqrt);
   else printf("Calculation of the sqrt is impossible. Sorry. You are stupid.\n");

  
  
  system("PAUSE");	
  return 0;
}




//------------------------------------------------------------------------------
//������������ ������� ������:
//           x_n+1 = 0.5(x_n + a/x_n)

double Geron_Sqrt(double *x, int *n)
{
       double Function_Value = 1;
       
       double a = *x;
       int Itter = *n;
       
       int i = 0;
       for(i=1;i<=Itter;i++)
       {
                Function_Value=0.5*(Function_Value + a/Function_Value);
                }
                
       return Function_Value;
       }
       
       
       
       

//------------------------------------------------------------------------------
//���������� � ��� ������� sin(x):
//     sin(x) = x - (x^3)/3! + (x^5)/5! ........
//------------------------------------------------------------------------------

double Tailor_Sin(double *x, int *n)
{
       double Function_Value=0,
              Istina=sin(*x),
              Frac = 0,
              arg = *x;
       
       while (abs(arg)>2*M_PI)
       {
             if (arg>0) 
                arg -= 2*M_PI;
                
                else arg += 2*M_PI;
                } 
                
       double grade_X = arg;
       
       int nTerm=*n;
       double Factorial=1;
            
       int i=0;
       for(i=2;i<=nTerm+1;i++)
       {      
              Function_Value+=grade_X/Factorial;
              
              grade_X=grade_X*(arg)*(arg)*(-1);
              Factorial=Factorial*2*(i-1)*(2*i-1);
              
              if (i>150) 
                   {
                   printf("It's very much iiterations."
                   "I hope you will be satisfaction for my result\n"
                   "with 150 itterations.\n"); 
                   break;
                   }   
               }     
       return Function_Value;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//       ���������� � ��� ������������ ��������� �� ������� �������
//       ln(m) = 2*( (m-1)/(m+1) + 1/3*((m-1)/(m+1))^3 + ....... )


double Gregory_Ln(double *x, int *n)
{
       double argument = *x;   
       double Function_Value = 0;
     
       double Istina = log(*x);
       
       double y = (argument - 1)/(argument + 1);
       
       double Frac = 2*y;
       
       int factor = 1;

       int Itterations = *n;
       
       int i = 1;
       for( i ; i<=Itterations; i++)
            {
            Function_Value += Frac/factor;
            
            Frac *= (y*y);
            
            factor += 2;
            }     
       
       return Function_Value; 
       }
       
















