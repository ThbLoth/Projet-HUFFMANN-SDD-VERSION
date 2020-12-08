#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED

// liste contenant chaqeu caractère d'un texte
// ainsi que son nombre d'occurrence
typedef struct node
{
	int lettre;
    int nb_occ;
	struct node *succ;
} node;

typedef node * list;

// Liste qui va contenir les suites binaires des caracactères du texte
// a partir de l'arbre de huffman
typedef struct list_binaire
{
    int code;
    struct list_binaire* succ;
}list_binaire;

// arbre qui va contenir chaque caractère nouveau du texte
//ainsi que son nombre d'occurrence
typedef struct tree_node
{
	int lettre;	// le champ de données
    int nb_occ;
	struct tree_node *left, *right; // les références vers les deux fils
}tree_node;

typedef tree_node * arbre;

// liste d'arbre qui va aider à la création de l'arbre de huffman
typedef struct tree_array
{
    struct tree_node* data;
    struct tree_array* next;
}tree_array;

//Prototypes des fonctions

void Conversion(FILE*);
void CompteCarac(void);
list creation_liste_occ(int,int);
void nb_Occurrences(list*);
arbre creation_noeud(int,int);
tree_array* creation_elem_noeud(int,int);
tree_array* creation_liste_arbre(node*);
arbre arbre_huffman(tree_array*);
void affichage_arbre(arbre);
list_binaire* Creation_liste_binaire(int,list_binaire*);
list_binaire* suppression_derniere_val(list_binaire*);
void Creation_Dico(arbre,list_binaire*);
void encodage(void);
void encodage_huffman(void);

#endif // HUFFMAN_H_INCLUDED
