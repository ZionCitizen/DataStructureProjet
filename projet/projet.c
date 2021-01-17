#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#define TAILLE_NOMBRE 1000
#define TAILLE_TH 1000
#define TAILLE_DONNEES 4
//200000,400000,600000,1000000
// pour 100000 ça va prendre énormément de temps donc si vous voulez tester la question4 pour voir si ça fonctionne ça devrait suffir
// si voulez tester pour //200000,400000,600000,1000000 suffit juste de les rajouter dans le tableau ci-dessous et mettre la macro
//5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,100000
// TAILLE_DONNEES 19
int taille_des_donnees[TAILLE_DONNEES] = {1000,2000,3000,4000};
int taille_des_nombres_a_generer =10;

typedef struct cellule{
   int valeur;
   struct cellule *suivant;
}*Liste;

int tete(Liste l){
 return l->valeur;
}

Liste queue(Liste l){
 return l->suivant;
}

Liste creerListe(int x,Liste l){
	Liste L = malloc(sizeof(Liste));
	L->valeur = x;
	L->suivant = l;
	return L;
}

int estVide(Liste l){
	 if(l==NULL){
	 	return 1;
	 }
	 return 0;
}

void afficheListe(Liste l){
	 Liste p = l;
	 while(estVide(p)!=1){
	 	printf("[%d]",tete(p));
	 	p = queue(p);
	 }
	 printf("\n");
}

void freeMemoireListe(Liste *l){
	Liste p=NULL;
 while(*l!=NULL){
 	//printf("Suppression [%d]\n",(*l)->valeur); juste pour voir le maillon en cours de suppresion 
   p = (*l)->suivant;
   free(*l);
   *l = p;
 }
 *l = NULL;
 //printf("Memoire Liberer\n");
}

int recupereValeur(char c){
  return c%48;
}

int tailleNombreSaisie(char *tab){
    int taille=0;
    while(tab[taille]!='\0'){
        taille++;
    }
    return taille;
}

void question1(){
  char *saisie = malloc(TAILLE_NOMBRE*sizeof(char));
  int TAILLE_TABLEAU;
  Liste maliste = NULL;
  printf("1-Creation Tres Grand Nombre Entier: \n");
  printf("Veuillez Saisir Un Nombre\n");
  scanf("%s",saisie);
  TAILLE_TABLEAU  = tailleNombreSaisie(saisie);
  for(int i=TAILLE_TABLEAU-1;i>-1;i--){
        maliste  = creerListe(recupereValeur(saisie[i]),maliste);
  }
  afficheListe(maliste);
  freeMemoireListe(&maliste);
}

Liste getListe(){   
  char *saisie = malloc(TAILLE_NOMBRE*sizeof(char));
  int TAILLE_TABLEAU;                                   // même fonction que question1 juste on retourne en plus la liste créé
  Liste maliste = NULL;
  printf("Veuillez Saisir Un Nombre\n");
  scanf("%s",saisie);
  TAILLE_TABLEAU  = tailleNombreSaisie(saisie);
  for(int i=TAILLE_TABLEAU-1;i>-1;i--){
        maliste  = creerListe(recupereValeur(saisie[i]),maliste);
  }
  return maliste;
}
/*****************************************QUESTION II*********************************************/

typedef struct noeud{
  Liste nombre;
  struct noeud *gauche;
  struct noeud *droit;
}*Noeud;

int estVideNoeud(Noeud n){
    if(n==NULL) return 1;
    return 0;
 }

void creerNoeudListe(Noeud *n,Liste l){
   *n = malloc(sizeof(Noeud));
   (*(*n)).nombre = l;
   (*(*n)).gauche = NULL;
   (*(*n)).droit = NULL;
}

int max(int a,int b){
  if(a>b) return a;
  return b;
}

int hauteur(Noeud n){
    if(estVideNoeud(n)==1)return -1;
    return 1+max(hauteur(n->gauche),hauteur(n->droit));
}

int valeurAbsolue(int valeur){
 if(valeur<0)return (-valeur);
 return valeur;
}

int estUnAVL(Noeud n){
 if(estVideNoeud(n)==1){
     return 1;
 }else
      if(valeurAbsolue(hauteur(n->gauche)-hauteur(n->droit))<=1){
             return estUnAVL(n->gauche);
             return estUnAVL(n->droit);
         }

      else{
        return 0;
      }
  }

void rotationDroite(Noeud *n){
  Noeud temp = NULL;
 if(estVideNoeud(*n)!=1){
    temp = (*n)->gauche;
    (*n)->gauche = temp->droit;
    temp->droit = *n;
    *n = temp;
 }
}

