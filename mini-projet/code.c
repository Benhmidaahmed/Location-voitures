
#include <stdio.h>
#include <time.h>
#include<stdlib.h>
typedef struct {
int minute;
int heure;
int jour;
} Horaire ;
typedef struct {
int id;
Horaire horaireDateSouhaite;
Horaire dureeHeureMinute;
int typeActivite;
int idZoneSrc;
int idZoneDest;
int idLigne;
int sens;
int distanceParcourue;
Horaire horaireArrivee;
} Activite ;
typedef struct {
int cin;
int idZoneHabitat;
int idZoneTravail;
int idZoneCourante;
int intentionVoyage;
int idLigneCourante;
int sensCourant;
int idZoneDest;
int nombreActivites;
Activite activites[8];
} Personne ;
typedef struct {
int id;
int row;
int column;
int nombrePersonnes;
Personne personnes[100];
} Zone ;
typedef struct {
int row;
int column;
int codeRue;
} Subdivision ;
typedef struct {
int idZoneSrc;
int idZoneDest;
int distance;
int idLigne;
int sens;
Horaire dureeApproximative;
int nombresubdivisions;
Subdivision parcours[20];
} Troncon ;

typedef struct {
int id;
int nombreZones;
int idZones[10];
} Ligne ;
typedef struct {
int id;
int idLigne;
int sens;
Horaire horaireDateDepart;
} Tache ;
typedef struct {
int zoneSrc;
int zoneDest;
int idLigne;
int sens;
int idBus;
Horaire dateVente;
int distance;
int prix;
} Ticket ;

typedef struct {
int rue;
int zone;
int bus;
}casecarte;

typedef struct {
int id;
int idZoneCourante;
int row;
int column;
int enRoute;
int idLigneCourante;
int sensCourant;
int idZoneSrc;
int idZoneDest;
int nombreTaches;
Tache taches[10];
int nombrePassagers;
Personne passagers[20];
int nombreTickets;
Ticket tickets[200];
} Bus ;
typedef struct {
    int idZoneSrc;
    int idZoneDest;
    int idLigne;
    int sens;
    int distance;
} Liaison;
typedef struct {
    int nombreLiaisons;
    Liaison liaisons[];
} ListeLiaisons;

void chargerZones(Zone zones[], int *nombreZones)
{
    FILE *fic = fopen("zones.txt", "r");
    int i = 0;

    while (i <=9 && (fic) != NULL)
    {
        fscanf(fic, "%d %d %d", &zones[i].id, &zones[i].row, &zones[i].column);
        i++;
    }

    *nombreZones = i;
    fclose(fic);
}

void afficherZones(Zone zones[], int nombreZones)
{
    int i;
    for (i=0;i<=9;i++)
    {
         printf("id:%d row:%d column=%d \n", zones[i].id, zones[i].row, zones[i].column);
    }

}
void sauvegarderZones(Zone zones[], int nombreZones, char* zoneSauv)
{
    FILE *fic = fopen("zoneSauv.txt", "w");
    int i;

    for (i=0;i<=9;i++)
    {
         fprintf(fic,"id:%d row:%d column=%d \n", zones[i].id, zones[i].row, zones[i].column);
    }
    fclose(fic);

}
void chargerTroncons(Troncon troncons[], int *nombreTroncons)
{
    FILE *fic = fopen("troncons.txt", "r");
    int i = 0;
    int j;

    while (i < 10 && !feof(fic))
    {
        int nbsub;
        fscanf(fic, "%d %d %d %d %d %d %d", &troncons[i].idZoneSrc, &troncons[i].idZoneDest, &troncons[i].distance, &troncons[i].dureeApproximative.jour, &troncons[i].dureeApproximative.heure, &troncons[i].dureeApproximative.minute, &nbsub);

        troncons[i].nombresubdivisions = nbsub;

        for (j = 0; j <= troncons[i].nombresubdivisions-1; j++)
        {
            fscanf(fic, "%d %d %d", &troncons[i].parcours[j].row, &troncons[i].parcours[j].column, &troncons[i].parcours[j].codeRue);
        }

        i++;
    }

    *nombreTroncons = i;
    fclose(fic);
}


void afficherTroncons(Troncon troncons[], int nombreTroncons)
{
    int i, j;
    for (i = 0; i < nombreTroncons; i++)
    {
        printf("idZoneSrc:%d idZoneDest:%d distance: %d  Duree Approximative: %d jours %d heures %d minutes Nombre de subdivisions: %d", troncons[i].idZoneSrc, troncons[i].idZoneDest, troncons[i].distance, troncons[i].dureeApproximative.jour, troncons[i].dureeApproximative.heure, troncons[i].dureeApproximative.minute, troncons[i].nombresubdivisions);
        for (j = 0; j < troncons[i].nombresubdivisions; j++)
        {
            printf(" Subdivision %d: row=%d column=%d codeRue=%d\n", j + 1, troncons[i].parcours[j].row, troncons[i].parcours[j].column, troncons[i].parcours[j].codeRue);
        }

        printf("\n");
    }
}


void sauvegarderTroncons(Troncon troncons[], int nombreTroncons, char* tronconSauv)
{
    FILE *fic = fopen("tronconSauv.txt", "w");


    for (int i = 0; i < nombreTroncons; i++)
    {
        fprintf(fic, "idZoneSrc:%d idZoneDest:%d distance:%d Duree Approximative:%d jours %d heures %d minutes Nombre de subdivisions:%d\n",
                troncons[i].idZoneSrc, troncons[i].idZoneDest, troncons[i].distance,
                troncons[i].dureeApproximative.jour, troncons[i].dureeApproximative.heure,
                troncons[i].dureeApproximative.minute, troncons[i].nombresubdivisions);

        for (int j = 0; j < troncons[i].nombresubdivisions; j++)
        {
            fprintf(fic, "Subdivision %d: row=%d column=%d codeRue=%d\n", j + 1,
                    troncons[i].parcours[j].row, troncons[i].parcours[j].column,
                    troncons[i].parcours[j].codeRue);
        }

        fprintf(fic, "\n");
    }

    fclose(fic);
}

