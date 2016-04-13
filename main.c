#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
void poredjaj(int, int *);
int main(int argc, char *argv[]) {
    int i, ii, iii, broj_cifara = 4, broj_znakova = 6, max_pokusaja = 10,
        na_mestu, na_pogresnom_mestu, *kombinacija, *tacna_kombinacija;
    bool potrefio = false, tesko = false, *preskoci1, *preskoci2;
    char c;
    while((c = getopt(argc, argv, "c:p:ltz:h")) != -1)
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
                exit(0);
                break;
        }
    kombinacija = malloc(broj_cifara * sizeof(int));
    tacna_kombinacija = malloc(broj_cifara * sizeof(int));
    preskoci1 = malloc(broj_cifara * sizeof(bool));
    preskoci2 = malloc(broj_cifara * sizeof(bool));
    srand(time(NULL));
    for(i = 0; i < broj_cifara; i++)
        *(tacna_kombinacija + i) = rand() % broj_znakova + 1;
    puts("Koristi -h zastavicu pri pokretanju za pomoc.\n");
    if(tesko == true)
        puts("Tezina: tesko\n");
    else {
        puts("Tezina: lagano\n\nBrojevi u kombinaciji su poredjani po velicini\n");
        poredjaj(broj_cifara, tacna_kombinacija);
    }
    printf("Kombinaciju mogu ciniti brojevi od 1 do %d\n\n", broj_znakova);
    printf("Broj pokusaja: %d\n\n", max_pokusaja);
    for(i = 1; (potrefio == false) && (i <= max_pokusaja); i++) {
        na_mestu = 0;
        na_pogresnom_mestu = 0;
        for(ii = 0; ii < broj_cifara; ii++) {
            *(preskoci1 + ii) = false;
            *(preskoci2 + ii) = false;
        }
        printf("Unesi kombinaciju: ");
        for(ii = 0; ii < broj_cifara; ii++)
            scanf("%d", kombinacija + ii);
        if(tesko == false)
            poredjaj(broj_cifara, kombinacija);
        for(ii = 0; ii < broj_cifara; ii++)
            if(*(kombinacija + ii) == *(tacna_kombinacija + ii)) {
                na_mestu++;
                *(preskoci1 + ii) = true;
                *(preskoci2 + ii) = true;
            }
        for(ii = 0; ii < broj_cifara; ii++)
            for(iii = 0; iii < broj_cifara; iii++)
                if((*(kombinacija + ii) == *(tacna_kombinacija + iii)) &&
                   (*(preskoci1 + ii) == false) && (*(preskoci2 + iii) == false)) {
                    na_pogresnom_mestu++;
                    *(preskoci1 + ii) = true;
                    *(preskoci2 + iii) = true;
                }
        if(na_mestu == broj_cifara)
            potrefio = true;
        printf("Na mestu: %d Na pogresnom mestu: %d Ostalo pokusaja: %d\n\n",
               na_mestu, na_pogresnom_mestu, max_pokusaja - i);
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
    free(preskoci1);
    free(preskoci2);
    fseek(stdin, 0, SEEK_END);
    getchar();
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
