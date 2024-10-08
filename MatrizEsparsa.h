
typedef struct tCelula
{
    int linha, coluna;
    int valor;
    tCelula *direita, *abaixo;
}tCelula;

typedef struct
{
    int m, n;
    tCelula *inicio, *fimLinha, *fimColuna;
}tMatriz;

void criar_matrix(){

}