void rotationGauche(Noeud *n){
 Noeud temp = NULL;
 if(estVideNoeud(*n)!=1){
    temp = (*n)->droit;
    (*n)->droit = temp->gauche;
    temp->gauche = (*n);
    (*n) = temp;
 }
}

void rotationDroiteGauche(Noeud *n){
    rotationDroite(&(*n)->droit);
    rotationGauche(&(*n));

}

void rotationGaucheDroite(Noeud *n){
    rotationGauche(&(*n)->gauche);
    rotationDroite(&(*n));
  }

void parcoursPrefixe(Noeud n){
   if(n!=NULL){
   	printf("Noeud: ");
    afficheListe(n->nombre);
    parcoursPrefixe(n->gauche);
    parcoursPrefixe(n->droit);
   }
}

int desequilibre(Noeud n){
  if(valeurAbsolue(hauteur(n->gauche)-hauteur(n->droit))>=2)return 1;
  return 0;
}

void reequilibre(Noeud *n){
 if(estVideNoeud((*n))!=1){
 	  if(hauteur((*n)->gauche)-hauteur((*n)->droit)>=2){
 	  	  	if(estVideNoeud((*n)->gauche->droit)==1){
 	  	  		  rotationDroite(n);
 	  	  	}else{
 	  	  		 rotationGaucheDroite(n);
 	  	  	}
 	  }else
 	   	  if(hauteur((*n)->gauche)-hauteur((*n)->droit)<=-2){
 	   	  		  if(estVideNoeud((*n)->droit->gauche)==1){
 	   	  		  	 rotationGauche(n);
 	   	  		  }else{
 	   	  		  	 rotationDroiteGauche(n);
 	   	  		  }
 	   	   }
 }else{
 	 return;
 }

}

int tailleListe(Liste l){
	Liste p = NULL;
	int taille=0;
	p = l;
 while(estVide(p)!=1){
 	taille = taille+1;
 	p = queue(p);
	}
return taille;
}
                                                          /* fonction qui compare deux nombre de taille identique*/
int compareNombreTailleIdentique(Liste l1,Liste l2){			/* 1 si nb1 >nb2 | -1 si nb2>nb1 | 0 ils sont egaux */
   Liste p1 = l1;
   Liste p2 = l2;
   while(estVide(p1)!=1){
   	   if(tete(p1)>tete(p2)){return 1;}
   	   else if(tete(p2)>tete(p1)){return -1;}
   	   p1 = queue(p1);
   	   p2 = queue(p2);
   }
return 0;	
}

int compareNombreListe(Liste l1,Liste l2){
   int t1 = tailleListe(l1);
   int t2 = tailleListe(l2);
   if(t1!=t2){
   	    if(t1>t2){
   	    	 return 1;
   	    }else{
   	    	  return -1;
   	    }
   }else{
   	  return compareNombreTailleIdentique(l1,l2);
   }
}

void ajouterAVL(Noeud *n,Liste l){
	if(estVideNoeud(*n)!=1){
       if(compareNombreListe(l,((*n)->nombre))==1){   // si le nombre qu'on veut inserer est plus grand que le noeud ou on se trouve on part a droite
       	  ajouterAVL((&(*n)->droit),l);
       }else
            if(compareNombreListe(l,((*n)->nombre))==-1) // si le nombre qu'on veut inserer est plus petit que le noeud ou on se trouve on part a gauche
             {
            ajouterAVL((&(*n)->gauche),l);
       			}else{
					printf("Insertion Impossible Noeud Identique !\n"); 
					return;
       			}

	}else{
		 creerNoeudListe(n,l);  // si l arbre est vide en premier lieu | ou qu on a trouver ou inserer le noeud on l insere 
	}
	if(estUnAVL(*n)){  // on véréfie si c'est un avl on retourne tout est bon
		return;
	}else{   // si il est déséquilibré on le rééquilibre
		reequilibre(n);
	 }
}

int rechercheAVL(Liste x,Noeud n){
   if(estVideNoeud(n)){
    printf("n est pas present !\n ");
   	return 0;
   } 
    else
    	if(compareNombreListe(x,n->nombre)==0){// si 0 x est present dans n return 1
      printf("est Present dans L Arbre \n");
        return 1;
    	}else
    	   if(compareNombreListe(x,n->nombre)==1){	// si x >n->nombre alors on part a droite
    	   	return rechercheAVL(x,n->droit);
    	   }else{
    	   	return rechercheAVL(x,n->gauche);		 //si x <n->nombre alors on part a gauche
    	   }
}

