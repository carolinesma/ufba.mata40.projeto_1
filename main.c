/***Trabalho prático 1 - Estrutura de dados e Algorítimos
    Caroline da Silva Morais Alves
    Prof Leandro Andrade
    TAD do tipo fila para gerenciar dados de cidades
    brasileiras como população, idh e renda per capita***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

/* ESTRUTURA DA LISTA*/

typedef struct TipoCelula *TipoApontador;
typedef struct TipoCelula{
    int indice;
    int marcador;
    char cidade[50];
    char estado[50];
    int populacao;
    double pib;
    float idh;
    TipoApontador prox, ant, pEstado, pIdh, aIdh;

}TipoCelula;

typedef struct TipoLista{
    TipoApontador primeiro, ultimo, primeiroIdh, ultimoIdh;

}TipoLista;

void inicializa (TipoLista *lista){
    lista->primeiro = lista->ultimo = lista->primeiroIdh = lista->ultimoIdh = NULL;

}
TipoApontador criarNo (){
    TipoApontador novo;

    novo = (TipoApontador)malloc(sizeof(TipoCelula));
    novo->ant = NULL;
    novo->prox = NULL;
    novo->pEstado = NULL;
    novo->aIdh = NULL;
    novo->pIdh = NULL;

return novo;
}

/* FUNÇÕES */

int vazia (TipoLista *lista){ //VERIFICA SE A LISTA ESTÁ VAZIA
    if (lista->primeiro == NULL)
        return 1;
    else
        return 0;
}
void inserir (TipoLista *lista, TipoCelula *novo){ //INSERE OS NÓS NA LISTA
    if (vazia(lista))
        lista->primeiro = novo;
    else{
       lista->ultimo->prox = novo;
       novo->ant = lista->ultimo;}
    lista->ultimo = novo;
}
TipoApontador buscaCidade (TipoLista *lista, TipoApontador noh, char nome[20]){ //BUSCA UMA CIDADE A PARTIR DA POSIÇÃO DO NÓ DADO
    TipoApontador aux;
    aux = noh;

    if (!vazia(lista)){
        while (aux!=NULL){
            if (strcmp(aux->cidade, nome)==0)
                return (aux);
            aux = aux->prox;}
    }
return aux;
}

void imprimirListaIdh (TipoLista *lista){ //IMPRIME A LISTA IDH EM DECRESCENTE
    TipoApontador aux;
    int i;
    aux = lista->ultimoIdh;

    while (aux!=NULL){
            printf("%d \n", i++);
        printf("nome: %s\n", aux->cidade);
        printf("estado: %s\n", aux->estado);
        printf("populacao: %d\n", aux->populacao);
        printf("pib per capita: %lf\n", aux->pib);
        printf("idh: %f\n\n", aux->idh);
        aux = aux->aIdh;
    }
}

int lerDados (TipoLista *lista){ //LER DADOS DE UM ARQUIVO E MONTA A LISTA
    TipoApontador novo;
    char linha[200], *string;
    int populacao, cont;
    double pib;
    float idh;
    FILE *dados;
    cont = 1;

    dados =  fopen("data.csv","r");

    if(dados == NULL){
        printf("Erro de leitura de arquivo\n");
        return 0;}
    else {
        fgets(linha, 200, dados);
        while(fgets(linha, 200, dados)!=NULL){
            novo = criarNo();

            novo->indice = cont;
            novo->marcador = 0;
            string = strtok(linha, ";");
            strcpy(novo->cidade, string);
            string = strtok(NULL, ";");
            strcpy(novo->estado, string);
            string = strtok(NULL, ";");
            sscanf(string, "%d", &populacao);
            novo->populacao = populacao;
            string = strtok(NULL, ";");
            sscanf(string, "%lf", &pib);
            novo->pib = pib;
            string = strtok(NULL, ";");
            sscanf(string, "%f", &idh);
            novo->idh = idh;

            inserir(lista, novo);
            cont ++;}
}
fclose(dados);

subListaIdh(lista);
subListaEstado(lista);

return 1;
}

void subListaEstado(TipoLista *lista){ //CRIA SUBCONJUNTOS DE LISTA COM O PONTEIRO PEstado
    TipoApontador aux1, aux2;

    aux1 = lista->primeiro;
    aux1->marcador = 1;                                         //identifica os nós já comparados
    aux2 = aux1->prox;

    if (!vazia(lista)){
        while((aux1!=NULL)&&(aux2!=NULL)){
            while(aux2!=NULL){                              //laço para busca dos estados correspondente
                if(strcmp(aux1->estado,aux2->estado)==0){   //comprara se os estados são iguais e realiza a associação com o ponteiro
                    aux1->pEstado = aux2;
                    aux1 = aux2;
                    aux1->marcador = 1;}
                aux2 = aux2->prox;}
                                                            //iniciasliza novos ponteiros para verificação de novo grupo de municipios
            aux1 = lista->primeiro;
            while((aux1!=NULL)&&(aux1->marcador==1)){
                aux1 = aux1->prox;}

            if(aux1!=NULL){
                aux1->marcador = 1;
                aux2 = aux1;
                while((aux2!=NULL)&&(aux2->marcador==1))
                    aux2 = aux2->prox;}
        }
    zerarMarcador(lista);
    }
return;
}

