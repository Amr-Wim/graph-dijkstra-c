#include <stdio.h>
#include <stdlib.h>

#define Infini 9999   // Constante pour representer une distance infinie (pour Dijkstra)

/*----------------------------------------------------------
                Structures du graphe
-----------------------------------------------------------*/

typedef struct noeud {
    int info;           // Identifiant du noeud
    struct noeud *suc;  // Pointeur vers le noeud suivant
} noeud;

typedef struct arc {
    struct noeud *S;    // Source
    struct noeud *D;    // Destination
    int val;            // Poids de l'arc
    struct arc *suc;    // Pointeur vers l'arc suivant
} arc;

typedef struct graphe {
    noeud *LN;   // Tete de la liste des noeuds
    arc *LA;     // Tete de la liste des arcs
} Graphe;

/*----------------------------------------------------------
   Structure pour l'algorithme de Dijkstra
-----------------------------------------------------------*/

typedef struct STR_chemin {
    noeud *Dest;        // Noeud destination
    noeud *Interm;      // Predecesseur
    int etat;           // 0 = provisoire, 1 = finalise
    int c;              // Cout depuis la source
    struct STR_chemin *suc;
} cheminDijkstra;

typedef cheminDijkstra* listeDijkstra;

/*----------------------------------------------------------
   Fonctions Dijkstra
-----------------------------------------------------------*/

void insererNoeudDijkstra(noeud *N, int infoS, Graphe G, listeDijkstra *L){
    arc *Q;
    listeDijkstra P, R;

    // 1. Crée un nouvel élément de la liste Dijkstra pour ce noeud
    P = (cheminDijkstra*)malloc(sizeof(cheminDijkstra));
    P->Dest = N;
    P->Interm = N;
    P->suc = NULL;

    // 2. Initialisation selon que le noeud est la source ou non
    if(N->info == infoS){
        P->etat = 1;   // Source : distance finalisée
        P->c = 0;      // Distance = 0
    } else {
        P->etat = 0;   // Autres noeuds : provisoire
        P->c = Infini; // Distance inconnue au départ
    }

    // 3. Vérifie si la source a un arc direct vers ce noeud
    Q = G.LA;
    while(Q != NULL && !(Q->S->info == infoS && Q->D == N))
        Q = Q->suc;

    // Si un arc direct existe, on initialise le prédécesseur et la distance
    if(Q != NULL){
        P->Interm = Q->S;
        P->c = Q->val;
    }

    // 4. Insertion à la fin de la liste Dijkstra
    if(*L == NULL){
        *L = P;
    } else {
        R = *L;
        while(R->suc != NULL)
            R = R->suc;
        R->suc = P;
    }
}


listeDijkstra RechercherW(listeDijkstra L){
    int min = Infini;         // On initialise la distance minimale à "Infini"
    listeDijkstra W = NULL;   // Pointeur qui contiendra le noeud provisoire le plus proche

    // Parcours de toute la liste Dijkstra
    while(L != NULL){
        // Si le noeud est provisoire (etat == 0) et que sa distance est plus petite que la distance minimale trouvée
        if(L->etat == 0 && L->c < min){
            min = L->c;   // On met à jour la distance minimale
            W = L;        // On mémorise ce noeud comme le plus proche pour l'instant
        }
        L = L->suc;      // Passage au noeud suivant dans la liste
    }

    // Retourne le noeud provisoire ayant la plus petite distance depuis la source
    // Si aucun noeud provisoire n'existe (tous finalisés), W restera NULL
    return W;
}


void Dijkstra(Graphe G, int infoS, listeDijkstra *L){
    noeud *N = G.LN;         // Pointeur pour parcourir tous les noeuds du graphe
    listeDijkstra W;          // Pointeur pour le noeud provisoire choisi à chaque étape
    *L = NULL;                // Initialisation de la liste Dijkstra vide

    // -----------------------------
    // 1 Initialisation de la liste Dijkstra
    // -----------------------------
    // On parcourt tous les noeuds du graphe et on les ajoute à la liste Dijkstra
    while(N != NULL){
        insererNoeudDijkstra(N, infoS, G, L);  // Initialise chaque noeud (distance, état, prédécesseur)
        N = N->suc;
    }

    // -----------------------------
    // 2 Boucle principale de Dijkstra
    // -----------------------------
    do {
        // Cherche le noeud provisoire ayant la plus petite distance depuis la source
        W = RechercherW(*L);  
        if(W == NULL) break;  // Si aucun noeud provisoire restant, on a fini
        W->etat = 1;          // Finalise ce noeud : la distance minimale est désormais définitive

        // Parcourt tous les arcs du graphe pour mettre à jour les voisins de W
        arc *Q = G.LA;
        while(Q != NULL){
            // Si l'arc part du noeud finalisé W vers un voisin V
            if(Q->S == W->Dest){
                listeDijkstra V = *L;  // Parcourt la liste Dijkstra pour trouver le voisin
                while(V != NULL){
                    // Si V est le noeud destination et est encore provisoire
                    if(V->Dest == Q->D && V->etat == 0){
                        int nv = W->c + Q->val;  // Distance potentielle via W
                        // Si ce chemin est meilleur que la distance actuelle de V
                        if(nv < V->c){
                            V->c = nv;            // Met à jour la distance minimale
                            V->Interm = W->Dest;  // Met à jour le prédécesseur
                        }
                    }
                    V = V->suc;
                }
            }
            Q = Q->suc;  // Passe à l'arc suivant
        }
    } while(W != NULL);  // Répète jusqu'à ce qu'il n'y ait plus de noeuds provisoires
}


