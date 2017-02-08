#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//On définit la constante de taille. Maximum 5 bateaux  Maximum 5 cases par bateau
#define TAILLE 5
#define TMAP 9
//On définit un type énuméré etat qui nous permettra de vérifier si la case/le bateau/la flotte est sauf ou détruite
typedef enum Etat{
    Sauf,Detruit
}Etat;
//On définit le type structuré cellule qui contient deux coordonnées (entiers) et un état
typedef struct Cellule{

    int colonne;
    int ligne;
    Etat Cetat;

}Cellule;
//On définit le type stucturé bateau qui contient un tableau de cellule, une taille (entier) et un état
typedef struct Bateau{

    Cellule nCel[TAILLE];
    int Btaille;
    Etat Betat;

}Bateau;
//On définit le type structuré flotte qui contient un tableau de bateau, une taille (entier) et un état
typedef struct Flotte{

    Bateau nBateau[TAILLE];
    int Ftaille;
    Etat Fetat;

}Flotte;
//On définit un enuméré comme booléen
enum BOOL{

    True,False
};
//On définit la fonction initCellule
//BUT: Initialiser une variable de type cellule à partir de deux entiers
//ENTREE : Deux entiers
//SORTIE : Une variable de type cellule avec les deux entiers comme variable de colonne et de ligne et un état prédéfini
Cellule initCellule(int colonne,int ligne);
//On définit la fonction compareCellule
//BUT: Comparer deux variables de type cellule pour savoir si elles ont les mêmes variable de ligne et de colonne
//ENTREE : Deux variables de type cellule
//SORTIE : Un Boolean égale à true si les cellules ont les mêmes valeurs de colonne et de ligne.
enum BOOL compareCellule(Cellule Cel1,Cellule Cel2);
//On définit la fonction initBateau
//BUT: Initiliser une variable de type Bateau à partir de 4 entier
//ENTREE : 4 entiers : Colonne et ligne de la première cellule du bateau, nombre de cellule composant le bateau et direction vers laquelle le bateau se déploît à partir de la première cellule
//SORTIE : Une variable de type bateau
Bateau initBateau(int colonne,int ligne,int tailBat,int direction);
//On définit la fonction compareCelBateau
//BUT: Vérifier si une cellule correspond à une des cellules d'un bateau
//ENTREE : Une cellule et un bateau
//SORTIE : Un boolean égale à vrai si une des cellules du bateau possède les mêmes valeurs de ligne et colonne que la cellule entrée.
enum BOOL compareCelBateau(Cellule Cel, Bateau Bat);
//On définit la fonction compareCelFlotte
//BUT: Vérifier si une cellule correspond à une des cellules d'un bateau appartenant à la flotte
//ENTREE : Une cellule et une flotte
//SORTIE : Un boolean égale à vrai si une des cellules des bateaux de la flotte possède les mêmes valeurs de ligne et colonne que la cellule entrée.
enum BOOL compareCelFlotte(Cellule Cel, Flotte Flot);
//On définit la fonction ChoixBateau
//BUT : Définir un bateau appartenant à la flotte d'un joueur
//ENTREE : Une flotte et la taille du bateau à définir
// SORTIE : Le nouveau bateau de la flotte avec les coordonnées choisies par le joueur
Bateau ChoixBateau(Flotte Flot,int Tail);
//On définit la fonction initFlotte
//BUT : Initialiser un variable de typer flotte.
//ENTREE : Rien. On appel la fonction ChoixBateau pour définir les cinq bateaux composant la flotte
//SORTIE : La flotte du joueur avec ses cinq bateaux définis
Flotte initFlotte();
//On définit la fonction Affichage
//But : Afficher l'état et la position de la flotte du joueur
//Entree : Une flotte
//Sortie : Un texte résumant l'état, les coordonnées des cellules appartenant aux bateaux composant la flotte du joueur.
void Affichage(Flotte Flot);
//On définit la fonction BateauDetruit
//BUT : Vérifier si toutes les cellules d'un bateau sont détruites afin de passer l'état du bateau de sauf à détruit et de mettre à jour la flotte associée.
//Entree : Une flotte
//Sortie : La flotte mise à jour.
Flotte BateauDetruit(Flotte Flot);
//On définit la fonction Tir
//BUT : Lire les entrées de l'utilisateur qui définit une cellule sur laquelle il veut tirer et vérifier si cette cellule appartient à la flotte visée et la passer à l'état détruit
//ENTREE : La flotte. Les entrées de l'utilisateur sont demandées dans la fonction.
//SORTIE : La flotte mise à jour
Flotte Tir(Flotte Flot);

