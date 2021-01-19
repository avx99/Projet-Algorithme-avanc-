
#include "HashTable.h"





void    write_tab_in_file(char **t,char *str)
{
    int i;
    int fd;

    i = 0;
    FILE *fp = NULL;
    fp = fopen(str,"a");
    fclose(fp);
    fd = open(str,O_WRONLY);
    while (t[i])
    {
        write(fd,t[i],strlen(t[i]));
        write(fd,"\n",1);
        i++;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

char		*ft_strjoin(char *s1, char *s2)
{
	char	*temp;
	size_t	a;
	size_t	b;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	a = strlen(s1);
	b = strlen(s2);
	temp = malloc(sizeof(char) * (a + b + 1));
	if (temp == NULL)
		return (NULL);
	strcpy(temp, (char*)s1);
	strcat(temp, (char*)s2);
    //free(s1);
    //free(s2);
	return (temp);
}


////////////////////////////////////////////////////////////////////////////



char    **MappingToSet(char *fichier)
{
    char *str;
    int word_len;
    char *buff;
    int k = 2;
    int n;
    char **tab;
    char *temp;
    int fd;

    fd = open(fichier,O_RDONLY);
    buff = malloc(sizeof(char)*2);
    tab = (char **)(malloc(sizeof(char*)*1));
    word_len = 0;
    word_number = 0;
    str = strdup("");
    while ((n=read(fd,buff,1)) > 0)
    {
        buff[n] = '\0';
        if (buff[0] != '\n' && buff[0] != '\0')
        {
            str = ft_strjoin(str,buff);
            word_len++;
        }
         if (buff[0] == '\n' )
        {
            str[word_len] = '\0';
            tab[word_number] = malloc(sizeof(char) * (word_len+1));
            strcpy(tab[word_number],str);
             str = strdup(str + word_len);
            // free(str);
            // str = strdup("");
            word_number++;
            tab = realloc(tab,k * sizeof(char*));
            k++;
            word_len = 0;
        }
    }
    tab[word_number] = malloc(sizeof(char) * word_len);
    strcpy(tab[word_number], str);
    tab = realloc(tab, (k-1) * sizeof(char*));
    tab[word_number + 1] = NULL;
    return (tab);   
}


/////////////////////////////////////////////////////////////////////

int     CalculHashe(char *str)
{
    int s;
    int j;

    j = 0;
    s = 0;
    while (str[j])
    {
        if (str[j] >= 'A' && str[j] <= 'Z')
        {
            s = s + str[j] - ('A' - 'a');
            j++;
        }
        else
        {
            s = s + str[j];
            j++;
        }
        
    }
    return (s%word_number);
}

///////////////////////////////////////////////////////////////////////

void    ajoutMot(node **hash_table,char *str)
{
    int i;
    int key;
    //char *temp;

    key = CalculHashe(str);
    i = 0;
    if (hash_table[key] == NULL)
    {
        //temp = str;
        hash_table[key] = malloc(sizeof(node));
        hash_table[key]->key = key;
        hash_table[key]->content = malloc(sizeof(char)*strlen(str));
        hash_table[key]->content = strdup("");
        hash_table[key]->content = ft_strjoin(hash_table[key]->content,str);
        //hash_table[key]->content = strdup(str);
        hash_table[key]->next = NULL;
        //free(temp);
    }
    else
    {
        node *temp;
        node *new;
        temp = malloc(sizeof(node));
        new = malloc(sizeof(node));
        temp = hash_table[key];
        while (temp->next != NULL)
            temp = temp->next;
        new->content = str;
        new->next = NULL;
        temp->next = new;
    }
}

/////////////////////////////////////////////////////////////////////

node    **MappingToHashTable(char *fichier)
{
    char **tab;
    node **hash_table;
    int i;
    int fd;
    
    i = 0;
    fd = open(fichier,O_RDONLY);
    tab = MappingToSet(fichier);
    hash_table = malloc(sizeof(node*)*word_number);
    while (i < word_number+1)
    {
        hash_table[i] = NULL;
        i++;
    }
    i=0;
    while (i <= word_number)
    {
        ajoutMot(hash_table,tab[i]);
        i++;
    }
    //free(tab);
    return (hash_table);
}

//////////////////////////////////////////////////////////////////////

list *creat_list(char *fichier)
{
    int i;
    int j;
    list *tab;
    node **hash_table;
    node *temp;

    hash_table = MappingToHashTable(fichier);
    tab = malloc(word_number*sizeof(list));
    i = 0;
    j = 0;
    while (i < word_number)
    {
        while (hash_table[i] == NULL && i>=word_number)
            i++;
        temp = malloc(sizeof(node));
        temp = hash_table[i];
        while (temp != NULL)
        {      
            tab[j].content = malloc(strlen(temp->content)*sizeof(char));
            //tab[j].content = strdup("");
            tab[j].content = strdup(temp->content);
            tab[j].key = hash_table[i]->key;
            temp = temp->next;
            j++;
        }
        free(temp);
        i++;
    }
    return (tab);
}

////////////////////////////////////////////////////////////////////////////

char    **purge_Levenshtein(char *fichier)
{
    char **out;
    list *tab;
    int i;
    int j;
    int jj;
    int k;
    int p;
    int cle;
    int counter;
    //int fd;

    //fd = open(fichier,O_RDONLY);
    i = 0;
    j = 0;
    k = 2;
    tab = creat_list(fichier);
    out = malloc(k*sizeof(char *));
    while (i <= word_number)
    {
        p = i+1;
        counter = 1;
        while (counter <= 6 && p<=word_number)
        {
            cle = tab[p].key;
            while (cle == tab[p].key && p<=word_number)
            {
                if (LevenshteinDistance(tab[i].content,tab[p].content) <= 0.4)
                {
                    counter = 7;
                    break;
                }
                else
                    p++;
            }
            counter++;
            if (counter == 6 || p > word_number)
            {
                out[j] = malloc(strlen(tab[i].content)*sizeof(char));
                out[j] = strdup("");
                out[j] = ft_strjoin(out[j],tab[i].content);
                //printf("coun=%d**p=%d**out[%d] = %s\n",counter,p,j,out[j]);
                k++;
                out = realloc(out,k*sizeof(char *));
                j++;
                counter++;
            }
        }
        i++;
    }
    out[j] = malloc(strlen(tab[word_number].content)*sizeof(char));
    out[j] = strdup("");
    out[j] = ft_strjoin(out[j],tab[word_number].content);
    out[j+1]=NULL;
    return (out);
}

//////////////////////////////////////////////////////////////////////////////


char    **purge_Jaro(char *fichier)
{
    char **out;
    list *tab;
    int i;
    int j;
    int jj;
    int k;
    int p;
    int cle;
    int counter;
    //int fd;

    //fd = open(fichier,O_RDONLY);
    i = 0;
    j = 0;
    k = 2;
    tab = creat_list(fichier);
    out = malloc(k*sizeof(char *));
    while (i <= word_number)
    {
        p = i+1;
        counter = 1;
        while (counter <= 6 && p<=word_number)
        {
            cle = tab[p].key;
            while (cle == tab[p].key && p<=word_number)
            {
                if (jaro_winkler_distance(tab[i].content,tab[p].content) >= 0.8)
                {
                    counter = 7;
                    break;
                }
                else
                    p++;
            }
            counter++;
            if (counter == 6 || p > word_number)
            {
                out[j] = malloc(strlen(tab[i].content)*sizeof(char));
                out[j] = strdup("");
                out[j] = ft_strjoin(out[j],tab[i].content);
                k++;
                out = realloc(out,k*sizeof(char *));
                j++;
                counter++;
            }
        }
        i++;
    }
    out[j] = malloc(strlen(tab[word_number].content)*sizeof(char));
    out[j] = strdup("");
    out[j] = ft_strjoin(out[j],tab[word_number].content);
    out[j+1]=NULL;
    return (out);
}
//////////////////////////////////////////////////////////////////////////////
char    **purge_Soundex(char *fichier)
{
    char **out;
    list *tab;
    char *s1;
    char *s2;
    int i;
    int j;
    int jj;
    int k;
    int p;
    int cle;
    int counter;
    //int fd;

    //fd = open(fichier,O_RDONLY);
    i = 0;
    j = 0;
    k = 2;
    tab = creat_list(fichier);
    out = malloc(k*sizeof(char *));
    while (i < word_number)
    {
        p = i+1;
        counter = 1;
        while (counter <= 6 && p<word_number)
        {
            cle = tab[p].key;
            while (cle == tab[p].key && p<word_number)
            {
                s1 = strdup(soundex(tab[i].content));
                s2 = strdup(soundex(tab[p].content));
                if (strcmp(s1,s2) == 0)
                {
                    counter = 7;
                    break;
                }
                else
                    p++;
                free(s1);
                free(s2);
            }
            counter++;
            if (counter == 6 || p == word_number)
            {
                out[j] = malloc(strlen(tab[i].content)*sizeof(char));
                out[j] = strdup("");
                out[j] = ft_strjoin(out[j],tab[i].content);
                k++;
                out = realloc(out,k*sizeof(char *));
                j++;
                counter++;
            }
            if (tab[i].key == tab[word_number - 1].key)
            {
                while (i < word_number)
                {
                    counter = i+1;
                    while (counter < word_number)
                    {
                        s1 = strdup(soundex(tab[i].content));
                        s2 = strdup(soundex(tab[p].content));
                        if (strcmp(s1,s2) == 0)
                        {
                            i++;
                            break;
                        }
                        else
                            counter++;
                        free(s1);
                        free(s2);
                    }
                    if (counter == word_number)
                    {
                        out[j] = malloc(strlen(tab[i].content)*sizeof(char));
                        out[j] = strdup("");
                        out[j] = ft_strjoin(out[j],tab[i].content);
                        k++;
                        out = realloc(out,k*sizeof(char *));
                        j++;
                        break;
                    }
                }
            }
        }
        i++;
    }
    // out[j] = malloc(strlen(tab[word_number-1].content)*sizeof(char));
    // out[j] = strdup("");
    // out[j] = ft_strjoin(out[j],tab[word_number-1].content);
    out[j]=NULL;
    return (out);
}

//////////////////////////////////////////////////////////////////////////////


char    **purge_Ngram(char *fichier)
{
    char **out;
    list *tab;
    int i;
    int j;
    int jj;
    int k;
    int p;
    int cle;
    int counter;
    //int fd;

    //fd = open(fichier,O_RDONLY);
    i = 0;
    j = 0;
    k = 2;
    tab = creat_list(fichier);
    out = malloc(k*sizeof(char *));
    while (i <= word_number)
    {
        p = i+1;
        counter = 1;
        while (counter <= 6 && p<=word_number)
        {
            cle = tab[p].key;
            while (cle == tab[p].key && p<=word_number)
            {
                if (ngram_distance(tab[i].content,tab[p].content,1) >= 0.75)
                {
                    counter = 7;
                    break;
                }
                else
                    p++;
            }
            counter++;
            if (counter == 6 || p > word_number)
            {
                out[j] = malloc(strlen(tab[i].content)*sizeof(char));
                out[j] = strdup("");
                out[j] = ft_strjoin(out[j],tab[i].content);
                k++;
                out = realloc(out,k*sizeof(char *));
                j++;
                counter++;
            }
            // if (tab[i].key == tab[word_number].key)
            // {
            //     while (i < word_number)
            //     {
            //         counter = i+1;
            //         while (counter < word_number)
            //         {
            //             if (LevenshteinDistance(tab[counter].content,tab[i].content) <= 0.4)
            //             {
            //                 i++;
            //                 break;
            //             }
            //             else
            //                 counter++;
            //         }
            //         if (counter == word_number)
            //         {
            //             out[j] = malloc(strlen(tab[i].content)*sizeof(char));
            //             out[j] = strdup("");
            //             out[j] = ft_strjoin(out[j],tab[i].content);
            //             printf("----------***out[%d] = %s\n",j,out[j]);
            //             k++;
            //             out = realloc(out,k*sizeof(char *));
            //             j++;
            //             break;
            //         }
            //     }
            // }
        }
        i++;
    }
    out[j] = malloc(strlen(tab[word_number].content)*sizeof(char));
    out[j] = strdup("");
    out[j] = ft_strjoin(out[j],tab[word_number].content);
    out[j+1]=NULL;
    return (out);
}