void freeMemoireArbre(Noeud *n){
  if(*n==NULL){
     return;
  }else{
     freeMemoireArbre(&(*n)->gauche);
     freeMemoireArbre(&(*n)->droit);
     freeMemoireListe(&(*n)->nombre);
     free(*n);
   }
}
void question2(){
//Tester avec: 25-60-35-10-5-20-65-45-70-40-50-55-30-15 pour tester si la fonction rééquilibre fonctionne correctement 
// https://www.cs.usfca.edu/~galles/visualization/AVLtree.html   | pour la visualisation des insertions 
Noeud n = NULL;
Liste maliste = NULL;
int saisie = 1;
 printf("2-Construction D Un AVL: \n");
 while(saisie!=0){
    maliste = getListe();
    ajouterAVL(&n,maliste);
    printf("Voulez Vous Inserez Un Autre Nombre ? 1/0 \n");
    scanf("%d",&saisie);
 }
 printf("Affichage par Ordre Prefixe \n");
 parcoursPrefixe(n);
 printf("Voulez vous Lancer une Recherche ? 1/0\n");
 int recherche;
 scanf("%d",&recherche);
 if(recherche) rechercheAVL(getListe(),n);
 freeMemoireArbre(&n);
 printf("Memoire Liberer\n");
 printf("Au Revoir\n");
}
/**********************************************QUESTION III TABLES_HACHAGES**************************************************************************/

int sommeListe(Liste l){
  Liste temp = l;
  int somme = 0;
  while(temp!=NULL){
     somme = somme + tete(temp);
     temp = queue(temp);
  }
  return somme;
}

int fonctionHachage(Liste l,int taille){
  return (sommeListe(l)%taille);
}

void initialiseTableTH(Liste nombres[],int taille){
   for(int i=0;i<taille;i++){
      nombres[i] = NULL;
   }
}

void afficheListeTH(Liste l){
   Liste p = l;
   while(estVide(p)!=1){
    if(tete(p)!=124) printf("[%d]",tete(p));
    else printf("->");
     p = queue(p);
   }
   printf("\n");
}

void afficheTouteLaTable(Liste nombres[],int taille){
    int i = 0;
    while(i<taille){
       if(nombres[i]!=NULL){
         printf("Indice: %d Contient: ",i);
         afficheListeTH(nombres[i]);
       }
       i++;
    }
}

void rechercheTH(Liste cle,Liste nombres[],int taille){
  int indiceHachage = fonctionHachage(cle,taille);
   if(nombres[indiceHachage]!=NULL && cle!=NULL){
      if(compareNombreTailleIdentique(nombres[indiceHachage],cle)==0){
             printf("La Cle est Presente dans La Table :=) !\n");
        }
        else{
        Liste temp = nombres[indiceHachage];
        while(temp!=NULL){
           if(tete(temp)==124) temp = temp->suivant;
              if(compareNombreTailleIdentique(temp,cle)==0){
                  printf("La Cle est Presente dans La Table :=) !\n");
                  return;
                }
            while(tete(temp)!=124){
             temp = queue(temp);
                 }
              }   
              printf("La Cle n est pas presente dans la table :=( \n");       
        }  
      }
  else{
    printf("La Cle n est pas presente dans la table :=( \n");
  }
}

void afficheListeIndex(Liste nombres[],int index){
  afficheListeTH(nombres[index]);
}

int collisionDetection(Liste nombres[],int indiceHachage){
    if(nombres[indiceHachage]!=NULL){
      printf("------------------Une Collision s'est produite !-------------------------\n");
      return 1;
    }
    return 0;
}
// résolution des collisions avec chainage 
void question3(){
 Liste nombres[TAILLE_TH];
 initialiseTableTH(nombres,TAILLE_TH);     
 Liste maliste = NULL;
 int insertion = 1;
 int indiceHachage = 0; //pour eviter les appeles multiples de fonctionHachage
 printf("3-Tables de Hachages \n");
  while(insertion!=0){
   maliste = getListe();
   indiceHachage = fonctionHachage(maliste,TAILLE_TH);
   if(collisionDetection(nombres,indiceHachage)){ // si y a une collision on fait pointer le nombre->suivant vers maliste 
        Liste temp = nombres[indiceHachage];
        while(temp->suivant!=NULL){
            temp = temp->suivant;
        }
        Liste separateur = NULL;
        separateur = creerListe(124,separateur);//124 qui correspend a | dans la table ascci (a l affichage remplacer par ->) il marque la fin d'un nombre  
        temp->suivant = separateur;
        separateur->suivant = maliste;
   }else{
     nombres[indiceHachage] = maliste;
   }
   printf("Indice donnee par la fonction de Hachage: %d\n",indiceHachage);
   afficheListeIndex(nombres,indiceHachage);
   printf("Voulez vous Inserez un Autre Element ? 1/0 \n");
   scanf("%d",&insertion);
 }
afficheTouteLaTable(nombres,TAILLE_TH);
printf("Voulez vous lancer une Recherche ? 1/0\n");
int recherche;
scanf("%d",&recherche);
if(recherche) rechercheTH(getListe(),nombres,TAILLE_TH);
}
/************************************QUESTION IV*****************************************************/

