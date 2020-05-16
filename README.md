# Marele Arhipelag Eao-Zinci

## Descriere

Arhipelagul Eao-Zinci din Orientul Indepartat este in plina dezvoltare. Fiecare insula din arhipelag produce zilnic o serie de resurse. Acestea sunt folosite local si/sau distribuite catre alte insule folosind flota aeriana Eao-Zinci.

Rutele de transport sunt configurate in fiecare dimineata pentru a asigura distributia optima a resurselor (__etapa de proiectare__).

Intrand in era automatizarii, conducatorii arhipelagului doresc sa treaca la urmatorul pas si sa poata sa-si distribuie resursele in cel mai eficient mod posibil (__etapa de analiza__).

Mai mult, pentru a elimina potentialele conflicte in ce priveste accesul la flota aeriana, in fiecare seara, avioanele sunt redistribuite intre insule (__etapa de gestiune__).

Pentru a rezolva aceste probleme, conducatorii cauta un _programator priceput_ si au formlat problemelor lor mai jos!

## Input

Va fi pus la dispozitie fisierul __date.in__  care va avea urmatoarea structura:

1. Numar de insule - n
2. Pe urmatoarele n linii se vor descrie insulele cu resursele proprii.

        Nume insula
            Numar resurse -m
            Tip_1 resursa si cantitate
            Tip_2 resursa si cantitate
            ...
            Tip_m resursa si cantitate

            Exemplu:
            Island1
                3
                Fier 350
                Carbune 150
                Piatra 100
            Island2
                3
                Argint 200
                Aur 10
                Fier 350

<br><br>

3. Numar conexiuni -p (se vor prezenta conexiunile intre insulele arhipelagului si durate de zbor prestabilie).

4.  Pe urmatoarele p linii se vor afisa conexiunile intre insule: __Island Y - IslandZ durata_zbor__

        Exemplu:
        Island1 - Island3 30
        Island1 - Island5 25

    __Observatie:__ Daca exista conexiunea intre insula X si insula Y, atunci exista zbor care duce din X in Y, dar si un zbor care duce din Y in X.

5. __Cerinte partea de proiectare si analiza__ (se citesc fluxul de date pana la terminarea fisierului in cazul testelor 1-8 si, respectiv, pana la intalnirea primei linii care contine doar o valoare intreaga in cazull testelor 9-14). Cerintele pentru etapele de proiectare si analiza pot sa fie:
    * __conexiune X Y__
    * __adauga_zbor X Y cost__
    * __anulare_zbor X Y__
    * __legatura X__
    * __alte_cerinte__ (vor fi prezentate mai jos)

            Exemplu:
            conexiune Island1 Island3
            adauga_zbor Island2 Island3 15
            anulare_zbor Island3 Island5

## Descriere cerinte

Dupa citirea insulelor si conexiunilor, fisierul de input va contine partea de proiectare (modificarea traseelor intre insule pentru ziua curent) si cea de analiza a datelor pentru distribuirea optima a resurselor. Astfel:

### __1. Proiectare__

Avand in vedere dezvoltarea continua a arhipelagului in fiecare zi si intentia acestora de automatizare a distribuirii resurselor catre celelalte insule in nevoie, se comunica niste modificari generale.

* __[conexiune IslandX IslandY]__ : se va afisa __OK__ daca exista conexiune directa intre cele doua insule si __NO__ in caz contrar.
* __[legatura IslandX]__ : se cere __legatura directa__ a IslandX cu celelalte insule din arhipelag

    __Observatie:__ In cazul in care nu exista nicio legatura __NU__ se afiseaza nimic
* __[adauga_zbor IslandX IslandY cost]__ : se va adauga un __drum direct__ de durata __cost__ intre __IslandX__ si __IslandY__

* __[anulare_zbor IslandX IslandY]__ : se va sterge drumul direct dintre IslandX si IslandY

* __[max_resurse]__ : se va afisa numarul de resurse distincte de pe tot arhipelagul, urmat de numele resurselor separate printr-un spatiu in ordine lexicografica.

    __Exemplu :__ __5 Argint Aur Carbune Fier Piatra__

* __[max_cantitate resursa]__ : se va afisa insula (respectiv insulele) cu cantitatea cea mai mare de resursa disponibila (__Observatie__ : Afisarea insulelor se va face in ordine, adica de la prima la ultima)
    
    __Exemplu :__ Pentru max_cantitate Fier se va afisa : __Island1 Island2__

### __2. Analiza__

In urmatoarea parte, se vor dezvolta algoritmi pentru determinarea eficienta a drumurilor, respectiv timpului intre doua insule.

