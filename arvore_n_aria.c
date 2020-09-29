#include "arvore_n_aria.h"
#include <stdio.h>
#include <stdlib.h>

// Protótipos das funções privadas
void profundidade( NoArvore *n ); // similar ao percurso em pré-ordem.
void profundidade_xml( NoArvore *n, int nivel );
NoArvore *aloca_no( int info );
NoArvore *busca_no( NoArvore *n, int chave );
void desaloca_pos_ordem( NoArvore *n );


void inicializa_Arvore( Arvore *p, int valor_raiz ){
     p->raiz = aloca_no( valor_raiz );
}

int insere_filho( Arvore a, int pai, int filho ){
    NoArvore *no_pai = busca_no( a.raiz , pai );
    if( no_pai == NULL)
        return 0; // Erro: pai não foi encontrado!
    
    if( no_pai->filho == NULL )
        no_pai->filho = aloca_no( filho );
    else{
        NoArvore *aux = no_pai->filho;
        while( aux->irmao != NULL )
            aux = aux->irmao;
        aux->irmao = aloca_no( filho );
    }
    return 1; // Sucesso            
}

NoArvore *busca_no( NoArvore *n, int chave ){
	if( n->info == chave )
	    return n;
    
    NoArvore *aux;
    
    if( n->filho != NULL ){
        aux = busca_no( n->filho, chave );
        if( aux != NULL)
            return aux;
    }
    
	if( n->irmao != NULL ){
        aux = busca_no( n->irmao, chave );
        if( aux != NULL)
            return aux;
    }
	
	return NULL;
}


void percurso_profundidade( Arvore a ){
	if( a.raiz == NULL)
		printf("Arvore vazia!\n");
	else{
		printf("Percurso na arvore em profundidade:\n");
		profundidade( a.raiz );
	}
	printf("\n");
}

void profundidade( NoArvore *n ){
	if( n != NULL ){
		printf("%d\n", n->info );
		profundidade( n->filho );
		profundidade( n->irmao );
	}
}

void gera_xml( Arvore a ){
	if( a.raiz == NULL)
		printf("<Arvore-vazia>\n");
	else{
		profundidade_xml( a.raiz, 0);
	}
	printf("\n");
}

void profundidade_xml( NoArvore *n, int nivel ){
    int i;

    for( i = 0 ; i < nivel ; i++ )
        printf("  ");
    
    if( n->filho == NULL )
        printf("<%d/>\n", n->info+1 );
    else{
        printf("<%d>\n", n->info+1 );
        
	    profundidade_xml( n->filho, nivel + 1 );
        
        for( i = 0 ; i < nivel ; i++ )
 			printf("  ");
     	printf("</%d>\n", n->info+1 );
    }
    
    if( n->irmao != NULL )
        profundidade_xml( n->irmao, nivel );
}

void desaloca_arvore( Arvore *p ){
	desaloca_pos_ordem( p->raiz );
	p->raiz = NULL;
}

void desaloca_pos_ordem( NoArvore *n ){
	if( n != NULL){
		desaloca_pos_ordem( n->filho );
		desaloca_pos_ordem( n->irmao );
		free( n );
	}
}

NoArvore *aloca_no( int info ){
	NoArvore *p = malloc( sizeof(NoArvore) );
	if( p == NULL)
		return NULL;

	p->info = info;
	p->filho = p->irmao = NULL;
	return p;
}
