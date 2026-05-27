
/* Ziviani - Projeto de Algoritmos
7.9 - Grafos usando listas de adjacências
Busca em Profundidade */

#include<stdlib.h>
#include<stdio.h>

#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   100
#define TRUE            1
#define FALSE           0

typedef int TipoValorVertice;
typedef int TipoValorAresta;

typedef struct TipoItem {
  TipoValorVertice Vertice;
  TipoValorAresta Aresta;
} TipoItem;

typedef struct TipoCelula* TipoApontador;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct TipoLista {
  TipoApontador Primeiro;
  TipoApontador Ultimo;
} TipoLista;

typedef struct TipoGrafo {
  TipoLista Adj[MAXNUMVERTICES + 1];
  TipoValorVertice NumVertices;
  TipoValorAresta NumArestas;
} TipoGrafo;

typedef short TipoValorTempo;

typedef enum {
  branco, cinza, preto
} TipoCor;

//short i;
//int FimListaAdj;
TipoGrafo Grafo; // Vetores ficam melhor fora da pilha

TipoValorTempo d[MAXNUMVERTICES + 1], t[MAXNUMVERTICES + 1];
TipoCor Cor[MAXNUMVERTICES+1];
short Antecessor[MAXNUMVERTICES+1];

/*--Entram aqui os operadores do Programa 2.4--*/
void FLVazia(TipoLista *Lista) {
   Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Primeiro;
  Lista->Primeiro->Prox = NULL;
}  /* FLVazia */

char Vazia(TipoLista Lista) { 
  return (Lista.Primeiro == Lista.Ultimo);
}  /* Vazia */

void Insere(TipoItem *x, TipoLista *Lista) { 
  /*-- Insere depois do ultimo item da lista --*/
  Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Ultimo->Prox;
  Lista->Ultimo->Item = *x;
  Lista->Ultimo->Prox = NULL;
}  /* Insere */

/*-- Entram aqui os operadores do Programa 6.2 --*/
void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2, TipoValorAresta *Aresta, TipoGrafo *Grafo) { 
  TipoItem x;
  x.Vertice = *V2;
  x.Aresta = *Aresta;
  Insere(&x, &Grafo->Adj[*V1]);
}  /* InsereAresta */

void FGVazio(TipoGrafo *Grafo) {
  short i;
  for (i = 0; i <= Grafo->NumVertices - 1; i++)
    FLVazia(&Grafo->Adj[i]);
}  /* FGVazio */

char ExisteAresta(TipoValorVertice Vertice1, TipoValorVertice Vertice2, TipoGrafo *Grafo) {
   TipoApontador Aux;
  char EncontrouAresta = FALSE;
  Aux = Grafo->Adj[Vertice1].Primeiro->Prox;
  while (Aux != NULL && EncontrouAresta == FALSE) 
    { if (Vertice2 == Aux->Item.Vertice)
      EncontrouAresta = TRUE;
      Aux = Aux->Prox;
    }
  return EncontrouAresta;
}  /* ExisteAresta */

char ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo) { 
  return (Grafo->Adj[*Vertice].Primeiro == Grafo->Adj[*Vertice].Ultimo);
}  /* ListaAdjVazia */

TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo) { 
  return (Grafo->Adj[*Vertice].Primeiro->Prox);
}  /* PrimeiroListaAdj */

void ProxAdj(TipoValorVertice *Vertice, TipoValorVertice *Adj, TipoValorAresta *Aresta, TipoApontador *Prox, char *FimListaAdj) { 
  /* --Retorna Adj apontado por Prox--*/
  *Adj = (*Prox)->Item.Vertice;
  *Aresta = (*Prox)->Item.Aresta;
  *Prox = (*Prox)->Prox;
  if (*Prox == NULL) *FimListaAdj = TRUE;
}  /* ProxAdj- */

void ImprimeLista(TipoLista Lista) { 
  TipoApontador Aux;
  Aux = Lista.Primeiro->Prox;
  while (Aux != NULL) 
    { printf("%3d (%d)", Aux->Item.Vertice, Aux->Item.Aresta);
      Aux = Aux->Prox;
    }
}  /* ImprimeLista */

void ImprimeGrafo(TipoGrafo *Grafo) {
  short i;
  for (i = 0; i <= Grafo->NumVertices - 1; i++) 
    { printf("Vertice%2d:", i);
      if (!Vazia(Grafo->Adj[i])) ImprimeLista(Grafo->Adj[i]);
      putchar('\n');
    }
}  /* ImprimeGrafo */

