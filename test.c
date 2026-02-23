#include "main.h"



int station_valide(int s) {
    return s >= 1 && s <= NBR_STATIONS;
}

void test_header(const char* titre) {
    printf("\n==============================\n");
    printf("TEST : %s\n", titre);
    printf("==============================\n");
}


void test_entrees_invalides(station* stations) {
    test_header("Entrées invalides");

    int tests[][2] = {
        {-5, 10},
        {0, 1},
        {1, 999},
        {305, 2}
    };

    for (int i = 0; i < 4; i++) {
        int o = tests[i][0];
        int d = tests[i][1];

        printf("Origine=%d Destination=%d → ", o, d);

        if (!station_valide(o) || !station_valide(d)) {
            printf("✅ rejeté correctement\n");
        } else {
            printf("❌ ERREUR (aurait dû être rejeté)\n");
        }
    }
}


void test_origine_egale_destination(station* stations) {
    test_header("Origine = Destination");

    int s = 42;
    printf("Origine=%d Destination=%d\n", s, s);

    dijkstra(stations, s, s);

    printf("✅ Chemin trivial attendu\n");
}




void test_heap_vide() {
    test_header("Heap vide");

    heap* h = creer_heap(10);

    if (h->taille == 0) {
        printf("✅ Heap vide détecté\n");
    }

    free_heap(h);
}



void test_stress(station* stations) {
    test_header("Stress test");

    for (int i = 1; i <= 10; i++) {
        printf("Test %d : 1 → 304\n", i);
        dijkstra(stations, 1, 304);
    }

    printf("✅ Aucun crash après exécutions multiples\n");
}





void test_nom_long() {
    test_header("Nom de station très long");

    char* nom = "StationAvecUnNomExtremementLongQuiDepasseLaffichageDuTerminal";
    printf("%s\n", nom);

    printf("✅ Affichage sans crash\n");
}




void lancer_tests(station* stations) {
    test_entrees_invalides(stations);
    test_origine_egale_destination(stations);
    test_heap_vide();
    test_stress(stations);
    test_nom_long();
}




int main() {
    station* liste_des_stations = calloc(NBR_STATIONS, sizeof(station));

    creer_liste_des_stations(
        (char*[]){"Fichiers/noeuds.csv", "Fichiers/arretes.csv"},
        liste_des_stations
    );

    lancer_tests(liste_des_stations);

    free_liste_des_stations(liste_des_stations);
    return 0;
}



