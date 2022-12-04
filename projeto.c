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
                }
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

    fclose(img);

    //Passando os dados pra struct
    m.linha = linha;
    m.coluna = coluna;
    m.maior = maior;

    //chama a função clarear e cria o primeiro arquivo
    //FUNÇÃO NÃO ESTÁ R
    clarear(m);

//Liberando espaço alocado para a matriz
        for (i=0; i < linha; i++){
        free (matriz[i]);}
        free(matriz);

//Liberando espaço alocado para a matriz da struct
        for (i=0; i < linha; i++){
            free (m.matriz[i]);}
        free(m.matriz);

    while(getchar() != '\n');
    getchar();
    return 0;

}


//-------------------------------------------------//
//Função para criar o arquivo mais claro

void clarear(pgm m)
    {
    printf("TESTANDO A FUNÇÃO CLAREAR\n");

    int i,j;
    FILE *IMG1 = fopen ("arquivo1.pgm","w");

    //Cria o cabeçalho da primeira imagem alterada
    fprintf(IMG1, "P2");
    fputc('\n', IMG1);
    fprintf(IMG1, "%d %d", m.linha, m.coluna);
    fputc('\n', IMG1);
    fprintf(IMG1, "%d", m.maior);
    fputc('\n', IMG1);

    //Coloca a matriz no arquivo criado
    for(i = 0; i < m.linha; i++){
        for(j = 0; j < m.coluna;j++){
            fprintf(IMG1,"%i ", m.matriz[i][j] + 25);
        }
    }
    if (IMG1 == NULL)
        printf("Falha ao criar arquivo");
    else
        printf("Arquivo criado com sucesso");
    fclose (IMG1);
}
