#include "main.h"



heap* creer_heap(int taille) {
    heap* h = malloc(sizeof(heap));
    h->donnee = malloc(taille * sizeof(noeud));
    h->taille = 0;
    return h;
}


void push_heap(heap* h , noeud n){
    int compteur=h->taille++;
    h->donnee[compteur]=n;

    while(compteur>0){
        int parent=(compteur-1)/2;
        if(h->donnee[parent].distance > h->donnee[compteur].distance){
            noeud temp=h->donnee[parent];
            h->donnee[parent]=h->donnee[compteur];
            h->donnee[compteur]=temp;
            compteur=parent;
        }
        else{
            break;
        }
    }
}


noeud pop_heap(heap* h){
    noeud min=h->donnee[0];
    h->donnee[0]=h->donnee[h->taille-1];
    h->taille--;

    int compteur=0;
    while(1){
        int gauche=2*compteur +1;
        int droite=2*compteur +2;
        int plus_petit=compteur;
        if(gauche < h->taille && h->donnee[gauche].distance < h->donnee[plus_petit].distance){
            plus_petit=gauche;
        }
        if(droite < h->taille && h->donnee[droite].distance < h->donnee[plus_petit].distance){
            plus_petit=droite;
        }
        if(plus_petit != compteur){
                noeud temp=h->donnee[compteur];
                h->donnee[compteur]=h->donnee[plus_petit];
                h->donnee[plus_petit]=temp;
                compteur=plus_petit;
            }
        else{
            break;
        }
    }
    return min;
}


void free_heap(heap* h) {
    free(h->donnee);
    free(h);
}

void dijkstra(station* liste_des_stations, int origine, int destination)
{   
    
    if(origine == destination){
        printf("🚶‍♂️ Vous êtes déjà à votre destination !\n");
        return;
    }

    if(origine < 1 || origine > NBR_STATIONS || destination < 1 || destination > NBR_STATIONS){
        printf("❌ Numéro de station invalide. Veuillez réessayer.\n");
        printf("\n⏱ Temps total : 0 minutes\n");
        return;
    }
    
    int distances[NBR_STATIONS][MAX_LIGNES];
    int prede_station[NBR_STATIONS][MAX_LIGNES];
    int prede_ligne[NBR_STATIONS][MAX_LIGNES];

    for (int i = 0; i < NBR_STATIONS; i++) {
        for (int j = 0; j < MAX_LIGNES; j++) {
            distances[i][j] = INFINI;
            prede_station[i][j] = -1;
            prede_ligne[i][j] = -1;
        }
    }
   
    for (int i = 0; i < MAX_LIGNES; i++) {
        distances[origine-1][i] = 0;
    }

    heap* h = creer_heap(NBR_STATIONS*MAX_LIGNES);
    push_heap(h, (noeud){origine-1, -1, 0});

    while (h->taille > 0) {
        noeud courant = pop_heap(h);

        if (courant.ligne != -1  && courant.distance > distances[courant.station][courant.ligne]) continue;

        
        station s = liste_des_stations[courant.station];
        for (int i = 0; i < s.nb_voisins; i++) {
            
            int cout;  // coût de déplacement
            if (courant.ligne == -1 || courant.ligne == s.ligne[i]) 
                cout= 1; 
            else
               cout = 6; // pénalité pour changement de ligne

            int nouvelle_distance = courant.distance + cout;

            if(nouvelle_distance < distances[s.destination[i]][s.ligne[i]]) {
                distances[s.destination[i]][s.ligne[i]] = nouvelle_distance;
                prede_station[s.destination[i]][s.ligne[i]] = courant.station;
                prede_ligne[s.destination[i]][s.ligne[i]] = courant.ligne;
                push_heap(h, (noeud){s.destination[i], s.ligne[i], nouvelle_distance});
            }

        }
    }

   int meilleur_ligne=-1;
   int meilleur_distance=INFINI;
    for(int i=0; i<MAX_LIGNES; i++){
          if(distances[destination-1][i] < meilleur_distance){
                meilleur_distance=distances[destination-1][i];
                meilleur_ligne=i;
          }
    }

    etat chemin[1000];
    int taille=0;
    int station_courant=destination-1;
    int ligne_courant=meilleur_ligne;
    while(station_courant != -1 ){
        chemin[taille++] = (etat){station_courant, ligne_courant};
        int temp_station=prede_station[station_courant][ligne_courant];
        int temp_ligne=prede_ligne[station_courant][ligne_courant];
        station_courant=temp_station;
        ligne_courant=temp_ligne;
    }



    printf("\n🚇 Chemin optimal :\n");

    for (int i = taille - 1; i > 0; i--) {
        printf("%s\n", liste_des_stations[chemin[i].station].nom);

        if (chemin[i].ligne != chemin[i-1].ligne && chemin[i].ligne != -1) {
            printf("   ⤷ Correspondance (vers Ligne %d)\n", chemin[i-1].ligne);
        } else {
            printf("   ⤷ Ligne %d\n", chemin[i-1].ligne);
        }
    }
    printf("%s\n", liste_des_stations[chemin[0].station].nom);
    printf("\n⏱ Temps total : %d minutes\n", meilleur_distance);


    


   
   free_heap(h);
    
} 


