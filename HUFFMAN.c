#include <stdlib.h>
#include <stdio.h>

// fonction qui convertit le texte en une liste binaire
// en fonction du code ASCII
void Conversion(FILE * fic)
{
    FILE * fout;
    int carac;
    int bin = 128;
	fout = fopen("binary.txt","w");

	if (fic == NULL)
	{
        perror("Fichier d'origine illisible");
		exit(-1);
	}

	if (fout  == NULL)
	{
        perror("Fichier de sortie illisible");
		exit(-1);
	}

    while ((carac = fgetc(fic)) != EOF)
    {
        while(carac > -1)
        {
            fprintf(fout,"%d",carac/bin);

            if(carac>=bin)
            {
                carac = carac - bin;
            }

            bin = bin/2;

            if (bin == 0)
            {
                break;
            }
        }

        bin = 128;
    }

    fclose(fout);
    fclose(fic);
}

// fonction comptant le nombre de caractère du texte
// et ennregistre ce nombre dns un autre fichier
void CompteCarac(void)
{
    FILE * fic;
    FILE * fout;

    fic = fopen("Alice.txt","r");
    fout = fopen("output.txt","w");

    int compteur = 0;

	if (fic  == NULL)
	{
        perror("Fichier d'origine illisible");
		exit(-1);
	}

	if (fout  == NULL)
	{
        perror("Fichier de sortie illisible");
		exit(-1);
	}

    while(getc(fic)!= EOF)
    {
        compteur = compteur +1 ;
    }
    fprintf(fout,"Le fichier d'entree contient %d caracteres",compteur);

    fclose(fout);
    fclose(fic);
}

// création d'un nouvel élément dans la liste
node* creation_liste_occ(int lettre,int nb_occ)
{
    node* nouvel_element = (node*) malloc(sizeof(node));
    nouvel_element->lettre = lettre;
    //printf("%c->",nouvel_element->lettre);
    nouvel_element->nb_occ = nb_occ;
    //printf("%d\n",nouvel_element->nb_occ);
    nouvel_element->succ = NULL;
    return nouvel_element;
}

// utilise la fonction creation_liste_occ pour mettre chaque
// nouveau caractère dans une liste ainsi que son nombre d'occurrence.
void nb_Occurrences(list* stock_occ)
{
    int i;
    int tab[128] = {0};
    int carac;
    list temp;
    FILE * fic;

    fic = fopen("Alice.txt","r");

    if (fic == NULL)
	{
        perror("Fichier d'origine illisible");
		exit(-1);
	}

    while ((carac = fgetc(fic)) != EOF)
    {
        tab[carac]++;
    }

    for (i=0; i<128;i++)
    {
        if (tab[i] != 0)
        {
            if (*stock_occ == NULL)
            {
                *stock_occ = creation_liste_occ(i,tab[i]);
                temp = *stock_occ;
            }
            else
            {
                temp->succ = creation_liste_occ(i,tab[i]);
                temp=temp->succ;
            }
        }
    }
}


// fonction créant un nouveau noeud dans un arbre.
arbre creation_noeud(int lettre, int occ)
{
    arbre nouveau_noeud = (tree_node*)malloc(sizeof(arbre));
    nouveau_noeud->lettre = lettre;
    nouveau_noeud->nb_occ = occ;
    nouveau_noeud->right = NULL;
    nouveau_noeud->left = NULL;
    return nouveau_noeud;
}

// fonction, utilisant la fonction creation_noeud, remplissant le noeud créée.
tree_array* creation_elem_noeud(int lettre, int occ)
{
    tree_array* nouvel_element = (tree_array*)malloc(sizeof(tree_array));
    nouvel_element->data = creation_noeud(lettre,occ);
    nouvel_element->next = NULL;
    return nouvel_element;
}

// utilisation de la fonction creation_elem_noeud
//pour créée une liste d'arbre à partir des noeuds de la précédente fonction.
tree_array* creation_liste_arbre(node* liste_occ)
{
    if (liste_occ != NULL)
    {
        tree_array* ListeArbre = creation_elem_noeud(liste_occ->lettre, liste_occ->nb_occ);
        tree_array* temp = ListeArbre;
        liste_occ = liste_occ ->succ;

        while (liste_occ != NULL)
        {
            temp->next = creation_elem_noeud(liste_occ->lettre, liste_occ->nb_occ);
            liste_occ = liste_occ->succ;
            temp = temp->next;
        }

        return ListeArbre;
    }
    return NULL;
}

