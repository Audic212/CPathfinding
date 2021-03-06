#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "main.h"
#include "pathfinding.h"


NodeArray *CreateNodeArray(){
    NodeArray *array = NULL;
    array = calloc(1, sizeof(NodeArray));
    array->firstNode = NULL;
    return array;
}

void DestroyNodeArray(NodeArray *array){
    Node *actual_node = array->firstNode;
    Node *precedent_node = NULL;
    while(actual_node != NULL){
        precedent_node = actual_node;
        actual_node = actual_node->suivant;
        free(precedent_node);
    }
    free(array);
}

Node* CreateNode(NodeArray *array){
    Node *node = NULL;
    if(array->firstNode == NULL){
        array->firstNode = calloc(1, sizeof(Node));
        node = array->firstNode;
    } else {
        node = array->firstNode;
        while(node->suivant != NULL){
            node = node->suivant;
        }
        node->suivant = calloc(1, sizeof(Node));
        node = node->suivant;
    }
    node->suivant = NULL;
    return node;
}

void DestroyNode(NodeArray *array, int place){
    Node *node = NULL;
    Node *precedent_node = NULL;
    int index = 0;
    node = array->firstNode;

    if(place == 0){
        array->firstNode = node->suivant;

        free(node);
    } else {
        while((node->suivant != NULL) && (index < place)){
            precedent_node = node;
            node = node->suivant;
            index++;
        }
        precedent_node->suivant = node->suivant;
        free(node);
    }
}

Node* NodeNumber(NodeArray *array, int number){
    Node *node = NULL;
    int index = 0;
    node = array->firstNode;
    while((index < number) && (node->suivant != NULL)){
        node = node->suivant;
        index++;
    }
    return node;
}

int ArraySize(NodeArray *array){
    Node *node = NULL;
    int index = 0;
    node = array->firstNode;
    while((node != NULL) && (index < 100)){
        node = node->suivant;
        index++;
    }
    return index;
}

Node* CopyNode(Node *destination, Node *source){
    Node *node;
    node = destination->suivant;
    memcpy(destination, source, sizeof(Node));
    destination->suivant = node;
    return destination;
}

void ReverseArray(int array[], int size){
    int *aux = NULL, i = 0, j = size - 1;
    aux = calloc(1, size * sizeof(int));
    while(i < size){
        aux[j] = array[i];
        j--;
        i++;
    }
    i = 0;
    j = 0;
    while(aux[j] == 0){
        j++;
    }
    while(j < size){
        array[i] = aux[j];
        i++;
        j++;
    }
}