void chargerFlotteBus(Bus flotteBus[], int *nombreBus) {
    FILE *fic = fopen("flottebus.txt", "r");
    int i = -1;
    int j = 0;
    int nbBus = 0;

    while (i < 10 && !feof(fic) ) {

        fscanf(fic, "%d %d %d %d %d %d %d %d", &flotteBus[i + 1].id, &flotteBus[i + 1].idZoneCourante, &flotteBus[i + 1].row, &flotteBus[i + 1].column, &flotteBus[i + 1].enRoute, &flotteBus[i + 1].idLigneCourante, &flotteBus[i + 1].sensCourant, &flotteBus[i + 1].nombreTaches);
        i++;
        nbBus = flotteBus[i].nombreTaches;

        for (j = 0; j < nbBus; j++) {
            fscanf(fic, "%d %d %d %d %d %d", &flotteBus[i].taches[j].id, &flotteBus[i].taches[j].idLigne, &flotteBus[i].taches[j].sens, &flotteBus[i].taches[j].horaireDateDepart.jour, &flotteBus[i].taches[j].horaireDateDepart.heure, &flotteBus[i].taches[j].horaireDateDepart.minute);
        }
    }

    *nombreBus = i +1;

    fclose(fic);
}

void afficherFlotteBus(Bus flotteBus[], int nombreBus) {
    int i, j;
    for (i = 0; i < nombreBus; i++) {
        printf("busid:%d zone:%d row: %d  col: %d enroute: %d idligne:%d sens:%d nbTaches:%d \n",
               flotteBus[i].id, flotteBus[i].idZoneCourante, flotteBus[i].row, flotteBus[i].column, flotteBus[i].enRoute,
               flotteBus[i].idLigneCourante, flotteBus[i].sensCourant, flotteBus[i].nombreTaches);

        for (j = 0; j < flotteBus[i].nombreTaches; j++) {
            printf("Tache %d: idligne=%d sens=%d jour=%d heures:%d minutes=%d \n",
                   flotteBus[i].taches[j].id, flotteBus[i].taches[j].idLigne, flotteBus[i].taches[j].sens,
                   flotteBus[i].taches[j].horaireDateDepart.jour, flotteBus[i].taches[j].horaireDateDepart.heure,
                   flotteBus[i].taches[j].horaireDateDepart.minute);
        }

        printf("\n");
    }
}

void sauvegarderFlotteBus(Bus flotteBus[], int nombreBus, char* flotteBuSauv )
{
    FILE *fic = fopen("flotteBuSauv.txt", "w");
   int i, j;
    for (i = 0; i < nombreBus; i++) {
        fprintf(fic,"busid:%d zone:%d row: %d  col: %d enroute: %d idligne:%d sens:%d nbTaches:%d \n",
               flotteBus[i].id, flotteBus[i].idZoneCourante, flotteBus[i].row, flotteBus[i].column, flotteBus[i].enRoute,
               flotteBus[i].idLigneCourante, flotteBus[i].sensCourant, flotteBus[i].nombreTaches);

        for (j = 0; j < flotteBus[i].nombreTaches; j++) {
            fprintf(fic,"Tache %d: idligne=%d sens=%d jour=%d heures:%d minutes=%d \n",
                   flotteBus[i].taches[j].id, flotteBus[i].taches[j].idLigne, flotteBus[i].taches[j].sens,
                   flotteBus[i].taches[j].horaireDateDepart.jour, flotteBus[i].taches[j].horaireDateDepart.heure,
                   flotteBus[i].taches[j].horaireDateDepart.minute);
        }

    }
}
void chargerLignes(Ligne lignes[], int *nombreLignes) {
    FILE *fic = fopen("lignes.txt", "r");
    int i = 0;
    int j = 0;
    int nblign = 0;

    while (i < 10 && !feof(fic)) {
        fscanf(fic, "%d %d", &lignes[i].id, &lignes[i].nombreZones);
        nblign = lignes[i].nombreZones;

        for (j = 0; j < nblign; j++) {
            fscanf(fic, "%d", &lignes[i].idZones[j]);
        }

        i++;
    }

    *nombreLignes = i;

    fclose(fic);
}

void afficherLignes(Ligne lignes[], int nombreLignes) {
    int i, j;
    for (i = 0; i < nombreLignes; i++) {
        printf("idligne:%d nbzone:%d \n", lignes[i].id, lignes[i].nombreZones);
        for (j = 0; j < lignes[i].nombreZones; j++) {
            printf(" idZone%d: %d\n", j + 1, lignes[i].idZones[j]);
        }

        printf("\n");
    }
}
void sauvegarderLignes(Ligne lignes[],int nombreLignes, char*ligneSauv)
{
    FILE *fic = fopen("ligneSauv.txt", "w");
    int i, j;
    for (i = 0; i < nombreLignes; i++) {
        fprintf(fic,"idligne:%d nbzone:%d \n", lignes[i].id, lignes[i].nombreZones);
        for (j = 0; j < lignes[i].nombreZones; j++) {
            fprintf(fic," idZone%d: %d\n", j + 1, lignes[i].idZones[j]);
        }
    }
}
void rechercherLigneSens(int idZoneSrc, int idZoneDest, Ligne lignes[], int nombreLignes, int idLigne, int *l, int *s) {
    *l = -1;
    *s = -1;

    for (int i = 0; i < nombreLignes; i++) {
        if (lignes[i].id == idLigne) {
            *l = i;
            for (int j = 0; j < lignes[i].nombreZones - 1; j++) {
                if ((idZoneSrc < idZoneDest) && (lignes[i].idZones[j] == idZoneSrc || lignes[i].idZones[j] == idZoneDest)) {
                    *s = 0;

                } else if ((idZoneSrc > idZoneDest) && (lignes[i].idZones[j] == idZoneSrc || lignes[i].idZones[j] == idZoneDest)) {
                    *s = 1;

                }
            }
        }
    }
}


