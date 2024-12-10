#define MAX_STACK_SIZE 5
#define MAX_CITOYEN 1000
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 1000
#define MAX_LINE_LENGTH 256
char* trouverNomGouv(int numero) {
    FILE *fichier = fopen("txt", "r");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return NULL;
    }
    char ligne[MAX_LINE_LENGTH];
    int numeroCourant;
    char nomGouv[MAX_LINE_LENGTH];
    while (fgets(ligne, MAX_LINE_LENGTH, fichier) != NULL) {
        if (sscanf(ligne, "%d %[^\n]", &numeroCourant, nomGouv) == 2) {
            if (numeroCourant == numero) {
                fclose(fichier);
                char* resultat = malloc(strlen(nomGouv) + 1);
                if (resultat == NULL) {
                    printf("Erreur : allocation mémoire échouée.\n");
                    return NULL;
                }
                strcpy(resultat, nomGouv);
                return resultat;
            }
        }
    }
    fclose(fichier);
    printf("Numéro de gouvernement introuvable.\n");
    return NULL;
}
typedef struct {
    char modif_value[50];
    char modif_name[50];
}modification;
typedef struct
{
    modification *contents[MAX_STACK_SIZE];
    unsigned nb_values;
} stack;
stack *stack_new(void)
{
stack *s;
s= malloc(sizeof(stack));
if (!s)
return NULL;
s -> nb_values = 0;
return s;
}
/* Lib`ere la pile <s>. */
void stack_free(stack *s)
{
free(s);
}
int stack_push(stack *s, void *p)
{
if (s -> nb_values >= MAX_STACK_SIZE)
return -1;
s -> contents[s -> nb_values++] = p;
return 0;
}
void *stack_pop(stack *s)
{
if (!(s -> nb_values))
return NULL;
return s -> contents[--(s -> nb_values)];
}
void *stack_top(stack *s)
{
if (!(s -> nb_values))
return NULL;
return s -> contents[s -> nb_values - 1];
}
unsigned stack_size(stack *s)
{
return s -> nb_values;
}
int stack_is_empty(stack *s)
{
return s -> nb_values == 0;
}
stack T[MAX_CITOYEN];
int total_citoyens = 0;
typedef struct {
    int jour;
    int mois;
    int annee;
}date ;
typedef struct {
    int gouvernorat;
    char municipalite[50];
    int code_postal;
}lieu;
typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    int age ;
    date date_de_naissance;
    lieu lieu_de_naissance;
    char sexe[1];
    char etat_civil[50];
    int taille_de_menage ;
    int niveau_d_education;
    char situation_professionnelle[50];
    int revenue;
    char occupation[50];
    char type_de_logement[50];
    lieu lieu_de_residence;;
    char langue_parle[50];
    char religion[50];
    char acces_au_soins[50];
    char etat_de_sante[50];
    char couverture_sociale[50];
    char mode_de_transport[50];
    char secteur_publique_ou_privee[50];
}citoyen;
citoyen citoyens[MAX_CITOYEN];
stack* Tab[MAX_CITOYEN];
int G [MAX_CITOYEN];
void ajouter_citoyen () {
    if (total_citoyens >= MAX_CITOYEN ) {
        printf("Capacité maximale atteinte.\n");
    return;
    }
    citoyen c;
    c.id = total_citoyens;
    printf("Entrez le nom: ");
    scanf(" %s",&c.nom);
    printf("Entrez le prenom: ");
    scanf(" %s",&c.prenom);
    printf("Entrez le sexe: ");
    scanf(" %s",&c.sexe);
    printf("Entrez l'age: ");
    scanf("%i", &c.age);
    printf("taper le jour de naissance ");
    scanf(" %i", &c.date_de_naissance.jour);
    printf("tapez le mois de naissance:");
    scanf(" %i", &c.date_de_naissance.mois);
    printf("taper l annee  de naissance:");
    scanf(" %i", &c.date_de_naissance.annee);
    printf("taper le gouvernorat de naissance:");
    scanf(" %i", &c.lieu_de_naissance.gouvernorat);
    printf("taper la municipalite de naissance:");
    scanf(" %s", &c.lieu_de_naissance.municipalite);
    printf("taper le code postal du lieu de naissance:");
    scanf(" %d", &c.lieu_de_naissance.code_postal);
    printf("taper le taille de menage:");
    scanf(" %d", &c.taille_de_menage);
    printf("taper la situation professionnelle:");
    scanf(" %s", &c.situation_professionnelle);
    printf("taper loccupation:");
    scanf(" %s", &c.occupation);
    printf("taper le type de logement:");
    scanf(" %s", &c.type_de_logement);
    printf("taper le gouvernorat de residence:");
    scanf(" %i", &c.lieu_de_residence.gouvernorat);
    printf("taper la municipalite de residence:");
    scanf(" %s", &c.lieu_de_residence.municipalite);
    printf("taper le code postal de residence:");
    scanf(" %i", &c.lieu_de_residence.code_postal);
    printf("Entrez les langues parlees:");
    scanf(" %s",&c.langue_parle);
    printf("Entrez lacces aux soins:");
    scanf(" %s",&c.acces_au_soins);
    printf("Entrez letat de sante:");
    scanf(" %s",&c.etat_de_sante);
    printf("Entrez la couverture sociale:");
    scanf(" %s",&c.couverture_sociale);
    printf("Entrez le mode de transport:");
    scanf(" %s",&c.mode_de_transport);
    printf("Entrez le secteur est publique ou privee:");
    scanf(" %s",&c.secteur_publique_ou_privee);
    printf("Entrez l'etat civil:");
    scanf(" %s",&c.etat_civil);
    printf("Entrez le revenu annuel:");
    scanf("%d", &c.revenue);
    printf("Entrez le niveau d'education:");
    scanf(" %i",&c.niveau_d_education);
    printf("Entrez la religion:");
    scanf(" %s", c.religion);
    citoyens[total_citoyens] = c;
    total_citoyens++;
    printf("citoyen ajoute avec succes !");
}
void ajouter_modification() {
    int x;
    printf("Tapez l'identifiant unique");
    scanf(" %i",&x);
    for (int i = 0; i < MAX_CITOYEN; i++) {
        Tab[i] = stack_new();
        if (!Tab[i]) {
            printf("Erreur d'allocation mémoire pour TAB[%d]\n", i);
            return;
        }
    }
    if (0<=x && x<total_citoyens) {

        modification *m = malloc(sizeof(modification));
        char name[30];
        char value[30];
        printf("donner le nom de votre modofication");
        scanf(" %s",name);
        printf("donner la nouvelle valeur");
        scanf(" %s",value);
        strcpy(m->modif_value,value);
        strcpy(m->modif_name,name);
        stack_push(Tab[x],m);
        printf("modification ajoutee avec succes");
    }else {
        printf("Tapez l'id n'existe pas");
    }
}
void mettre_a_jour() {
    int s=0;
    for (int i = 0;i<total_citoyens; i++) {
        if (!stack_is_empty(Tab[i])) {
            s++;
            modification* m=stack_pop(Tab[i]);
            if (strcmp(m->modif_name,"nom")==0) {
                strcpy(citoyens[i].nom,m->modif_value );
            }else if (strcmp(m->modif_name,"prenom")==0) {
                strcpy(citoyens[i].prenom,m->modif_value );
            }else {
                citoyens[i].age=atoi(m->modif_value);
            }
        }
    }if (s=!0) {
        printf("la mise a jour est terminee");
    }else{
        printf("pas de modification");
    }
}
void afficher_citoyen () {
    if (total_citoyens ==0) {
        printf("pas de citoyens ajoutes");
        return ;
    }
    int x ;
    do {
        printf("Tapez l'identifiant unique");
        scanf(" %i",&x);
    }
    while (total_citoyens <=x || x<0);
            printf("le nom:%s\n", citoyens[x].nom);
            printf("le prenom:%s\n", citoyens[x].prenom);
            printf("le sexe:%s\n", citoyens[x].sexe);
            printf("l'age:%d\n", citoyens[x].age);
            printf("le jour de naissance:%i\n",citoyens[x].date_de_naissance.jour);
            printf("le mois de naissance:%i\n",citoyens[x].date_de_naissance.mois);
            printf("lannee  de naissance:%i\n" ,citoyens[x].date_de_naissance.annee);
            printf("le gouvernorat de naissance:%i\n" ,citoyens[x].lieu_de_naissance.gouvernorat);
            printf("la municipalite de naissance :%i\n" ,citoyens[x].taille_de_menage);
            printf("le code postal de naissance:%i\n" ,citoyens[x].lieu_de_naissance.code_postal);
            printf("le taille de menage:%i\n" ,citoyens[x].taille_de_menage);
            printf("la situation professionnelle:%s\n" ,citoyens[x].situation_professionnelle);
            printf("loccupation:%s\n" ,citoyens[x].occupation);
            printf("le type de logement:%s\n" ,citoyens[x].type_de_logement );
            printf("le gouvernorat de residence:%i\n" ,citoyens[x].lieu_de_residence.gouvernorat);
            printf("la municipalite de residence:%s\n" ,citoyens[x].lieu_de_residence.municipalite);
            printf("le code postal de residence:%d\n" ,citoyens[x].lieu_de_residence.code_postal);
            printf("les langues parlees:%s\n" ,citoyens[x].langue_parle);
            printf("lacces aux soins:%s\n" ,citoyens[x].acces_au_soins);
            printf("letat de sante:%s\n" ,citoyens[x].etat_de_sante);
            printf("la couverture sociale:%s\n" ,citoyens[x].couverture_sociale);
            printf("le mode de transport:%s\n" ,citoyens[x].mode_de_transport);
            printf("le secteur est publique ou privee:%s\n" ,citoyens[x].secteur_publique_ou_privee);
            printf("l'etat civil:%s\n" ,citoyens[x].etat_civil);
            printf("le revenu annuel:%i\n" ,citoyens[x].revenue);
            printf("le niveau d'education:%i\n" ,citoyens[x].niveau_d_education);
            printf("la religion:%s\n" ,citoyens[x].religion);
        }
