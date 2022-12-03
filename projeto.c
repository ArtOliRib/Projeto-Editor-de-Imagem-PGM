#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

typedef struct{
    int linha;
    int coluna;
    int maior;
    int matriz [512][512];
} pgm;

//------------------------------------------------//
//Essa função serve apenas para testes
//preencher uma matriz 512/512 para testes
void fill(int m[][512])
{
    for (int i = 0; i < 512; i++)
        for (int j = 0; j < 512; j++)
            m[i][j] = rand() % 100;
    return;
}

//-------------------------------------------------//
//Função para criar o arquivo mais claro
void clarear() {
    FILE *IMG1 = fopen("CLAREAR.pgm","a");
    pgm tam;
    int i,j;

    //tamanho dado por mim, precisa ser alterado para ler o valor do arquivo
    tam.linha = 512;
    tam.coluna = 512;
    tam.maior = 50;

    //preencher matriz para testes
    fill (tam.matriz);

    //Cria o cabeçalho da primeira imagem alterada
    fprintf(IMG1, "P2");
    fputc('\n', IMG1);
    fprintf(IMG1, "%d %d", tam.linha, tam.coluna);
    fputc('\n', IMG1);
    fprintf(IMG1, "%d", tam.maior);
    fputc('\n', IMG1);

    //Coloca a matriz no arquivo criado
    for(i = 0; i < tam.linha;i++){
        for(j = 0; j < tam.coluna;j++){
            fprintf(IMG1,"%i ",tam.matriz[i][j]);
        }
    }
    fclose (IMG1);
};

//-------------------------------------------------//

int main(int argc, char *argv[]){
    setlocale(LC_ALL,"portuguese");

    //abre o arquivo principal pelo CMD
    FILE *img = fopen(argv[1], "r");

        //verifica se o arquivo foi aberto corretamente
        if (img == NULL)
            printf("Falha ao abrir imagem");
        else
            printf("Imagem pgm aberta");

    //fecha o arquivo principal
    fclose(img);

    //chama a função clarear e cria o primeiro arquivo
    clarear();

    while(getchar() != '\n');
    getchar();
    return 0;

}