Liste generateurNombreListeAleatoire(int taille_nombre){
  int nombre[taille_nombre];
  Liste maliste = NULL;

  for(int i=0;i<taille_nombre;i++){
    nombre[i] = rand() % 10;
  }
  for(int i=taille_nombre-1;i>-1;i--){
        maliste  = creerListe(nombre[i],maliste);
  }
  return maliste;
}

/****************************************QUESTION 4-1******************************************/
int generateurAvl(int taille_du_nombre_a_generer,int taille_tableau){ 
int temps_mills = 0;
int i = 0;
Liste tableau_nombre[taille_tableau];
Noeud n = NULL;
srand(time(NULL));
int nombre[15] = {8,5,4,8,9,7,8,1,5,1,5,4,7,8,9}; // veuilez saisir ici un nombre que vous voulez recherchez |ps: oublier pas de redimensioner la taille du tableau
Liste NOMBRE_A_RECHERCHER = NULL;
for(int i=15;i>-1;i--){
NOMBRE_A_RECHERCHER  = creerListe(nombre[i],NOMBRE_A_RECHERCHER);
}
sleep(1);
while(i<taille_tableau){        
	printf("Generation Num:  %d\n",i);
	if(i == taille_tableau -1){
	tableau_nombre[i] = NOMBRE_A_RECHERCHER;  // on insere le nombre a la derniere case du tableau(cas au pire) 
	}else{
		 tableau_nombre[i] = generateurNombreListeAleatoire(taille_du_nombre_a_generer);
	}  
    i++;
}
i = 0;
clock_t debut_prog = clock();    
printf("Insertion dans l Arbre ...\n");
sleep(1);
while(i<taille_tableau){    // debut des insertions des nombres dans l Arbre
 ajouterAVL(&n,tableau_nombre[i]);
 printf("Insertion Num=%d\n",i);
	 i++;
}
//parcoursPrefixe(n);  pour afficher les noeuds crées
rechercheAVL(NOMBRE_A_RECHERCHER,n);
clock_t fin_prog = clock();
return (fin_prog - debut_prog);
}

void testRechercheAVL(){
int temps_necessaire[TAILLE_DONNEES];
FILE* fichier = NULL;
printf("4-1 Complexite AVL\n");
printf("Lancement...\n");
sleep(2);
 for(int i=0;i<TAILLE_DONNEES;i++){
   printf("Taille des Donnees a Genere: %d\n",taille_des_donnees[i]);
   sleep(1);
   temps_necessaire[i] = generateurAvl(taille_des_nombres_a_generer,taille_des_donnees[i]);
 }

 fichier = fopen("grapheAVL.txt","w+");
 printf("Sauvegarde Des Donnees Reussi ! \n");
for(int i=0;i<TAILLE_DONNEES;i++){
  printf("Taille des Données:%d Temps Necessaire a la Recherche: %d ms\n",taille_des_donnees[i],temps_necessaire[i]);
  if(i==0){
  fprintf(fichier,"Taille des Données:   Temps Necessaire a la Recherche:(ms)\n");
  }
  fprintf(fichier,"%d                              %d\n",taille_des_donnees[i],temps_necessaire[i]);
}

}

