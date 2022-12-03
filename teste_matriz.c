#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

typedef struct{
    int linha;
    int coluna;
    int maior;
    int matriz [512][512];
} pgm;

int main(){
    setlocale(LC_ALL,"portuguese");

    FILE *img1 = fopen("lal.txt","a");

    pgm tam;
    int i,j;
    tam.linha = 1;
    tam.coluna = 1;
    tam.maior = 50;
    tam.matriz[0][0] = 1;

    /*for ( i=0; i<10;i++)
            for ( j=0; j<10;j++){
                scanf ("%i", tam.matriz[ i ][ j ]);
    }*/
    //Cria o cabeçalho da primeira imagem alterada
    fprintf(img1, "P2");
    fputc('\n', img1);
    fprintf(img1, "%d %d", tam.linha, tam.coluna);
    fputc('\n', img1);
    fprintf(img1, "%d", tam.maior);
    fputc('\n', img1);
    for(i = 0; i < tam.linha;i++){
        for(j = 0; j < tam.coluna;j++){
            fprintf(img1,"%i",tam.matriz[i][j]);
        }
    }



    while(getchar() != '\n')

            ;
        getchar();
        return 0;

}
