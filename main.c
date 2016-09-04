#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <limits.h>
#define IZLAZ 0
int main(int argc, char *argv[]) {
    int i, ii, iii, cifra, duzina = 0, broj_cifara = 4, broj_znakova = 6, max_pokusaja = 10,
        na_mestu, na_pogresnom_mestu, *kombinacija, *tacna_kombinacija, trenutna_cifra;
    bool tesko = false, *preskoci1, *preskoci2, brise;
    char na_mestu_znak = '*', na_pogresnom_mestu_znak = '.', broj[11];
    while((i = getopt(argc, argv, "c:p:t:z:m:n:h")) != -1)
        switch(i) {
            case 'c':
                broj_cifara = (ii = atoi(optarg)) > 1 ? ii : 4;
                break;
            case 'p':
                max_pokusaja = (ii = atoi(optarg)) >= 1 ? ii : 10;
                break;
            case 't':
                tesko = optarg[0];
                break;
            case 'z':
                broj_znakova = (ii = atoi(optarg)) > 1 ? ii : 6;
                break;
            case 'm':
                na_mestu_znak = optarg[0];
                break;
            case 'n':
                na_pogresnom_mestu_znak = optarg[0];
                break;
            case 'h':
                printf("-c [broj] podesi broj cifara u kombinaciji (2 - %d)\n"
                    "-p [broj] podesi dozvoljeni broj pokusaja (1 - %d)\n"
                    "-z [broj] podesi broj razlicitih znakova u kombinaciji (2 - %d)\n"
                    "-m [znak] podesi znak koji predstavlja broj na mestu\n"
                    "-n [znak] podesi znak koji predstavlja broj na pogresnom mestu\n"
                    "-t [broj] podesi tezinu na:\n"
                    "\t0 - lako (redosled je nebitan)\n"
                    "\t1 - tesko (redosled je bitan)\n\n"
                    "Ukoliko je unesena besmislena vrednost koristice se podrazumevana.\n",
                    INT_MAX, INT_MAX, INT_MAX);
                getch();
                return 0;
        }
    if(!tesko)
        na_pogresnom_mestu_znak = na_mestu_znak;
    for(i = max_pokusaja; i; i /= 10)
      duzina++;
    kombinacija = malloc(broj_cifara * sizeof(int));
    tacna_kombinacija = malloc(broj_cifara * sizeof(int));
    preskoci1 = malloc(broj_cifara * sizeof(bool));
    preskoci2 = malloc(broj_cifara * sizeof(bool));
    srand(time(NULL));
    i = broj_cifara;
    while(i--)
        tacna_kombinacija[i] = rand() % broj_znakova + 1;
    printf("Koristi -h zastavicu pri pokretanju za pomoc.\n"
        "Pritisni 0 da prekines\n"
        "Tezina: %s\n"
        "Kombinaciju mogu ciniti brojevi od 1 do %d\n"
        "Broj pokusaja: %d\n", tesko ? "tesko" : "lako", broj_znakova, max_pokusaja);
    for(i = 1; i <= max_pokusaja; i++) {
        trenutna_cifra = na_mestu = na_pogresnom_mestu = 0;
        ii = broj_cifara;
        while(ii--)
            preskoci1[ii] = preskoci2[ii] = false;
        putchar('\n');
        UNESI:
        printf("\r#%*d |", duzina, i);
        if(trenutna_cifra > 0)
            for(ii = 0; ii < trenutna_cifra; ii++)
                printf("%d|", kombinacija[ii]);
        while(trenutna_cifra < broj_cifara) {
            ii = 0;
            while(true) {
                if((cifra = getch()) == '\r') {
                    if(ii)
                        break;
                    else {
                        putchar('\a');
                        continue;
                    }
                }
                if(cifra == '0' && !ii) {
                    fputs("\rDa li zelite da izadjete? y/n", stdout);
                    while((cifra = getch()) != 'y' && cifra != 'n')
                        putchar('\a');
                    if(cifra == 'y')
                        goto NIJE_POTREFIO;
                    else {
                        fputs("\r                             ", stdout);
                        goto UNESI;
                    }
                }
                if(cifra == '\b') {
                    if(ii) {
                        fputs("\b \b", stdout);
                        ii--;
                    } else
                        if(trenutna_cifra)
                            if(brise) {
                                fputs("\b \b", stdout);
                                itoa(kombinacija[--trenutna_cifra], broj, 10);
                                ii = strlen(broj);
                                brise = false;
                            } else
                                brise = true;
                        else
                            putchar('\a');
                    continue;
                }
                if(ii > 9) {
                    putchar('\a');
                    continue;
                }
                putchar(broj[ii++] = cifra);
                brise = false;
            }
            putchar('|');
            broj[ii] = '\0';
            kombinacija[trenutna_cifra++] = atoi(broj);
        }
        for(ii = 0; ii < broj_cifara; ii++)
            if(kombinacija[ii] == tacna_kombinacija[ii]) {
                na_mestu++;
                preskoci1[ii] = preskoci2[ii] = true;
                putchar(na_mestu_znak);
            }
        for(ii = 0; ii < broj_cifara; ii++)
            for(iii = 0; iii < broj_cifara; iii++)
                if(kombinacija[ii] == tacna_kombinacija[iii] && !preskoci1[ii] && !preskoci2[iii]) {
                    na_pogresnom_mestu++;
                    preskoci1[ii] = preskoci2[iii] = true;
                    putchar(na_pogresnom_mestu_znak);
                }
        if(!tesko)
            na_mestu += na_pogresnom_mestu;
        if(na_mestu == broj_cifara) {
            puts("\n-----\nBravo!");
            goto KRAJ;
        }
    }
    NIJE_POTREFIO:
    printf("\n-----\nJebi ga sad... Tacna kombinacija: |");
    for(i = 0; i < broj_cifara; i++)
        printf("%d|", tacna_kombinacija[i]);
    putchar('\n');
    KRAJ:
    free(kombinacija);
    free(tacna_kombinacija);
    free(preskoci1);
    free(preskoci2);
    getch();
    return 0;
}