int calculerDistance(int idZoneSrc, int idZoneDest, Ligne lignes[], int idLigne, Troncon troncons[], int nombreLignes, int nombreTroncons) {
    int d = 0;
    int i, j, l, s;


    rechercherLigneSens(idZoneSrc, idZoneDest, lignes, nombreLignes, idLigne, &l, &s);


    for (i = 0; i < nombreTroncons; i++) {

        if (troncons[i].idZoneSrc == idZoneSrc && troncons[i].idZoneDest == idZoneDest) {
            d += troncons[i].distance;
        }
    }

    return d;
}

void affecterPersonneZone(Zone zones[], Personne pers)
{
    int j = zones[pers.idZoneHabitat].nombrePersonnes;
    zones[pers.idZoneHabitat].personnes[j] = pers;
    zones[pers.idZoneHabitat].nombrePersonnes++;

}
void genererPersonne(Zone zones[], int nombreZones, Ligne lignes[], int nombreLignes) {
    int i;
    srand(time(NULL));
    Personne pers;
    int idZoneSrc, idZoneDest, idLigne;
    int distance;

    for (i = 0; i < 300; i++) {
        pers.cin = i + 1;
        pers.idZoneHabitat = rand() % 10;
        pers.idZoneTravail = rand() % 10;
        pers.idZoneCourante = -1;
        pers.intentionVoyage = 0;
        pers.idLigneCourante = -1;
        pers.sensCourant = -1;
        pers.idZoneCourante = pers.idZoneHabitat;
        pers.nombreActivites = 3;

        // Activit� 0
        pers.activites[0].id = 0;
        pers.activites[0].horaireDateSouhaite.jour = 0;
        pers.activites[0].horaireDateSouhaite.heure = 6 + rand() % 3;
        pers.activites[0].horaireDateSouhaite.minute = 0;
        pers.activites[0].dureeHeureMinute.jour = 0;
        pers.activites[0].dureeHeureMinute.heure = 8;
        pers.activites[0].dureeHeureMinute.minute = 0;
        pers.activites[0].typeActivite = 1;
        pers.activites[0].idZoneSrc = pers.idZoneHabitat;
        pers.activites[0].idZoneDest = pers.idZoneTravail;
        pers.activites[0].idLigne = 0;
        rechercherLigneSens(pers.activites[0].idZoneSrc, pers.activites[0].idZoneDest, lignes, nombreLignes, pers.activites[0].idLigne, &pers.activites[1].idLigne, &pers.activites[0].sens );



        // Activit� 1
        pers.activites[1].id = 1;
        pers.activites[1].horaireDateSouhaite.jour = 0;
        pers.activites[1].horaireDateSouhaite.heure = 8 + (6 + rand() % 3);
        pers.activites[1].horaireDateSouhaite.minute = 0;
        pers.activites[1].dureeHeureMinute.jour = 0;
        pers.activites[1].dureeHeureMinute.heure = 2;
        pers.activites[1].dureeHeureMinute.minute = 0;
        pers.activites[1].typeActivite = 0;
        pers.activites[1].idZoneSrc = pers.activites[0].idZoneDest;
        pers.activites[1].idZoneDest = pers.intentionVoyage;
        pers.activites[1].idLigne = 0;
        rechercherLigneSens(pers.activites[1].idZoneSrc, pers.activites[1].idZoneDest, lignes, nombreLignes, pers.activites[1].idLigne, &pers.activites[1].idLigne, &pers.activites[1].sens );




        // Activit� 2
        pers.activites[2].id = 2;
        pers.activites[2].horaireDateSouhaite.jour = 0;
        pers.activites[2].horaireDateSouhaite.heure = 10 + (6 + rand() % 3);
        pers.activites[2].horaireDateSouhaite.minute = 0;
        pers.activites[2].dureeHeureMinute.jour = 0;
        pers.activites[2].dureeHeureMinute.heure = 14;
        pers.activites[2].dureeHeureMinute.minute = 0;
        pers.activites[2].typeActivite = 0;
        pers.activites[2].idZoneSrc = pers.activites[1].idZoneDest;
        pers.activites[2].idZoneDest = pers.idZoneHabitat;
        pers.activites[2].idLigne = 0;

        rechercherLigneSens(pers.activites[2].idZoneSrc, pers.activites[2].idZoneDest, lignes, nombreLignes, pers.activites[2].idLigne, &pers.activites[2].idLigne, &pers.activites[2].sens );


        affecterPersonneZone(zones, pers);
    }
}
void afficherPersonnes(Zone zones[], int nombreZones) {
    int i, j, k;
    for (i = 0; i < 10; i++) {
        printf("Zone:%d NombrePersonnes:%d\n", i, zones[i].nombrePersonnes);

        for (j = 0; j <zones[i].nombrePersonnes ; j++) {
            Personne pers = zones[i].personnes[j];
            printf("  Cin:%d idZoneHabitat:%d idZoneTravail:%d idZoneCourante:%d intentionVoyage:%d idLigneCourante:%d sensCourant:%d idZoneCourante:%d nombreActivites:%d \n",
                    pers.cin, pers.idZoneHabitat, pers.idZoneTravail,
                    pers.idZoneCourante, pers.intentionVoyage, pers.idLigneCourante,
                    pers.sensCourant, pers.idZoneCourante, pers.nombreActivites);

            for (k = 0; k < pers.nombreActivites; k++) {
                Activite act = pers.activites[k];
                printf("    Activite:%d id:%d horaireDateSouhaite: jour:%d heure:%d minute:%d dureeHeureMinute: jour:%d heure:%d minute:%d typeActivite:%d idZoneSrc:%d idZoneDest:%d idLigne:%d sens:%d \n",
                        k, act.id, act.horaireDateSouhaite.jour, act.horaireDateSouhaite.heure, act.horaireDateSouhaite.minute,
                        act.dureeHeureMinute.jour, act.dureeHeureMinute.heure,
                        act.dureeHeureMinute.minute, act.typeActivite, act.idZoneSrc, act.idZoneDest,act.idLigne,act.sens);
            }
        }
    }
}


