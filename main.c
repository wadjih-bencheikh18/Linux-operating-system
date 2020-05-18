#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
/*dans ce qui suit on a optté pour les listes lineaires chainnées pour
 faire notre solution , pour creer les utilisateurs , groupes, fichiers
 et repertoires , et meme pour ajouter un utilisateur a un groupe, --> on a creer
 une liste de pointeur vers groures pour chaque utilisateur et pour
 ajouter un utilisateur a un groupes il suffit juste d'ajouter le pointeur vers
 ce groupes dans la liste de l'utilisateur , et pour l'enlever il suffit de le
 spprimer de cette liste , concernat les droit d'acces , chaque a des droit de lecture
 ecriture et modification attribuer en binaire "111" , pour les fichier , des droit
 pour les groupes de l'uitilisateur et de others , c'est le meme concept de linux
 concernant la matrice on a met dan le premiere lingne les noms des utilisateurs
 et dans la premiere colonne les noms des fichier et a chaque fois on fait une
 mise a jour a la matrice ,a l'aide de la fonction realloc "tableau dynamique" , donc
 le tableau contient les droit attribuer de chaque fichier a chaque utilisateur et
 affiche erreur si il y a une incoherances dans les droits a la fin de l execution
 on affiche le nombres des maillons parcourus ,NOTA : la personne qui execute le programme
 va faire toute foncinalités possible a l'aide des commandes afficher dans le programme , et on
 a utilise la machine abstraite pour manipuler toutes foncionalités  */
 /* PS: les groupes contient tout les fichier  et donc pour permetrre a un utilisateur de l'acces a un fichier entant que groups
 il faut l'ajouter a ce groupe et il prendras les droit des groupes auquel il appartient*/



//----------------------------------------affichage------------------------------
typedef char *String;
COORD coord={0,0};
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void ClearScreen(void)
{
    system("cls");
}
//type user
typedef struct Users
{
    char UserName[50];
    char Password[50];
    struct Users *Suivant;
    struct GRP *Group;
}*USER;
// la machine abstraite de user

void AllouerUSER(USER *P)
{
    (*P)=(USER)malloc(sizeof(struct Users)); //allocation d'un espace memoire pour un maillon de type user
}
USER USERSuivant(USER H)
{
    return H->Suivant;
}
void aff_USERSuivant(USER H,USER val)
{
    H->Suivant=val;
}
char *USERName(USER H)
{
    return H->UserName;
}
void aff_USERName(USER H,char *val)
{
    strcpy(H->UserName,val);
}
char *USERPassword(USER H)
{
    return H->Password;
}
void aff_USERPassword(USER H,char *val)
{
    strcpy(H->Password,val);
}
struct GRP *USERGroups(USER H)
{
    return H->Group;
}
void aff_USERGroups(USER H,struct GRP *val)
{
    H->Group=val;
}
//structure GRP
struct GRP
{
    struct Groups *Group;
    struct GRP *Suivant; // pointeur vers le grp suivantdans la liste
};
// la machine abstraite de GRP
void AllouerGRP(struct GRP **P)
{
    (*P)=(struct GRP *)malloc(sizeof(struct GRP)); //allocation d'un espace memoire pour un maillon de type user
}
struct GRP *GRPSuivant(struct GRP *H)
{
    return H->Suivant;
}
void aff_GRPSuivant(struct GRP * H,struct GRP *val)
{
    H->Suivant=val;
}
struct Groups *GRPGroups(struct GRP *H)
{
    return H->Group;
}
void aff_GRPGroups(struct GRP *H,struct Groups *val)
{
    H->Group=val;
}


// type fichier
typedef struct fichier
{
    char Nom[20];
    USER OWNER; // l'utilisateur proprietaire du  fichier
    char DAOWNER[20]; //les droit affect¨¦ par le proprietaire
    struct fichier *Suivant; // pointeur vers le fichier suivant dans la liste des fichiers
}*FICHIER;
void AllouerFICHIER(FICHIER *P)
{
    (*P)=(FICHIER)malloc(sizeof(struct fichier)); //allocation d'un espace memoire pour un maillon de type user
}
char *FICHIERNom(FICHIER F)
{
    return F->Nom;
}
void aff_FICHIERNom(FICHIER F,char *val)
{
    strcpy(F->Nom,val);
}
USER FICHIEROWNER(FICHIER F)
{
    return F->OWNER;
}
void aff_FICHIEROWNER(FICHIER F,USER val)
{
    F->OWNER=val;
}
char *FICHIERDAOWNER(FICHIER F)
{
    return F->DAOWNER;
}
void aff_FICHIERDAOWNER(FICHIER F,char *val)
{
    strcpy(F->DAOWNER,val);
}
FICHIER FICHIERSuivant(FICHIER F)
{
    return F->Suivant;
}
void aff_FICHIERSuivant(FICHIER F,FICHIER val)
{
    F->Suivant=val;
}
// type repertoire
typedef struct repertoire
{
    char Nom[20];
    USER OWNER; //proprietaire du rep
    char DAOWNER[20]; // les droits du rep pour savoir si on a l acces a manipuler les fich de ce rep
    struct repertoire *Suivant; // pointeur vers next repertoir d=0
    struct fichier *Down; // pointeur vers les fichier d=1
}*REPERTOIRE;
// machine abstraite des repertoire
void AllouerREPERTOIRE(REPERTOIRE *P)
{
    (*P)=(REPERTOIRE)malloc(sizeof(struct repertoire)); //allocation d'un espace memoire pour un maillon de type user
}
char *REPERTOIRENom(REPERTOIRE F)
{
    return F->Nom;
}
void aff_REPERTOIRENom(REPERTOIRE F,char *val)
{
    strcpy(F->Nom,val);
}
USER REPERTOIREOWNER(REPERTOIRE F)
{
    return F->OWNER;
}
void aff_REPERTOIREOWNER(REPERTOIRE F,USER val)
{
    F->OWNER=val;
}
char *REPERTOIREDAOWNER(REPERTOIRE F)
{
    return F->DAOWNER;
}
void aff_REPERTOIREDAOWNER(REPERTOIRE F,char *val)
{
    strcpy(F->DAOWNER,val);
}
REPERTOIRE REPERTOIRESuivant(REPERTOIRE F)
{
    return F->Suivant;
}
void aff_REPERTOIRESuivant(REPERTOIRE F,REPERTOIRE val)
{
    F->Suivant=val;
}
FICHIER REPERTOIREDown(REPERTOIRE F)
{
    return F->Down;
}
void aff_REPERTOIREDown(REPERTOIRE F,FICHIER val)
{
    F->Down=val;
}
// type GROUPS
typedef struct Groups
{
    char GroupName[20]; // nom
    struct REP *RACINE; // ptr vers les repertoire
    struct Groups *Suivant;// ptr vers next
}*GROUPS;

