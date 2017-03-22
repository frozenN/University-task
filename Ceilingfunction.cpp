#include <bits/stdc++.h>

using namespace std;

string formaArvore;
set<string> formasDiferentes;
// set armazena elementos unicos de um determinado td (string)

class node {
public:
  int valor;
  node *direita, *esquerda;
  node(){};
  node(int _valor)
  {
    valor = _valor;
    direita = esquerda = NULL;
  }

};

node *insereNo(node *R, int _valor)
{
  if(!R)
    return new node(_valor);
  if(_valor > R->valor)
    R->direita =  insereNo(R->direita, _valor);
  else
    R->esquerda = insereNo(R->esquerda, _valor);
  return R;
}

void infix(node *R)
{
  if(!R) return;
  if(R->esquerda)
  {
    formaArvore.push_back('E');
    infix(R->esquerda);
  }
  else
    formaArvore.push_back('e');
  if(R->direita)
  {
    formaArvore.push_back('R');
    infix(R->direita);
  }
  else
    formaArvore.push_back('r');

}

void solve()
{
  int n, k;
  scanf("%d %d", &n, &k);
  while(n--)
  {
    int inteiroLeitura;
    node *arvore = NULL;
    formaArvore.clear();
    formaArvore.push_back('G');
    for(int i = 0; i < k; ++i)
    {
      scanf("%d", &inteiroLeitura);
      arvore = insereNo(arvore, inteiroLeitura);
    }
    infix(arvore);
    formasDiferentes.insert(formaArvore);
  }
  printf("%d\n", (int)formasDiferentes.size());

}

int main()
{
  solve();
  return 0;
}