void sauvegarderPersonnes(Zone zones[], int nombreZones, char* personneSauv ) {
    int i, j, k;
    FILE* fic = fopen("personneSauv.txt", "w");

    for (i = 0; i < nombreZones; i++) {
        fprintf(fic, "%d %d\n", i, zones[i].nombrePersonnes);

        for (j = 0; j < zones[i].nombrePersonnes; j++) {
            Personne pers = zones[i].personnes[j];
            fprintf(fic, "%d %d %d %d %d %d %d %d \n",
                    pers.cin, pers.idZoneHabitat, pers.idZoneTravail,
                    pers.idZoneCourante, pers.intentionVoyage, pers.idLigneCourante,
                    pers.sensCourant, pers.idZoneCourante, pers.nombreActivites);

            for (k = 0; k < pers.nombreActivites; k++) {
                Activite act = pers.activites[k];
                fprintf(fic, "%d %d %d %d %d %d %d %d %d %d %d %d %d\n",
                        k, act.id, act.horaireDateSouhaite.jour, act.horaireDateSouhaite.heure, act.horaireDateSouhaite.minute,
                        act.dureeHeureMinute.jour, act.dureeHeureMinute.heure,
                        act.dureeHeureMinute.minute, act.typeActivite, act.idZoneSrc, act.idZoneDest,act.idLigne,act.sens);
            }
        }
    }

    fclose(fic);
}

void chargerPersonnes(Zone zones[], int* nombreZones, char* nomFichier) {
    FILE *fic = fopen("personneSauv.txt", "r");
    int i = 0;
    int j = 0;
    int nbzones = 0;

    while (i < 10 && !feof(fic)) {
        fscanf(fic, "Zone:%d NombrePersonnes:%d", &j, &zones[i].nombrePersonnes);
        nbzones = zones[i].nombrePersonnes;

        for (j = 0; j < nbzones; j++) {
            fscanf(fic, "Cin:%d idZoneHabitat:%d idZoneTravail:%d idZoneCourante:%d intentionVoyage:%d idLigneCourante:%d sensCourant:%d idZoneCourante:%d nombreActivites:%d",
                    &zones[i].personnes[j].cin, &zones[i].personnes[j].idZoneHabitat, &zones[i].personnes[j].idZoneTravail,
                    &zones[i].personnes[j].idZoneCourante, &zones[i].personnes[j].intentionVoyage, &zones[i].personnes[j].idLigneCourante,
                    &zones[i].personnes[j].sensCourant, &zones[i].personnes[j].idZoneCourante, &zones[i].personnes[j].nombreActivites);

            for (int k = 0; k < zones[i].personnes[j].nombreActivites; k++) {
                fscanf(fic, "Activite:%d id:%d horaireDateSouhaite: jour:%d heure:%d minute:%d dureeHeureMinute: jour:%d heure:%d minute:%d typeActivite:%d idZoneSrc:%d idZoneDest:%d idligne:%d sens:%d",
                        &k, &zones[i].personnes[j].activites[k].id, &zones[i].personnes[j].activites[k].horaireDateSouhaite.jour,
                        &zones[i].personnes[j].activites[k].horaireDateSouhaite.heure, &zones[i].personnes[j].activites[k].horaireDateSouhaite.minute,
                        &zones[i].personnes[j].activites[k].dureeHeureMinute.jour, &zones[i].personnes[j].activites[k].dureeHeureMinute.heure,
                        &zones[i].personnes[j].activites[k].dureeHeureMinute.minute, &zones[i].personnes[j].activites[k].typeActivite,
                        &zones[i].personnes[j].activites[k].idZoneSrc, &zones[i].personnes[j].activites[k].idZoneDest,&zones[i].personnes[j].activites[k].idLigne,&zones[i].personnes[j].activites[k].sens);
            }
        }

        i++;
    }

    *nombreZones = i;

    fclose(fic);
}


