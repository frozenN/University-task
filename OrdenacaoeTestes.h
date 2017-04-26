/* Gabriel Erzinger Dousseau - Universidade Federal de Itajuba */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//Auxiliares

void read_file(){
	freopen("/home/gabriel/Codigos/in", "r", stdin);
}

void write_file(){
	freopen("/home/gabriel/Codigos/out", "w", stdout);
}

void gera_ordenados(int v[], int tam){
	int i;
	for(i = 0; i < tam; ++i)
		v[i] = i;
}

void gera_aleatorio(int v[], int tam){
	int i;
	srand(time(NULL));
	for(i = 0; i < tam; ++i)
		v[i] = rand()%1000;
}

void printv(int v[], int n){
	int i;
	for( i = 0; i < n; ++i)
	{
			printf("%d ", v[i]);
	}
	printf("\n");
}

void scanv(int v[], int n){
	int i;
	for(i = 0; i < n; ++i)
		scanf("%d", &v[i]);
}

void auxswap(int a, int b){
	int aux = a;
	a = b;
	b = aux;
	return;
}

void swap(int *a, int *b){
	*a = *a^*b;
	*b = *b^*a;
	*a = *a^*b;	
	return;
}

int particiona(int v[], int l, int r){
	int s = v[l]; // s é o inicio
	int i = l+1; // i é o segundo elemento
	int j = r; // j é o ultimo elemento
	while(1)
	{
		while(i<=r && v[i] <= s) ++i; // enquanto i(seg1) for menor= que (r) e v[i] menor que o primeiro elemento
		while(s < v[j]) --j; // enquanto o primeiro é menor que o ultimo, desloca do ultimo para o primeiro
		if(i>=j) break; // se o primeiro apontador passou o segundo, já deu já
		swap(&v[i], &v[j]); // enquanto i <= j, inverte v[i] e v[j]
		++i, --j; // i anda 1, j volta 1
	}

	v[l] = v[j], v[j] = s; //ultima troca
	return j; // retorna o meio
}

int min(int v[], int pos, int tam){
	int j;
	int posicao_menor = pos;
	for(j = pos+1; j < tam; ++j)
	{
		if(v[j] < v[posicao_menor])
			posicao_menor = j;
	}
	return posicao_menor;
}

int bsort(int vetor[], int n){
	int aux, cmp=0;
	int i, j;
	for(i=n-1; i >= 1; i--) {   
    for(j=0; j < i ; j++){   
   	  cmp++;
      if(vetor[j]>vetor[j+1]) {
        aux = vetor[j];
        vetor[j] = vetor[j+1];
        vetor[j+1] = aux;
        printv(vetor,n);	
        }
      }
	}
	return cmp;
}


int selectionsort(int vetor3[], int n){
	int i, posicao_menor, cmp=0;
	for(i = 0; i < n-1; ++i)
	{
		posicao_menor = min(vetor3, i, n);
		cmp+=(n-i+1)+1;
		if(posicao_menor != i)
		{
			swap(&(vetor3[i]), &(vetor3[posicao_menor]));
			printv(vetor3, n);
		}
	}
	return cmp;
}


void insertion(int v[], int n){
	int i, j, k;
	for(j = 1; j < n; ++j)
	{
		k = v[j];
		i = j - 1;
		while(i >= 0 && v[i] > k)
		{
			v[i+1] = v[i];
			i--;
		}
		v[i+1] = k;
	}
}

void quicksort(int vet[], int inicio, int fim){
	int pivo;
	if(inicio < fim)
	{
		pivo = particiona(vet, inicio, fim);
		quicksort(vet, inicio, pivo-1);
		quicksort(vet, pivo+1, fim);
	}
	return;
}

void mS(int v[], int b, int e){
	int i, j, k, mid, *v2;
	if(b==e) return;
	int aux = b+e;
	mid = aux>>1;
	mS(v, b, mid);
	mS(v, mid+1, e);

	i = b;
	j = mid+1;
	k = 0;

	v2 = (int *) malloc(sizeof(int) * (e - b +1));

	while(i < mid+1 || j < e + 1)
	{
		if(i == mid + 1)
		{
			v2[k] = v[j];
			j++;
			k++;
		}
		else
		{
			if(j==e+1)
			{
				v2[k] = v[i];
				i++;
				k++;
			}
			else
			{
				if(v[i] < v[j])
				{
					v2[k] = v[i];
					i++;
					k++;
				}
				else
				{
					v2[k] = v[j];
					j++;
					k++;
				}
			}
		}
	}
	//printv(v, n);
	for(i = b; i <= e; ++i)
		v[i] = v2[i-b];
	free(v2);
}

void processo1(int vetor[], int n){
	clock_t t;
	t = clock();
	mS(vetor, 0, n-1);
	t = clock() - t;
	double timet = ((double)t)/(CLOCKS_PER_SEC/1);
	printf("\n Tempo Merge Sort : %lf\n", timet);
}

void processo2(int vetor2[], int n){
	clock_t t;
	t = clock();
	insertion(vetor2, n);
	t = clock() - t;
	double timet = ((double)t)/(CLOCKS_PER_SEC/1);
	//printf("\n Tempo Insertion Sort : %lf\n", timet);
}

void processo3(int vetor3[], int n){
	clock_t t;
	t = clock();
	selectionsort(vetor3, n);
	t = clock() - t;
	double timet = ((double)t)/(CLOCKS_PER_SEC/1);
	printf("\n Tempo Selection Sort : %lf\n", timet);
}

void processo4(int vetor3[], int n){
	clock_t t;
	t = clock();
	quicksort(vetor3,0, n);
	t = clock() - t;
	double timet = ((double)t)/(CLOCKS_PER_SEC/1);
	printf("\n Tempo QuickSort : %lf clocks\n", timet);
}

int binary_search(int v[], int x, int l, int r){

 	int mid = (l+r)/2;
 	
 	if(v[mid] == x) return mid;
 	if(l == r)	return -1;
 	
 	else if(v[mid] > x)  return binary_search(v, x, l, mid-1);
 	else if(v[mid] < x)  return binary_search(v, x, mid+1, r);
}

int sequencial_search(int v[], int x, int tam){
	int i;
	for(i = 0; i < tam; ++i){
		if(v[i] == x) return i;
	}

	return -1;
}
