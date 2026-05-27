/* Ziviani - Projeto de Algoritmos
Busca em Largura com listas de adjacência
/* 16/04/03 - Ubu */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>

/* Implementacao TAD Grafo com listas/apontadores */

#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   100
#define FALSE           0
#define TRUE            1
#define INFINITO        INT_MAX

/*--Entram aqui os tipos do Programa 7.4 --*/
typedef int TipoValorVertice;
typedef int TipoPeso;
typedef struct TipoItem {
  TipoValorVertice Vertice;
  TipoPeso Peso;
} TipoItem;

typedef struct TipoCelula* TipoApontador;
typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;
typedef struct TipoLista {
  TipoApontador Primeiro, Ultimo;
} TipoLista;
typedef struct TipoFila {
  TipoApontador Frente, Tras;
} TipoFila;
typedef struct TipoGrafo {
  TipoLista Adj[MAXNUMVERTICES + 1];
  TipoValorVertice NumVertices;
  int NumArestas;
} TipoGrafo;
typedef short  TipoValorTempo;
typedef enum {
  branco, cinza, preto
} TipoCor;

int i, NArestas;
short FimListaAdj;
TipoValorVertice V1, V2, Adj;
TipoPeso Peso;
TipoGrafo Grafo; // Global, só porque pode ser grande
TipoValorVertice NVertices;
TipoItem Origem;
int Dist[MAXNUMVERTICES + 1]; // Esses vetores podem ser globais, se forem grandes
TipoCor Cor[MAXNUMVERTICES + 1];
int Antecessor[MAXNUMVERTICES + 1];

/*--Entram aqui os operadores do Programa 2.4--*/
void FLVazia(TipoLista *Lista)
{ Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Primeiro;
  Lista->Primeiro->Prox = NULL;
} 

short ListaVazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem *Origem, TipoLista *Lista)
{ /*-- Insere depois do ultimo item da lista --*/
  Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Ultimo->Prox;
  Lista->Ultimo->Item = *Origem;
  Lista->Ultimo->Prox = NULL;
}

/* -- Entram aqui os operadores do Programa 2.19 --*/
 void FFVazia(TipoFila *Fila)
{ Fila->Frente = (TipoApontador)malloc(sizeof(TipoCelula));
  Fila->Tras = Fila->Frente;
  Fila->Frente->Prox = NULL;
}

short FilaVazia(TipoFila Fila)
{ return (Fila.Frente == Fila.Tras);
}

void Enfileira(TipoItem Origem, TipoFila *Fila)
{ Fila->Tras->Prox =(TipoApontador)malloc(sizeof(TipoCelula));
  Fila->Tras = Fila->Tras->Prox;
  Fila->Tras->Item = Origem;
  Fila->Tras->Prox = NULL;
}

void Desenfileira(TipoFila *Fila, TipoItem *Item)
{ TipoApontador q;
  if (FilaVazia(*Fila)) 
  { printf(" Erro: fila está vazia\n");
    return;
  }
  q = Fila->Frente;
  Fila->Frente = Fila->Frente->Prox;
  *Item = Fila->Frente->Item;
  free(q);
}  

void ImprimeFila(TipoFila Fila)
{ TipoApontador Aux;
  Aux = Fila.Frente->Prox;
  while (Aux != NULL) 
    { printf("%3d (%d)", Aux->Item.Vertice, Aux->Item.Peso);
      Aux = Aux->Prox;
    }
}  

/*-- Entram aqui os operadores do Programa 7.2 --*/
void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2,
             TipoPeso *Peso, TipoGrafo *Grafo)
{ TipoItem Origem;
  Origem.Vertice = *V2;
  Origem.Peso = *Peso;
  Insere(&Origem, &Grafo->Adj[*V1]);
}

void FGVazio(TipoGrafo *Grafo)
{ short i;
  for (i = 0; i <= Grafo->NumVertices - 1; i++)
    FLVazia(&Grafo->Adj[i]);
}

short ExisteAresta(TipoValorVertice Vertice1,
           TipoValorVertice Vertice2, TipoGrafo *Grafo)
{ TipoApontador Aux;
  short EncontrouAresta = FALSE;
  Aux = Grafo->Adj[Vertice1].Primeiro->Prox;
  while (Aux != NULL && EncontrouAresta == FALSE) 
    { if (Vertice2 == Aux->Item.Vertice)
        EncontrouAresta = TRUE;
      Aux = Aux->Prox;
    }
  return EncontrouAresta;
} 

short ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo)
{ return (Grafo->Adj[*Vertice].Primeiro == Grafo->Adj[*Vertice].Ultimo);
}

TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo)
{ return (Grafo->Adj[*Vertice].Primeiro->Prox);
}  

void ProxAdj(TipoValorVertice *Vertice, TipoValorVertice *Adj,
            TipoPeso *Peso, TipoApontador* Prox, short *FimListaAdj)
{  /* --Retorna Adj apontado por Prox--*/
  *Adj = (*Prox)->Item.Vertice;
  *Peso = (*Prox)->Item.Peso;
  *Prox = (*Prox)->Prox;
  if (*Prox == NULL)
    *FimListaAdj = TRUE;
}