void initialiserCarte(casecarte cartegeo[20][20], Zone zones[], Ligne lignes[], Troncon troncons[], Bus flotteBus[], int nombreZones, int nombreLignes, int nombreTroncons, int nombreBus)
{
    int i, j = 0, r, c, k, b;
    for (int r = 0; r < 20; r++) {
        for (int c = 0; c < 20; c++) {
            cartegeo[r][c].rue = 0;
            cartegeo[r][c].zone = -1;
            cartegeo[r][c].bus = -1;
        }
    }

    for (i = 0; i < nombreZones; i++) {
        r = zones[i].row;
        c = zones[i].column;
        cartegeo[r][c].zone = zones[i].id;
    }

    for (k = 0; k < nombreBus; k++) {
        int r = flotteBus[k].row;
        int c = flotteBus[k].column;
        if (cartegeo[r][c].bus == -1) {
            cartegeo[r][c].bus = flotteBus[k].id;
        } else {
            cartegeo[r][c].bus = 100;
        }
    }

    for (b = 0; b < 10; b++) {
            j=0;
        while (j < troncons[b].nombresubdivisions) {

            int r = troncons[b].parcours[j].row;
            int c = troncons[b].parcours[j].column;
            cartegeo[r][c].rue = troncons[b].parcours[j].codeRue;

            j++;
        }
    }
}


void afficherCarteGeo(casecarte cartegeo[20][20], Zone zones[], Bus flotteBus[], int nombreZones, int nombreLignes, int nombreTroncons, int nombreBus)
{
    for (int i = 0; i < 20; i++) {

        for (int j = 0; j < 20; j++) {
            if (cartegeo[i][j].zone != -1 && cartegeo[i][j].bus == -1) {
                    int id=cartegeo[i][j].zone;
                printf("Z%d%d", cartegeo[i][j].zone ,zones[id].nombrePersonnes);
            } else if (cartegeo[i][j].zone != -1 && cartegeo[i][j].bus != -1) {
                if (cartegeo[i][j].bus < 100) {
                    printf("Z%dB%d", cartegeo[i][j].zone, cartegeo[i][j].bus);
                } else {
                    printf("Z%dBM", cartegeo[i][j].zone);
                }
            }

             else if (cartegeo[i][j].zone == -1 && cartegeo[i][j].bus != -1) {
                printf("[B%d]", cartegeo[i][j].bus);
            }

             else if (cartegeo[i][j].rue == 3 || cartegeo[i][j].rue == 2 || cartegeo[i][j].rue == 1) {
                printf("%c%c%c%c", 205, 205, 205, 205);
            } else if (cartegeo[i][j].rue == 4 || cartegeo[i][j].rue == 8 || cartegeo[i][j].rue == 12) {
                printf("   %c", 186);
            } else if (cartegeo[i][j].rue == 5) {
                printf("%c%c%c%c", 205,205,205,187);
            } else if (cartegeo[i][j].rue == 6) {
                printf("   %c",  201);
            } else if (cartegeo[i][j].rue == 7) {
                printf("   %c", 203);
            } else if (cartegeo[i][j].rue == 9) {
                printf("%c%c%C%c",205,205,205,188);
            } else if (cartegeo[i][j].rue == 10) {
                printf("   %c",200);
            } else if (cartegeo[i][j].rue == 11) {
                printf("   %c", 202);
            } else if (cartegeo[i][j].rue == 13) {
                printf("   %c", 185);
            } else if (cartegeo[i][j].rue == 14) {
                printf("   %c", 204);
            } else if (cartegeo[i][j].rue == 15) {
                printf("%c%c%c%c", 205,205,205,206);
            } else {
                printf("    ");
            }
        }
        printf("\n");
    }
}
int rechercher_tache_demmarage_bus(int idBus,Bus flotteBus[], Horaire horaire) {
    int m, h,i,j;


             if (flotteBus[idBus].nombreTaches <= 0) {
        return -1;
    }

    for (i = 0; i < flotteBus[idBus].nombreTaches; i++) {

        if (flotteBus[idBus].taches[i].horaireDateDepart.jour == horaire.jour &&
            flotteBus[idBus].taches[i].horaireDateDepart.heure == horaire.heure &&
            flotteBus[idBus].taches[i].horaireDateDepart.minute == horaire.minute) {

            return flotteBus[idBus].taches[i].id;
        }
    }
    return -1;

        }


