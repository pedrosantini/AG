#include <stdio.h>
#include <stdlib.h>

// Definição das estruturas de dados do grafo
typedef struct grafo grafo;
typedef struct vertice vertice;
typedef struct aresta aresta;

// Funções do grafo (declarações)
int grafo_nulo(grafo *g);
int buscar_vert(int id, grafo *g);
int buscar_aresta(int v1, int v2, grafo *g);
void insert_vertice(int id, grafo *g);
void insert_aresta(int v1, int v2, int peso, grafo *g);
void visualizar_grafo(grafo *g);
void remover_vertices(int id, grafo *g);
void remover_aresta(int v1, int v2, grafo *g);
int informa_grau(int v, grafo *g);
int grafo_conexo(grafo *g);
void conv_mat_adj(grafo *g);
int qtd_v(grafo *g);
int qtd_a(grafo *g);
int busca_em_profundidade(vertice *v, int *verticesVisitados, grafo *g);
void busca_em_largura(vertice *v, int *visitado, grafo *g);
vertice *visitarVert(int id, grafo *g);


// Estrutura do grafo, contendo uma lista de vértices
typedef struct grafo{
    vertice *inicio; // Ponteiro para o primeiro vértice da lista
}grafo;

// Estrutura do vértice, contendo uma lista de arestas
typedef struct vertice{
    aresta *a; // Ponteiro para a lista de arestas do vértice
    vertice *next; // Ponteiro para o próximo vértice na lista
    int id; // Identificador único do vértice
}vertice;


// Estrutura da aresta, que conecta dois vértices
typedef struct aresta{
    int aid;      // Identificador do vértice de destino
    int p;        // Peso da aresta
    aresta *prox; // Ponteiro para a próxima aresta

}aresta;


// Função para criar e inicializar um grafo vazio
grafo *criar_grafo(){
    grafo *g = (grafo*)calloc(sizeof(grafo), 1);

    g->inicio = NULL; // Inicializa o grafo sem vértices

    return g;
}

// Verifica se o grafo está vazio (nulo)
int grafo_nulo(grafo *g){
    if (g->inicio == NULL)
        return 1;
    return 0;
}

// Insere um novo vértice no grafo, se ele ainda não existir
void insert_vertice(int x, grafo *g){
    if (!grafo_nulo(g)){
        if (!buscar_vert(x, g)){
            vertice *aux = g->inicio;
            while(aux->next != NULL)
                aux = aux->next;
            aux->next = (vertice*)calloc(sizeof(vertice), 1);
            aux->next->id = x;
            
        }
        else
            printf("vertice ja existe\n");
    }
    else{
        g->inicio = (vertice*)calloc(sizeof(vertice), 1);
        g->inicio->id = x;
    }
}

// Insere uma aresta entre dois vértices, com peso especificado
void insert_aresta(int v1, int v2, int peso, grafo *g){ 
    if(!grafo_nulo(g)){   
        if (v2 != v1){ // Verifica se a aresta não é uma laço (vértice para ele mesmo) 
            if (!buscar_aresta(v1, v2, g)){
                if (buscar_vert(v1, g) && buscar_vert(v2, g)){
                    vertice *auxV1 = g->inicio;
                    vertice *auxV2 = g->inicio;

                    
                    // Localiza os vértices v1 e v2
                    while ((auxV1->id != v1) || (auxV2->id != v2)){
                        if(auxV1->id != v1)
                            auxV1 = auxV1->next;
                        
                        if (auxV2->id != v2)
                            auxV2 = auxV2->next;
                    }

                    aresta *a1;
                    aresta *a2;
                    
                    // Insere a aresta nos dois vértices
                    if ((auxV1->a == NULL) && (auxV2->a == NULL)){
                        
                        auxV1->a = (aresta*)calloc(1, sizeof(aresta));
                        auxV1->a->aid = v2;
                        auxV1->a->p = peso;

                        auxV2->a = (aresta*)calloc(1, sizeof(aresta));
                        auxV2->a->aid = v1;
                        auxV2->a->p = peso;                        

                    }

                    else if ((auxV1->a != NULL) && (auxV2->a == NULL)){
                        a1 = auxV1->a;

                        while(a1->prox != NULL){                        
                            a1 = a1->prox;
                        }

                        a1->prox = (aresta*)calloc(1, sizeof(aresta));
                        a1->prox->aid = v2;
                        a1->prox->p = peso;

                        auxV2->a = (aresta*)calloc(1, sizeof(aresta));
                        auxV2->a->aid = v1;
                        auxV2->a->p = peso;



                    }

                    else if ((auxV1->a == NULL) && (auxV2->a != NULL)){
                        a2 = auxV2->a;

                        while(a2->prox != NULL){                        
                            a2 = a2->prox;
                        }

                        a2->prox = (aresta*)calloc(1, sizeof(aresta));
                        a2->prox->aid = v1;
                        a2->prox->p = peso;

                        auxV1->a = (aresta*)calloc(1, sizeof(aresta));
                        auxV1->a->aid = v2;
                        auxV1->a->p = peso;
                    }

                    else{
                        a1 = auxV1->a;
                        a2 = auxV2->a;

                        while(a1->prox != NULL){                        
                            a1 = a1->prox;
                        }

                        while(a2->prox != NULL){                        
                            a2 = a2->prox;
                        }

                        a1->prox = (aresta*)calloc(1, sizeof(aresta));
                        a1->prox->aid = v2;
                        a1->prox->p = peso;

                        a2->prox = (aresta*)calloc(1, sizeof(aresta));
                        a2->prox->aid = v1;
                        a2->prox->p = peso;

                    }            
                                

                }
                else
                    printf("pelo menos um dos vertices nao existe\n");
            }
            else
                printf("aresta ja existe\n");
        }
        else
            printf("vertices iguais\n");   
    }
}