void calcul_taux_alphabetisation(){
    if (total_citoyens ==0) {
        printf("pas de citoyens ajoutes");
        return ;
    }
    int s=0;
    for (int i=0 ; i<total_citoyens ; i++) {
        if (citoyens[i].niveau_d_education>=1) {
            s++;
        }
    }
const float T = ((float)s/(float)total_citoyens)*100;
        printf("Taux alphabetisation total de %f",T);
    }
void calcul_la_repartition_de_population_par_gouvernorat() {
    if (total_citoyens ==0) {
        printf("pas de citoyens ajoutes");
        return ;
    }
    G[0]=citoyens[0].lieu_de_residence.gouvernorat ;
    if (total_citoyens ==1) {
        printf("le nombre de citoyens du gouvernorat%i est 1 !" ,G[0]);
    }
else {
    int s=0;
    for (int i=1 ; i<total_citoyens ; i++){
        int v=0 ;
        for (int j=0 ; j<i ; j++) {
            if (G[j]==G[i]) {
                v=1;
            }
            if (v==0){
                G[i]=citoyens[i].lieu_de_residence.gouvernorat;
                s++;
            }
        }
    }for (int i=0 ; i<s ; i++) {
        int s1=0;
        for (int j=0 ; j<total_citoyens ; j++) {
            if (citoyens[j].lieu_de_naissance.gouvernorat==G[i]) {
                s1++;
            }
        }printf("le nombre de citoyens du gouvernorat%i est %i" ,G[i],s1);
    }
}
}
void Calculer_le_taux_de_chomage() {
    if (total_citoyens ==0) {
        printf("pas de citoyens ajoutes");
        return ;
    }
    int s1=0;
    int s=0;
    for (int i=0 ; i<total_citoyens ; i++) {
        int c =6+ citoyens[i].niveau_d_education;
        if (strcmp(citoyens[i].situation_professionnelle,"aucune")==1 && c<citoyens[i].age  ) {
            s++ ;}
        if (citoyens[i].situation_professionnelle!="aucune") {
            s1++;
        }
    }
    float k = (float) s / (float) s1;
    float m=k*100;
    printf("Tau de chomage est %f",m);
    }
