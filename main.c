#include <rlutil.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
enum Verificare
{
   Esuat=0,
   Trecut=1,

};

typedef struct userr
{
    char nume[ad];
    char parola[ad];
} user;
//-----------------------------FUNCTII ADMINISTRARE USER-------------------------------//

void scriere_admin(int n, user *v)
{
    FILE* f = fopen("admin.txt", "wb");
    fprintf(f,"%d ",n);
    int i;
    for(i=0;i<n;i++)
    {
        int j;
        for(j=0;(unsigned int)j<strlen(v[i].nume);j++)
        v[i].nume[j]-=3;
        for(j=0;(unsigned int)j<strlen(v[i].parola);j++)
        v[i].parola[j]-=3;
    }
    for(i=0;i<n;i++)
        fprintf(f,"%s %s ", v[i].nume,v[i].parola);
    fclose(f);
}
void adaugare_admin(int n, user *v)
{
    printf("Introduce-ti numele utilizatorului : ");
    scanf("%10s", v[n].nume);
    printf("Introduce-ti parola utilizatorului : ");
    scanf("%10s", v[n].parola);
}
void stergere_admin(int *n, user *v,int i)
{
        for (;i<*n;i++)
            v[i]=v[i+1];
        (*n)--;
        scriere_admin(*n,v);
}
//-----------------------------FUNCTIA DE LOGARE-------------------------------//
int logare()
{
        FILE* f = fopen("admin.txt","rb");
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
        for(i=0;i<n;i++)
        {
            int j;
            for(j=0;(unsigned int)j<strlen(v[i].nume);j++)
            v[i].nume[j]+=3;
            for(j=0;(unsigned int)j<strlen(v[i].parola);j++)
            v[i].parola[j]+=3;
        }
        printf("Introduceti numele (maxim 10 caractere) : ");
        scanf("%10s", nume1);
        for(i=0;i<n;i++)
        if (strcmp(nume1,v[i].nume)==0)
            break;
        if(i==n)
            {
                fclose(f);
                free(v);
                enum Verificare d=Esuat;
                return d;
            }
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
    int verificare = 0;
    while(verificare == 0)
    {
        if(strcmp(parola,v[j].parola) == 0)
        verificare=1;
    else
        j++;
    }
            int cont;
            while(1)
            {
                cls();
                printf("|Daca doriti sa adaugati un administrator introduceti : 1\n|Daca doriti sa stergeti un cont de administrator introduceti : 2\n|Iar pentru a continua introduceti : 3\n|Optiunea aleasa : ");
                scanf("%d",&cont);
                switch(cont)
                   {
                    case(1):
                    {
                        ++n;
                        v = realloc(v, (n)*sizeof(*v));
                        if(v == NULL)
                        {
                            puts("realloc a esuat!!");
                            exit(-1);
                        }
                        --n;
                        adaugare_admin(n,v);
                        ++n;
                        scriere_admin(n,v);
                         for(i=0;i<n;i++)
                        {
                            for(j=0;(unsigned int)j<strlen(v[i].nume);j++)
                            v[i].nume[j]+=3;
                            for(j=0;(unsigned int)j<strlen(v[i].parola);j++)
                            v[i].parola[j]+=3;
                        }
                        cls();
                        break;
                    }
                    case(2):
                    {
                        printf("Conturile sunt urmatoarele : \n");
                        for(i=0;i<n;i++)
                        printf("%d. %s %s \n", i,v[i].nume, v[i].parola);
                        printf("Introduce-ti al catelea cont sa fie sters : ");
                        scanf("%d", &i);
                        stergere_admin(&n,v,i);
                        break;
                    }

                    case(3):
                    {
                        free(v);
                        return 1;
                    }
                   }
            }
}


enum Corigente
{
    una=1,