// création de l'arbre de Huffman à partir de la liste d'arbre crée grace
// à la fonction creation_liste_arbre
arbre arbre_huffman(tree_array* liste)
{
    if (liste == NULL)
    {
        return NULL;
    }

    tree_array*  temp = NULL;
    tree_array*  temp2 = NULL;
    tree_array*  min1 = NULL;
    tree_array*  min2 = NULL;

    while (liste->next != NULL)
    {
        temp = liste;
        min1 = liste;
        temp2 = NULL;
        while (temp->next != NULL)
        {
            if (min1->data->nb_occ> temp->next->data->nb_occ)
            {
                temp2 = temp;
                min1 = temp->next;
            }

            temp = temp->next;
        }

        if (temp2 == NULL)
        {
            liste = liste->next;
        }
        else
        {
            temp2->next = temp2->next->next;
        }
        temp = liste;
        min2 = liste;
        temp2 = NULL;

        if (min1 == liste)
        {
            min2 = liste->next;
            temp = liste->next;
        }

        while (temp->next != NULL)
        {
            if ((min2->data->nb_occ > temp->next->data->nb_occ) && temp->next != min1)
            {
                temp2 = temp;
                min2 = temp->next;
            }
            temp = temp->next;
        }

    if (temp2 == NULL)
    {
        liste = liste->next;
    }

    else
    {
      temp2->next = temp2->next->next;
    }

    temp = creation_elem_noeud (36, min1->data->nb_occ+ min2->data->nb_occ);
    temp->data->right = min1->data;
    temp->data->left = min2->data;
    temp->next = liste;
    liste = temp;
    }

    return liste->data;
}

/*
void affichage_arbre (arbre a)
{
    if (a != NULL)
    {
        affichage_arbre(a->left);
        printf("%d",a->nb_occ);
        printf("%c ",a->lettre);
        affichage_arbre(a->right);
    }
}
*/

// création d'un liste binaire pour obtenir la suite binaire de chaque caractère
// à partir de l'arbre de huffman
list_binaire* Creation_list_binaire(int nb, list_binaire* binaire)
{
    list_binaire* nouveau = (list_binaire*)malloc(sizeof(list_binaire));
    nouveau->code = nb;
    nouveau->succ = NULL;
    if (binaire == NULL)
    {
        binaire = nouveau;
    }
    else
    {
        list_binaire* temp = binaire;

        while (temp->succ != NULL)
        {
            temp = temp->succ;
        }

        temp->succ = nouveau;
    }
    return binaire;
}

// fonction supprmiant la derniere valeur d'une liste.
list_binaire* suppression_derniere_val (list_binaire* binaire)
{
    if (binaire == NULL)
    {
        return NULL;
    }

    if (binaire->succ == NULL)
    {
        return NULL;
    }

    list_binaire* temp = binaire;
    while (temp->succ->succ != NULL)
    {
        temp = temp->succ;
    }

    temp->succ = NULL;
    return binaire;
}

// création du dictionnaire de Huffman grace aux fonctions
// Creation_list_binaire, qui au fur et à mesure construit la suite binaires
// de chaque caractère, et suppression_derniere_val qui va supprimer le dernier chiffre
// car le dernier "chemin" correspind à la feuille.
void Creation_Dico(arbre a,list_binaire* binaire)
{
    if (a == NULL)
    {
        exit(-1);
    }

    else if (a->left == NULL && a->right == NULL)
    {
        FILE* fdic = fopen("dico.txt", "a");

        if (fdic == NULL)
        {
            printf("Erreur mémoire");
            exit(-1);
        }

        fprintf(fdic,"%c:",a->lettre);

        while (binaire != NULL)
        {
            fprintf(fdic,"%d", binaire->code);
            binaire = binaire->succ;
        }

        fprintf(fdic,"\n");
        fclose(fdic);
    }

    else
    {
        Creation_Dico(a->left, Creation_list_binaire(0,binaire));
        binaire = suppression_derniere_val(binaire);
        Creation_Dico(a->right, Creation_list_binaire(1,binaire));
        binaire = suppression_derniere_val(binaire);
    }
}

// fonction permettant de traduire le texte en une suite bianire
// a partir de l'arbre et du dictionnaire de Huffman.
void encodage (void)
{
    FILE *fic = fopen("Alice.txt", "r");
    FILE *fdic = fopen("dico.txt", "r");
    FILE *fout = fopen("traduction.txt", "a");
    char lettre;
    if (fic==NULL || fdic==NULL || fout==NULL)
    {
        printf("Erreur mémoire");
        exit(1);
    }

    while ((lettre = fgetc(fic)) != EOF)
    {
        fseek(fdic, 0, SEEK_SET);
        while (fgetc(fdic) != lettre)
        {
            while (fgetc(fdic) != '\n')
            {
                lettre = lettre;
            }
        }

        fgetc(fdic);

        while ((lettre = fgetc(fdic)) != '\n')
        {
            fprintf(fout, "%c", lettre);
        }
    }
      fclose(fout);
      fclose(fdic);
      fclose(fic);
}

// fonction permettant de compresser la taille du main en utilisant
// toute les fonction du projet dans cette fonction.
void encodage_huffman (void)
{
      FILE * fic;
      list liste_occurence = NULL;
      arbre arbre_huff;
      tree_array* liste_transformee = NULL;
      list_binaire* binaire;
      fic = fopen("Alice.txt","r");
      Conversion(fic);
      CompteCarac();
      nb_Occurrences(&liste_occurence);
      liste_transformee=creation_liste_arbre(liste_occurence);
      arbre_huff = arbre_huffman(liste_transformee);
      Creation_Dico(arbre_huff,binaire);
      encodage();
}