void afficherDijkstraFichier(int infoS, int infoD, listeDijkstra L, FILE *fout){
    listeDijkstra node = L;

    // Cherche dans la liste Dijkstra le noeud destination
    while(node != NULL && node->Dest->info != infoD)
        node = node->suc;

    // Si le noeud n'existe pas ou s'il est inaccessible
    if(node == NULL || node->c == Infini){
        fprintf(fout, "Pas de chemin de %d a %d\n", infoS, infoD);
        return;
    }

    int chemin[100];  // Tableau pour stocker le chemin inversé
    int idx = 0;
    listeDijkstra tmp = node;

    // Remonte les prédécesseurs pour reconstruire le chemin
    while(tmp->Dest->info != infoS){
        chemin[idx++] = tmp->Dest->info;

        listeDijkstra prev = L;
        // Cherche le prédécesseur du noeud courant
        while(prev != NULL && prev->Dest != tmp->Interm)
            prev = prev->suc;
        tmp = prev;
    }
    chemin[idx++] = infoS;  // Ajoute la source à la fin

    // Écrit le chemin et la distance totale dans le fichier
    fprintf(fout, "Chemin de %d a %d (distance=%d) : ", infoS, infoD, node->c);
    int i;
    for(i = idx-1; i >= 0; i--){
        fprintf(fout, "%d", chemin[i]);
        if(i != 0) fprintf(fout, " -> ");
    }
    fprintf(fout, "\n");
}


/*----------------------------------------------------------
               Lecture du fichier input.txt
-----------------------------------------------------------*/

Graphe lireFichier(const char *filename, int *source){
    FILE *f = fopen(filename, "r");
    if(!f){
        printf("Erreur ouverture fichier input\n");
        exit(1);
    }

    // Lecture de la source (premier nombre du fichier)
    if(fscanf(f, "%d", source) != 1){
        printf("Erreur lecture source\n");
        exit(1);
    }

    int s, d, w;
    int maxNoeud = *source;  // commencer par la source
    int arcCount = 0;

    // Compter les arcs et le plus grand indice de noeud
    while(fscanf(f, "%d %d %d", &s, &d, &w) == 3){
        if(s > maxNoeud) maxNoeud = s;
        if(d > maxNoeud) maxNoeud = d;
        arcCount++;
    }

    int n = maxNoeud + 1;
    int m = arcCount;

    // Allocation des noeuds
    noeud *tab = malloc(n * sizeof(noeud));
    int i;
    for(i = 0; i < n; i++){
        tab[i].info = i;
        tab[i].suc = (i < n-1) ? &tab[i+1] : NULL;
    }

    // Retour au debut du fichier et ignorer la source
    rewind(f);
    fscanf(f, "%*d");  // sauter la source

    // Lecture des arcs
    arc *head = NULL, *tail = NULL;
    for(i = 0; i < m; i++){
        if(fscanf(f, "%d %d %d", &s, &d, &w) != 3){
            printf("Erreur lecture arc ligne %d\n", i+1);
            exit(1);
        }
        arc *A = malloc(sizeof(arc));
        A->S = &tab[s];
        A->D = &tab[d];
        A->val = w;
        A->suc = NULL;

        if(head == NULL){
            head = tail = A;
        } else {
            tail->suc = A;
            tail = A;
        }
    }

    fclose(f);

    Graphe G;
    G.LN = &tab[0];
    G.LA = head;

    return G;
}


/*----------------------------------------------------------
                           MAIN
-----------------------------------------------------------*/

int main(){
    int source;

    Graphe G = lireFichier("input.txt", &source);

    listeDijkstra L = NULL;

    Dijkstra(G, source, &L);

    FILE *fout = fopen("output.txt", "w");

    noeud *target = G.LN;
    while(target != NULL){
        afficherDijkstraFichier(source, target->info, L, fout);
        target = target->suc;
    }

    fclose(fout);

    printf("Resultats ecrits dans output.txt\n");
    return 0;
}

