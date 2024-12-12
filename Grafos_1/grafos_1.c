#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grafos.h"



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

    insert_aresta(1, 2, g);
    insert_aresta(1, 6, g);
    insert_aresta(2, 3, g);
    insert_aresta(2, 4, g);
    insert_aresta(3, 5, g);
    insert_aresta(4, 6, g);
    insert_aresta(4, 5, g);
    insert_aresta(4, 7, g);
    insert_aresta(7, 8, g);
    insert_aresta(7, 9, g);


    visualizar_grafo(g);

    int op=0;

    

    while(op!=6){
        printf("\nEscolha uma das opcoes: \n");
        printf("1 - Inserir Vertice\n");
        printf("2 - Inserir Aresta\n");
        printf("3 - Visualizar grafo\n");
        printf("4 - Remover Vertice\n");
        printf("5 - Remover Aresta\n");
        printf("6 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        int n, i;
        int id, ant, prox;

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
                    printf("\nId do vertice anterior e do proximo respectivamente: ");
                    scanf("%d %d", &ant, &prox);

                    insert_aresta(ant, prox, g);
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