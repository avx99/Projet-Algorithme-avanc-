#include "Set.h"

int     main()
{
    int choix;
    int k;
    double jaro;
    int levenshtien_choix;
    int i = 0;
    char nom_fichier[256];
    char nom_fichier_out[256];
    char **tab_out;
    clock_t t1,t2;
    printf("%f\n",LevenshteinDistance("zsw","zaqqswq"));
    printf("\t*************(PROJET ALGORITHMIQUE AVANCE)*************\n");
    printf("\t*                                                     *\n");
    printf("\t*REALISER PAR :                                       *\n");
    printf("\t*              EL KHIYATI MOUAD                       *\n");
    printf("\t*              ABOUZID OUSSAMA                        *\n");
    printf("\t*                                                     *\n");
    printf("\t*                                                     *\n");
    printf("\t*              (ALGORITHME NAIVE)                     *\n");
    printf("\t*                                                     *\n");
    printf("\t*VEUILLEZ AFFECTER UN CHOIX:                          *\n");
    printf("\t***-FILTRER VOTRE FICHIER PAR LA DISTANCE:            *\n");
    printf("\t*1-LEVENSHTIEN                                        *\n");
    printf("\t*2-SOUNDEX                                            *\n");
    printf("\t*3-JARO-WINKLER                                       *\n");
    printf("\t*4-N-GRAMME                                           *\n");
    printf("\t*5-QUITTER                                            *\n");
    printf("\t*******************************************************\n");
    do
    {	
        scanf("%d",&choix);
        if (choix != 1 && choix != 2 &&choix != 3 &&choix != 4 &&choix != 5)
            printf("NOMBRE INCORRECT !!\n");
    }
    while(choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5);
    printf("CHOIX=%d\n",choix);
    switch(choix)
    {
        case 1:
        
        printf("VEUILLEZ TAPER LE NOM DE VOTRE FICHIER(AVEC SON FORMAT):\n");
        scanf("%s",nom_fichier);
        printf("NOM_FICHIER=%s\n",nom_fichier);
        printf("1\n");
        MappingToSet(nom_fichier);
        printf("1\n");
        tab_out = purge_Levenshtein(nom_fichier);
        printf("VOILA LES ELEMENTS DE VOTRE FICHIER:\n");
        while (tab[i])
        {
            printf("tab[%d] = %s\n",i,tab[i]);
            i++;
        }
        i = 0;
        printf("VOILA LES ELEMENTS DE VOTRE FICHIER FILTRER:\n");
        while (tab_out[i])
        {
            printf("tab_out[%d] = %s\n",i,tab_out[i]);
            i++;
        }
        printf("EST CE QUE VOUS VOULEZ TAPER VOTRE NOUVEAU TABLEAU DANS UN NOUVEAU FICHIER (1/0)?:\n");
        do
        {
            scanf("%d",&k);
            if (k != 1 && k != 0)
                printf("INCORRECT !! RETAPER SVP\n");
        }while(k != 1 && k != 0);
        if (k == 0)
        {
            printf("FIN\n\n\n");
            return (0);
        }
        else
        {   
            printf("DONNEZ LE NOM DE CE FICHIER:\n");
            scanf("%s",nom_fichier_out);
            write_tab_in_file(tab_out,nom_fichier_out);
            printf("LES ELEMENTS DE VOTRE FICHIER FILTRE SONT DANS: %s\n",nom_fichier_out);
            printf("POUR LE VOIR TAPEZ SUR TERMINAL LA COMMANDE (cat %s) \n",nom_fichier_out);
            printf("FIN\n\n\n");
            return(0);
        }
        case 2:
        printf("VEUILLEZ TAPER LE NOM DE VOTRE FICHIER(AVEC SON FORMAT):\n");
        scanf("%s",nom_fichier);
        printf("NOM_FICHIER=%s\n",nom_fichier);
        MappingToSet(nom_fichier);
        tab_out = purge_Soundex(nom_fichier);
        printf("VOILA LES ELEMENTS DE VOTRE FICHIER:\n");
        while (tab[i])
        {
            printf("tab[%d] = %s\n",i,tab[i]);
            i++;
        }
        i = 0;
        printf("VOILA LES ELEMENTS DE VOTRE FICHIER FILTRER:\n");
        while (tab_out[i])
        {
            printf("tab_out[%d] = %s\n",i,tab_out[i]);
            i++;
        }
        printf("EST CE QUE VOUS VOULEZ TAPER VOTRE NOUVEAU TABLEAU DANS UN NOUVEAU FICHIER (1/0)?:\n");
        do
        {
            scanf("%d",&k);
            if (k != 1 && k != 0)
                printf("INCORRECT !! RETAPER SVP\n");
        }while(k != 1 && k != 0);
        if (k == 0)
        {
            printf("FIN\n\n\n");
            return (0);
        }
        else
        {   
            printf("DONNEZ LE NOM DE CE FICHIER:\n");
            scanf("%s",nom_fichier_out);
            write_tab_in_file(tab_out,nom_fichier_out);
            printf("LES ELEMENTS DE VOTRE FICHIER FILTRE SONT DANS: %s\n",nom_fichier_out);
            printf("POUR LE VOIR TAPEZ SUR TERMINAL LA COMMANDE (cat %s) \n",nom_fichier_out);
            printf("FIN\n\n\n");
            return(0);
        }
        case 3:
        printf("VEUILLEZ TAPER LE NOM DE VOTRE FICHIER(AVEC SON FORMAT):\n");
        scanf("%s",nom_fichier);
        printf("NOM_FICHIER=%s\n",nom_fichier);
        MappingToSet(nom_fichier);
        tab_out = purge_Jaro(nom_fichier);
        printf("VOILA LES ELEMENTS DE VOTRE FICHIER:\n");
        while (tab[i])
        {
            printf("tab[%d] = %s\n",i,tab[i]);
            i++;
        }
        i = 0;
        printf("VOILA LES ELEMENTS DE VOTRE FICHIER FILTRER:\n");
        while (tab_out[i])
        {
            printf("tab_out[%d] = %s\n",i,tab_out[i]);
            i++;
        }
        printf("EST CE QUE VOUS VOULEZ TAPER VOTRE NOUVEAU TABLEAU DANS UN NOUVEAU FICHIER (1/0)?:\n");
        do
        {
            scanf("%d",&k);
            if (k != 1 && k != 0)
                printf("INCORRECT !! RETAPER SVP\n");
        }while(k != 1 && k != 0);
        if (k == 0)
        {
            printf("FIN\n\n\n");
            return (0);
        }
        else
        {   
            printf("DONNEZ LE NOM DE CE FICHIER:\n");
            scanf("%s",nom_fichier_out);
            write_tab_in_file(tab_out,nom_fichier_out);
            printf("LES ELEMENTS DE VOTRE FICHIER FILTRE SONT DANS: %s\n",nom_fichier_out);
            printf("POUR LE VOIR TAPEZ SUR TERMINAL LA COMMANDE (cat %s) \n",nom_fichier_out);
            printf("FIN\n\n\n");
            return(0);
        }         
        case 4:
        printf("VEUILLEZ TAPER LE NOM DE VOTRE FICHIER(AVEC SON FORMAT):\n");
        scanf("%s",nom_fichier);
        printf("NOM_FICHIER=%s\n",nom_fichier);
        MappingToSet(nom_fichier);
        tab_out = purge_Ngram(nom_fichier);
        printf("VOILA LES ELEMENTS DE VOTRE FICHIER:\n");
        while (tab[i])
        {
            printf("tab[%d] = %s\n",i,tab[i]);
            i++;
        }
        i = 0;
        printf("VOILA LES ELEMENTS DE VOTRE FICHIER FILTRER:\n");
        while (tab_out[i])
        {
            printf("tab_out[%d] = %s\n",i,tab_out[i]);
            i++;
        }
        printf("EST CE QUE VOUS VOULEZ TAPER VOTRE NOUVEAU TABLEAU DANS UN NOUVEAU FICHIER (1/0)?:\n");
        do
        {
            scanf("%d",&k);
            if (k != 1 && k != 0)
                printf("INCORRECT !! RETAPER SVP\n");
        }while(k != 1 && k != 0);
        if (k == 0)
        {
            printf("FIN\n\n\n");
            return (0);
        }
        else
        {   
            printf("DONNEZ LE NOM DE CE FICHIER:\n");
            scanf("%s",nom_fichier_out);
            write_tab_in_file(tab_out,nom_fichier_out);
            printf("LES ELEMENTS DE VOTRE FICHIER FILTRE SONT DANS: %s\n",nom_fichier_out);
            printf("POUR LE VOIR TAPEZ SUR TERMINAL LA COMMANDE (cat %s) \n",nom_fichier_out);
            printf("FIN\n\n\n");
            return(0);
        }         
        case 5:
        printf("FIN\n\n\n");
        return (0);
    }
    return(0);
}