    doua=2,
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
        int mmate,mfizica,mchimie,minfo,mtic,mbio,meng,mfr,msport,mromana,mmuzica,mdesen;
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
        for(;*i<n && obs == 0;++*i)
        {
                int j;
                obs=1;
                j=3;
            while(j>=0 && obs == 1)
            {
                if(v[*i].cnp[j] == (int)(c%10) )
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
 //-----------------------------FUNCTIA DE SCRIERE IN FISIER-------------------------------//
void scriere(catalog * v, int n)
{
    FILE* g = fopen("FileIn.txt", "w");
    FILE* f = fopen("NrDate.txt", "w");
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
       fprintf(f,"%d",n);
       fclose(f);
    fclose(g);
}


void modificareVarsta(int i, int b, catalog *v,int n)
 {
    v[i].varsta=b;
    scriere(v,n);
 }

void modificareZi(int i, int b,catalog *v,int n)
 {
    v[i].varsta=b;
    scriere(v,n);
 }

void modificareLuna(int i, int b,catalog *v,int n)
 {
    v[i].varsta=b;
    scriere(v,n);
 }

void modificareAn(int i, int b,catalog *v,int n)
 {
    v[i].varsta=b;
    scriere(v,n);
 }

void modificareNume(int i, char *a,catalog *v,int n)
 {
     strcpy(v[i].nsp,a);
     scriere(v,n);
 }

void modificareGen(int i,catalog *v,int n)
 {
     char a[2];
    printf("Introduceti noua litera ce reprezinta sexul individului : ");
    scanf("%1s",a);
    *a=toupper(*a);
    if(strcmp(a,"M")==0 ||strcmp(a,"F")==0 )
        strcpy(v[i].gen,a);
    else {
        puts("VA ROG INTRODUCETI M SAU F!");
        modificareGen(i,v,n);
    }
    scriere(v,n);
 }

void stergere_copil( int i, int *n,catalog *v)
 {
     for (;i<*n;i++)
        v[i]=v[i+1];
   (*n)--;
   scriere(v,*n);
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
    scanf("%" PRIu64,&cnp1);
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
        fscanf(g, "%d %60s %1s %d %d %d %" PRIu64, &v[*i].varsta , v[*i].nsp , v[*i].gen , &v[*i].zi , &v[*i].luna , &v[*i].an, &cnp1);
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
            v[*i].mmate=0;
            obs = v[*i].nmate[0];
            for(j=1;j<=obs;j++)
            {
                v[*i].mmate=v[*i].mmate+v[*i].nmate[j];
            }
            if(obs>0)
             v[*i].mmate/=obs;
            fscanf(g,"%d", &v[*i].nfizica[0]);
            obs = v[*i].nfizica[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].nfizica[j]);
            }
            v[*i].mfizica=0;
            obs = v[*i].nfizica[0];
            for(j=1;j<=obs;j++)
            {
                v[*i].mfizica=v[*i].mfizica+v[*i].nfizica[j];
            }if(obs>0)
             v[*i].mfizica/=obs;
            fscanf(g,"%d", &v[*i].nchimie[0]);
            obs = v[*i].nchimie[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].nchimie[j]);
            }
            v[*i].mchimie=0;
            obs = v[*i].nchimie[0];
            for(j=1;j<=obs;j++)
            {
                v[*i].mchimie=v[*i].mchimie+v[*i].nchimie[j];
            }if(obs>0)
             v[*i].mchimie/=obs;
            fscanf(g,"%d", &v[*i].ninfo[0]);
            obs = v[*i].ninfo[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].ninfo[j]);
            }
            v[*i].minfo=0;
            obs = v[*i].ninfo[0];
            for(j=1;j<=obs;j++)
            {
                v[*i].minfo=v[*i].minfo+v[*i].ninfo[j];
            }if(obs>0)
             v[*i].minfo/=obs;
            fscanf(g,"%d", &v[*i].ntic[0]);
            obs = v[*i].ntic[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].ntic[j]);
            }v[*i].mtic=0;
            obs = v[*i].ntic[0];
            for(j=1;j<=obs;j++)
            {
                v[*i].mtic=v[*i].mtic+v[*i].ntic[j];
            }if(obs>0)
             v[*i].mtic/=obs;
            fscanf(g,"%d", &v[*i].nbio[0]);
            obs = v[*i].nbio[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].nbio[j]);
            }
            v[*i].mbio=0;
            obs = v[*i].nbio[0];
            for(j=1;j<=obs;j++)
            {
                v[*i].mbio=v[*i].mbio+v[*i].nbio[j];
            }if(obs>0)
             v[*i].mbio/=obs;
            fscanf(g,"%d", &v[*i].neng[0]);
            obs = v[*i].neng[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].neng[j]);
            }
            v[*i].meng=0;
            obs = v[*i].neng[0];
            for(j=1;j<=obs;j++)
            {
                v[*i].meng=v[*i].meng+v[*i].neng[j];
            }if(obs>0)
             v[*i].meng/=obs;
            fscanf(g,"%d", &v[*i].nfr[0]);
            obs = v[*i].nfr[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].nfr[j]);
            }
            v[*i].mfr=0;
            obs = v[*i].nfr[0];
            for(j=1;j<=obs;j++)
            {
                v[*i].mfr=v[*i].mfr+v[*i].nfr[j];
            }if(obs>0)
             v[*i].mfr/=obs;
            fscanf(g,"%d", &v[*i].nsport[0]);
            obs = v[*i].nsport[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].nsport[j]);
            }
            v[*i].msport=0;
            obs = v[*i].nsport[0];
            for(j=1;j<=obs;j++)
            {
                v[*i].msport=v[*i].msport+v[*i].nsport[j];
            }if(obs>0)
             v[*i].msport/=obs;
            fscanf(g,"%d", &v[*i].nromana[0]);
            obs = v[*i].nromana[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].nromana[j]);
            }
            v[*i].mromana=0;
            obs = v[*i].nromana[0];
            for(j=1;j<=obs;j++)
            {
                v[*i].mromana=v[*i].mromana+v[*i].nromana[j];
            }if(obs>0)
             v[*i].mromana/=obs;
            fscanf(g,"%d", &v[*i].nmuzica[0]);
            obs = v[*i].nmuzica[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].nmuzica[j]);
            }
            v[*i].mmuzica=0;
            obs = v[*i].nmuzica[0];
            for(j=1;j<=obs;j++)
            {
                v[*i].mmuzica=v[*i].mmuzica+v[*i].nmuzica[j];
            }if(obs>0)
             v[*i].mmuzica/=obs;
            fscanf(g,"%d", &v[*i].ndesen[0]);
            obs = v[*i].ndesen[0];
            j=1;
            for(; obs ; --obs, ++j)
            {
                fscanf(g,"%d", &v[*i].ndesen[j]);
            }
            v[*i].mdesen=0;
            obs = v[*i].ndesen[0];
            for(j=1;j<=obs;j++)
            {
                v[*i].mdesen=v[*i].mdesen+v[*i].ndesen[j];
            }if(obs>0)
            v[*i].mdesen/=obs;
    }

    fclose(g);
    fclose(f);
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
//-----------------------------FUNCTIA DE ADAUGARE NOTE-----------------------------//
void adaugare_mate(int n,catalog *v)
{
    int i=0;
    for(;i<n;i++)
    {
        int nota;
        v[i].nmate[0]++;
        nota=v[i].nmate[0];
        printf("Elevul actual este : %s\n", v[i].nsp);
        printf("Introduce-ti o singura nota: ");
        scanf("%d",&v[i].nmate[nota]);
        if(v[i].nmate[nota]==0)
            v[i].nmate[0]--;
    }
}
void adaugare_fizica(int n,catalog *v)
{
    int i=0;
    for(;i<n;i++)
    {
        int nota;
        v[i].nfizica[0]++;
        nota=v[i].nfizica[0];
        printf("Elevul actual este : %s\n", v[i].nsp);
        printf("Introduce-ti o singura nota: ");
        scanf("%d",&v[i].nfizica[nota]);
        if(v[i].nfizica[nota]==0)
            v[i].nfizica[0]--;
    }

}
void adaugare_biologie(int n,catalog *v)
{
    int i=0;
    for(;i<n;i++)
    {
        int nota;
        v[i].nbio[0]++;
        nota=v[i].nbio[0];
        printf("Elevul actual este : %s\n", v[i].nsp);
        printf("Introduce-ti o singura nota: ");
        scanf("%d",&v[i].nbio[nota]);
        if(v[i].nbio[nota]==0)
            v[i].nbio[0]--;
    }
}
void adaugare_tic(int n,catalog *v)
{
    int i=0;
    for(;i<n;i++)
    {
        int nota;
        v[i].ntic[0]++;
        nota=v[i].ntic[0];
        printf("Elevul actual este : %s\n", v[i].nsp);
        printf("Introduce-ti o singura nota: ");
        scanf("%d",&v[i].ntic[nota]);
        if(v[i].ntic[nota]==0)
            v[i].ntic[0]--;
    }
}
void adaugare_romana(int n,catalog *v)
{
    int i=0;
    for(;i<n;i++)
    {
        int nota;
        v[i].nromana[0]++;
        nota=v[i].nromana[0];
        printf("Elevul actual este : %s\n", v[i].nsp);
        printf("Introduce-ti o singura nota: ");
        scanf("%d",&v[i].nromana[nota]);
        if(v[i].nromana[nota]==0)
            v[i].nromana[0]--;
    }
}
void adaugare_chimie(int n,catalog *v)
{
    int i=0;
    for(;i<n;i++)
    {
        int nota;
        v[i].nchimie[0]++;
        nota=v[i].nchimie[0];
        printf("Elevul actual este : %s\n", v[i].nsp);
        printf("Introduce-ti o singura nota: ");
        scanf("%d",&v[i].nchimie[nota]);
        if(v[i].nchimie[nota]==0)
            v[i].nchimie[0]--;
    }
}
void adaugare_info(int n,catalog *v)
{
    int i=0;
    for(;i<n;i++)
    {
        int nota;
        v[i].ninfo[0]++;
        nota=v[i].ninfo[0];
        printf("Elevul actual este : %s\n", v[i].nsp);
        printf("Introduce-ti o singura nota: ");
        scanf("%d",&v[i].ninfo[nota]);
        if(v[i].ninfo[nota]==0)
            v[i].ninfo[0]--;
    }
}
void adaugare_desen(int n,catalog *v)
{
    int i=0;
    for(;i<n;i++)
    {
        int nota;
        v[i].ndesen[0]++;
        nota=v[i].ndesen[0];
        printf("Elevul actual este : %s\n", v[i].nsp);
        printf("Introduce-ti o singura nota: ");
        scanf("%d",&v[i].ndesen[nota]);
        if(v[i].ndesen[nota]==0)
            v[i].ndesen[0]--;
    }
}
void adaugare_muzica(int n,catalog *v)
{
    int i=0;
    for(;i<n;i++)
    {
        int nota;
        v[i].nmuzica[0]++;
        nota=v[i].nmuzica[0];
        printf("Elevul actual este : %s\n", v[i].nsp);
        printf("Introduce-ti o singura nota: ");
        scanf("%d",&v[i].nmuzica[nota]);
        if(v[i].nmuzica[nota]==0)
            v[i].nmuzica[0]--;
    }
}
void adaugare_sport(int n,catalog *v)
{
    int i=0;
    for(;i<n;i++)
    {
        int nota;
        v[i].nsport[0]++;
        nota=v[i].nsport[0];
        printf("Elevul actual este : %s\n", v[i].nsp);
        printf("Introduce-ti o singura nota: ");
        scanf("%d",&v[i].nsport[nota]);
        if(v[i].nsport[nota]==0)
            v[i].nsport[0]--;
    }
}
void adaugare_franceza(int n,catalog *v)
{
    int i=0;
    for(;i<n;i++)
    {
        int nota;
        v[i].nfr[0]++;
        nota=v[i].nfr[0];
        printf("Elevul actual este : %s\n", v[i].nsp);
        printf("Introduce-ti o singura nota: ");
        scanf("%d",&v[i].nfr[nota]);
        if(v[i].nfr[nota]==0)
            v[i].nfr[0]--;
    }
}
void adaugare_engleza(int n,catalog *v)
{
    int i=0;
    for(;i<n;i++)
    {
        int nota;
        v[i].neng[0]++;
        nota=v[i].neng[0];
        printf("Elevul actual este : %s\n", v[i].nsp);
        printf("Introduce-ti o singura nota: ");
        scanf("%d",&v[i].neng[nota]);
        if(v[i].neng[nota]==0)
            v[i].neng[0]--;
    }
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
            cls();
             while(1)
    {
        //-----------------------------AFISARE CATALOG-----------------------------//
        afisare_elev(n, v);
        x=0;
        printf("|Introduceti numele elevului pentru a schimba datele\n|Pentru a iesi introduceti x\n|Pentru a adauga un elev introduceti add\n|Pentru a adauga note introduceti numele materiei la care doriti sa adaugati note(mate,romana,biologie,engleza,fizica,chimie,informatica,tic,franceza,muzica,desen,sport)\n|!!Pentru adaugarea notelor introduceti 0 daca nu doriti sa adaugati o nota!!\n|Optiunea aleasa : ");
        scanf("%60s", nume_si_prenume);
        i=cautare_elev(nume_si_prenume,v,n);
        terminalClear();
    // VERIFICA DACA A FOST INTRODUSA OPTIUNEA DE IESIRE SAU ADAUGARE SAU O MATERIE
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
        else if(strcmp(nume_si_prenume,"mate")==0)
        {
            adaugare_mate(n,v);
            scriere(v,n);
            citire(v,&i);
            continue;
        }
            else if(strcmp(nume_si_prenume,"romana")==0)
            {
                adaugare_romana(n,v);
            scriere(v,n);
            citire(v,&i);
            continue;

            }
            else if(strcmp(nume_si_prenume,"fizica")==0)
            {
                adaugare_fizica(n,v);
            scriere(v,n);
            citire(v,&i);
            continue;
            }
            else if(strcmp(nume_si_prenume,"biologie")==0)
            {
                adaugare_biologie(n,v);
            scriere(v,n);
            citire(v,&i);
            continue;
            }
            else if(strcmp(nume_si_prenume,"engleza")==0)
            {
                adaugare_engleza(n,v);
            scriere(v,n);
            citire(v,&i);
            continue;
            }
            else if(strcmp(nume_si_prenume,"franceza")==0)
            {
                adaugare_franceza(n,v);
            scriere(v,n);
            citire(v,&i);
            continue;
            }
            else if(strcmp(nume_si_prenume,"chimie")==0)
            {
                adaugare_chimie(n,v);
            scriere(v,n);
            citire(v,&i);
            continue;
            }
            else if(strcmp(nume_si_prenume,"sport")==0)
            {
                adaugare_sport(n,v);
            scriere(v,n);
            citire(v,&i);
            continue;
            }
            else if(strcmp(nume_si_prenume,"tic")==0)
            {
                adaugare_tic(n,v);
            scriere(v,n);
            citire(v,&i);
            continue;
            }
            else if(strcmp(nume_si_prenume,"muzica")==0)
            {
                adaugare_muzica(n,v);
            scriere(v,n);
            citire(v,&i);
            continue;
            }
            else if(strcmp(nume_si_prenume,"desen")==0)
            {
                adaugare_desen(n,v);
            scriere(v,n);
            citire(v,&i);
            continue;
            }
            else if(strcmp(nume_si_prenume,"informatica")==0)
            {
                adaugare_info(n,v);
            scriere(v,n);
            citire(v,&i);
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
                            modificareVarsta(i,a,v,n);
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
                            modificareZi(i,a,v,n);
                            modificareLuna(i,b,v,n);
                            modificareAn(i,c,v,n);
                        }
                break;}
            //---------GEN---------//
            case(3):
                {
                    printf("Genul lui %s este %s . Pentru a modifica introduceti 1 : \n", v[i].nsp,v[i].gen);
                     scanf("%d", &x);
                    if(x==1)
                        {
                            modificareGen(i,v,n);
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
                            modificareNume(i,a,v,n);
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
