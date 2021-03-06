/*
  CIC250 - Cálculo Numérico para Computação
  Exercicio prático 02 - 15/03/2017
  33592 - Gabriel Erzinger Dousseau

  Calculo de raizes reais de funções reais - metodo da Falsa Posição
*/
#include <bits/stdc++.h>

using namespace std;

double A, B;
const double precisao = 1e-3;

double f(double x) //Alterar este trecho para modificar a função
{
  return 2*x - pow(exp(1.0), -x);
}

void setA(double _a){A = _a;}
void setB(double _b){B = _b;}

int main(){
  double auxa, auxb;
  cout << "Posicao Falsa.:\nEntre com o intervalo [A, B] inicial \n";
  cin >> auxa >> auxb;
  setA(auxa); setB(auxb);
  int it = 0; // numero de iterações
  if(f(A)*f(B) > 0) {
    cout << "Nao existe raiz no intervalo especificado\n";
    return 0;
  }
  else
  {
    double meio;
    while(abs(A-B) > precisao)
    {
      it++;
      meio = (A*f(B) - B * f(A))/(f(B)- f(A));
      if(f(A) * f(meio) > 0)
        setA(meio);
      else
        setB(meio);
      if(it >= 50) break;
    }
    printf("Raiz encontrada em x : %lf\n Numero de iteracoes : %d\n", meio, it);
  }

}
