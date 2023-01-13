#include <rlutil.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 31
#define MAX1 61
#define MAX2 2
#define ad 11
 //-----------------------------STUDENT : PREDA CRISTIAN-----------------------------------------------------------------------------------//
 //-----------------------------GRUPA : 164------------------------------------------------------------------------------------------------//
 //-----------------------------PROGRAM PENTRU MANAGEMENTUL UNEI BAZE DE DATE CE REPREZINTA UN CATALOG VIRTUAL-----------------------------//

void terminalClear()
{
cls();
}

typedef struct userr
{
    char nume[ad];
    char parola[ad];
} user;
//-----------------------------FUNCTIA DE LOGARE-------------------------------//
int logare()
{
        FILE* f = fopen("admin.txt","r");
        int n;
        fscanf(f,"%d",&n);
        user *v = malloc(n * sizeof(*v));
        char nume1[ad],parola[ad];
        int i=0;
        while(i<n)
        {
            fscanf(f,"%10s", v[i].nume);
            fscanf(f,"%10s", v[i].parola);
            i++;
        }
        printf("Introduceti numele (maxim 10 caractere) : ");
        scanf("%10s", nume1);
        for(i=0;i<n;i++)
        if (strcmp(nume1,v[i].nume)==0)
            break;
        if(i==n)
            return 0;
        int j=i;
        printf("Introduceti parola (maxim 10 caractere) : ");
    for(i=0; i <ad-1;i++)
    {
        char c;
        c = getch();
        parola[i] = c;
        if ( parola[i] == '\b' && i!=0)
        {
            printf("\b \b");
            i-= 2;
            continue;
        }
        else if ( parola[i] == '\b' && i == 0)
        {
            i--;
            printf("\b \b");
            printf(" ");
            continue;
        }
        else if( parola[i] != '\r')
            printf("*");
        else
            break;
    }
    parola[i]='\0';
    if(strcmp(parola,v[j].parola) == 0)
        {
            free(v);
            return 1;
        }
    else
        {
            free(v);
            return -1;
        }
}

enum Stare_elev
{
   Corigent=0,
   Trecut=1,

};

enum Optiune
{
    n=0,

    d=1,
};

typedef struct catalog
{
        int varsta;
        char nsp[MAX1];
        char gen[MAX2];
        int zi;
        int luna;
        int an;
        char initiala_tata[4];
        int cnp[ad+2];
        double medie;
        int nmate[ad], nfizica[ad], nchimie[ad], ninfo[ad], ntic[ad], nbio[ad], neng[ad], nfr[ad], nsport[ad], nromana[ad], nmuzica[ad], ndesen[ad];
        int mmate[MAX2],mfizica[MAX2],mchimie[MAX2],minfo[MAX2],mtic[MAX2],mbio[MAX2],meng[MAX2],mfr[MAX2],msport[MAX2],mromana[MAX2],mmuzica[MAX2],mdesen[MAX2];
}catalog;

//------------------FUNCTIA DE CAUTARE A ELEVULUI------------//

int cautare_elev(char* nume_si_prenume,catalog *v, int n)
 {
     int i=0;
     while(i<n && strcmp(v[i].nsp, nume_si_prenume) !=0 )
     {
         i++;

     }
     if(i<n)
        return i;
    else
        return -1;
 }

 int logare2(int n, catalog *v, int cnp1, int *i)
 {

        int obs= 0;
        unsigned long long int c=cnp1;
        int c1;
        for(;*i<n && obs == 0;++*i)
        {
            c1=c%10;
                int j;
                obs=1;
                j=3;
            while(j>=0 && obs == 1)
            {
                if(v[*i].cnp[j] == c1 )
                {
                    c/=10;
                    --j;
                    obs=1;
                }
                else
                    obs=0;
            }
            c=cnp1;

        }
        --*i;
        return obs;
 }

void modificareVarsta(int i, int b, catalog *v)
 {
    v[i].varsta=b;
 }

void modificareZi(int i, int b,catalog *v)
 {
    v[i].varsta=b;
 }

void modificareLuna(int i, int b,catalog *v)
 {
    v[i].varsta=b;
 }

void modificareAn(int i, int b,catalog *v)
 {
    v[i].varsta=b;
 }

void modificareNume(int i, char *a,catalog *v)
 {
     strcpy(v[i].nsp,a);
 }

