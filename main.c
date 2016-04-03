#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
void poredjaj(int, int *);
int main(int argc, char *argv[]) {
    int i, ii, iii, broj_cifara = 4, max_pokusaja = 10, na_mestu,
        *kombinacija, *tacna_kombinacija;
    bool potrefio = false, tesko = false;
    char c;
    while((c = getopt(argc, argv, "c:p:lth")) != -1)
        switch(c) {
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
            case 'h':
                puts("-c [broj] promeni broj cifara u kombinaciji");
                puts("-p [broj] promeni dozvoljeni broj pokusaja");
                puts("-l podesi tezinu na lagano (brojevi su poredjani)");
                puts("-t podesi tezinu na tesko (brojevi nisu poredjani)\n");
                bgetc();
                exit(0);
                break;
        }
    kombinacija = malloc(broj_cifara * sizeof(int));
    tacna_kombinacija = malloc(broj_cifara * sizeof(int));
    srand(time(NULL));
    for(i = 0; i < broj_cifara; i++)
        *(tacna_kombinacija + i) = rand() % 6 + 1;
    if(tesko == true)
        puts("Tezina: tesko\n");
    else {
        puts("Tezina: lagano\nBrojevi u kombinaciji su poredjani po velicini");
        poredjaj(broj_cifara, tacna_kombinacija);
    }
    printf("Broj pokusaja: %d\n\n", max_pokusaja);
    for(i = 1; (potrefio == false) && (i <= max_pokusaja); i++) {
        na_mestu = 0;
        printf("Unesi kombinaciju: ");
        for(ii = 0; ii < broj_cifara; ii++)
            scanf("%d", kombinacija + ii);
        if(tesko == false)
            poredjaj(broj_cifara, kombinacija);
        for(ii = 0; ii < broj_cifara; ii++)
            if(*(kombinacija + ii) == *(tacna_kombinacija+ ii))
                na_mestu++;
        if(na_mestu == broj_cifara)
            potrefio = true;
        printf("Na mestu: %d Ostalo pokusaja: %d\n\n", na_mestu, max_pokusaja - i);
    }
    if(potrefio == true)
        puts("\nBravo!");
    else {
        printf("\nJebi ga sad... Tacna kombinacija: ");
        for(i = 0; i < broj_cifara; i++)
            printf("%d ", *(tacna_kombinacija + i));
        puts("");
    }
    free(kombinacija);
    free(tacna_kombinacija);
    bgetc();
    return 0;
}
void poredjaj(int duzina_niza, int *niz) {
    int i, t;
    bool poredjao = false;
    while(poredjao == false) {
        poredjao = true;
        for(i = 0; i < duzina_niza - 1; i++)
            if(*(niz + i) > *(niz + i + 1)) {
                poredjao = false;
                t = *(niz + i);
                *(niz + i) = *(niz + i + 1);
                *(niz + i + 1) = t;
            }
    }
}
/*
int bgetc() {
    fseek(stdin, 0, SEEK_END);
    return getchar();
}
*/