void PathFinding(Systeme galaxie[TAILLE][TAILLE], int path[20], int debut, int fin){
    NodeArray *listeOuverte = NULL;
    NodeArray *listeFermee = NULL;
    NodeArray *listeEnfants = NULL;
    Node *depart = malloc(sizeof(Node));
    Node *arrivee = malloc(sizeof(Node));
    Node *current_node = NULL;
    Node *temporary_node = NULL;
    Node *children = NULL;

    int index = 0, current_index = 0, children_index = 0;
    int enfant[4], parent;

    //printf("%d -> %d\n\n", debut, fin);


    depart->x = galaxie[debut / TAILLE][debut - (debut / TAILLE) * TAILLE].x;
    depart->y = galaxie[debut / TAILLE][debut - (debut / TAILLE) * TAILLE].y;
    depart->g = 0;
    depart->h = 0;
    depart->f = 0;
    depart->numero = debut;
    depart->suivant = NULL;
    depart->parent = 0;

    arrivee->x = galaxie[fin / TAILLE][fin - (fin / TAILLE) * TAILLE].x;
    arrivee->y = galaxie[fin / TAILLE][fin - (fin / TAILLE) * TAILLE].y;
    arrivee->g = 0;
    arrivee->h = 0;
    arrivee->f = 0;
    arrivee->numero = fin;

    memset(path, 0, sizeof(int) * 50);

    listeOuverte = CreateNodeArray();
    listeFermee = CreateNodeArray();
    listeEnfants = CreateNodeArray();
    CopyNode(CreateNode(listeOuverte), depart);

    while(ArraySize(listeOuverte) > 0){
        //printf("\n%d ", ArraySize(listeOuverte));
        current_node = listeOuverte->firstNode;
        current_index = 0;
        index = 0;

        //recupere l'element le plus petit
        while(index < ArraySize(listeOuverte)){
            temporary_node = NodeNumber(listeOuverte, index);
            if(current_node->f > temporary_node->f){
                current_node = temporary_node;
                current_index = index;
            }
            index++;
        }
        //printf("node:%d, x:%d, y:%d, f:%d, g:%d, h:%d, parent:%d", current_node->numero, current_node->x, current_node->y, current_node->f, current_node->g, current_node->h, current_node->parent);

        current_node = CopyNode(CreateNode(listeFermee), current_node);
        DestroyNode(listeOuverte, current_index);

        DestroyNodeArray(listeEnfants);
        listeEnfants = CreateNodeArray();

        //�cire resultat
        if(current_node->numero == fin){
                printf("\n");
                current_index = 1;
                path[0] = fin;
                while(current_node->numero != debut){
                    path[current_index] = current_node->parent;
                    parent = current_node->parent;
                   // printf("%d ", current_node->parent);
                    index = 0;
                    while((current_node->numero != parent) && (index < 100)){
                        current_node = NodeNumber(listeFermee, index);
                        index++;
                    }
                    current_index++;
                }
                while(current_index < 50){
                    path[current_index] = 0;
                    //printf("%d ", 0);
                    current_index++;
                }
                printf("\n");
                ReverseArray(path, 20);
                return;
        }

        memset(enfant, 0, sizeof(int) * 4);
        children_index = 0;
        while(children_index < 4){
            enfant[children_index] = current_node->numero;
            switch(children_index){
            case 0:
                index = galaxie[current_node->numero - (current_node->numero / TAILLE) * TAILLE][current_node->numero / TAILLE].hyperlane1;
                break;
            case 1:
                index = galaxie[current_node->numero - (current_node->numero / TAILLE) * TAILLE][current_node->numero / TAILLE].hyperlane2;
                break;
            case 2:
                index = galaxie[current_node->numero - (current_node->numero / TAILLE) * TAILLE][current_node->numero / TAILLE].hyperlane3;
                break;
            case 3:
                index = galaxie[current_node->numero - (current_node->numero / TAILLE) * TAILLE][current_node->numero / TAILLE].hyperlane4;
                break;
            }
            if(index != 0){
                children = CreateNode(listeEnfants);
                children->numero = index;
                children->x = galaxie[index / TAILLE][index - (index / TAILLE) * TAILLE].x;
                children->y = galaxie[index / TAILLE][index - (index / TAILLE) * TAILLE].y;
                children->parent = current_node->numero;
            }
            children_index++;
        }

        children_index = 0;
        index = 0;
        while(children_index < ArraySize(listeEnfants)){
            while(index < ArraySize(listeFermee)){
                if(NodeNumber(listeEnfants, children_index)->numero == NodeNumber(listeFermee, index)->numero){
                    goto finBoucleEnfants;
                }
                index++;
            }

            NodeNumber(listeEnfants, children_index)->g = current_node->g + 1;
            NodeNumber(listeEnfants, children_index)->h = pow(NodeNumber(listeEnfants, children_index)->x - arrivee->x, 2.0) + pow(NodeNumber(listeEnfants, children_index)->y - arrivee->y, 2.0);
            NodeNumber(listeEnfants, children_index)->f = NodeNumber(listeEnfants, children_index)->g + NodeNumber(listeEnfants, children_index)->h;

            index = 0;
            while(index < ArraySize(listeOuverte)){
                if(NodeNumber(listeEnfants, children_index)->numero == NodeNumber(listeOuverte, index)->numero){
                       if(NodeNumber(listeEnfants, children_index)->g > NodeNumber(listeOuverte, index)->g){
                            goto finBoucleEnfants;
                        }
                }
                index++;
            }
            //printf("\n  enfant:%d h:%d, g:%d, f:%d", NodeNumber(listeEnfants, children_index)->numero, NodeNumber(listeEnfants, children_index)->h, NodeNumber(listeEnfants, children_index)->g, NodeNumber(listeEnfants, children_index)->f);
            CopyNode(CreateNode(listeOuverte), NodeNumber(listeEnfants, children_index));
            finBoucleEnfants:
            children_index++;
        }
        //printf("\n");
    }
}