void deplacerBus(casecarte cartegeo[20][20],int idBusCourant ,Zone zones[], Ligne lignes[], Troncon troncons[], Bus flotteBus[], int nombreZones, int nombreLignes, int nombreTroncons, int nombreBus, Horaire horaireCourant) {
    int destination, r, c;



        printf("Deplacement du bus %d\n", idBusCourant);

        destination = -1;

        if (flotteBus[idBusCourant].sensCourant == 0) {
            printf("Sens du bus %d : aller\n", idBusCourant);

            for (int i = 0; i < lignes[flotteBus[idBusCourant].idLigneCourante].nombreZones; i++) {
                if (lignes[flotteBus[idBusCourant].idLigneCourante].idZones[i] == flotteBus[idBusCourant].idZoneCourante) {
                    if (i + 1 < lignes[flotteBus[idBusCourant].idLigneCourante].nombreZones) {
                        destination = lignes[flotteBus[idBusCourant].idLigneCourante].idZones[i + 1];
                        printf("Destination trouvee pour le bus %d : zone %d\n", idBusCourant, destination);
                    } else {
                        printf("Le bus %d est deja � la derniere zone de sa ligne.\n", idBusCourant);
                    }
                    break;
                }
            }

            if (destination != -1) {
                for (int j = 0; j < nombreTroncons; j++) {
                    if (troncons[j].idZoneSrc == flotteBus[idBusCourant].idZoneCourante && troncons[j].idZoneDest == destination) {
                        printf("Troncon trouvc pour le bus %d : %d -> %d\n", idBusCourant, troncons[j].idZoneSrc, troncons[j].idZoneDest);

                        int busDeplace = 0;


                        for (int i = 0; i < troncons[j].nombresubdivisions; i++) {
                            if (troncons[j].parcours[i].row == flotteBus[idBusCourant].row && troncons[j].parcours[i].column == flotteBus[idBusCourant].column) {
                                cartegeo[flotteBus[idBusCourant].row][flotteBus[idBusCourant].column].bus = -1;

                                if (i < troncons[j].nombresubdivisions - 1) {
                                    r = troncons[j].parcours[i + 1].row;
                                    c = troncons[j].parcours[i + 1].column;
                                } else {
                                    r = zones[troncons[j].idZoneDest].row;
                                    c = zones[troncons[j].idZoneDest].column;
                                    flotteBus[idBusCourant].idZoneCourante = destination;

                                    if (lignes[flotteBus[idBusCourant].idLigneCourante].idZones[lignes[flotteBus[idBusCourant].idLigneCourante].nombreZones - 1] == troncons[j].idZoneDest) {
                                        flotteBus[idBusCourant].enRoute = 0;
                                        printf("Le bus %d a termine sa ligne.\n", idBusCourant);
                                    }
                                }
                                flotteBus[idBusCourant].row = r;
                                flotteBus[idBusCourant].column = c;
                                cartegeo[r][c].bus = flotteBus[idBusCourant].id;
                                busDeplace = 1;
                                break;
                            }
                        }

                        if (!busDeplace) {
                            r = troncons[j].parcours[0].row;
                            c = troncons[j].parcours[0].column;
                            flotteBus[idBusCourant].row = r;
                            flotteBus[idBusCourant].column = c;
                            cartegeo[r][c].bus = flotteBus[idBusCourant].id;
                        }
                        break;
                    }
                }
            }

        } else if (flotteBus[idBusCourant].sensCourant == 1) {
            printf("Sens du bus %d : retour\n", idBusCourant);

            for (int i = lignes[flotteBus[idBusCourant].idLigneCourante].nombreZones - 1; i >= 0; i--) {
                if (lignes[flotteBus[idBusCourant].idLigneCourante].idZones[i] == flotteBus[idBusCourant].idZoneCourante) {
                    if (i - 1 >= 0) {
                        destination = lignes[flotteBus[idBusCourant].idLigneCourante].idZones[i - 1];
                        printf("Destination trouvee pour le bus %d : zone %d\n", idBusCourant, destination);
                    } else {
                        printf("Le bus %d est deja � la premiere zone de sa ligne.\n", idBusCourant);
                    }
                    break;
                }
            }

            if (destination != -1) {
                for (int j = 0; j < nombreTroncons; j++) {
                    if (troncons[j].idZoneDest == flotteBus[idBusCourant].idZoneCourante && troncons[j].idZoneSrc == destination) {
                        int busDeplace = 0;

                        for (int i = 0; i < troncons[j].nombresubdivisions; i++) {
                            if (troncons[j].parcours[i].row == flotteBus[idBusCourant].row && troncons[j].parcours[i].column == flotteBus[idBusCourant].column) {
                                cartegeo[flotteBus[idBusCourant].row][flotteBus[idBusCourant].column].bus = -1;

                                if (i > 0) {
                                    r = troncons[j].parcours[i - 1].row;
                                    c = troncons[j].parcours[i - 1].column;
                                } else {
                                    r = zones[troncons[j].idZoneSrc].row;
                                    c = zones[troncons[j].idZoneSrc].column;
                                    flotteBus[idBusCourant].idZoneCourante = destination;

                                    if (lignes[flotteBus[idBusCourant].idLigneCourante].idZones[0] == troncons[j].idZoneSrc) {
                                        flotteBus[idBusCourant].enRoute = 0;
                                        printf("Le bus %d a termine sa ligne.\n", idBusCourant);
                                    }
                                }
                                flotteBus[idBusCourant].row = r;
                                flotteBus[idBusCourant].column = c;
                                cartegeo[r][c].bus = flotteBus[idBusCourant].id;
                                busDeplace = 1;
                                break;
                            }
                        }

                        if (!busDeplace) {
                            r = troncons[j].parcours[troncons[j].nombresubdivisions - 1].row;
                            c = troncons[j].parcours[troncons[j].nombresubdivisions - 1].column;
                            flotteBus[idBusCourant].row = r;
                            flotteBus[idBusCourant].column = c;
                            cartegeo[r][c].bus = flotteBus[idBusCourant].id;
                        }
                        break;
                    }
                }
            }
        }

}

int rechercher_activites_personne(int cin, Personne personnes[], int nombrePersonnes, Horaire horaire) {
    for (int i = 0; i < nombrePersonnes; i++) {
        if (personnes[i].cin == cin) { // V�rifie que la personne correspond
            for (int j = 0; j < personnes[i].nombreActivites; j++) {
                Activite act = personnes[i].activites[j];
                if (act.horaireDateSouhaite.jour == horaire.jour &&
                    act.horaireDateSouhaite.heure == horaire.heure &&
                    act.horaireDateSouhaite.minute == horaire.minute) {
                    return personnes[i].intentionVoyage =1; // Retourne l'ID de l'activit� trouv�e
                }else {return personnes[i].intentionVoyage =0;}
            }
        }
    }
    return -1; // Retourne -1 si aucune activit� correspondante n'est trouv�e
}