// Visualiza o grafo imprimindo os vértices e suas arestas
void visualizar_grafo(grafo *g){
    if (!grafo_nulo(g)){
        vertice *auxV = g->inicio;
        while (auxV != NULL){
            printf("%d ->", auxV->id);
            aresta *auxA = auxV->a;

            while (auxA != NULL){
                printf(" %d (%d) ->", auxA->aid, auxA->p);
                auxA = auxA->prox;
            }

            printf(" -- \n");

            auxV = auxV->next;
            
        }
    }
    else
        printf("o grafo nao existe\n");

}

// Verifica se um vértice com id especificado existe no grafo
int buscar_vert(int id, grafo *g){
    if (!grafo_nulo(g)){
        vertice *auxV = g->inicio;
        while (auxV != NULL){
            if (id == auxV->id)
                return 1;
            auxV = auxV->next;
        }
    }
    return 0;
}

// Verifica se uma aresta entre dois vértices existe no grafo
int buscar_aresta(int v1, int v2, grafo *g){
    if (buscar_vert(v1, g) && buscar_vert(v2, g)){
        vertice *auxV = g->inicio;

        while (auxV->id != v1)
            auxV = auxV->next;
        
        aresta *auxA = auxV->a;

        while (auxA != NULL){
            if (auxA->aid == v2)
                return 1;
            auxA = auxA->prox;
        }
            
    }

    return 0;
}

// Remove um vértice do grafo, e todas as arestas associadas a ele
void remover_vertices(int id, grafo *g){
    if (!grafo_nulo(g)){
        if (buscar_vert(id, g)){
            vertice *vProx = g->inicio;
            vertice *vAnt = NULL; 
            
            while (vProx->id != id){
                vAnt = vProx;
                vProx = vProx->next;
            }

            if (vProx->a != NULL){
                aresta *aAux = vProx->a;

                // Remove todas as arestas associadas ao vértice
                while (aAux != NULL){
                    remover_aresta(aAux->aid, vProx->id, g);
                    aAux = aAux->prox;
                }
            }    

            // Remove o vértice da lista
            if (vAnt == NULL){
                if (vProx->next == NULL)
                    g->inicio = NULL;
                
                else
                    g->inicio = vProx->next;
            }
            else{
                if (vProx->next == NULL)
                    vAnt->next = NULL;
                
                else
                    vAnt->next = vProx->next;
            }

            free(vProx);
        }
        else
            printf("o vertice nao existe\n");
    }
}

// Remove uma aresta do grafo
void remover_aresta(int v1, int v2, grafo *g){
    if (!grafo_nulo(g)){
        if (buscar_aresta(v1, v2, g)){
            vertice *auxV1 = g->inicio;
            vertice *auxV2 = g->inicio;

            while ((auxV1->id != v1) || (auxV2->id != v2)){
                if(auxV1->id != v1)
                    auxV1 = auxV1->next;
                
                if (auxV2->id != v2)
                    auxV2 = auxV2->next;
            }

            aresta *agora1 = NULL;
            aresta *agora2 = NULL;

            aresta *proxima1 = auxV1->a;
            aresta *proxima2 = auxV2->a;

            while (proxima1->aid != v2){
                agora1 = proxima1;
                proxima1 = proxima1->prox;
            }

            while (proxima2->aid != v1){
                agora2 = proxima2;
                proxima2 = proxima2->prox;
            }


            if (agora1 == NULL){
                if (proxima1->prox == NULL)
                    auxV1->a = NULL;
                else
                    auxV1->a = proxima1->prox;
            }
            else{
                if (proxima1->prox == NULL)
                    agora1->prox = NULL;
                else
                    agora1->prox = proxima1->prox;
            }

            if (agora2 == NULL){
                if (proxima2->prox == NULL)
                    auxV2->a = NULL;
                else
                    auxV2->a = proxima2->prox;
            }
            else{
                if (proxima2->prox == NULL)
                    agora2->prox = NULL;
                else
                    agora2->prox = proxima2->prox;
            }

            printf("removida a aresta (%d, %d)", proxima1->aid, proxima2->aid);
            free(proxima1);
            
            free(proxima2);

        }
        else
            printf("a aresta nao existe\n");
    }
    
}
///////////////////// A PARTIR DAQUI T3 e T4/////////////////////////////