void calculer_le_revenu_moyen(){
    if (total_citoyens ==0) {
        printf("pas de citoyens ajoutes");
        return ;
    }
    int s=0;
    int s1=0;
    for (int i=0 ; i<total_citoyens ; i++) {
        s+=citoyens[i].revenue;
        if (citoyens[i].revenue!=0) {
            s1++;
        }
    }
    const float k=(float)(s)/(float)s1;
    printf("le revenu moyen est%f",k);

    }
void calcule_le_taux_de_fecondite(){
    if (total_citoyens ==0) {
        printf("pas de citoyens ajoutes");
        return ;
    }
    int s=0;
    int s1=0;
    int v1=0;
    int v2=0;
    for (int i=0 ; i<total_citoyens ; i++) {
        if (citoyens[i].age<40 && citoyens[i].age>18 && (strcmp(citoyens[i].sexe,"F")==0)){
            s++;
            v1=1;
        }if (citoyens[i].age<6) {
            s1++;
            v2=1;
        }

    }if (v1==1 && v2==1) {
        const float l = (float)s1 /(float)s;
        printf("le tau de fecondite est %f",l);
    }else {
        printf("pas de femmes ou d enfant");
    }
}
void calculer_le_taux_de_croissance_moyen_annuel() {
    if (total_citoyens ==0) {
        printf("pas de citoyens ajoutes");
        return ;
    }
    int s=0;
    int s1=0;
    for (int i=0 ; i<total_citoyens ; i++) {
        if (citoyens[i].date_de_naissance.annee ==2024) {
            s++;
        }if (citoyens[i].date_de_naissance.annee==2019) {
            s1++;
        }
    }
    const float l = (float) (s - s1) / (float) s1;
    printf("le taux de croissance moyen est %f",l);
}
void donner_le_minimum_de_revenue(){
    if (total_citoyens ==0) {
        printf("pas de citoyens ajoutes");
        return ;
    }
    int min=citoyens[0].revenue;
    for (int i=1 ; i<total_citoyens ; i++) {
        if (citoyens[i].revenue<min) {
            min=citoyens[i].revenue;
        }
    }printf("le minimum de revenue est %i",min);
}
void calculer_le_taux_de_pauvrete() {
    if (total_citoyens ==0) {
        printf("pas de citoyens ajoutes");
        return ;
    }
    int SMIC;
    printf("Donner le SMIC de votre etat");
    scanf("%i",&SMIC);
    int s=0;
    int s1;
    for (int i=0 ; i<total_citoyens ; i++) {
        if (citoyens[i].revenue<SMIC) {
            s++;
        }if (citoyens[i].revenue !=0) {
            s1++;
        }
    }int p=(s/s1)*100;
    printf("le tau de pauvrete est %i",p);
}
int main () {
    int x=0;
    int choix;
    do{
        printf("\n****MENU****\n");
        printf("1. Ajouter citoyen\n");
        printf("2. Rechercher un citoyen par id\n");
        printf("3. le taux dalphabetisation\n");
        printf("4. la repartition de population par gouvernorat \n");
        printf("5. le taux de chomage\n");
        printf("6. le revenu moyen\n");
        printf("7. le taux de fecondite\n");
        printf("8. le taux de croissance moyen annuel\n");
        printf("9. le minimum de revenue\n");
        printf("10. le taux de pauvrete\n");
        printf("11. ajouter modification\n");
        printf("12. mettre a jour\n");
        printf("13. Quitter");
        printf("\nentrer votre choix");
        scanf("%i",&choix);
        switch (choix) {
            case 1:
                ajouter_citoyen();
            x=1;
            break;
            case 2:
                afficher_citoyen();
            x=1;
            break;
            case 3:
                calcul_taux_alphabetisation();
            x=1;
            break;
            case 4:
                calcul_la_repartition_de_population_par_gouvernorat();
            x=1;
            break;
            case 5:
                Calculer_le_taux_de_chomage();
            x=1;
            break;
            case 6:
                calculer_le_revenu_moyen();
            x=1;
            break;
            case 7:
                calcule_le_taux_de_fecondite();
            x=1;
            break;
            case 8:
                calculer_le_taux_de_croissance_moyen_annuel();
            x=1;
            break;
            case 9:
                donner_le_minimum_de_revenue();
            x=1;
            break;
            case 10:
                calculer_le_taux_de_pauvrete();
            x=1;
            break;
            case 11:
                ajouter_modification();
            x=1;
            break;
            case 12:
                mettre_a_jour();
            x=1;
            break;
            case 14:
                break;

        }
    }while (x==1);
}