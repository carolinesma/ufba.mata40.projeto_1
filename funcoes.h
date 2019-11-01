#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

typedef struct TipoCelula *TipoApontador;
typedef struct TipoCelula TipoCelula;
typedef struct TipoLista TipoLista;
void inicializa (TipoLista *lista);
TipoApontador criarNo ();
int vazia (TipoLista *lista);
void inserir (TipoLista *lista, TipoCelula *novo);
TipoApontador buscaCidade (TipoLista *lista, TipoApontador noh, char nome[20]);
void imprimir (TipoLista *lista);
int lerDados (TipoLista *lista);
void subListaEstado(TipoLista *lista);
void menorIdh(TipoLista *lista);
void menorIdh(TipoLista *lista);
void subListaIdh (TipoLista *lista);
TipoApontador buscaEstado (TipoLista *lista, char estado[50]);
void dadosDeUmaCidade (TipoLista *lista, char cidade[50]);
void dadosEstado (TipoLista *lista, char estado[50]);
void imprimirEstado (TipoApontador Estado);
void zerarMarcador(TipoLista *lista);
void pibMaior(TipoLista *lista);
void pibMenor(TipoLista *lista);
void popMaior(TipoLista *lista);
void listadeEstados(TipoLista *lista, TipoLista *estados);
void imprimirIdhOrdenado (TipoLista *estados);

#endif // FUNCOES_H_INCLUDED