void creer_liste_des_stations(char* nom_fichier[], station* liste_des_stations)
{
    FILE* fp = fopen(nom_fichier[0], "r");

    if (!fp){
        printf("Can't open file\n");
        exit(1);
    }

    else {
        char buffer[1024];
        int index = 0;

        fgets(buffer, 1024, fp); // sauter l'en-tête

        while (fgets(buffer, 1024, fp) && index < NBR_STATIONS) {
            char* value = strtok(buffer, ",\n");
            
            if(value) {
                liste_des_stations[index].nom = strdup(value);
                liste_des_stations[index].destination = NULL;
                liste_des_stations[index].ligne = NULL;
                liste_des_stations[index].nb_voisins = 0;
                index++;

            }
        }
        fclose(fp);

    }


    fp = fopen(nom_fichier[1], "r");

    if (!fp){
        printf("Can't open file\n");
        exit(1);
    }

    else {
        char buffer[1024];
        int index = 0;

        fgets(buffer, 1024, fp); // sauter l'en-tête

        while (fgets(buffer, 1024, fp) && index < NBR_STATIONS) {
                    
        
            int origine, dest, ligne;
            if (sscanf(buffer, "%d,%d,%d", &origine, &dest, &ligne) != 3)
                continue;

            station* s = &liste_des_stations[origine-1];
            s->destination = realloc(s->destination, (s->nb_voisins + 1) * sizeof(int));
            s->ligne       = realloc(s->ligne,       (s->nb_voisins + 1) * sizeof(int));

            if (!s->destination || !s->ligne) {
                perror("Erreur realloc");
                exit(EXIT_FAILURE);
            }

            // ajouter les données
            s->destination[s->nb_voisins] = dest-1;
            s->ligne[s->nb_voisins] = ligne;
            s->nb_voisins++;
            
        
        }
        fclose(fp);

    }
    
       
}



void free_liste_des_stations(station* liste_des_stations)
{
    for (int i = 0; i < NBR_STATIONS; i++) {
        free(liste_des_stations[i].nom);
        free(liste_des_stations[i].destination);
        free(liste_des_stations[i].ligne);
    }
    free(liste_des_stations);
}

void afficher_stations(station* liste) {
    for (int i = 0; i < NBR_STATIONS; i++) {
        printf("%3d - %s\n", i + 1, liste[i].nom);
    }
}


void menu(station* liste_des_stations) {
    int choix;
    int origine = -1, destination = -1;

    do {
        printf("\n========================================\n");
        printf(" 🚇  SYSTÈME DE NAVIGATION MÉTRO\n");
        printf("========================================\n");
        printf("1 - Afficher la liste des stations\n");
        printf("2 - Choisir la station de départ\n");
        printf("3 - Choisir la station d'arrivée\n");
        printf("4 - afficher le chemin optimal\n");
        printf("0 - Quitter\n");
        printf("========================================\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                afficher_stations(liste_des_stations);
                break;

            case 2:
                printf("Entrez le numéro de la station de départ : ");
                scanf("%d", &origine);
                break;

            case 3:
                printf("Entrez le numéro de la station d'arrivée : ");
                scanf("%d", &destination);
                break;

            case 4:
                if (origine < 1 || origine > NBR_STATIONS || destination < 1 || destination > NBR_STATIONS) {
                    printf("❌ Veuillez choisir des stations valides.\n");
                } else {
                    printf("🔍 Calcul du chemin optimal de %s à %s...\n", liste_des_stations[origine-1].nom, liste_des_stations[destination-1].nom);
                    dijkstra(liste_des_stations, origine, destination);
                }
                break;

            case 0:
                printf("👋 merci pour votre confiance.\n");
                break;

            default:
                printf("❌ Choix invalide.\n");
        }

    } while (choix != 0);
}



int main ()
{ 
    station* liste_des_stations = calloc(NBR_STATIONS , sizeof(station));
    creer_liste_des_stations((char* []){"Fichiers/noeuds.csv","Fichiers/arretes.csv"}, liste_des_stations);

    char buffer[1024];
    FILE* fp = fopen("Fichiers/fun.txt", "r");
    while ( ! feof( fp ) ) {
        fputc( fgetc( fp ), stdout );
    }

    menu(liste_des_stations);

    fseek(fp, 0, SEEK_SET); 
     while ( ! feof( fp ) ) {
        fputc( fgetc( fp ), stdout );
    }
    fclose(fp);
    

    free_liste_des_stations(liste_des_stations);

    return 0;
}
    











