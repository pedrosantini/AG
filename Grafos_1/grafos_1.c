#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grafos.h"


int main()
{
    grafo *g = criar_grafo();

    insert_vertice(1, g);
    insert_vertice(2, g);
    insert_vertice(4, g);
    insert_vertice(6, g);


    visualizar_grafo(g);

    insert_aresta(1, 2, g);
    insert_aresta(4, 1, g);
    insert_aresta(6, 4, g);
    insert_aresta(4, 6, g);
    insert_aresta(2, 4, g);

    //printf("--%d--\n", buscar_aresta(1, 2, g));

    visualizar_grafo(g);

    // remover_aresta(2, 4, g);
    // remover_aresta(1, 2, g);
    remover_aresta(1, 4, g);
    

    printf("\n");

    visualizar_grafo(g);


    return 0;
}