void majPersonnesUneZone(Horaire horaireCourant, Zone zones[], int idZone, Ligne lignes[], int nombreLignes, Troncon troncons[], int nombreTroncons) {
    int i, j;


    for (i = 0; i < zones[idZone].nombrePersonnes; i++) {
        Personne pers = zones[idZone].personnes[i];
        for (j = 0; j < pers.nombreActivites; j++) {
            Activite act = pers.activites[j];
            if (act.horaireDateSouhaite.heure == horaireCourant.heure && act.horaireDateSouhaite.minute == horaireCourant.minute) {
                int idLigneTrouvee, idLigneCourante, sensCourant;
                rechercherLigneSens(act.idZoneSrc, act.idZoneDest, lignes, nombreLignes, &idLigneTrouvee, &idLigneCourante, &sensCourant);
                if (pers.idZoneCourante != act.idZoneDest) {
                    zones[act.idZoneDest].personnes[zones[act.idZoneDest].nombrePersonnes++] = pers;
                    zones[idZone].personnes[i].idLigneCourante = idLigneCourante;
                    zones[idZone].personnes[i].sensCourant = sensCourant;
                    zones[idZone].personnes[i].idZoneCourante = act.idZoneDest;
                    zones[idZone].personnes[i].intentionVoyage=1;
                    zones[idZone].nombrePersonnes--;

                }

                break;
            }
        }
    }
}

void majPersonnesToutesZones(Horaire horaireCourant, ListeLiaisons *l, Zone zones[], int nombreZones, Ligne lignes[], int nombreLignes, Troncon troncons[], int nombreTroncons) {
    int i;
    for (i = 0; i < nombreZones; i++) {
        majPersonnesUneZone(horaireCourant, zones, i, lignes, nombreLignes, troncons, nombreTroncons);
    }
}
void majCarteGeographique(Horaire horaireCourant, Zone zones[], int nombreZones, Ligne lignes[], int nombreLignes, Troncon troncons[], int nombreTroncons) {
    int i;

    for (i = 0; i < nombreZones; i++) {
        majPersonnesUneZone(horaireCourant, zones, i, lignes, nombreLignes, troncons, nombreTroncons);
    }

}

void deroulerSemaine(casecarte cartegeo[20][20], Ticket tickets[], Zone zones[], Ligne lignes[], Troncon troncons[], Bus flotteBus[], int nombreZones, int nombreLignes, int nombreTroncons, int nombreBus) {
    Horaire now;
    int m, h, j, k, i;
    ListeLiaisons l;
    initialiserCarte(cartegeo, zones, lignes, troncons, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus);

    for (j = 0; j < 7; j++) { // Pour chaque jour de la semaine
        for (h = 6; h < 22; h++) { // Heures de fonctionnement : 6h � 22h
            for (m = 0; m < 60; m++) { // Chaque minute
                now.jour = j;
                now.heure = h;
                now.minute = m;



                // Gestion des personnes, mise � jour des cartes et bus
                majPersonnesToutesZones(now, &l, zones, nombreZones, lignes, nombreLignes, troncons, nombreTroncons);
                afficherCarteGeo(cartegeo, zones, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus);

                // Gestion des bus
                for (i = 0; i < nombreBus; i++) {
                    if (flotteBus[i].enRoute == 0) { // Si le bus est stationn�
                        k = rechercher_tache_demmarage_bus(i, flotteBus, now);
                        if (k > -1) { // Si une t�che de d�marrage est trouv�e
                            flotteBus[i].enRoute = 1;
                            printf("Le bus %d d�marre � %02d:%02d\n", i, now.heure, now.minute);
                        }
                    }

                    if (flotteBus[i].enRoute == 1) { // Si le bus est en route
                        printf("Le bus %d est en route.\n", i);
                        deplacerBus(cartegeo, i, zones, lignes, troncons, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus, now);
                    }
                }

                // Gestion de la vitesse en fonction de l'entr�e utilisateur
                int vitesse = 1; // Par d�faut, passer une minute
                int iterations = 1; // Par d�faut, 1 it�ration
                char c;

                printf("Entrez la vitesse :\n");
                printf("1 - 1 minute, 2 - 10 minutes, 3 - 1 heure, 4 - 4 heures, 5 - 1 jour\n");
                scanf(" %c", &c);

                if (c == '1') {
                    vitesse = 1; // Passer une minute
                    iterations = 0;
                } else if (c == '2') {
                    vitesse = 1; // Passer 10 minutes
                    iterations = 10;
                } else if (c == '3') {
                    vitesse = 1; // Passer 1 heure
                    iterations = 60;
                } else if (c == '4') {
                    vitesse = 1; // Passer 4 heures
                    iterations = 240;
                } else if (c == '5') {
                    vitesse = 1; // Passer 1 jour
                    iterations = 1440;
                } else {
                    printf("Touche invalide, vitesse par d�faut : 1 minute.\n");
                }

                // Boucle en fonction de la vitesse
                for (int iter = 0; iter < iterations; iter++) {
                     printf("Temps actuel : Jour %d, %02d:%02d\n", now.jour, now.heure, now.minute);

                    now.minute += vitesse;

                    // Ajuster les heures et les jours si n�cessaire
                    while (now.minute >= 60) {
                        now.minute -= 60;
                        now.heure++;
                    }
                    while (now.heure >= 24) {
                        now.heure -= 24;
                        now.jour++;
                    }
                    while (now.jour >= 7) {
                        now.jour -= 7;
                    }

                    // Mettre � jour les op�rations n�cessaires
                    majPersonnesToutesZones(now, &l, zones, nombreZones, lignes, nombreLignes, troncons, nombreTroncons);
                    afficherCarteGeo(cartegeo, zones, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus);

                    for (i = 0; i < nombreBus; i++) {
                        if (flotteBus[i].enRoute == 0) {
                            k = rechercher_tache_demmarage_bus(i, flotteBus, now);
                            if (k > -1) {
                                flotteBus[i].enRoute = 1;
                                printf("Le bus %d d�marre � %02d:%02d\n", i, now.heure, now.minute);
                            }
                        }

                        if (flotteBus[i].enRoute == 1) {
                            printf("Le bus %d est en route.\n", i);
                            deplacerBus(cartegeo, i, zones, lignes, troncons, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus, now);
                        }
                    }
                }
            }
        }
    }
}