void modificareGen(int i,catalog *v)
 {
     char a[2];
    printf("Introduceti noua litera ce reprezinta sexul individului : ");
    scanf("%1s",a);
    *a=toupper(*a);
    if(strcmp(a,"M")==0 ||strcmp(a,"F")==0 )
        strcpy(v[i].gen,a);
    else {
        puts("VA ROG INTRODUCETI M SAU F!");
        modificareGen(i,v);
    }
 }

void stergere_copil( int i, int *n,catalog *v)
 {
     for (;i<*n;i++)
        v[i]=v[i+1];
   (*n)--;
}

 //-----------------------------FUNCTIA DE ADAUGARE-----------------------------//
void adaugareElev(int *n,catalog *v)
{
    int i=*n;
    unsigned long long int cnp1;
    printf("Introduceti varsta :");
    scanf("%d", &v[i].varsta);

    printf("\nIntroduceti numele si prenumele ca in exemplul urmator (Popescu_Alin) :");
    scanf("%60s", v[i].nsp);

    printf("\nIntroduceti sexul individului M sau F:");
    scanf("%1s", v[i].gen);

    printf("\nIntroduceti data de nastere cu spatiu intre argumente ca in exemplul urmator (11 12 2003) :");
    scanf("%d %d %d", &v[i].zi , &v[i].luna , &v[i].an);
    printf("\nIntroduceti cnp-ul:");
    scanf("%" SCN64u,&cnp1);
    int j;
    for(j=12;j>=0;j--)
        {
            v[i].cnp[j]=cnp1%10;
            cnp1/=10;
        }
    *n+=1;
}

//-----------------------------FUNCTIA DE CITIRE DIN FISIER-------------------------------//
void citire(catalog *v, int *i)
{
    int n;
    FILE* f = fopen("NrDate.txt","r");
    FILE* g = fopen("FileIn.txt", "r");
    fscanf(f,"%d", &n);
    for(*i=0;*i<n;++*i)
    {
        unsigned long long int cnp1;
        fscanf(g, "%d %60s %1s %d %d %d %" SCN64u, &v[*i].varsta , v[*i].nsp , v[*i].gen , &v[*i].zi , &v[*i].luna , &v[*i].an, &cnp1);
        int j;
        for(j=12;j>=0;j--)
        {
            v[*i].cnp[j]=cnp1%10;
            cnp1/=10;
        }

            fscanf(g,"%d", &v[*i].nmate[0]);
            int obs = v[*i].nmate[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].nmate[j]);
            }
            fscanf(g,"%d", &v[*i].nfizica[0]);
            obs = v[*i].nfizica[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].nfizica[j]);
            }
            fscanf(g,"%d", &v[*i].nchimie[0]);
            obs = v[*i].nchimie[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].nchimie[j]);
            }
            fscanf(g,"%d", &v[*i].ninfo[0]);
            obs = v[*i].ninfo[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].ninfo[j]);
            }
            fscanf(g,"%d", &v[*i].ntic[0]);
            obs = v[*i].ntic[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].ntic[j]);
            }
            fscanf(g,"%d", &v[*i].nbio[0]);
            obs = v[*i].nbio[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].nbio[j]);
            }
            fscanf(g,"%d", &v[*i].neng[0]);
            obs = v[*i].neng[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].neng[j]);
            }
            fscanf(g,"%d", &v[*i].nfr[0]);
            obs = v[*i].nfr[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].nfr[j]);
            }
            fscanf(g,"%d", &v[*i].nsport[0]);
            obs = v[*i].nsport[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].nsport[j]);
            }
            fscanf(g,"%d", &v[*i].nromana[0]);
            obs = v[*i].nromana[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].nromana[j]);
            }
            fscanf(g,"%d", &v[*i].nmuzica[0]);
            obs = v[*i].nmuzica[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].nmuzica[j]);
            }
            fscanf(g,"%d", &v[*i].ndesen[0]);
            obs = v[*i].ndesen[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].ndesen[j]);
            }
    }

    fclose(g);
    fclose(f);
}