void menorIdh(TipoLista *lista){ //ENCONTRA A CIDADE COM MENOR IDH E DIRECIONA UM PONTEIRO PARA ELA
    TipoApontador aux, menor;
    aux = lista->primeiro;
    menor = aux;

    if(!vazia(lista)){
        while(aux!=NULL){
            if(aux->idh <= menor->idh){
                menor = aux;}
            aux = aux->prox;}
    }
    lista->primeiroIdh = menor;
return;
}

void subListaIdh (TipoLista *lista){//CRIA SUBLISTA ORDENADA POR IDH
    TipoApontador aux, menor, anterior;
    menorIdh(lista);

    aux = lista->primeiro;
    menor = aux;
    anterior = lista->primeiroIdh;
    anterior->marcador = 1;

    if(!vazia(lista)){
        while(menor!=NULL){
            while(aux!=NULL){
                if((aux->idh <= menor->idh)&&(aux->marcador!=1)){
                    menor = aux;}
                aux = aux->prox;}

                menor->marcador = 1;
                anterior->pIdh = menor;
                menor->aIdh = anterior;
                anterior = menor;
                lista->ultimoIdh = menor;
                aux = lista->primeiro;
                menor = aux;

                while((menor!=NULL)&&(menor->marcador == 1)) // o nó precisa não ter sido contabilizado
                    menor = menor->prox;
                }
    zerarMarcador(lista);
        }

return;
}

TipoApontador buscaEstado (TipoLista *lista, char estado[50]){//RETORNA PRIMEIRO NÓ PERTENCENTE A UM ESTADO
    TipoApontador aux;
    aux = lista->primeiro;

    while((aux!=NULL)&&(strcmp(aux->estado, estado)!=0))
        aux = aux->prox;

return aux;
}

void dadosDeUmaCidade (TipoLista *lista, char cidade[50]){ //OP = c IMPRIMME DADOS DE UMA CIDADE
    TipoApontador aux;

    aux = buscaCidade(lista, lista->primeiro, cidade);

    while(aux!=NULL){
        printf("nome: %s\n", aux->cidade);
        printf("estado: %s\n", aux->estado);
        printf("populacao: %d\n", aux->populacao);
        printf("pib per capita: %lf\n", aux->pib);
        printf("idh: %f\n\n", aux->idh);
        aux = buscaCidade(lista, aux->prox, cidade);}

return;
}

void dadosEstado (TipoLista *lista, char estado[50]){ //OP = e IMPRIME DADOS DE UM ESTADO
    TipoApontador aux;
    int cont = 0;
    int populacao = 0;
    double pib = 0;
    float idh = 0;

    aux = buscaEstado(lista, estado);

        if (!vazia(lista)){
            if(aux!=NULL){
                while (aux!=NULL){
                    populacao = aux->populacao + populacao;
                    pib = aux->pib + pib;
                    idh = aux->idh + idh;
                    cont++;
                    aux = aux->pEstado;}
            }
        }

    if(cont>0){
        printf("estado: %s\n", estado);
        printf("numero de municipios: %d\n", cont);
        printf("populacao: %d\n", populacao);
        printf("pib per capita %lf\n", pib);
        printf("idh: %f\n", idh/cont);}

return;
}

void zerarMarcador(TipoLista *lista){ //ZERA OS MARCADORES AUXILIARES
    TipoApontador aux;
    aux = lista->primeiro;

    while(aux!=NULL){
       aux->marcador = 0;
       aux = aux->prox;
    }
return;
}

void pibMaior(TipoLista *lista){ //OP = a IMPRIME 10 MAIORES PIBS
    TipoApontador aux, maior;
    int i, quantidade;
    quantidade = 10;

    aux = lista->primeiro;
    maior = aux;

    if(!vazia(lista)){
        for(i=0; i<quantidade; i++){
            while(aux!=NULL){
                if((aux->pib >= maior->pib)&&(aux->marcador!=1))
                    maior = aux;
                aux = aux->prox;}
                if(maior->marcador!=1){
                    printf("nome: %s\n", maior->cidade);
                    printf("estado: %s\n", maior->estado);
                    printf("populacao: %d\n", maior->populacao);
                    printf("pib per capita: %lf\n", maior->pib);
                    printf("idh: %f\n", maior->idh);
                    printf("\n");
                    maior->marcador = 1;
                    aux = lista->primeiro;
                    maior = aux;}
                    }
        zerarMarcador(lista);
        }
return;
}