int main()
{
    int nbrJ;
    int i;
    int tour,cible;
    int FinPartie;
    printf("Combien de joueurs ?\n");
    fflush(stdin);
    scanf("%i",&nbrJ);
    Flotte Joueurs[nbrJ];
    //Initialisation des Flottes
    for (i=0;i<nbrJ;i++)
    {
        system("cls");
        printf("Joueur %i :\n",i+1);
        Joueurs[i]=initFlotte();
    }
    FinPartie=1;
    tour=0;
    cible=-1;
    //Boucle du jeu
    while (FinPartie==1)
    {
        system("cls");
        printf("Joueur %i :\n",tour+1);
        Affichage(Joueurs[tour]);
        if (nbrJ>2)
        {
            printf("Quel joueur visez-vous ?\n");
            for (i=0;i<nbrJ;i++)
            {
                if (i!=tour){
                    printf("Joueur %i ?\n",i+1);
                }
            }
            fflush(stdin);
            scanf("%i",&cible);
        } else
        {
            if (tour==0)
            {
                cible=2;
            } else
            {
                cible=1;
            }
        }
        Joueurs[cible-1]=Tir(Joueurs[cible-1]);
        Joueurs[cible-1]=BateauDetruit(Joueurs[cible-1]);
        printf("Appuyer sur Entree pour passer au prochain joueur.\n");
        getch();
        if (Joueurs[cible-1].Ftaille==0)
        {
            printf("Le joueur %i a detruit la flotte du joueur %i, il remporte la partie.\n",tour+1,cible);
            FinPartie=0;
        } else
        {
            if (tour<nbrJ-1)
            {
                tour++;
            } else
            {
                tour=0;
            }
        }
    }
    return 0;
}