void allouergroup(GROUPS *G)
{
    (*G) =(GROUPS)malloc(sizeof(struct Groups));
}

GROUPS GROUPSSuivant(GROUPS H)
{
    return H->Suivant;
}
void aff_GROUPSuivant(GROUPS H,GROUPS val)
{
    H->Suivant=val;
}
char *GROUPSName(GROUPS H)
{
    return H->GroupName;
}
void aff_GROUPSName(GROUPS H,char *val)
{
    strcpy(H->GroupName,val);
}

struct REP *GROUPSRacine(GROUPS H)
{
    return H->RACINE;
}
void aff_GROUPSRacine(GROUPS H,struct REP *val)
{
    H->RACINE=val;
}

// sturcture repertoir pour le group
struct REP
{
    REPERTOIRE Repertoire; // le repertoire
    struct REP *Suivant;// pointeur vers le repertoire suivant
    struct FICH *Down; // pointeur vers les fichiers
    char DA[20];// les droits d acces du repertoire
};
void AllouerREP(struct REP **P)
{
    (*P)=(struct REP *)malloc(sizeof(struct REP)); //allocation d'un espace memoire pour un maillon de type user
}
REPERTOIRE REPRepertoire(struct REP *F)
{
    return F->Repertoire;
}
void aff_REPRepertoire(struct REP *F,REPERTOIRE val)
{
    F->Repertoire=val;
}
char *REPDa(struct REP *F)
{
    return F->DA;
}
void aff_REPDa(struct REP *F,char *val)
{
    strcpy(F->DA,val);
}
struct REP *REPSuivant(struct REP *F)
{
    return F->Suivant;
}
void aff_REPSuivant(struct REP *F,struct REP *val)
{
    F->Suivant=val;
}
struct FICH *REPDown(struct REP *F)
{
    return F->Down;
}
void aff_REPDown(struct REP *F,struct FICH *val)
{
    F->Down=val;
}
// structure fichier pour le group
struct FICH
{
    FICHIER Fichier; // le fichier
    struct FICH *Suivant; // ptr vers fichier suivant dans la liste
    char DA[20];// les droit d acces
};
void AllouerFICH(struct FICH **P)
{
    (*P)=(struct FICH *)malloc(sizeof(struct FICH)); //allocation d'un espace memoire pour un maillon de type user
}
FICHIER FICHFichier(struct FICH *F)
{
    return F->Fichier;
}
void aff_FICHFichier(struct FICH *F,FICHIER val)
{
    F->Fichier=val;
}
char *FICHDa(struct FICH *F)
{
    return F->DA;
}
void aff_FICHDa(struct FICH *F,char *val)
{
    strcpy(F->DA,val);
}
struct FICH *FICHSuivant(struct FICH *F)
{
    return F->Suivant;
}
void aff_FICHSuivant(struct FICH * F,struct FICH *val)
{
    F->Suivant=val;
}

// creation d'un utilisateur
void CreateUser(USER *TeteUser,int *It)
{
    char A[50];
    USER P; //variable de type user
    AllouerUSER(&P);
    printf("Entrez le nom d'utilisateur :");
    scanf("%s",A);// remplissache du champ nom de la structure
    aff_USERName(P,A);
    printf("Entrez le mot de passe :");
    scanf("%s",A);//remplissage du champ mdp de la struct
    aff_USERPassword(P,A);
    aff_USERGroups(P,NULL);
    (*It)++;
    if ((*TeteUser)==NULL)// si la lste des utilisateur est vide
    {
        aff_USERSuivant(P,NULL); //pointeur tete vers l'utilisateur cr¨¦e
        *TeteUser=P;
    }
    else // si la liste n'est pas vide
    {
        aff_USERSuivant(P,USERSuivant(*TeteUser)); //liaison du nouveau utilisateur au precedent
        aff_USERSuivant(*TeteUser,P);
    }
}

