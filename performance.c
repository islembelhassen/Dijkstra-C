#include "main.h"

int main ()
{ 
    station* liste_des_stations = calloc(NBR_STATIONS , sizeof(station));
    creer_liste_des_stations((char* []){"Fichiers/noeuds.csv","Fichiers/arretes.csv"}, liste_des_stations);

    dijkstra(liste_des_stations, 2, 14);

    free_liste_des_stations(liste_des_stations);

    return 0;
}