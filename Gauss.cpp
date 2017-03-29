/*
  CIC250 - Cálculo Numérico para Computação
  Exercicio prático 04 - 29/03/2017
  33592 - Gabriel Erzinger Dousseau
  33508 - Rogerio da Silva Junior
  Resolução de sistemas lineares pelo método de Gauss
*/


#include <bits/stdc++.h>

using namespace std;

#define EPS 1e-10
#define INF 0x3f3f3f3f

const int N = 4; // Alterar N
const int M = 5; // Alterar M
double a[N+5][M+5]; //matriz de coeficientes
vector<double> res; //vetor de respostas, res[i] = resposta para a enesima variavel

void print(){
  for(int i = 0; i < N; ++i)
  {
    for(int j = 0; j < M; ++j)
    {
      if(j) printf(" ");
      printf("%.4lf", a[i][j]);
    }
    printf("\n");
  }
  printf("\n\n");

  return;
}

int gauss()
{//O(n²)
  int n = N;
  int m = M - 1;

  print();
  vector<int> preans(m, -1);
  for(int col = 0, lin = 0; col < m && lin < n; ++col)
  {
    int select = lin; //equacao selecionada
    for(int i = lin; i < n; ++i) //seleciona linhas
      if( abs(a[i][col]) > abs(a[select][col]) ) //seleciona a maior eq
        select = i;
    if( abs( a[select][col] ) < EPS ) //se for != 0
      continue;
    for(int i = col; i <= m; ++i) //troca as equações
      swap(a[select][i], a[lin][i]);
    preans[col] = lin; // associa coluna/linha/ eq

    for(int i = 0; i < n; ++i)
    {
      if( i != lin )
      {
        double coef = a[i][col] / a[lin][col]; //coeficiente de multiplicação
        for(int j = col; j <=m; ++j)
        {
          a[i][j] -= coef*a[lin][j]; // a[i][j] = a[i][j] - coef*a[linha][j]
        }
      }
    }
    lin++;
    print();
  }

  res.assign(m, 0);

  for(int i = 0; i < m; ++i) //para as variaveis
    if(preans[i] != -1)
      res[i] = a[preans[i]][m] / a[preans[i]][i]; //a[][m] é o resultado, a[][i] é o coeficiente livre

  for(int i = 0; i < n; ++i)
  {
    double sum = 0;
    for(int j = 0; j < m; ++j)
      sum += res[j] * a[i][j]; // multiplica o valor da variavel j pelo coeficiente a[i][j] e soma
    if(abs( a[i][m]-sum ) > EPS)
        return -1; // nao solucionou
  }

  for(int i = 0; i < m; ++i)
    if(preans[i] == -1)
      return INF;
}

void printans()
{
  printf("Solucoes: \n");
  for(int i = 0; i < res.size(); ++i)
  {
    if(i) printf(" ");
    printf("X[%d] = %g", i+1, res[i]);
  }
  printf("\n");
}

void input(){
  printf("Entre com a matriz A^(0)(%dx%d) (alterar N e M no programa), ie, o sistema de equacoes\n", N, M);
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < M; ++j)
      scanf("%lf", &a[i][j]);
}

int solve(){
  input();
  gauss();
  printans();
}

int main(){
  return !solve();
}