Cellule initCellule(int colonne,int ligne){
    Cellule newCel;
    newCel.ligne=ligne;
    newCel.colonne=colonne;
    newCel.Cetat=Sauf;
    return newCel;
}
enum BOOL compareCellule(Cellule Cel1,Cellule Cel2){
    if ((Cel1.ligne==Cel2.ligne)&&(Cel1.colonne==Cel2.colonne))
    {
        return True;
    } else
    {
        return False;
    }
}
Bateau initBateau(int colonne,int ligne,int tailBat,int direction){
    Bateau newBat;
    int i;
    newBat.Btaille=tailBat;
    newBat.Betat=Sauf;
    for (i=0;i<newBat.Btaille;i++)
    {
        if (direction==0)//gauche x-1
        {
            newBat.nCel[i]=initCellule(colonne-i,ligne);

        } else if (direction==1)//haut y-1
        {
            newBat.nCel[i]=initCellule(colonne,ligne-i);

        } else if (direction==2)//droite x+1
        {
            newBat.nCel[i]=initCellule(colonne+i,ligne);

        } else if (direction==3)//Bas y+1
        {
            newBat.nCel[i]=initCellule(colonne,ligne+i);
        }
    }
    return newBat;

}
enum BOOL compareCelBateau(Cellule Cel, Bateau Bat){
    int stockBool;
    int i;
    stockBool=1;
    i=0;
    while ((stockBool==1)&&(i<Bat.Btaille))
    {
        if (compareCellule(Cel,Bat.nCel[i])==True)
        {
            stockBool=0;
        } else
        {
            stockBool=1;
            i++;
        }
    }
    if (stockBool==0)
    {
        return True;
    }  else
    {
        return False;
    }
}
enum BOOL compareCelFlotte(Cellule Cel, Flotte Flot){
    int stockBool;
    int i;
    i=0;
    stockBool=1;
    while ((stockBool==1)&&(i<Flot.Ftaille))
    {
        if (compareCelBateau(Cel,Flot.nBateau[i])==True)
        {
            stockBool=0;
        } else
        {
            stockBool=1;
            i++;
        }
    }
    if (stockBool==0)
    {
        return True;
    }  else
    {
        return False;
    }
}
Bateau ChoixBateau(Flotte Flot,int Tail){
    Cellule newCel,compCel;
    Bateau newBat;
    int okCel,okBat,colonne,ligne,direction;
    int i,j;
    okCel=0;
    okBat=0;
    int okDir[4] = {
        1,1,1,1
    };
    //Boucle construction bateau
    while (okBat==0)
    {
        //Boucle création première cellule
        while (okCel==0)
        {
            printf("Entrez les coordonnees de sa premiere cellule.\n");
            printf("On commence par x (entier entre 0 et %i compris):\n",TMAP);
            fflush(stdin);
            scanf("%i",&colonne);
            printf("Puis y (entier entre 0 et %i compris):\n",TMAP);
            fflush(stdin);
            scanf("%i",&ligne);
            newCel=initCellule(colonne,ligne);
            if (compareCelFlotte(newCel,Flot)==False){
                printf("Cellule disponible ! \n");
                okCel=1;
            } else
            {
                printf("Cellule indisponible, on recommence ! \n");
            }
        }
        //Boucle vérification directions disponibles
        for (i=0;i<4;i++)
        {
            j=0;
            while ((okDir[i]==1)&&(j<Tail))
            {
                if (i==0) // gauche x-1
                {
                    compCel.colonne=newCel.colonne-j;
                    compCel.ligne=newCel.ligne;
                    if ((compareCelFlotte(compCel,Flot)==False)&&(compCel.colonne>-1)){
                        okDir[i]=1;
                        j++;
                    } else {
                        okDir[i]=0;
                    }
                }
                if (i==1) //haut y-1
                {
                    compCel.colonne=newCel.colonne;
                    compCel.ligne=newCel.ligne-j;
                    if ((compareCelFlotte(compCel,Flot)==False)&&(compCel.ligne>-1)){
                        okDir[i]=1;
                        j++;
                    } else {
                        okDir[i]=0;
                    }
                }
                if (i==2) //droite x+1
                {
                    compCel.colonne=newCel.colonne+j;
                    compCel.ligne=newCel.ligne;
                    if ((compareCelFlotte(compCel,Flot)==False)&&(compCel.colonne<(TMAP+1))){
                        okDir[i]=1;
                        j++;
                    } else {
                        okDir[i]=0;
                    }
                }
                if (i==3) //bas y+1
                {
                    compCel.colonne=newCel.colonne;
                    compCel.ligne=newCel.ligne+j;
                    if ((compareCelFlotte(compCel,Flot)==False)&&(compCel.ligne<(TMAP+1))){
                        okDir[i]=1;
                        j++;
                    } else {
                        okDir[i]=0;
                    }
                }
            }
        }
        //Boucle choix de la direction
        if ((okDir[0]==1)||(okDir[1]==1)||(okDir[2]==1)||(okDir[3]==1)){
            printf("Les directions disponibles sont : \n");
            if (okDir[0]==1)
            {
                printf("Gauche. Tapez 0. \n");
            }
            if (okDir[1]==1)
            {
                printf("Haut. Tapez 1. \n");
            }
            if (okDir[2]==1)
            {
                printf("Droite. Tapez 2. \n");
            }
            if (okDir[3]==1)
            {
                printf("Bas. Tapez 3. \n");
            }
            printf("Tapez le chiffre associer a la direction dans quelle vous voulez orienter votre bateau ? (Tapez 4 pour redefinir la cellule.) ");
            fflush(stdin);
            scanf("%i",&direction);
            if (direction==4)
            {
                okCel=0;
            } else if (okDir[direction]==1)
            {
                newBat=initBateau(colonne,ligne,Tail,direction);
                okBat=1;
            } else
            {
                direction=-1;
            }

        }
    }
    return newBat;
}
Flotte initFlotte(){
    Flotte newFlot;
    newFlot.Fetat=Sauf;
    newFlot.Ftaille=0;

    printf("Nous allons placer vos cinq bateaux.\n");

    printf("On commence par le porte-avions (5 cases).\n");
    newFlot.nBateau[0]=ChoixBateau(newFlot,5);
    newFlot.Ftaille++;

    printf("On passe au croiseur (4 cases).\n");
    newFlot.nBateau[1]=ChoixBateau(newFlot,4);
    newFlot.Ftaille++;

    printf("On passe au contre_torpilleurs (3 cases).\n");
    newFlot.nBateau[2]=ChoixBateau(newFlot,3);
    newFlot.Ftaille++;

    printf("On passe au sous-marin (3 cases).\n");
    newFlot.nBateau[3]=ChoixBateau(newFlot,3);
    newFlot.Ftaille++;

    printf("On finis par le torpilleur (2 cases).\n");
    newFlot.nBateau[4]=ChoixBateau(newFlot,2);
    newFlot.Ftaille++;

    return newFlot;

}
void Affichage(Flotte Flot){
    int i,j;
    printf("Voici l'etat et la position de votre flotte.\n");
    for (i=0;i<Flot.Ftaille;i++)
    {
        printf("Bateau %i :\n",i+1);
        for (j=0;j<Flot.nBateau[i].Btaille;j++)
        {
            printf("Cellule %i : ",j+1);
            printf("Pos : ");
            printf("Colonne : %i ",Flot.nBateau[i].nCel[j].colonne);
            printf("Ligne : %i ",Flot.nBateau[i].nCel[j].ligne);
            if (Flot.nBateau[i].nCel[j].Cetat==Sauf)
            {
                printf("Etat : Sauf \n");
            } else
            {
                printf("Etat : Touche \n");
            }
        }
    }
}
Flotte BateauDetruit(Flotte Flot){
    int i,j;
    for (i=0;i<Flot.Ftaille;i++)
    {
        j=0;
        while ((Flot.nBateau[i].nCel[j].Cetat==Detruit)&&(j<Flot.nBateau[i].Btaille))
        {
            j++;
        }
        if (j==Flot.nBateau[i].Btaille)
        {
            Flot.nBateau[i].Betat=Detruit;
            printf("Le bateau %i est detruit. \n",i+1);
            if (i<Flot.Ftaille-1)
            {
                Flot.nBateau[i]=Flot.nBateau[Flot.Ftaille-1];
                Flot.Ftaille=Flot.Ftaille-1;
            } else {
                Flot.Ftaille=Flot.Ftaille-1;
            }
        }
    }
    return Flot;
}
Flotte Tir(Flotte Flot){
    int colonne,ligne;
    int i,j;
    Cellule newCel;
    printf("Entrez les coordonnees de la cellule cible.\n");
    printf("On commence par x (entier entre 0 et %i compris):\n",TMAP);
    fflush(stdin);
    scanf("%i",&colonne);
    printf("Puis y (entier entre 0 et %i compris):\n",TMAP);
    fflush(stdin);
    scanf("%i",&ligne);
    newCel=initCellule(colonne,ligne);
    if (compareCelFlotte(newCel,Flot)==True)
    {
        for (i=0;i<Flot.Ftaille;i++)
        {
            for (j=0;j<Flot.nBateau[i].Btaille;j++)
            {
                if ((Flot.nBateau[i].nCel[j].colonne==colonne)&&(Flot.nBateau[i].nCel[j].ligne==ligne))
                {
                    Flot.nBateau[i].nCel[j].Cetat=Detruit;
                    printf("Touche Bateau num %i Taille %i Cel %i \n",i,Flot.nBateau[i].Btaille,j);
                }
            }
        }
    } else
    {
        printf("Rate ! \n");
    }
    return Flot;
}
