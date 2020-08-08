#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "main.h"
#include "pathfinding.h"

void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void CreateGalaxie(Systeme galaxie[TAILLE][TAILLE]){
    int i = 0, j = 0, k = 0;

    while(i < TAILLE){
        while(j < TAILLE){
            galaxie[j][i].x = (j + 1) * 10;
            galaxie[j][i].y = (i + 1) * 10;
            if(((i - 1 >= 0) && (i - 1 <= TAILLE)))
                galaxie[j][i].hyperlane1 = k - TAILLE;
            if(((j - 1 >= 0) && (j - 1 <= TAILLE)))
                galaxie[j][i].hyperlane2 = k - 1;
            if((j - 1 >= 0) && (j - 1 < TAILLE))
                galaxie[j - 1][i].hyperlane3 = k;
            if((i - 1 >= 0) && (i - 1 < TAILLE))
            galaxie[j][i - 1].hyperlane4 = k;
            j++;
            k++;
        }
        j = 0;
        i++;
    }



}

int main()
{
    Systeme galaxie[TAILLE][TAILLE];
    //NodeArray *array = NULL;
    int path[50] = {0};
    int i = 0, j = 0, k = 0, l = 0;
    int debut = 5, fin = 60;
    scanf("%d", &debut);
    scanf("%d", &fin);
    memset(galaxie, 0, sizeof(galaxie));

    CreateGalaxie(galaxie);

    PathFinding(galaxie, path, debut, fin);

    i = 0;
    j = 0;
    k = 0;
    l = 0;
    while(i < TAILLE){
        while(j < TAILLE){
            Color(15, 0);
            l = 0;
            if(k == debut) {
                Color(6, 0);
            } else if(k == fin) {
                Color(4, 0);
            } else {
                while(l < 50){
                    if((k == path[l]) && (k != 0))
                        Color(3, 0);
                    l++;
                }
            }
            if(k < 10)
                printf("%d  ", k);
            else
                printf("%d ", k);
            j++;
            k++;
        }
        printf("\n");
        j = 0;
        i++;
    }

    return 0;
}