void ImprimeLista(TipoLista Lista)
{ TipoApontador Aux;
  Aux = Lista.Primeiro->Prox;
  while (Aux != NULL) 
    { printf("%d (%d)  ", Aux->Item.Vertice, Aux->Item.Peso);
      Aux = Aux->Prox;
    }
} 

void ImprimeGrafo(TipoGrafo *Grafo)
{ int i;
  for (i = 0; i <= Grafo->NumVertices - 1; i++) 
    { printf("Vertice %2d: ", i);
      if (!ListaVazia(Grafo->Adj[i]))
        ImprimeLista(Grafo->Adj[i]);
      putchar('\n');
    }
} 

void VisitaBfs(TipoValorVertice u, TipoGrafo *Grafo, 
               int *Dist, TipoCor *Cor, int *Antecessor)
{ TipoValorVertice v;
  TipoApontador Aux;
  short FimListaAdj;
  TipoPeso Peso;
  TipoItem Item;
  TipoFila Fila;
  
  Cor[u] = cinza;
  Dist[u] = 0;
  FFVazia(&Fila);
  Item.Vertice = u;
  Item.Peso = 0;
  Enfileira(Item, &Fila);
  printf("Visita origem; %2d - Cor: cinza - F: ", u);
  ImprimeFila(Fila);
  getchar();
  while (!FilaVazia(Fila)) 
  { Desenfileira(&Fila, &Item);
    u = Item.Vertice;
    if (!ListaAdjVazia(&u, Grafo)) 
    { Aux = PrimeiroListaAdj(&u, Grafo);
      FimListaAdj = FALSE;
      while (FimListaAdj == FALSE) 
      { ProxAdj(&u, &v, &Peso, &Aux, &FimListaAdj);
        if (Cor[v] != branco) {
            continue;
        }
        Cor[v] = cinza;
        Dist[v] = Dist[u] + 1;
        Antecessor[v] = u;
        Item.Vertice = v;
        Item.Peso = Peso;
        Enfileira(Item, &Fila);
      }
    }
    Cor[u] = preto;
    printf("Visita: %2d - Dist: %2d - Cor: preto - F: ", u, Dist[u]);
    ImprimeFila(Fila);
    getchar();
  }
}  

void BuscaEmLargura(TipoValorVertice Origem, TipoGrafo *Grafo) {

    TipoValorVertice x;
    int Vez;
    
    for (x = 0; x <= Grafo->NumVertices - 1; x++) 
        { Cor[x] = branco;
        Dist[x] = INFINITO;
        Antecessor[x] = -1;
        }
    for (x = 0; x <= Grafo->NumVertices - 1; x++) 
        { 
        Vez = (Origem + x) % Grafo->NumVertices;
        if (Cor[Vez] == branco) {
            VisitaBfs(Vez, Grafo, Dist, Cor, Antecessor);
        }
    }
}

void ImprimeCaminho(TipoValorVertice Origem, TipoValorVertice v, TipoGrafo *Grafo, int *Dist , TipoCor *Cor, int *Antecessor) { 
    if (Origem == v) { 
        printf ("%d " , Origem); 
        return; 
    }
    if (Antecessor[v] == -1) {
        printf ("Não existe caminho de %d até %d" , Origem, v);
    }
    else { 
        ImprimeCaminho(Origem, Antecessor[v], Grafo, Dist, Cor, Antecessor); 
        printf ("%d " , v);
    }
}

/* ============================================================= */

int main() {
    system("cls");
    setlocale(LC_ALL,".UTF-8");

    /*-- Programa principal --*/

    printf("\n--- TEORIA DOS GRAFOS ---\n\n");

    /* -- NumVertices: definido antes da leitura das arestas --*/
    /* -- NumArestas: inicializado com zero e incrementando a --*/
    /* -- cada chamada de InsereAresta                       --*/

    printf("No. vertices: ");
    scanf("%d%*[^\n]", &NVertices);

    printf("No. arestas: ");
    scanf("%d%*[^\n]", &NArestas);

    Grafo.NumVertices = NVertices;
    Grafo.NumArestas = 0;
    FGVazio(&Grafo);

    for (int i = 0; i <= NArestas - 1; i++) { 
        printf("\nInsere V1 -- V2 -- Peso: ");
        scanf("%d %d %d%*[^\n]", &V1, &V2, &Peso);
        getchar();

        Grafo.NumArestas++;
        InsereAresta(&V1, &V2, &Peso, &Grafo);   /*1 chamada : G direcionado*/
        InsereAresta(&V2, &V1, &Peso, &Grafo);   /*2 chamadas: G nao-direcionado*/
    }

    printf("\nImprimindo Grafo:\n\n");
    ImprimeGrafo(&Grafo);
    getchar();

    printf("\nImprimindo Caminhos (digite -1 -1 para sair):\n\n");
    
    do { 
        printf("\n\nImprime caminho: V1 -- V2: ");
        scanf("%d %d%*[^\n]", &V1, &V2);

        getchar();

        if(V1 == -1 || V2 == -1) {
            break;
        }

        BuscaEmLargura(V1, &Grafo);

        ImprimeCaminho(V1, V2, &Grafo, Dist, Cor, Antecessor);

    } while (1);

    getchar();
    
    return 0;
}