void embarquerPersonnes(Zone zones[], Bus flotteBus[], int idZone, int idBus, Horaire horaireCourant) {
    int zoneIndex = -1;
    int busIndex = -1;
    int busPlein = 0;
    int MAX_PERSONNES;
    int MAX_PASSAGERS;
    for (int i = 0; i < MAX_PERSONNES && zoneIndex == -1; i++) {
        if (zones[i].id == idZone) {
            zoneIndex = i;
        }
    }

    for (int i = 0; i < MAX_PERSONNES && busIndex == -1; i++) {
        if (flotteBus[i].id == idBus) {
            busIndex = i;
        }
    }
    if (zoneIndex != -1 && busIndex != -1) {
        if (flotteBus[busIndex].enRoute == 1) {
            for (int i = 0; i < zones[zoneIndex].nombrePersonnes; i++) {
                if (zones[zoneIndex].personnes[i].idZoneCourante == idZone &&
                    zones[zoneIndex].personnes[i].activites[0].horaireDateSouhaite.heure == horaireCourant.heure &&
                    zones[zoneIndex].personnes[i].activites[0].horaireDateSouhaite.minute == horaireCourant.minute) {
                    if (flotteBus[busIndex].nombrePassagers < MAX_PASSAGERS) {
                        flotteBus[busIndex].passagers[flotteBus[busIndex].nombrePassagers++] = zones[zoneIndex].personnes[i];
                        printf("Personne avec cin %d embarqu�e dans le bus %d.\n", zones[zoneIndex].personnes[i].cin, flotteBus[busIndex].id);
                    } else {
                        busPlein = 1;
                    }
                }
            }
            if (busPlein) {
                printf("Le bus est plein, impossible d'embarquer plus de passagers.\n");
            }
        } else {
            printf("Le bus n'est pas en route pour embarquer des passagers.\n");
        }
    } else {
        printf("Erreur : Zone ou bus introuvable.\n");
    }
}

void debarquerPersonnes(Zone zones[], Bus flotteBus[], int idZone, int idBus) {
    int zoneIndex = -1;
    int busIndex = -1;
    int MAX_PERSONNES;
    int MAX_PASSAGERS;
    for (int i = 0; i < MAX_PERSONNES && zoneIndex == -1; i++) {
        if (zones[i].id == idZone) {
            zoneIndex = i;
        }
    }
    for (int i = 0; i < MAX_PASSAGERS && busIndex == -1; i++) {
        if (flotteBus[i].id == idBus) {
            busIndex = i;
        }
    }
    if (zoneIndex != -1 && busIndex != -1) {
        for (int i = 0; i < flotteBus[busIndex].nombrePassagers; i++) {
            if (flotteBus[busIndex].passagers[i].idZoneDest == idZone) {
                for (int j = i; j < flotteBus[busIndex].nombrePassagers - 1; j++) {
                    flotteBus[busIndex].passagers[j] = flotteBus[busIndex].passagers[j + 1];
                }
                flotteBus[busIndex].nombrePassagers--;
                printf("Personne avec cin %d d�barqu�e de bus %d � la zone %d.\n", flotteBus[busIndex].passagers[i].cin, flotteBus[busIndex].id, idZone);
            }
        }
    } else {
        printf("Erreur : Zone ou bus introuvable.\n");
    }
}



int main ()
{
Zone zones[10];
Bus flotteBus[10];
int nombreBus;
char flotteBuSauv;
char zoneSauv,tronconSauv;
Troncon troncons[10];
int nombreTroncons;
    int nombreZones;
    int nombreLignes;
    Ligne lignes [10];
    char ligneSauv;
    char personneSauv;
    Ticket tickets [100];
    chargerZones(zones, &nombreZones);
    afficherZones(zones,nombreZones);
    sauvegarderZones(zones,nombreZones,&zoneSauv);
    chargerTroncons(troncons,&nombreTroncons);
    afficherTroncons(troncons, nombreTroncons);
    sauvegarderTroncons(troncons,nombreTroncons,&tronconSauv);
    chargerFlotteBus(flotteBus,&nombreBus);
    afficherFlotteBus(flotteBus,nombreBus);
    sauvegarderFlotteBus(flotteBus,nombreBus,&flotteBuSauv );
    chargerLignes(lignes,&nombreLignes);
    afficherLignes(lignes,nombreLignes);
    sauvegarderLignes(lignes,nombreLignes,&ligneSauv);
    genererPersonne(zones,nombreZones,  lignes, nombreLignes);
    afficherPersonnes(zones, nombreZones);
    sauvegarderPersonnes(zones,nombreZones,&personneSauv);
    chargerPersonnes( zones, &nombreZones,&personneSauv);
    casecarte cartegeo[20][20];
    initialiserCarte(cartegeo, zones, lignes, troncons, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus);
    afficherCarteGeo(cartegeo, zones, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus);
    deroulerSemaine(cartegeo, tickets, zones,  lignes,  troncons,  flotteBus, nombreZones,nombreLignes,  nombreTroncons,nombreBus);
    return 0;
}
