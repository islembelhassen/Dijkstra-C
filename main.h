#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<limits.h>


#define INFINI INT_MAX
#define NBR_STATIONS 304
#define MAX_LIGNES 16


typedef struct {
    char* nom;
    int* destination;
    int* ligne;
    int nb_voisins;
} station;

typedef struct {
    int station;
    int ligne;
    int distance;
}noeud;

typedef struct {
    noeud* donnee;
    int taille;

}heap;

typedef struct {
    int station;
    int ligne;
    int distance;
}etat;


heap* creer_heap(int taille) ;


void push_heap(heap* h , noeud n);


noeud pop_heap(heap* h);


void free_heap(heap* h);

void dijkstra(station* liste_des_stations, int origine, int destination);

void creer_liste_des_stations(char* nom_fichier[], station* liste_des_stations);



void free_liste_des_stations(station* liste_des_stations);

void afficher_stations(station* liste);


void menu(station* liste_des_stations) ;