//-----------------------------FUNCTIA DE SCRIERE IN FISIER-------------------------------//
void scriere(catalog * v, int n)
{
    FILE* g = fopen("FileIn.txt", "w");
    for(int i = 0; i< n ; i++)
       {
           fprintf(g , "%d %s %s %d %d %d ", v[i].varsta , v[i].nsp , v[i].gen , v[i].zi , v[i].luna , v[i].an);
           int j;
        for(j=0;j<13;j++)
        {
            fprintf(g , "%d", v[i].cnp[j]);
        }
        fprintf(g , " ");
            fprintf(g,"%d ", v[i].nmate[0]);
            int obs = v[i].nmate[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fprintf(g,"%d ", v[i].nmate[j]);
            }
            fprintf(g,"%d ", v[i].nfizica[0]);
            obs = v[i].nfizica[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fprintf(g,"%d ", v[i].nfizica[j]);
            }
            fprintf(g,"%d ", v[i].nchimie[0]);
            obs = v[i].nchimie[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fprintf(g,"%d ", v[i].nchimie[j]);
            }
            fprintf(g,"%d ", v[i].ninfo[0]);
            obs = v[i].ninfo[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fprintf(g,"%d ", v[i].ninfo[j]);
            }
            fprintf(g,"%d ", v[i].ntic[0]);
            obs = v[i].ntic[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fprintf(g,"%d ", v[i].ntic[j]);
            }
            fprintf(g,"%d ", v[i].nbio[0]);
            obs = v[i].nbio[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fprintf(g,"%d ", v[i].nbio[j]);
            }
            fprintf(g,"%d ", v[i].neng[0]);
            obs = v[i].neng[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fprintf(g,"%d ", v[i].neng[j]);
            }
            fprintf(g,"%d ", v[i].nfr[0]);
            obs = v[i].nfr[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fprintf(g,"%d ", v[i].nfr[j]);
            }
            fprintf(g,"%d ", v[i].nsport[0]);
            obs = v[i].nsport[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fprintf(g,"%d ", v[i].nsport[j]);
            }
            fprintf(g,"%d ", v[i].nromana[0]);
            obs = v[i].nromana[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fprintf(g,"%d ", v[i].nromana[j]);
            }
            fprintf(g,"%d ", v[i].nmuzica[0]);
            obs = v[i].nmuzica[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fprintf(g,"%d ", v[i].nmuzica[j]);
            }
            fprintf(g,"%d ", v[i].ndesen[0]);
            obs = v[i].ndesen[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fprintf(g,"%d ", v[i].ndesen[j]);
            }
       fprintf(g, "\n");}
    fclose(g);
}

//-----------------------------FUNCTIA DE SORTARE-------------------------------//
int sortare_nume(const void * a, const void * b)
{
        catalog * A = (catalog *) a;
        catalog * B = (catalog *) b;
 return strcmp(A->nsp,B->nsp);
}

//-----------------------------FUNCTIA DE AFISARE DATE ELEV-----------------------------//
void afisare_elev(int n, catalog *v)
{
    int i;
    for(i=0; i<n; ++i)
    printf("|| %d || %s || %s || %d.%d.%d ||\n", v[i].varsta , v[i].nsp , v[i].gen , v[i].zi , v[i].luna , v[i].an);
}

 //-----------------------------FUNCTIA MAIN-----------------------------//
