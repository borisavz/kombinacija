# kombinacija
Zajebana igrica za vežbanje vijuga.

Cilj igre je potrefiti tačnu kombinaciju za određen broj pokušaja.

Zastavice:
    -h pomoć
    -c [broj] podesi broj cifara u kombinaciji (2 - 2147483647)
    -p [broj] podesi dozvoljeni broj pokusaja (1 - 2147483647)
    -z [broj] podesi broj razlicitih znakova u kombinaciji (2 - 2147483647)
    -m [znak] podesi znak koji predstavlja broj na mestu
    -n [znak] podesi znak koji predstavlja broj na pogresnom mestu
    -t [broj] podesi tezinu na:
        0 - lako (redosled je nebitan)
        1 - tesko (redosled je bitan)

    Ukoliko je unesena besmislena vrednost koristice se podrazumevana.

Podrazumevane vrednosti:
    broj cifara: 4
    broj pokušaja: 10
    broj znakova: 6
    znak za broj na mestu: *
    znak za broj na pogrešnom mestu: .
        *ukoliko je težina podešena na lako znak za broj na pogrešnom mestu je isti kao znak za broj na mestu
    težina: lako
