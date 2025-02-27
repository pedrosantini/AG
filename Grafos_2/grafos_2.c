#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grafos_2.h"



int main(){
    grafo *g = criar_grafo();

    insert_vertice(1, g);
    insert_vertice(2, g);
    insert_vertice(3, g);
    insert_vertice(4, g);
    insert_vertice(5, g);
    insert_vertice(6, g);
    insert_vertice(7, g);
    insert_vertice(8, g);
    insert_vertice(8, g);
    insert_vertice(9, g);

    insert_aresta(1, 2, 1, g);
    insert_aresta(1, 6, 2, g);
    insert_aresta(2, 3, 3, g);
    insert_aresta(2, 4, 4, g);
    insert_aresta(3, 5, 5, g);
    insert_aresta(4, 6, 6, g);
    insert_aresta(4, 5, 7, g);
    insert_aresta(4, 7, 8, g);
    insert_aresta(7, 8, 9, g);
    insert_aresta(7, 9, 10, g);


    visualizar_grafo(g);

    int op=0;

    

    while(op!=10){
        printf("\nEscolha uma das opcoes: \n");
        printf("1 - Inserir Vertice\n");
        printf("2 - Inserir Aresta\n");
        printf("3 - Visualizar grafo\n");
        printf("4 - Remover Vertice\n");
        printf("5 - Remover Aresta\n");
        printf("6 - Informar grau\n");
        printf("7 - Grafo eh conexo\n");
        printf("8 - Imprimir matriz de adjacencias\n");
        printf("9 - Informar vertices visitados pela busca em largura\n");


        printf("10 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        int n, i;
        int id, ant, prox, peso;

        switch(op){
            case 1:
                printf("\nQuantidade de Vertices que deseja inserir: ");
                scanf("%d", &n);

                for(i=1; i<=n; i++){
                    printf("\nId do vertice %d: ", i);
                    scanf("%d", &id);

                    insert_vertice(id, g);
                }

                break;
            
            case 2: 
                printf("\nQuantidade de arestas que deseja inserir: ");
                scanf("%d", &n);

                for(i=1; i<=n; i++){
                    printf("\nId do vertice anterior, o peso e o id do proximo vertice respectivamente: ");
                    scanf("%d %d %d", &ant, &peso, &prox);

                    insert_aresta(ant, prox, peso, g);
                }

                break;
            
            case 3:
                visualizar_grafo(g);
                break;
            
            case 4: 
                printf("\nId do vertice que deseja remover: ");
                scanf("%d", &id);

                remover_vertices(id, g);

                break;
            
            case 5: 
                printf("\nId do vertice anterior e do proximo respectivamente: ");
                scanf("%d %d", &ant, &prox);

                remover_aresta(ant, prox, g);

                break;
            
            case 6:
                printf("\nId do vertice: ");
                scanf("%d", &ant);

                printf("O grau do vertice eh %d", informa_grau(ant, g));

                break;

            case 7:
                if (grafo_conexo(g))
                    printf("O grafo eh conexo\n");
                else
                    printf("O grafo nao eh conexo\n");
                    
                            
                break;
            
            case 8:
                printf("Matriz de adjacencias: \n");
                conv_mat_adj(g);
                break;

            case 9:
                printf("\n");
                int *visitados = (int*)calloc(sizeof(int), qtd_v(g));
                busca_em_largura(g->inicio, visitados, g);
                free(visitados);
                break;            

            case 10:
                printf("Encerrando o Programa\n");
                break;

            default:
                printf("Opcao Invalida!\n");
                break;
        }
    }
    
    free(g);   
    
    return 0;
}