int main()
{
        int i=0, n;
        int y=0;
        int x;
//-----------------------------CITIRE DIN FISIER-----------------------------//
        FILE* f = fopen("NrDate.txt", "r");
        fscanf(f,"%d", &n);
        catalog *v = malloc(n * sizeof(*v));
        fclose(f);
        citire(v,&i);
        //afisare_elev(n,v);
//-----------------------------SORTARE ALFABETIC-----------------------------//
        qsort(v, n ,sizeof(*v), &sortare_nume);
        scriere(v,n);

//-----------------------------LOGARE-----------------------------//
    printf("Introduceti optiunea de logare\n->1 pentru elev/parinte\n->2 pentru cadru didactic\n:");
    scanf("%d",&y);
    switch(y)
    {case(1):
    {
        int j;
        int cnp1;
        int obs=1;
        while(obs==1)
        {
            i=0;
            printf("Introduceti primele 4 cifre din CNP-ul elevului:");
            scanf("%d",&cnp1);
            obs = logare2(n, v, cnp1,&i);
        if(obs==0)
        {
            printf("\nCNP gresit! Va rugam sa verificati si sa introduceti CNP-ul corect");
            obs=1;
        }
        else break;
        }

        printf("|| Varsta || Nume si Prenume || Sex || Data Nasterii || CNP ||\n");
        printf("|| %d || %s || %s || %d.%d.%d || ", v[i].varsta , v[i].nsp , v[i].gen , v[i].zi , v[i].luna , v[i].an);
         for(j=0;j<13;j++)
        {
            printf( "%d", v[i].cnp[j]);
        }
        puts(" ||");

        break;

    }
    case(2):
        {   while(logare()!=1)
            {
                terminalClear();
                printf("Numele sau parola sunt gresite!\n");
            }
            char nume_si_prenume[MAX1];
             while(1)
    {
        //-----------------------------AFISARE CATALOG-----------------------------//
        afisare_elev(n, v);
        x=0;
        printf("Introduceti numele elevului pentru a schimba datele\nx pentru a iesi \nadd pentru a adauga elevi: ");
        scanf("%60s", nume_si_prenume);
        i=cautare_elev(nume_si_prenume,v,n);
        terminalClear();
    // VERIFICA DACA A FOST INTRODUSA OPTIUNEA DE IESIRE SAU ADAUGARE
        if(strcmp(nume_si_prenume,"x")==0)
            {
                free(v);
                exit(0);
            }

       else if(strcmp(nume_si_prenume,"add")==0)
            {
                v = realloc(v, (n+1)*sizeof(*v));
                if(v == NULL)
                {
                    printf("\nEroare realloc!\n");
                    exit(-1);
                }
                adaugareElev(&n,v);
                FILE* g = fopen("NrDate.txt", "w");
                fprintf(g,"%d", n);
                fclose(g);
                qsort(v, n ,sizeof(*v), &sortare_nume);
                scriere(v,n);
                continue;

            }

    // CAUTA INDICELE ELEVULUI
        else if(i==-1)
            {
                printf("Elevul nu apartine acestei clase!\n");
                continue;
            }
        do{
        printf("Introduceti :\n->1 pentru varsta\n->2 pentru data de nastere\n->3 pentru gen\n->4 pentru a sterge copilul din catalog \n->5 pentru a modifica numele \n->6 pentru a iesi \n|Optiunea aleasa|:" );
        scanf("%d", &y);
        }while( y<1 || y>6);
        terminalClear();
            switch(y)
            {
            //---------VARSTA---------//
            case(1):
                {
                    printf("Varsta lui %s este %d. Pentru a o modifica introduceti 1:", v[i].nsp,v[i].varsta );
                    scanf("%d", &x);
                    if(x==1)
                        {
                            int a;
                            printf("\nIntroduceti noua varsta : ");
                            scanf("%d", &a);
                            modificareVarsta(i,a,v);
                        }

                break;
                }
            //---------DATA NASTERE---------//
            case(2):
                {
                    printf("Data de nastere a lui %s este %02d %02d %02d . Pentru a modifica data nasterii introduceti 1:", v[i].nsp,v[i].zi , v[i].luna, v[i].an);
                    scanf("%d", &x);
                    if(x==1)
                        {
                            int a,b,c;
                            printf("Introduceti noua data de nastere in ordinea zi luna an cu spatiu intre numere: ");
                            scanf("%d,%d,%d", &a,&b,&c);
                            modificareZi(i, a,v);
                            modificareLuna(i, b,v);
                            modificareAn(i, c,v);
                        }
                break;}
            //---------GEN---------//
            case(3):
                {
                    printf("Genul lui %s este %s . Pentru a modifica introduceti 1 : \n", v[i].nsp,v[i].gen);
                     scanf("%d", &x);
                    if(x==1)
                        {
                            modificareGen(i,v);
                        }
                break;}
            //---------STERGERE---------//
            case(4):
                {
                    stergere_copil(i,&n,v);
                break;
                }
            //---------MODIFICARE NUME---------//
            case(5):
                {
                    printf("Numele este %s\n", v[i].nsp);
                            char a[MAX1];
                            printf("Introduceti noul nume : ");
                            scanf("%60s", a);
                            modificareNume(i, a,v);
                            printf("Noul Nume : %s a fost schimbat cu succes", v[i].nsp);

                 break;
                }

             case(6):
                {
                    qsort(v, n ,sizeof(*v), &sortare_nume);
                    scriere(v,n);
                    free(v);
                    exit(0);
                }
            }
            terminalClear();
    }

            break;
        }
    }


    return 0;
}