int generateurTH(int taille_du_nombre_a_generer,int taille_tableau){
clock_t debut = clock(); // debut programme 
int nombre[15] = {8,5,4,8,9,7,8,1,5,1,5,4,7,8,9}; // veuilez saisir ici un nombre que vous voulez recherchez
Liste NOMBRE_A_RECHERCHER = NULL;
for(int i=15;i>-1;i--){
NOMBRE_A_RECHERCHER  = creerListe(nombre[i],NOMBRE_A_RECHERCHER);
}  
 Liste nombres[taille_tableau];
 initialiseTableTH(nombres,taille_tableau); 
 Liste maliste = NULL;
 int i = 0;
 int indiceHachage = 0;//pour eviter l appele multiple de la fonction fonctionHachage
 while(i<taille_tableau){
  if(i == taille_tableau -1) maliste = NOMBRE_A_RECHERCHER;
  else maliste = generateurNombreListeAleatoire(taille_du_nombre_a_generer);
   indiceHachage = fonctionHachage(maliste,taille_tableau);
  // printf("Indice donne par la fonction de Hachage: %d\n",indiceHachage); 
   if(collisionDetection(nombres,indiceHachage)){
        Liste temp = nombres[indiceHachage];
        while(temp->suivant!=NULL){
            temp = temp->suivant;
        }
        Liste separateur = NULL;
        separateur = creerListe(124,separateur);//124 qui correspond a | dans la table ascii mais que lors de l'affichage j'ai remplacer par ->
        temp->suivant = separateur;
        separateur->suivant = maliste;
   }else{
     nombres[indiceHachage] = maliste;
   }
     printf("insertion: %d\n",i);
   i++;
 }

printf("Affichage en Cours ...\n");
sleep(1);
//afficheTouteLaTable(nombres,taille_tableau); // pour afficher toutes les cles
rechercheTH(NOMBRE_A_RECHERCHER,nombres,taille_tableau);
clock_t duree = clock() - debut;
clock_t temps_necessaire = duree * 1000 / CLOCKS_PER_SEC;
return temps_necessaire;
}

void testRechercheTH(){
int temps_necessaire[TAILLE_DONNEES];
 FILE* fichier = NULL;
  printf("4-2 Complexite Table de Hachage \n");
 for(int i=0;i<TAILLE_DONNEES;i++){
   printf("Generation de: %d\n",taille_des_donnees[i]);
   sleep(1);
   temps_necessaire[i] = generateurTH(taille_des_nombres_a_generer,taille_des_donnees[i]);
 }
 fichier = fopen("grapheTableHachage.txt","w+");
 printf("Sauvegarde Des Donnees Reussi ! \n");
for(int i=0;i<TAILLE_DONNEES;i++){
  printf("Taille des Données:%d Temps Necessaire a la Recherche: %d ms\n",taille_des_donnees[i],temps_necessaire[i]);
  if(i==0)fprintf(fichier,"Taille des Données:         Temps Necessaire a la Recherche:(ms)\n");
  fprintf(fichier,"      %d                                   %d ms\n",taille_des_donnees[i],temps_necessaire[i]);
}
}

void question4(){
testRechercheAVL();
testRechercheTH();
}

/****************Programme en Plus qui regroupe le tous en une seule fonction************************************/      

void menu(){
printf("-----------------MENU-----------------\n");
printf("1-Creation Grand Entier Sous Forme D Une Liste \n");
printf("2-Implementation D Un Avl \n");
printf("3-Implementation D Une Table De Hachage \n");
printf("4-Complexite Comparaison Entre Table de Hachage et AVL \n");
printf("5-Quitter le Programme \n");
printf("----------------Fin MENU--------------\n");

}

void projet(){
  int choix;
  int enMarche = 1;
  int etape = 1; int ht = 0;
printf("Bonjour Quel Question Voulez vous Testez ? \n");

while(enMarche!=0){
 reesaye:;
 menu();
 scanf("%d",&choix);
   switch(choix){
     case 1:
     question1();
       break;

    case 2:
    question2();
      break;

    case 3:
    question3();
      break;

    case 4:
    printf("Voulez Tester D abord la complexite AVL ensuite les Tables de hachage ou bien le tous ? 1/0 \n");
    scanf("%d",&etape);
       if(etape){
        testRechercheAVL();
        printf("Test RechercheAVL Terminer Voulez Vous Lancez le Test de Recherche dans une Table de Hachage ? 1/0\n");
        scanf("%d",&ht);
        if(ht){
         testRechercheTH();
            }
        }else{
            question4();
        }
    case 5:
    enMarche = 0;
      break;
    printf("Terminer ! \n");
      break;
   
   default: 
     printf("Choix Indisponible Veuillez Faire un Choix Parmi Ceux Disponible dans le menu ci-dessous\n");
     goto reesaye;
     break;
   }

if(enMarche!=0){
  printf("Voulez Vous Testez Autre Chose ? 1/0\n");
  scanf("%d",&enMarche);
}

}
  
printf("Au-Revoir \n");
}                                                                           
 
int main(int argc,char *argv[]){
projet();
return EXIT_SUCCESS;}

