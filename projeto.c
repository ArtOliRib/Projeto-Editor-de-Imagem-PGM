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
//Função principal
int main(int argc, char *argv[]){
    setlocale(LC_ALL,"portuguese");

    char tipo [3];
    int linha, coluna, maior, **matriz, i,j;

    pgm m;

    //abre o arquivo principal pelo CMD
    FILE *img = fopen(argv[1], "r");

        //verifica se o arquivo foi aberto corretamente
        if (img == NULL)
            printf("Falha ao abrir a imagem '%s'.\nPor favor, tente novamente.", argv[1]);

        else {
            printf("\nImagem '%s' aberta com sucesso.\n\n", argv[1]);
            fscanf(img, "%s %d %d %d", &tipo, &linha, &coluna, &maior);


            matriz = malloc(linha*sizeof(int *));

            for(i = 0; i < linha; i++){
                matriz[i] = malloc(coluna*sizeof(int *));
            }

            for(i = 0;i<linha;i++){
                for(j=0;j<coluna;j++){
                    fscanf(img,"%i",&matriz[i][j]);
                }
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
    rotacao(m);
    binario(m);
    zoom(m);
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
    printf("Clareando a imagem\n");

    int i,j;
    FILE *IMG1 = fopen ("clarear.pgm","w");

    //Cria o cabeçalho da primeira imagem alterada
    fprintf(IMG1, "P2");
    fputc('\n', IMG1);
    fprintf(IMG1, "%d %d", m.linha, m.coluna);
    fputc('\n', IMG1);
    fprintf(IMG1, "%d", 255);
    fputc('\n', IMG1);

    //Coloca a matriz no arquivo criado
    for(i = 0; i < m.linha; i++){
        for(j = 0; j < m.coluna;j++){
            if (m.matriz[i][j] < 180){
            fprintf(IMG1,"%i ", m.matriz[i][j] + 60);}

            else
            fprintf(IMG1,"%i ", 255);
        }
    }
    if (IMG1 == NULL)
        printf("Falha ao criar arquivo");
    else
        printf("Arquivo criado com sucesso\n\n");
    fclose (IMG1);
}
//-------------------------------------------------//
//Função para rotacinar a imagem
void rotacao(pgm m)
    {
    printf("Girando a imagem 90º no sentido horário\n");

    int i,j;
    FILE *IMG1 = fopen ("Rotacao.pgm","w");

    //Cria o cabeçalho da primeira imagem alterada
    fprintf(IMG1, "P2");
    fputc('\n', IMG1);
    fprintf(IMG1, "%d %d", m.linha, m.coluna);
    fputc('\n', IMG1);
    fprintf(IMG1, "%d", m.maior);
    fputc('\n', IMG1);


    //Coloca a matriz no arquivo criado
    for(j = 0; j < m.coluna; j++){
        {
            for(i = m.linha-1; i >= 0 ; i--)
            fprintf(IMG1,"%i ", m.matriz[i][j]);
        }
    }

    if (IMG1 == NULL)
        printf("Falha ao criar arquivo.");
    else
        printf("Arquivo criado com sucesso\n\n");
    fclose (IMG1);
}




//-------------------------------------------------//
//Binarizar arquivo
void binario(pgm m)
    {

    printf("Binarizando a imagem\n");

    int i,j;
    int matrizbinaria [m.linha][m.coluna];

    /// Atribuindo os 1 e 0 para a nova matriz

    for(i=0; i<m.linha; i++) {
        for(j=0; j<m.coluna; j++){
            if (m.matriz[i][j] < 127){
                matrizbinaria[i][j] = 1;}
            else {
                matrizbinaria [i][j] = 0;}}}

    FILE *IMG1 = fopen ("binario.pgm","w");

    //Cria o cabeçalho da primeira imagem alterada
    fprintf(IMG1, "P2");
    fputc('\n', IMG1);

    fprintf(IMG1, "%d %d", m.linha, m.coluna);
    fputc('\n', IMG1);

    fprintf(IMG1, "%d", 1);
    fputc('\n', IMG1);

    //Coloca a matriz no arquivo criado
   for(i = 0; i < m.linha; i++){
        for(j = 0; j < m.coluna;j++){
            fprintf(IMG1,"%i ", matrizbinaria[i][j]);
        }
    }

    if (IMG1 == NULL)
        printf("Falha ao criar arquivo");
    else
        printf("Arquivo criado com sucesso\n");

    fclose (IMG1);

}

void zoom(pgm m)
    {
    printf("\nZoom\nFalta implementar\n");

    int i,j,o,y,k;
    int novaLinha,novaColuna;
    int entL = 0, entC = 0, modL = 2, modC = 2;

    FILE *IMG1 = fopen ("Zoom.pgm","w");

    //novos parametros da matriz
    novaLinha = m.linha / 2;
    novaColuna = m.coluna / 2;
    int matZoom[novaLinha][novaColuna];

    //nova matriz dinamica
    //matZoom = malloc(novaLinha*sizeof(int *));

    /*for(i = 0; i < novaLinha; i++){
            matZoom[i] = malloc(novaColuna*sizeof(int *));
    }*/

    for(i = 0; i < novaLinha;i++){
        for(j = 0; j < novaColuna;j++){
            for(y = entL;y< modL; y++){
                for(o = entC;o < modC;o++){
                    matZoom[i][j] = matZoom[i][j] + m.matriz[y][o];
                    //printf("%i ",matZoom[i][j]);
                }
            }
            }
            matZoom[i][j] = matZoom[i][j] / 4;
            //printf("%i ",matZoom[i][j]);
            entL = entL + 2;
            entC = entC +2;
            modL = entL +2;
            modC = modC +2;
        }

    //Cria o cabeçalho da primeira imagem alterada
    fprintf(IMG1, "P2");
    fputc('\n', IMG1);
    fprintf(IMG1, "%d %d", novaLinha, novaColuna);
    fputc('\n', IMG1);
    fprintf(IMG1, "%d", m.maior);
    fputc('\n', IMG1);

    //Coloca a matriz no arquivo criado
    for(i = 0; i < novaLinha; i++){
        for(j = 0; j < novaColuna;j++){
            fprintf(IMG1,"%i ", matZoom[i][j]);
        }
    }
    if (IMG1 == NULL)
        printf("Falha ao criar arquivo");
    else
        printf("Arquivo criado com sucesso\n");
    fclose (IMG1);
}
