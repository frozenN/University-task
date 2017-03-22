//CIC250 - Matematica Computacional
//Exercicio Pratico 03 - 22/03/2017
//33592 - Gabriel Erzinger Dousseau
//Calculo de raizes reais de funcoes reais - Metodo de Newton
#include <bits/stdc++.h>

using namespace std;

double f(double x)
{//Altere a função neste ponto
  return -1 + 5.5*x - 4*x*x + 0.5*x*x*x;
}

double dfdx(double x)
{//Altere a derivada da função neste ponto
  return 5.5 - 8*x + 1.5*x*x;
}


int main(){
  double po, p;
  int n;
  printf("Entre com a aproximacao inicial e o numero de interacoes\n");
  cin >> po >> n;

  for(int k = 1; k<=n ; ++k)
  {
    p = po - (f(po) / dfdx(po));
    po = p;
    if(abs(f(po)) < 0.000000001 ) break;
  }

  printf("Raiz encontrada: %lf\n", po);

}