void pibMenor(TipoLista *lista){ //OP = z IMPRIME 10 MENORES PIBS
    TipoApontador aux, menor;
    int i, quantidade;
    quantidade = 10;

    aux = lista->primeiro;
    menor = aux;


    if(!vazia(lista)){
        for(i=0; i<quantidade; i++){
            while(aux!=NULL){
                if((aux->pib <= menor->pib)&&(aux->marcador!=1))
                    menor = aux;
                aux = aux->prox;}
                if(menor->marcador!=1){
                    printf("nome: %s\n", menor->cidade);
                    printf("estado: %s\n", menor->estado);
                    printf("populacao: %d\n", menor->populacao);
                    printf("pib per capita: %lf\n", menor->pib);
                    printf("idh: %f\n", menor->idh);
                    printf("\n");
                    menor->marcador = 1;
                    aux = lista->primeiro;
                    menor = aux;}
                    }
        zerarMarcador(lista);
        }
return;
}

void popMaior(TipoLista *lista){ //OP = P IMPRIME 10 MAIORES POPULACOES
    TipoApontador aux, maior;
    int i, quantidade;
    quantidade = 10;

    aux = lista->primeiro;
    maior = aux;

    if(!vazia(lista)){
        for(i=0; i<quantidade; i++){
            while(aux!=NULL){
                if((aux->populacao >= maior->populacao)&&(aux->marcador!=1))
                    maior = aux;
                aux = aux->prox;}
                if(maior->marcador!=1){
                    printf("nome: %s\n", maior->cidade);
                    printf("estado: %s\n", maior->estado);
                    printf("populacao: %d\n", maior->populacao);
                    printf("pib per capita: %lf\n", maior->pib);
                    printf("idh: %f\n", maior->idh);
                    printf("\n");
                    maior->marcador = 1;
                    aux = lista->primeiro;
                    maior = aux;}
                    }
        zerarMarcador(lista);
        }
return;
}

void listadeEstados(TipoLista *lista, TipoLista *estados){ //CRIA UMA LISTA COM INFORMAÇÕES DOS ESTADOS
    TipoApontador aux, novo;
    aux = lista->primeiro;
    int cont = 0;
    int populacao = 0;
    double pib = 0;
    float idh = 0;
    char estado[50];
    strcpy(estado, aux->estado);

        while(aux!=NULL){
            while (aux!=NULL){
                aux->marcador = 1;
                populacao = aux->populacao + populacao;
                pib = aux->pib + pib;
                idh = aux->idh + idh;
                cont++;
                aux = aux->pEstado;}

        idh = idh/cont;
        novo = criarNo();
        strcpy(novo->estado, estado);
        novo->populacao = populacao;
        novo->pib = pib;
        novo->idh = idh;
        novo->indice = cont;
        inserir(estados, novo);
        populacao = 0;
        pib = 0;
        idh = 0;
        cont = 0;

        aux = lista->primeiro;
           while((aux!=NULL)&&(aux->marcador == 1)){
                    aux = aux->prox;}
            if(aux!=NULL)
            strcpy(estado, aux->estado);
    }

    imprimirIdhOrdenado (estados);

return;
}

void imprimirIdhOrdenado (TipoLista *estados){//IMPRIME LISTA ESTADOS ORDENADOS POR IDH
    TipoApontador aux, maior;
    aux = estados->primeiro;
    maior = aux->prox;

        if(!vazia(estados)){
        while(maior!=NULL){
            while(aux!=NULL){
                if((aux->idh >= maior->idh)&&(aux->marcador!=1)){
                    maior = aux;}
                aux = aux->prox;}

                maior->marcador = 1;

                printf("estado: %s\n", maior->estado);
                printf("numero de municipios: %d\n", maior->indice);
                printf("populacao: %d\n", maior->populacao);
                printf("pib per capita %lf\n", maior->pib);
                printf("idh: %f\n\n", maior->idh);

                aux = estados->primeiro;
                maior = aux;

                while((maior!=NULL)&&(maior->marcador == 1)) // o nó precisa não ter sido contabilizado
                    maior = maior->prox;
                }
    zerarMarcador(estados);
        }

return;
}
/* -------------------------PROGRAMA PRINCIPAL---------------------------------- */

int main()
{
    char op, nome[50];
    TipoLista lista;
    inicializa(&lista);
    lerDados(&lista);
    TipoLista estados;
    inicializa(&estados);


    op = 'c';
    while(op=='c'||op=='e'||op=='a'||op=='z'||op=='p'||op=='t'){
		scanf("%c",&op);
		switch (op){
			case 'c':
			    setbuf(stdin, NULL);
			    gets(nome);
			    printf("\n");
				dadosDeUmaCidade(&lista, nome);
			break;
			case 'e':
                setbuf(stdin, NULL);
			    gets(nome);
			    printf("\n");
                dadosEstado(&lista, nome);
			break;
			case 'a':
			    printf("\n");
                pibMaior(&lista);
			break;
			case 'z':
			    printf("\n");
                pibMenor(&lista);
			break;
			case 'p':
			    printf("\n");
                popMaior(&lista);
			break;
			case 't':
			    printf("\n");
                listadeEstados(&lista, &estados);
			break;

		}
	}
return 0;
}