// A partir do id, retorna seu vértice respectivo
vertice *visitarVert(int id, grafo *g){
    if (!grafo_nulo(g)){
        if (buscar_vert(id, g)){
            vertice *auxV = g->inicio;
            while (auxV->id != id) //procura o vértice com o id passado por parâmetro
                auxV = auxV->next;
            
            return auxV;
        }
    }
    return NULL; // caso não exista, retorna NULL;
}

// informa o grau do vértice
int informa_grau(int v, grafo *g){
    if (buscar_vert(v, g)){
        int gr = 0;
        vertice *auxV = visitarVert(v, g); //cria um auxiliar do vértice procurado
        
        aresta *auxA = auxV->a;

        while (auxA != NULL){
            gr++; // conta as arestas associadas ao vértice
            auxA = auxA->prox;
        }

        return gr;
    }

    return -1; // caso o vertice não exista
}

// Retorna a quantidade de vértices presentes no grafo
int qtd_v(grafo *g){ 
    if (!grafo_nulo(g)){
        int v=0;
        vertice *auxV = g->inicio; 
        while (auxV != NULL){ 
            v++; // soma cada vértice passado
            auxV = auxV->next;
        }
        return v;
    }
    return 0;
}


// Retorna a quantidade de vértices presentes no grafo
int qtd_a(grafo *g){
    if (!grafo_nulo(g)){
        int a=0;
        int v = qtd_v(g);
        for (int i=1; i < v; i++){
            for (int j=i+1; j <= v; j++){
                if (buscar_aresta(i, j, g))
                    a++;
            }
        }
        return a;
    }
    return 0;
}

// Retorna 1 se o grafo for conexo, e 0 caso não
int grafo_conexo(grafo *g){ 
    if(!grafo_nulo(g)){
        int qv;
        qv = qtd_v(g);

        int *v = (int*)calloc(qv, sizeof(int)); // vetor criado do tamanho da quantidade de vértices do grafo, a fim de definir em cada posição se o vértice foi visitado ou não

        vertice *auxV = g->inicio;

        busca_em_largura(auxV, v, g); // a busca em largura preenche o vetor e altera de 0 para 1 se o vértice for visitado

        for (int i=0; i < qv; i++){
            if (v[i] == 0)
                return 0; // caso algum vértice não tenha sido visitado retorna 0;
        }

    }
    return 1; // retorna 1 caso todos os vértices tenham sido visitados (é conexo)
}

// Imprime a matrix de adjacencias
void conv_mat_adj(grafo *g){
    if (!grafo_nulo(g)){
        int qv = qtd_v(g);

        for (int i=1; i < qv; i++){
            for (int j=1; j < qv; j++){
                if (buscar_aresta(i, j, g))
                    printf("1 "); // caso exista arestas entre vértices, imprime 1
                else
                    printf("0 "); // caso não exista arestas entre vértices, imprime 0
            }
            printf("\n");
        }
    }
}

// Executa a busca em largura, preenchendo um vetor de zeros passado por parâmetro
void busca_em_largura(vertice *v, int *visitado, grafo *g) {
    if (v == NULL || g == NULL) { 
        return;
    }

    int numVertices = qtd_v(g); // Obtém a quantidade de vértices do grafo
    for (int i = 0; i < numVertices; i++) {
        visitado[i] = 0; // Inicializa o vetor de visitados
    }

    vertice *fila[numVertices]; // Fila para armazenar os vértices a serem visitados
    int inicio = 0, fim = 0;

    fila[fim++] = v; // insere o vértice no fim da fila
    visitado[v->id-1] = 1; // marca o vértice inicial como visitado

    while (inicio < fim) {
        vertice *atual = fila[inicio++]; // desenfileira o vértice no início da fila
        printf("Visitando vertice: %d\n", atual->id); // anuncia o vértice visitado

        aresta *a = atual->a; // aresta auxiliar

        // marca cada um dos vizinhos do vértice atual e enfileira caso não tenha sido visitado
        while (a != NULL) {
            int vizinhoID = a->aid; 
            vertice *vizinho = visitarVert(vizinhoID, g); 
            
            if (vizinho != NULL && !visitado[vizinho->id - 1]) {
                visitado[vizinho->id - 1] = 1;
                fila[fim++] = vizinho;
            }
            a = a->prox;
        }
        // ao fim do laço, ele repete, até que todos os vértices da fila sejam visitados e a fila esteja vazia
    }
}


//FIM



























int busca_em_profundidade(vertice *v, int *visitado, grafo *g){
    if (v == NULL || visitado[v->id - 1]) {
        return 1;
    }
    else{
        visitado[v->id - 1] = 1;
        aresta *aux = v->a; 
        
        while (aux != NULL) {
            vertice *busca = g->inicio;

            while (busca != NULL && busca->id != aux->aid){
                busca = busca->next;
            }
            busca_em_profundidade(busca, visitado, g);
            aux = aux->prox;
        }
        return 0;
    }
}