// creation d'un nvx grp
void CreateGroup(GROUPS *tetegroup,REPERTOIRE RACINE,int *It)
{
    char i[20];
    FICHIER F;
    REPERTOIRE R=RACINE;
    char m[50];
    struct REP *H,*A=NULL;
    struct FICH *P,*B;
    GROUPS G;
    allouergroup(&G); // allouer un espace memoire de type GROUPS
    (*It)++;
    printf("entrer le nom du group:");
    scanf("%s",m);
    aff_GROUPSName(G,m);
    printf("entrer le droit par defaut :");
    scanf("%s",i);
    if (*tetegroup==NULL) // dans le cas ou il n'existe aucun group precedant
    {
        *tetegroup=G; // ce groupe sera la tete de la liste des groups
        aff_GROUPSuivant(G,NULL);
    }
    else // si non
    {
        aff_GROUPSuivant(G,GROUPSSuivant(*tetegroup)); // chainage des deux groupes
        aff_GROUPSuivant(*tetegroup,G);
    }
    while (R!=NULL) //remplissage du groupes crer avec tout les fichier existant dans le programme
    {
        AllouerREP(&H); // on commence a creer la liste des ptr vers les rep et fichier
        (*It)++;
        if (A==NULL) aff_GROUPSRacine(G,H); // si latete des ptr et nil on affecte une tete
        else aff_REPSuivant(A,H); // si non on les chaine
        A=H;
        aff_REPRepertoire(H,R);
        aff_REPDa(H,i);
        if(REPERTOIRESuivant(R)==NULL) aff_REPSuivant(H,NULL);
        if(REPERTOIREDown(R)==NULL) aff_REPDown(H,NULL);
        B=NULL;
        F=REPERTOIREDown(R); // les fichier sont sous les repertoires
        while (F!=0)
        {
            AllouerFICH(&P); // on fait presque la meme chose pour chainées le fichier de chaque repertoire
            if (B==NULL) aff_REPDown(H,P);
            else aff_FICHSuivant(B,P);
            B=P;
            aff_FICHFichier(P,F);
            aff_FICHDa(P,i);
            if(FICHIERSuivant(F)==NULL) aff_FICHSuivant(P,NULL);
            F=FICHIERSuivant(F);
            (*It)++;
        }
        R=REPERTOIRESuivant(R);
    }
}


//creation d'un fichier
void CreateFICHIER(REPERTOIRE P,GROUPS TeteGROUP,USER OWNER,int *It)
{
    char A[50];
    char i[50];
    struct REP *M; // ptr vers le reperoire pere
    FICHIER H; //var de type fichier
    GROUPS F;
    struct GRP *T;
    AllouerFICHIER(&H);// remplissage des informations du fchier
    (*It)++;
    aff_FICHIERSuivant(H,REPERTOIREDown(P));
    aff_REPERTOIREDown(P,H);
    aff_FICHIEROWNER(H,OWNER);
    printf("\nEntrer le nom du Fichier:");
    scanf(" %s",A);
    aff_FICHIERNom(H,A);
    printf("\nEntez le droit pour le user :");// affectation des droits personnalis¨¦
    scanf("%s",i);
    aff_FICHIERDAOWNER(H,i);
    F=TeteGROUP;
    if (F!=NULL)
    {
        while (F!=NULL) // initialisation des droits pour tt les grp a -1
        {
            (*It)++;
            for(M=GROUPSRacine(F);REPRepertoire(M)!=P;M=REPSuivant(M),(*It)++);
            struct FICH *P;
            AllouerFICH(&P); // maillon de type fich
            aff_FICHSuivant(P,REPDown(M));//update d chemin
            aff_REPDown(M,P);// update du chemin
            aff_FICHFichier(P,H); //affecation du fichier
            aff_FICHDa(P,"R"); //update des droit
            F=GROUPSSuivant(F);
        }
        printf("Entez le droit pour le group :");//affectation des droits au grp auquel le owner appartient
        scanf("%s",i); //le i represente les droit en numerique "101" r=1-> il a le droit de lecture,w=0-> il n'a pas le droit de l'ecriture
        T=USERGroups(OWNER);
        while (T!=NULL)
        {
            (*It)++;
            for(M=GROUPSRacine(GRPGroups(T));REPRepertoire(M)!=P;M=REPSuivant(M),(*It)++);
            aff_FICHDa(REPDown(M),i);
            T=GRPSuivant(T);
        }
        printf("Entez le droit pour les autres :");// affectation des droits pour les autres utilisateur dans le reste des groupes
        scanf("%s",i);
        F=TeteGROUP;
        while (F!=NULL)
        {
            (*It)++;
            for(M=GROUPSRacine(F);REPRepertoire(M)!=P;M=REPSuivant(M),(*It)++);
            if (strcmp(FICHDa(REPDown(M)),"R")==0)
            {
                aff_FICHDa(REPDown(M),i);
            }
            F=GROUPSSuivant(F);
        }
    }
}



