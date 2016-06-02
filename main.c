#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#define IZLAZ 0
#define POTREFIO -1
int poredi(const void *, const void *);
int main(int argc, char *argv[]) {
    int i, ii, iii, broj_cifara = 4, broj_znakova = 6, max_pokusaja = 10,
        na_mestu, na_pogresnom_mestu, *kombinacija, *tacna_kombinacija;
    bool tesko = false, *preskoci1, *preskoci2;
    while((i = getopt(argc, argv, "c:p:ltz:h")) != -1)
        switch(i) {
            case 'c':
                broj_cifara = atoi(optarg);
                break;
            case 'p':
                max_pokusaja = atoi(optarg);
                break;
            case 'l':
                tesko = false;
                break;
            case 't':
                tesko = true;
                break;
            case 'z':
                broj_znakova = atoi(optarg);
                break;
            case 'h':
                puts("-c [broj] podesi broj cifara u kombinaciji");
                puts("-p [broj] podesi dozvoljeni broj pokusaja");
                puts("-z [broj] podesi broj razlicitih znakova u kombinaciji");
                puts("-l podesi tezinu na lagano (brojevi su poredjani)");
                puts("-t podesi tezinu na tesko (brojevi nisu poredjani)");
                getchar();
                return 0;
        }
    kombinacija = malloc(broj_cifara * sizeof(int));
    tacna_kombinacija = malloc(broj_cifara * sizeof(int));
    preskoci1 = malloc(broj_cifara * sizeof(bool));
    preskoci2 = malloc(broj_cifara * sizeof(bool));
    srand(time(NULL));
    for(i = 0; i < broj_cifara; i++)
        *(tacna_kombinacija + i) = rand() % broj_znakova + 1;
    puts("Koristi -h zastavicu pri pokretanju za pomoc.\nKucaj 0 da prekines.\n");
    if(tesko == true)
        puts("Tezina: tesko");
    else {
        puts("Tezina: lagano\nBrojevi u kombinaciji su poredjani po velicini\n");
        qsort(tacna_kombinacija, broj_cifara, sizeof(int), poredi);
    }
    printf("Kombinaciju mogu ciniti brojevi od 1 do %d\n", broj_znakova);
    for(i = 0; i < max_pokusaja; i++) {
        printf("\nOstalo pokusaja: %d\n", max_pokusaja - i);
        na_mestu = 0;
        na_pogresnom_mestu = 0;
        for(ii = 0; ii < broj_cifara; ii++) {
            *(preskoci1 + ii) = false;
            *(preskoci2 + ii) = false;
        }
        printf("Unesi kombinaciju: ");
        for(ii = 0; ii < broj_cifara; ii++) {
            scanf("%d", kombinacija + ii);
            if(*(kombinacija + ii) == IZLAZ)
                break;
        }
        if(*(kombinacija + ii) == IZLAZ) {
            puts("Da li ste sigurni da zelite da prekinete igru? y/n");
            fseek(stdin, 0, SEEK_END);
            do
                iii = getchar();
            while(iii != 'y' && iii != 'n');
            fseek(stdin, 0, SEEK_END);
            if(iii == 'y')
                break;
            else {
                i--;
                continue;
            }
        }
        if(tesko == false)
            qsort(kombinacija, broj_cifara, sizeof(int), poredi);
        for(ii = 0; ii < broj_cifara; ii++)
            if(*(kombinacija + ii) == *(tacna_kombinacija + ii)) {
                na_mestu++;
                *(preskoci1 + ii) = true;
                *(preskoci2 + ii) = true;
            }
        for(ii = 0; ii < broj_cifara; ii++)
            for(iii = 0; iii < broj_cifara; iii++)
                if(*(kombinacija + ii) == *(tacna_kombinacija + iii) &&
                   *(preskoci1 + ii) == false && *(preskoci2 + iii) == false) {
                    na_pogresnom_mestu++;
                    *(preskoci1 + ii) = true;
                    *(preskoci2 + iii) = true;
                }
        if(na_mestu == broj_cifara) {
            i = POTREFIO;
            break;
        }
        printf("Na mestu: %d Na pogresnom mestu: %d\n", na_mestu, na_pogresnom_mestu);
    }
    if(i == POTREFIO)
        puts("\nBravo!");
    else {
        printf("\nJebi ga sad... Tacna kombinacija: ");
        for(i = 0; i < broj_cifara; i++)
            printf("%d ", *(tacna_kombinacija + i));
        puts("");
    }
    free(kombinacija);
    free(tacna_kombinacija);
    free(preskoci1);
    free(preskoci2);
    fseek(stdin, 0, SEEK_END);
    getchar();
    return 0;
}
int poredi(const void *a, const void *b) {
   return (*(int *) a - *(int *) b);
}