void VisitaDfs(TipoValorVertice u, TipoGrafo *Grafo, TipoValorTempo* Tempo, TipoValorTempo* d, TipoValorTempo* t, TipoCor* Cor, short* Antecessor) { 
  char FimListaAdj;
  TipoValorAresta Peso;
  TipoApontador Aux; 
  TipoValorVertice v;

  Cor[u] = cinza;
  (*Tempo)++; 
  d[u] = (*Tempo);
  printf("Visita%2d Tempo descoberta:%2d cinza\n", u, d[u]);
  printf("Pressione ENTER para continuar\n\n");
  getchar();
  
  if (!ListaAdjVazia(&u, Grafo)) 
  { Aux = PrimeiroListaAdj(&u, Grafo);
    FimListaAdj = FALSE;
    while (!FimListaAdj) 
      { ProxAdj(&u, &v, &Peso, &Aux, &FimListaAdj);
        if (Cor[v] == branco) 
        { Antecessor[v] = u;
          VisitaDfs(v, Grafo, Tempo, d, t, Cor, Antecessor);
        }
      }
  }
  Cor[u] = preto; (*Tempo)++; t[u] = (*Tempo);
  printf("Visita%2d Tempo termino:%2d preto\n", u, t[u]);
  printf("Pressione ENTER para continuar\n\n");
  getchar();
} 

void BuscaEmProfundidade(TipoGrafo *Grafo) { 
  TipoValorVertice x; 
  TipoValorTempo Tempo;
  Tempo = 0;

  for (x = 0; x <= Grafo->NumVertices - 1; x++) { 
      Cor[x] = branco; 
      Antecessor[x] = -1; 
  }

  for (x = 0; x <= Grafo->NumVertices - 1; x++) { 
      if (Cor[x] == branco) {
        VisitaDfs(x, Grafo, &Tempo, d, t, Cor, Antecessor);
      }
  }
}

int Ciclo(TipoGrafo *Grafo) {
  TipoValorVertice x; 
  TipoValorTempo Tempo;
  Tempo = 0;
  int qntRetorno = 0;

  for (x = 0; x <= Grafo->NumVertices - 1; x++) { 
      Cor[x] = branco; 
      Antecessor[x] = -1; 
  }

  for (x = 0; x <= Grafo->NumVertices - 1; x++) {
      
      if (Cor[x] == branco) {
        VisitaDfs(x, Grafo, &Tempo, d, t, Cor, Antecessor);
      }
      
      if (Cor[x] == cinza) {
         qntRetorno += 1;
      }
   }

   if (qntRetorno > 0) {
      printf("O grafo G(%d,%d) é cíclico, e possui %d ciclos", Grafo->NumVertices, Grafo->NumArestas, qntRetorno);
      return 0;
   }
   else {
      printf("O grafo G(%d,%d) é acíclico", Grafo->NumVertices, Grafo->NumArestas);
     return 1;
   }
}

/* ============================================================= */

int main() {  
    
  /*-- Programa principal --*/
  TipoValorVertice V1, V2;
  TipoValorAresta A;
  TipoItem x;
  
  int NVertices;
  int NArestas;
  
  /* -- NumVertices: definido antes da leitura das arestas --*/
  /* -- NumArestas: inicializado com zero e incrementado a --*/
  /* -- cada chamada de InsereAresta                       --*/
  
  printf("No. vertices: ");
  scanf("%d", &NVertices);
  printf("No. arestas: ");
  scanf("%d%*[^\n]", &NArestas);
  getchar();
  
  Grafo.NumVertices = NVertices;
  Grafo.NumArestas = 0;
  FGVazio(&Grafo);
  
  for (int i = 0; i <= NArestas - 1; i++) { printf("Insere V1 -- V2 -- Aresta: ");
      scanf("%d%d%d%*[^\n]", &V1, &V2, &A);
      getchar();
      Grafo.NumArestas++;
      InsereAresta(&V1, &V2, &A, &Grafo);   /*1 chamada : G direcionado*/
      /*InsereAresta(V2, V1, A, Grafo);*/
      /*2 chamadas: G nao-direcionado*/
  }
    
  printf("\nImprimindo grafo...\n");
  ImprimeGrafo(&Grafo);
  
  printf("\nTipo de grafo...\n");
  Ciclo(&Grafo);
  
  printf("\nExecutando DFS...\n");
  BuscaEmProfundidade(&Grafo);

  return 0;
}