// creation d'un nvx repertoire
void CreateREPERTOIRE(REPERTOIRE *RACINE,GROUPS TeteGROUP,USER OWNER,int *It)
{
    char A[50],i[50]; /*il reste a faire le chainage des reperoires et les droits ....*/
    int vide=0;
    REPERTOIRE H;
    GROUPS F;
    struct GRP *T;
    AllouerREPERTOIRE(&H);
    (*It)++;
    printf("\nentrer le nom du repertoire:");
    scanf("%s",A);
    aff_REPERTOIRENom(H,A);
    if(*RACINE!=NULL) // dans le cas ou la racine exist
    {
        (*It)++;
        aff_REPERTOIRESuivant(H,REPERTOIRESuivant(*RACINE));
        aff_REPERTOIRESuivant(*RACINE,H);
        aff_REPERTOIREDown(H,NULL);
    }
    else
    {
        (*RACINE)=H; // si nn metre ce repertoire comme racine
        aff_REPERTOIRESuivant(H,NULL);
        aff_REPERTOIREDown(H,NULL);
        vide=1; // pour savoir si la fonction est faite
    }
    aff_REPERTOIREOWNER(H,OWNER);// affectation des droits
    printf("Entez le droit pour le user :");
    scanf("%s",i);
    aff_REPERTOIREDAOWNER(H,i);
    F=TeteGROUP;
    if(F!=NULL)
    {
        while (F!=NULL)
        {
            (*It)++;
            if (vide!=1)
            {
                struct REP *P;
                AllouerREP(&P); // a chaque creation d'un nvx reoertoire on le rajoute
                aff_REPSuivant(P,REPSuivant(GROUPSRacine(F))); //  a la liste de tout les groups existant
                aff_REPSuivant(GROUPSRacine(F),P); // et on fait le chainage normal
                aff_REPRepertoire(P,H);
                aff_REPDown(P,NULL);
                aff_REPDa(P,"R");
            }// on affecte la mise a jour pour tout les group
            else
            {
                AllouerREP(&(F->RACINE));
                aff_REPRepertoire(F->RACINE,H); // update d'un groups vide
                aff_REPSuivant(F->RACINE,NULL);
                aff_REPDown(F->RACINE,NULL);
                aff_REPDa(F->RACINE,"R");;
            }
            F=GROUPSSuivant(F);
        }
        printf("Entez le droit pour le group :");
        scanf("%s",i); // et on les affecte des droite "groupe"
        T=USERGroups(OWNER);
        while (T!=NULL)
        {
            if (vide!=1) aff_REPDa(REPSuivant(GROUPSRacine(GRPGroups(T))),i);
            else
            {
                aff_REPDa(GROUPSRacine(GRPGroups(T)),i);;
            }
            (*It)++;
            T=GRPSuivant(T);
        }
        printf("Entez le droit pour les autres :");
        scanf("%s",i);
        F=TeteGROUP;
        while (F!=NULL) //affectation des droits pour les autre
        {
            if(vide!=1)
            {
                if (strcmp(REPDa(REPSuivant(GROUPSRacine(F))),"R")==0)
                {
                    aff_REPDa(REPSuivant(GROUPSRacine(F)),i);
                }
            }
            else
            {
                if (strcmp(REPDa(GROUPSRacine(F)),"R")==0)
                    {
                        aff_REPDa(GROUPSRacine(F),i);
                    }
            }
            (*It)++;
            F=GROUPSSuivant(F);
        }
    }
}
// lors de l'ajout d'un utilisateur a un groupe
void AddUSERdeGROUP(USER U,GROUPS G,int *It)
{
    struct GRP *Gr;
    AllouerGRP(&Gr);
    (*It)++;
    aff_GRPGroups(Gr,G);
    if(USERGroups(U)!=NULL)
    {
    aff_GRPSuivant(Gr,GRPSuivant(USERGroups(U)));//ajouter le groupe a la liste de cette utilisateur
    aff_GRPSuivant(USERGroups(U),Gr);
    }
    else
    {
        aff_USERGroups(U,Gr);
        aff_GRPSuivant(USERGroups(U),NULL);
    }
}
// lors de la suppression d'un utilisateur d'un groupe
void DeleteUSERdeGROUP(USER U,GROUPS G,int *It)  //suprimer G de user U
{
    int j=0;
    struct GRP *R,*H=USERGroups(U);
    if (H!=NULL)
    {
        while ((H!=NULL)&&(GRPGroups(H)!=G)&&(j==0)) // refaire le chainage de la liiste en exculant ce groupe
        {
            if (GRPGroups(GRPSuivant(H))==G)
            {
                R=GRPSuivant(H);
                aff_GRPSuivant(H,GRPSuivant(GRPSuivant(H)));
                free(R); // et on recupere l'espace memoire allouer
                j=1;
            }
            (*It)++;
            H=GRPSuivant(H);
        }
        if ((j==0)&&(GRPGroups(H)==G)) //le cas de premier maillon
        {
            aff_USERGroups(U,GRPSuivant(H));
            free(H);
            j=1;
        }
    }
}
// lors de la suppression d'un groupe
void DeleteGROUPdeListe(GROUPS P,GROUPS G,int *i,GROUPS *TeteGROUP,int *It)
{
    while ((P!=NULL)&&(P!=G)&&(*i==0))
        {
            if (GROUPSSuivant(P)==G)
            {

                aff_GROUPSuivant(P,GROUPSSuivant(G));
                *i=1;
                free(G);
            }
            (*It)++;
            P=GROUPSSuivant(P);
        }
        if ((*i==0) && (P==G)) //le cas ou le premier maillon c'est G
            {
               *TeteGROUP=GROUPSSuivant(*TeteGROUP);
               free(G);
               *i=1; //c'est le moyenne de connaitre esq il existe G ou non
            }
}
int DeleteGROUP(GROUPS *TeteGROUP,GROUPS G,USER TeteUSER,int *It)
{
    int i=0;
        //suppr le group de liste principale
    DeleteGROUPdeListe(*TeteGROUP,G,&i,TeteGROUP,It);
    if (i==1)
    {
        while (TeteUSER!=NULL) //delete le group dans la liste des USERS
        {
            DeleteUSERdeGROUP(TeteUSER,G,It);
            TeteUSER=USERSuivant(TeteUSER);
            (*It)++;
        }
    }
        return i;// 1 si le groupe existe sinon return 0
}
// machine absraite
void AffUSER(USER TeteUSER,int *It)
{
    struct GRP *G;
    printf("La liste des utilisateurs avec leur group :\n");
    while(TeteUSER!=NULL)
    {
        printf("%s\n",USERName(TeteUSER));
        G=USERGroups(TeteUSER);
        while(G!=NULL)
        {
            printf("\t%s\n",GROUPSName(GRPGroups(G)));
            G=GRPSuivant(G);
            (*It)++;
        }
        TeteUSER=USERSuivant(TeteUSER);
        (*It)++;
    }
}
void AffGROUP(GROUPS TeteGROUP,int *It)
{
    printf("Les groups :\n");
    while(TeteGROUP!=NULL)
    {
        printf("%s\n",GROUPSName(TeteGROUP));
        TeteGROUP=GROUPSSuivant(TeteGROUP);
        (*It)++;
    }
}
void AffARBER(REPERTOIRE RACINE,int *It)
{
    FICHIER F;
    printf("L'arborescente :\n");
    while(RACINE!=NULL)
    {
        printf("%s\n",REPERTOIRENom(RACINE));
        (*It)++;
        F=REPERTOIREDown(RACINE);
        while(F!=NULL)
        {
            printf("\t%s\n",FICHIERNom(F));
            F=FICHIERSuivant(F);
            (*It)++;
        }
        RACINE=REPERTOIRESuivant(RACINE);
    }
}
// fonction de recherche d'un utilisateur
int ChercheUSER(USER TeteUSER,USER *CurrentUSER,int *It)
{
    char Name[50];
    int i=0;
    printf("\nEntrez le nom d'utilisateur :");
    scanf(" %s",Name);
    while ((TeteUSER!=NULL) && (i==0))
    {
        if(strcmp(USERName(TeteUSER),Name)==0) // comparaison du nom de l user dans la liste des user
        {
            *CurrentUSER=TeteUSER; // recuperation de son adr a traver un ptr
            i=1;
        }
        TeteUSER=USERSuivant(TeteUSER);
        (*It)++;
    }
    if (i==0) printf("\nL'utilisateur \"%s\" est introuvable\n",Name);
    return i;
}
// recherche d'un groupe si il exist
int ChercheGROUP(GROUPS TeteGROUP,GROUPS *G,int *It)
{
    char Name[50];
    int i=0;
    printf("\nEntrez le nom du group :");
    scanf(" %s",Name);
    while(TeteGROUP!=NULL)
    {
        if(strcmp(GROUPSName(TeteGROUP),Name)==0)
        {
            *G=TeteGROUP;
            i=1;
        }
        TeteGROUP=GROUPSSuivant(TeteGROUP);
        (*It)++;
    }
    if (i==0) printf("\nLe group \"%s\" est introuvable\n",Name);
    return i;
}
// recherche d'un repertoire
int ChercheREPERTOIRE(REPERTOIRE RACINE,REPERTOIRE *R,int *It)
{
    char Name[50];
    int i=0;
    printf("\nEntrez le nom du repertoire :");
    scanf(" %s",Name);
    while(RACINE!=NULL)
    {
        if(strcmp(REPERTOIRENom(RACINE),Name)==0)
        {
            *R=RACINE;
            i=1;
        }
        RACINE=REPERTOIRESuivant(RACINE);
        (*It)++;
    }
    if (i==0) printf("\nLe repertoire \"%s\" est introuvable\n",Name);
    return i;
}
// dans le cas de la suppression d'un utilisateur
void permute(String ***tab,int t,int *l)
{
    (*tab)[t]=(*tab)[*l-1];
    (*l)=(*l)-1;
    *tab = (String **)realloc(*tab,(*l) * sizeof(String *));
}

