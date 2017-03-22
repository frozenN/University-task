//CIC250 - Matematica Computacional
//Exercicio Pratico 03 - 22/03/2017
//33592 - Gabriel Erzinger Dousseau
//Calculo de raizes reais de funcoes reais - Metodo de Newton
#include <bits/stdc++.h>

using namespace std;

double f(double x)
{//Altere a função neste ponto
  return sin(x) + cos(1+x*x) - 1;
}


int main(){
  double x0, x1, x3;
  int n;
  while(1){
    printf("Entre com x-1, x0  e o numero de interacoes\n");
    cin >> x0 >> x1 >> n;
    if(f(x0)*f(x1) < 0) break;
    else
    {
      printf("x0 e x1 nao possuem sinais opostos\n");
    }
  }

  for(int k = 1; k<=n ; ++k)
  {
    x3 = (x0*(f(x1)) - x1*(f(x0)))/(f(x1)-f(x0));
    x0 = x1;
    x1 = x3;
  }

  printf("Raiz encontrada: %lf\n", x3);

}
