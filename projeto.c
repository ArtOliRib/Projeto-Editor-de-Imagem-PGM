#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

typedef struct{
    int linha;
    int coluna;
    int maior;
    int **matriz;
} pgm;

//-------------------------------------------------//

int main(int argc, char *argv[]){
    setlocale(LC_ALL,"portuguese");

    char tipo [3];
    int linha, coluna, maior, **matriz, i,j;

    pgm m;

    //abre o arquivo principal pelo CMD
    FILE *img = fopen(argv[1], "r");

        //verifica se o arquivo foi aberto corretamente
        if (img == NULL)
            printf("Falha ao abrir imagem");

        else {
            printf("Imagem pgm aberta\n");
            fscanf(img, "%s %d %d %d", &tipo, &linha, &coluna, &maior);
            printf("%s\n%d %d\n%d", tipo, linha, coluna, maior);
            printf("\n");}

            matriz = malloc(linha*sizeof(int *));

            for(i = 0; i < linha; i++){
                matriz[i] = malloc(coluna*sizeof(int *));
            }

            for(i = 0;i<linha;i++){
                for(j=0;j<coluna;j++){
                    fscanf(img,"%i",&matriz[i][j]);
                    printf("%i ",matriz[i][j]);
                }
                printf("\n");
            }
//Alocação dinâmica para a matriz da struct
//Quando a matriz estiver correta, passar da matriz da main para a struct
        m.matriz = malloc(linha*sizeof(int *));
        for (i=0; i<linha; i++){
        m.matriz[i] = malloc(coluna*sizeof(int));}

//Passando a matriz para a struct
    for(i = 0;i<linha;i++)
        for(j=0;j<coluna;j++)
            m.matriz[i][j] = matriz[i][j];

//Liberando espaço alocado para a matriz
        for (i=0; i < linha; i++){
        free (matriz[i]);}
        free(matriz);

//Liberando espaço alocado para a matriz da struct
        for (i=0; i < linha; i++){
            free (m.matriz[i]);}
        free(m.matriz);

    fclose(img);

    //Passando os dados pra struct
    m.linha = linha;
    m.coluna = coluna;
    m.maior = maior;

    //chama a função clarear e cria o primeiro arquivo
    //FUNÇÃO NÃO ESTÁ R
    //clarear(linha, coluna, maior);

    while(getchar() != '\n');
    getchar();
    return 0;

}


//-------------------------------------------------//
//Função para criar o arquivo mais claro
//ESSA FUNÇÃO NÃO ESTÁ RODANDO
void clarear(int linha, int coluna, int maior)
    {
    printf("INICIO DA FUNÇÃO,  %d", maior);

    pgm m;
    int i,j;
    FILE *IMG1 = fopen ("CLAREAR.pgm","a");

    //preencher matriz para testes

    //Cria o cabeçalho da primeira imagem alterada
    fprintf(IMG1, "P2");
    fputc('\n', IMG1);
    fprintf(IMG1, "%d %d", linha, coluna);
    fputc('\n', IMG1);
    fprintf(IMG1, "%d", maior);
    fputc('\n', IMG1);

    //Coloca a matriz no arquivo criado
    for(i = 0; i < m.linha; i++){
        for(j = 0; j < m.coluna;j++){
            fprintf(IMG1,"%i ", m.matriz[i][j]);
        }
    }
    fclose (IMG1);
}


//------------------------------------------------//
//Essa função serve apenas para testes
//preencher uma matriz 512/512 para testes