// le update de la matrice de delete user
void DeleteUSER(USER tete,String ***Matrice,int *NbUSER,int *It)
{
    char supp[50];
    USER H;
    int i=0;
    printf("\nEntrez le nom d'utilisateur :");
    scanf(" %s",supp);
    for (i=1;i<*NbUSER;i++)
    {
        if (strcmp((*Matrice)[i][0],supp)==0) // si le nom de l utilisateur supprimer et trouver  dans la matrice
        {
            permute(Matrice,i,NbUSER); // remplacement de la ligne de l utilisateur supprimé avec la dernier ligne de la matrice
            i=*NbUSER;
        }
    } /*on avait besoin de faire ce replacement car realloc supprime la dernier ligne automatiquement*/
    i=0;
    while ((tete!=NULL)&&(strcmp(USERName(tete),supp)!=0)&&(i==0))
        {
            if (USERSuivant(tete)!=NULL)
            {
              if (strcmp(USERName(USERSuivant(tete)),supp)==0)
                {
                    H = USERSuivant(tete);
                    aff_USERSuivant(tete,USERSuivant(USERSuivant(tete)));
                    free(H);
                    i=1;
                }
            }
            tete=USERSuivant(tete);
            (*It)++;
        }
        if (i==0 && tete==NULL)// dans le cas ou l utilisateur n'existe pas
        {
            printf("erreur l'utilisateur \"%s\" non trouver",supp);
        }
        else if (i==0) // si on a lui demander de supprimer l'admin
        {
            printf("erreur : impossible de supprimer l'admin");
        }
}
// affichage du groupe
void afffichgrp(GROUPS G,int *It)
{
    struct REP *R=GROUPSRacine(G);
    struct FICH *F;
    while(R!=NULL)
    {
        printf("\n%s : %s",REPERTOIRENom(REPRepertoire(R)),REPDa(R));
        F=REPDown(R);
        while (F!=NULL)
        {
            printf("\n%s : %s",FICHIERNom(FICHFichier(F)),FICHDa(F));
            F=FICHSuivant(F);
            (*It)++;
        }
        R=REPSuivant(R);
        (*It)++;
    }
}
void InsertDroit(GROUPS G,int *It)
{
    char i[20];
    struct REP *R=GROUPSRacine(G);
    struct FICH *F;
    printf("Entrer le droit par defaut au group :");
    scanf("%s",i);
    while(R!=NULL)
    {
        aff_REPDa(R,i);
        F=REPDown(R);
        while (F!=NULL)
        {
            aff_FICHDa(F,i);
            F=FICHSuivant(F);
            (*It)++;
        }
        R=REPSuivant(R);
        (*It)++;
    }

}
// changemet de l'utilisateur courant
void ChangeUSER(USER TeteUSER,USER *CurrentUSER,int *It)
{
    USER U;
    char passwd[20];
    if (ChercheUSER(TeteUSER,&U,It)==1)
    {
        if (*CurrentUSER!=TeteUSER)
        {
            printf("\nEntrez le mot de passe :");
            scanf(" %s",passwd);
            if (strcmp(USERPassword(U),passwd)==0)
            {
                *CurrentUSER=U;
            }
            else printf("\nerreur de mot de passe");
        }
        else *CurrentUSER=U;
    }
}
//-----------------------la matrice-----------------------------------------------------
//dans le cas de la creation d'un utilisateur
void addligne(String ***A,int c,int *l)
{
    int j;
    (*A)= (String **)realloc((*A), sizeof(String *)*((*l)+1));
    *((*A)+*l) = (String *)malloc(sizeof(String)*c);
    for (j=0;j<c;j++)
    {
        (*A)[*l][j]=(char *)malloc(50*sizeof(char));
    }
    (*l)++;
}
// dans le cas de la creation d'un nvx fichier
void addcolon(String **A,int *c,int l)
{
    int i,j;
    for (i=0 ; i<l ;i++)
    {
        A[i] = (String *)realloc(*(A+i),sizeof(String)*((*c)+1));
    }
    for (j=0;j<l;j++)
    {
        A[j][*c]=(char *)malloc(50*sizeof(char));
    }
    (*c)++;
}
// affichage de la matrice
void EcrireMatrice(String **A,int c,int l)
{
	int i,j;
    for(i=0; i<l; ++i){
		for(j=0; j<c; ++j){
			printf("%s\t|", A[i][j]);
		}
		printf("\n");
	}

}
// creatin de la matrice initiale
void CreateMatrice(String ***A,int l,int c)
{
    int i,j;
    *A = (String **)malloc(sizeof(String *)*l);

	for(i=0; i<c; ++i){
		*(*A+i) = (String *)malloc(sizeof(String)*c);
	}
	for (i=0;i<l;i++)
	{
            for (j=0;j<c;j++)
            {
                (*A)[i][j]=(char *)malloc(50*sizeof(char));
            }
	}
}
// remplissage de la matrisse dans le cas de creation d'un nvx fichier
void UpdateMatriceF(String **Matrice,int NbUSER,int NbREP,REPERTOIRE R,FICHIER F,USER TeteUSER,int *It)
{
    USER U;
    char N[20];
    int i,E;
    struct GRP *H;
    struct FICH *M;
    struct REP *T;
    for (i=1;i<NbUSER;i++)// on doit parcourir tout les utilisateur dans tout les groups et comparer les droit pour enfin les maitre dans la case correspandante
    {
        for (U=TeteUSER;((U!=NULL)&& strcmp(USERName(U),Matrice[i][0])!=0);U=USERSuivant(U));
        E=0;
        strcpy(N,"R");
        H=U->Group;
        if (F->OWNER==U)
        {
            Matrice[i][NbREP]=FICHIERDAOWNER(F);
        }
        else if(H!=NULL)
        {
            while (H!=NULL)
            {
                for (T=H->Group->RACINE;T->Repertoire!=R;T=T->Suivant);
                M=T->Down;
                if (strcmp(N,"R")!=0&&strcmp(N,M->DA)!=0)
                {
                    Matrice[i][NbREP]="erreur";// si les droit son different on declare une erreur
                    H=NULL;
                    E=1;
                }
                strcpy(N,M->DA);
                if (H!=NULL)
                {
                    H=H->Suivant;
                    (*It)++;
                }
            }
            if (E!=1)
            {
                strcpy(Matrice[i][NbREP],N);
            }
        }
        else Matrice[i][NbREP]="     ";
    }
}
// remplissage de la matrice dans le cas de la creation d'un utilisateur
void UpdateMatriceAU(String **Matrice,USER U,int nbUSER,int nbFICH,REPERTOIRE RACINE,int *It)
 {
     int i,s,n=0;
     struct GRP* G=USERGroups(U);
     struct REP* R;
     struct FICH* F;
     FICHIER H;
     char A[50];
     for (i=1;i<nbUSER;i++)
     {
         if (strcmp(USERName(U),Matrice[i][0])==0)
         {
             s=i;
             i=nbUSER;//on sauvgarde la ligne de l utilisateur dans la matrice
         }
     } // on parcoure tout les groupes de cette utilisateur
     if (USERGroups(U)==NULL) //si l utilisateur n apartient a aucun groupe
     {
         for (i=1;i<nbFICH;i++)
         {
             while((RACINE!=NULL)&&(n==0))
             {
                 H=REPERTOIREDown(RACINE);
                 while((H!=NULL)&&(n==0))
                 {
                     if(strcmp(FICHIERNom(H),Matrice[0][i])==0)
                        {
                            n=1;
                        }
                    if (n!=1)
                    {
                        H=FICHIERSuivant(H);
                        (*It)++;
                    }
                 }
                 if (n!=1)
                {
                    RACINE=REPERTOIRESuivant(RACINE);
                    (*It)++;
                }
             }
             if (FICHIEROWNER(H)!=U) Matrice[s][i]="   ";
         }
     }
     else
     {
         while (G!=NULL)
         {
             R=GROUPSRacine(GRPGroups(G));
             while (R!=NULL)
             {
                 F=REPDown(R);// on parcour tout les fichier et on compare le nom de chaque fichier avec ls nom des fichier dans la matrice
                 while(F!=NULL)
                 {
                     for (i=1; i<nbFICH ; i++)
                     {
                         if (strcmp(FICHIERNom(FICHFichier(F)),Matrice[0][i])==0) // trouver la case correspande au fichier dans le groupe
                         {
                             Matrice[s][i]="     ";
                             strcpy(A,FICHDa(F));
                             if (FICHIEROWNER(FICHFichier(F))==U)
                             {
                                 Matrice[s][i]=FICHIERDAOWNER(FICHFichier(F));// affectation des droit
                             }
                            else if(n==0)
                            {
                                 Matrice[s][i]=FICHDa(F);// affectation des droits
                            }
                            else if (strcmp(A,Matrice[s][i])!=0)
                            {
                                Matrice[s][i]="erreur";// si les droit sont incoherant
                            }
                            else
                            {
                                Matrice[s][i]=FICHDa(F); // affectation des droits
                            }
                            i=nbFICH;
                         }
                     }
                     F =FICHSuivant(F);
                     (*It)++;
                 }
                 R= REPSuivant(R);
                 (*It)++;
         }
        n=1;
        G=GRPSuivant(G);
        (*It)++;
        }
    }
 }
 // update de la matrice dans le cas d'ajout d'un utilisateur a un groupe ou de suppression
