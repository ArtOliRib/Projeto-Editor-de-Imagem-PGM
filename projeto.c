#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

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


    char nome[260];
    char nometemp[260]; //Arquivo (sem o .pgm)
    char nomearq1[260]; //Arquivo Clarear
    char nomearq2[260]; //Arquivo Zoom
    char nomearq3[260]; //Arquivo Binario
    char nomearq4[260]; //Arquivo Rotação

    //Copiar o nome da string
    strcpy(nome, argv[1]);

    int qtd = strlen(nome);

    //Copia tudo antes do .pgm e fecha a string com \0
    for (i=0; i <= qtd-5; i++)
        nometemp[i] = nome[i];
    nometemp[i] = '\0';

    strcpy(nomearq1, nometemp);
    strcat(nomearq1, "1.pgm");

    strcpy(nomearq2, nometemp);
    strcat(nomearq2, "2.pgm");

    strcpy(nomearq3, nometemp);
    strcat(nomearq3, "3.pgm");

    strcpy(nomearq4, nometemp);
    strcat(nomearq4, "4.pgm");

//Alocação dinâmica para a matriz da struct
        m.matriz = malloc(linha*sizeof(int *));
        for (i=0; i<linha; i++){
        m.matriz[i] = malloc(coluna*sizeof(int));}

//Passando a matriz para a struct
    for(i = 0;i<linha;i++)
        for(j=0;j<coluna;j++)
            m.matriz[i][j] = matriz[i][j];

fclose(img);

    //Passando os dados pra struct.
    m.linha = linha;
    m.coluna = coluna;
    m.maior = maior;

    //chama todas as funçoes.
    clarear(m, nomearq1);
    zoom(m, nomearq2);
    binario(m, nomearq3);
    rotacao(m, nomearq4);

//Liberando espaço alocado para a matriz
        for (i=0; i < linha; i++){
        free (matriz[i]);}
        free(matriz);

//Liberando espaço alocado para a matriz da struct
        for (i=0; i < linha; i++){
            free (m.matriz[i]);}
        free(m.matriz);

return 0;
}

//Função para criar o arquivo mais claro
void clarear(pgm m, char* nomearq[])
    {
    printf("Clareando a imagem\n");

    int i,j;
    FILE *IMG1 = fopen (nomearq,"w");

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
        printf("Arquivo %s criado.\n\n", nomearq);
    fclose (IMG1);
}

//Função para rotacionar a imagem
void rotacao(pgm m, char* nomearq[])
    {
    printf("Girando a imagem 90º no sentido horário\n");

    int i,j;
    FILE *IMG1 = fopen (nomearq,"w");

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
        printf("Arquivo %s criado.\n\n", nomearq);
    fclose (IMG1);
}

//Binarizar arquivo
void binario(pgm m, char* nomearq[])
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

    FILE *IMG1 = fopen (nomearq,"w");

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
        printf("Arquivo %s criado.\n\n", nomearq);

    fclose (IMG1);

}

//Função Zoom
void zoom(pgm m, char* nomearq[])
    {
    printf("Diminuindo a imagem\n");
    int i,j,c,d,k;
    int novaLinha,novaColuna,novoMaior;


    FILE *IMG1 = fopen(nomearq,"w");

    //novos parametros da matriz
    novaLinha = m.linha / 2;
    novaColuna = m.coluna / 2;

    int matZoom[novaLinha][novaColuna];

    //Calculo dos pixels redimencionados para a nova matriz.
    c = 0;
    for(i  = 0; i < m.linha;i++){
        d = 0;
        for(j = 0; j < m.coluna;j++){
                matZoom[c][d] = (m.matriz[i][j] + m.matriz[i+1][j] + m.matriz[i][j + 1] + m.matriz[i + 1][j + 1])/4;
                d++;
                j++;
        }
        c++;
        i++;
    }

    //calculo do maior pixel da nova matriz.
    novoMaior = matZoom[0][0];
    for(i = 0; i < novaLinha;i++){
        for(j = 0; j < novaColuna; j++){
            if (matZoom[i][j] > novoMaior){
                novoMaior = matZoom[i][j];
            }
        }
    }

    //Cria o cabeçalho da primeira imagem alterada
    fprintf(IMG1, "P2");
    fputc('\n', IMG1);
    fprintf(IMG1, "%d %d", novaLinha, novaColuna);
    fputc('\n', IMG1);
    fprintf(IMG1, "%d", novoMaior);
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
        printf("Arquivo %s criado.\n\n", nomearq);
    fclose (IMG1);
}