* __[drum_zbor IslandX IslandY]__ : se cere afisarea __drumului cel mai scurt__ (din punctul de vedere al duratei) de la __IslandX__ la __IslandY__. Afisarea va fi de la prima insula intermediara pana la insula destinatie, adica IslandY. __Observatie :__ In cazul in care *__NU__* exista drum se va afisa __NO__

    In contextul minimizarii timpului de zbor se vor analiza doua scenarii:

    * __[timp_zbor IslandX IslandY]__ : se cere afisarea duratei minime in conditii de distribuire instanta. __Observatie :__ In cazul in care *__NU__* se poate determina timpul zborului se va afisa __INF__.
   
    * __[min_zbor IslandX IslandY]__ : se cere afisarea duratei minime in conditiile adaugarii stationarii pe insulele intermediare pana la IslandY. 
    
        _Acesta este cazul in care se distribuie resursele atunci cand traficul este ingreunat, considerandu-se o stationare standard de 15 minute pe fiecare insula, pentru atenuarea coliziunilor sau supraincarcarii aeroporturilor insulelor._

            Exemplu:
            Island1 - Island3 40
            Island1 - Island2 10
            Island2 - Island3 25

            Pentru drum_zbor Island1 Island3 se va afisa Island2 Island3

            Pentru timp_zbor Island1 Island3 se va afisa 35 (10+25)

            Pentru min_zbor Island1 Island3 se va afisa 40 (deoarece daca am fi ales drumul prin Island2 s-ar fi adaugat timpul de stationare de 15 si ar fi devenit 50 > 40)

### __3. Gestiune__ 

Pentru buna dispozitie a locuitorilor arhipelagului si evitarea razboaielor intre insule pe tema accesului facil la resurse si flota aeriana, conducatorii au hotarat urmatoarele: "deoarece la finalul zilei pot sa existe insule cu un aerodrom sub sau supraincarcat, flota se redistribuie in fiecare seara, daca e cazul."

Pentru optimizarea problemei, conducatorul arhipelagului, Ghi Yu, cere o analiza a tuturor posibilitatilor de gestionare a avioanelor, introducand atat restrictii, cat si evenimente recurente. In urma analizei, se doreste diminuarea sub/supraincarcarii: fiecare insula poate sa aiba un numar maxim de avioane, __toleranta__ maxima e comunicata tuturor si e aceeasi pentru toate insulele.

Structura este urmatoarea:

    Numar de insule n 
    Toleranta t
    Numar de avioane pentru fiecare insula (vector de dimensiune n)
    Pe fiecare dintre urmatoarele n linii se da vectorul cu ID-urile avioanelor insulei X (ID-urile sunt ordonate crescator)
    Pe urmatoarele n linii se gaseste matricea de adiacenta care precizeaza existenta conexiunilor directe intre insule (1 sau 0)

__Observatii:__
* Au prioritate insulele care pot asigura numarul de locuri egal cu numarul de avioane cedate de insula sursa

* Daca toate insulele cu care are conexiune InsulaX nu au cel putin numarul de locuri necesar, se reia procesul pornind de la prima insula cu care InsulaX are legatura.

    *Adica, se efectueaza cautari pana cand se gaseste o insula care poate sa primeasca numarul de avioane cedate. Daca nu exista o astfel de insula, dar in arhipelag numarul total de locuri disponibile este egal cu numarul de avioane, atunci avioanele vor fi distribuite in acele locuri. Daca nu exista o astfel de insula si in arhipelag nu exista un numar total de locuri disponibile egal cu numarul de avioane cedate se va afisa __Stack Overflow!__*

---
---
---
---

## Detalii rezolvare

In folderul cu toate fisierele se vor gasi _5_ fisiere sursa: __avion.c, graph.c, functions.c, files.c, BST.c__ cu headerele aferente (plus un header __utils.h__), si un makefile.

* In *__files.c__* sunt functiile de deschis un fisier cu rol de _append_, respectiv _write_

* In *__graph.c__* se regasesc functiile de creare/eliberare a grafului, citire din fisierul de input si adaugare in graf, adaugare a insulelor. Tot aici este apelata o functie pentru rezolvarea functiilor de la __1) Proiectare__ si __2) Analiza__, urmand ca ulterior sa fie eliberat grafului initial si creat un nou graf, pentru __3) Gestiune__.

* In *__functions.c__* se regasesc majoritatea functiilor necesare. Aici se vor regasi toate functiile descrise la cele trei etape, cat si o modalitate de citire a acestora din fisier (prin functia __readFunctions__).

* In *__BST.c__* se regasesc functiile de creare/eliberare a unui arbore binar de cautare, cat si de traversare in inordine. Rolul unui BST este mai mult pentru functia __max_resurse__ pentru cazul in care trebuie sa afisam afisarea resurselor distincte, in ordine lexicografica. Pentru aceasta cerinta am considerat ca un _Binary Search Tree_ ar fi fost tipul de structura cel mai potrivit.

* In *__avion.c__*  este functia _main_ a programului, unde imi deschid fisierul cu rol de write (doar pentru a crearea acestuia, nu scriu nimic), dupa care apelez functia __File_toGraph__.

    _Detaliile despre rolul fiecarei functii pot fi regasite in cod, prin intermediul comentariilor._