void UpdateMatriceG(String **Matrice,GROUPS G,int nbUSER,int nbREP,USER TeteUSER,REPERTOIRE RACINE,int *It)
{
    struct GRP *F;
    while (TeteUSER!=NULL)
    {
        F=USERGroups(TeteUSER);
        while(F!=NULL)
        {
            if (GRPGroups(F)==G)
            {
                UpdateMatriceAU(Matrice,TeteUSER,nbUSER,nbREP,RACINE,It);// on utilise la fonction precedante car on doit comparait tout les droit de tout les groupe restant de nouveaux
                F=NULL;
            }
            if (F!=NULL)
            {
                F=GRPSuivant(F);
                (*It)++;
            }
        }
        TeteUSER=USERSuivant(TeteUSER);
        (*It)++;
    }
}
int main()
{
    int i=1,j=1,N,E,It=0;
    int cmd=100,NbUSER=1,NbREP=1;
    String **Matrice;
    CreateMatrice(&Matrice,1,1);// creation de la matrice
    Matrice[0][0]="\\\\";
    REPERTOIRE RACINE=NULL,CurrentREPERTOIRE=NULL; //initialisation de tete de repertoire
    USER TeteUSER=NULL,CurrentUSER=NULL,U; //initialisation de tete des user
    GROUPS TeteGROUP=NULL,G; // initialisation de tete des groups
    printf("La creation du premier utilisateur\n\n");
    CreateUser(&TeteUSER,&It);// creation de l'admin PS : il nepeut pas etre supprimer
    addligne(&Matrice,NbREP,&NbUSER); /*update de la matrice*/
    Matrice[NbUSER-1][0]=USERName(TeteUSER);
    CurrentUSER=TeteUSER;
    printf("\nLa creation de la RACINE\n\n");
    CreateREPERTOIRE(&RACINE,TeteGROUP,CurrentUSER,&It);//creation du root
    CurrentREPERTOIRE=RACINE; /* l'admin et le root sont obligatoire pour pouvoir faire toute autre
	foncionalitées*/
    ClearScreen();
    printf("Entez \"404\" pour plus d'information ou \"0\" pour quiter.\n\n");
    printf("NOTE: \nLES DROIT D'ACCES SONT EN BINAIRE \n\n");
    printf("r(Read) \t|autorisation de lire le contenu du fichier\t|\n");
    printf("w(Write) \t|autorisation de modifier le contenu du fichier\t|\n");
    printf("x(eXecute) \t|autorisation d'exécuter le fichier          \t|\n\n");
    printf("Symbolique \t|En binaire\t|\n");
    printf("---        \t|000       \t|\n");/*affichage d'explication sur la maniere d'affectation des droits */
    printf("--x        \t|001       \t|\n");
    printf("-w-        \t|010       \t|\n");
    printf("-wx        \t|011       \t|\n");
    printf("r--        \t|100       \t|\n");
    printf("r-x        \t|101       \t|\n");
    printf("rw-        \t|110       \t|\n");
    printf("rwx        \t|111       \t|\n");

    while(cmd!=0)
    {
        printf("\n%s : %s $  ",USERName(CurrentUSER),REPERTOIRENom(CurrentREPERTOIRE));
        scanf(" %d",&cmd);
        switch (cmd)
        {
            case 404:
                printf("\n99-voir le nombre des maillon parcouru.\n");
                printf("1-Creer un nouveau repertoire.\n");
                printf("2-Creer un nouveau fichier.\n");
                printf("3-Afficher l'arborescente.\n");
                printf("4-Affichier la liste des utilisateur.\n");
                printf("5-Affichier la liste des groups.\n");
                printf("6-Changer l'utilisateur.\n");
                printf("7-Changer le repertoire courrant.\n");
                printf("8-la recherche d'un utilisateur.\n");
                printf("9-Ajouter un utilisateur a un group.\n");
                printf("10-Supprimer un utilisateur d'un group.\n");
                printf("11-afficher le droit de group.\n");
                printf("12-afficher la matrice.\n");
                if(CurrentUSER==TeteUSER)
                {
                    printf("13-Creer un nouveau utilisateur.\n");
                    printf("14-Creer un nouveau group.\n");
                    printf("15-Suprimer un utilisateur.\n");
                    printf("16-Suprimer un group.\n");
                    printf("17-Insertion de droit au group.\n\n");
                }
            break;
            case 99:
                printf("\nLe nombre des mailloin parcouru est :%d",It);
                break;
            case 0:
                ClearScreen();
                printf("good bye ...");
                printf("\nLe nombre des mailloin parcouru est :%d",It);
                break;
            case 1:
                CreateREPERTOIRE(&RACINE,TeteGROUP,CurrentUSER,&It); // creation d'un nvx rep
                break;
            case 2:
                CreateFICHIER(CurrentREPERTOIRE,TeteGROUP,CurrentUSER,&It);// creation d'un fichier
                addcolon(Matrice,&NbREP,NbUSER);// update de la taille de la matrice
                Matrice[0][NbREP-1]=FICHIERNom(REPERTOIREDown(CurrentREPERTOIRE));// remplissage du champ nom
                UpdateMatriceF(Matrice,NbUSER,NbREP-1,CurrentREPERTOIRE,REPERTOIREDown(CurrentREPERTOIRE),TeteUSER,&It);
                break;// remplissage de la colonnes avec les droits
            case 3:
                AffARBER(RACINE,&It);//affichage de l'arboraissante
                break;
            case 4:
                AffUSER(TeteUSER,&It); // affichage des listes des users
                break;
            case 5:
                AffGROUP(TeteGROUP,&It);// affichage de la liste des groupes
                break;
            case 6:
                ChangeUSER(TeteUSER,&CurrentUSER,&It);// changement de utilisateur courant
                break;
            case 7:
                ChercheREPERTOIRE(RACINE,&CurrentREPERTOIRE,&It);
                break;
            case 8:
                if (ChercheUSER(TeteUSER,&U,&It)==1) printf("l'utilisateur \"%s\" exsite UID=%d",USERName(U),U);
                break;
            case 9:
                if(ChercheUSER(TeteUSER,&U,&It)==1 && ChercheGROUP(TeteGROUP,&G,&It)==1)//dans le cas ou le groupes existe et le user existe
                {
                    AddUSERdeGROUP(U,G,&It);//on ajoute le user a le groupe
                    UpdateMatriceAU(Matrice,U,NbUSER,NbREP,RACINE,&It);// on fait la mise a jour des droits dans la matrice
                }
                break;
            case 10:
                if(ChercheUSER(TeteUSER,&U,&It)==1 && ChercheGROUP(TeteGROUP,&G,&It)==1)//ssi le user et le groupe existe
                {
                    DeleteUSERdeGROUP(U,G,&It);//suppression de l utilisateur du group
                    UpdateMatriceAU(Matrice,U,NbUSER,NbREP,RACINE,&It);//mise a jour des droits
                }
                break;
            case 11:
                if(ChercheGROUP(TeteGROUP,&G,&It)==1) afffichgrp(G,&It);// recherche d'un groupe
                break;
            case 12:
                EcrireMatrice(Matrice,NbREP,NbUSER);//affichage de la matrice
                break;
            default:
                if (CurrentUSER==TeteUSER) // des foncionalitées de l admine
                {
                    switch (cmd)
                    {
                        case 13:
                            CreateUser(&TeteUSER,&It);// creation de l utilisateur
                            addligne(&Matrice,NbREP,&NbUSER);// mise a jour de la taille de la matrice
                            Matrice[NbUSER-1][0]=USERName(USERSuivant(TeteUSER));// remplisage du champs nom
                            for (i=1;i<NbREP;i++) Matrice[NbUSER-1][i]="    ";
                            break;
                        case 14:
                            CreateGroup(&TeteGROUP,RACINE,&It);// creation d'un groupes
                            break;
                        case 15:
                            DeleteUSER(TeteUSER,&Matrice,&NbUSER,&It);// suppression
                            break;
                        case 16:
                            if(ChercheGROUP(TeteGROUP,&G,&It)==1)
							{
								DeleteGROUP(&TeteGROUP,G,TeteUSER,&It);
								for (U=TeteUSER;U!=NULL;U=USERSuivant(U)) UpdateMatriceAU(Matrice,U,NbUSER,NbREP,RACINE,&It);
							}//suppression d'un groupes si i existe
                            break;
                        case 17:
                            if(ChercheGROUP(TeteGROUP,&G,&It)==1) //remettre les droit pour le groupe
                            {
                                InsertDroit(G,&It);
                                UpdateMatriceG(Matrice,G,NbUSER,NbREP,TeteUSER,RACINE,&It);//update des droit de la matrice
                            }
                            break;
                        default:printf("Commande introuvable");
                    }
                }
                else printf("Commande introuvable");
        }
    }
}
