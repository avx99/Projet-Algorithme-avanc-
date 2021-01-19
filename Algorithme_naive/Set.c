#include "Set.h"

int maxi(int x, int y)
{
    return x > y ? x : y;
}
//**************************************

int mini(int x, int y)
{
    return x < y ? x : y;
}

//**************************************
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
//****************************************
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
	return (temp);
}
//****************************************************
char    **MappingToSet(char *fichier)
{
    char *str;
    int word_len;
    int word_number;
    int fd;
    char *buff;
    int k = 2;
    int n;
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
            tab[word_number] = malloc(sizeof(char) * word_len);
            strcpy(tab[word_number],str);
            str = strdup(str + word_len);
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


//*****************************************************

char    **purge_Levenshtein(char *fichier)
{
    char **out;
    int k;
    int i;
    int j;
    int counter;
    int fd;
    double d;

    fd = open(fichier,O_RDONLY);
    counter = 0;
    i = 0;
    j = 0;
    k = 2;
    if (tab[i] == NULL)
        return (NULL); 
    out = malloc(sizeof(char *)*k);
    out[j] = malloc(sizeof(char)*(1 + strlen(tab[i])));
    out[j] = strdup("");
    out[j] = ft_strjoin(out[j],tab[i]);
    i++;
    j++;
        while (counter <= j)
        {
            if (counter == j)
            {
                k++;
                out = realloc(out,k * sizeof(char*));
                out[j] = malloc(sizeof(char)*(1 + strlen(tab[i])));              
                out[j] = strdup("");
                out[j] = ft_strjoin(out[j],tab[i]);
                if (tab[i+1] == NULL)
                {
                    out[j+1] = NULL;   //we may have a problem in memorey we should use k not j
                    return(out);
                } 
                j++;
                i++;
                counter = 0;
            }
            if (counter != j)
            {
                if (LevenshteinDistance(tab[i],out[counter]) <= 0.4)
                {
                    i++;
                    counter = 0;
                }
                if (tab[i] == NULL)
                    return (out);
                if (LevenshteinDistance(tab[i],out[counter]) > 0.4)    //here we should use n not zero
                    counter++;
            }
        }
    return (NULL);
}


//*****************************************************
char    **purge_Jaro(char *fichier)
{
    char **out;
    int k;
    int i;
    int j;
    int counter;
    int fd;

    fd = open(fichier,O_RDONLY);
    counter = 0;
    i = 0;
    j = 0;
    k = 2;
    if (tab[i] == NULL)
        return (NULL); 
    out = malloc(sizeof(char *)*k);
    out[j] = malloc(sizeof(char)*(1 + strlen(tab[i])));
    out[j] = strdup("");
    out[j] = ft_strjoin(out[j],tab[i]);
    i++;
    j++;
        while (counter <= j)
        {
            if (counter == j)
            {
                k++;
                out = realloc(out,k * sizeof(char*));
                out[j] = malloc(sizeof(char)*(1 + strlen(tab[i])));              
                out[j] = strdup("");
                out[j] = ft_strjoin(out[j],tab[i]);
                if (tab[i+1] == NULL)
                {
                    out[j+1] = NULL;   //we may have a problem in memorey we should use k not j
                    return(out);
                } 
                j++;
                i++;
                counter = 0;
            }
            if (counter != j)
            {
                if (jaro_winkler_distance(tab[i],out[counter]) >= 0.8)
                {
                    i++;
                    counter = 0;
                }
                if (tab[i] == NULL)
                    return (out);
                if (jaro_winkler_distance(tab[i],out[counter]) < 0.8)
                    counter++;
            }
        }
    return (NULL);
}
//*****************************************************
char    **purge_Soundex(char *fichier)
{
    char **out;
    int k;
    int i;
    int j;
    int counter;
    int fd;
    char *s1;
    char *s2;

    fd = open(fichier,O_RDONLY);
    counter = 0;
    i = 0;
    j = 0;
    k = 2;
    if (tab[i] == NULL)
        return (NULL); 
    out = malloc(sizeof(char *)*k);
    out[j] = malloc(sizeof(char)*(1 + strlen(tab[i])));
    out[j] = strdup("");
    out[j] = ft_strjoin(out[j],tab[i]);
    i++;
    j++;
        while (counter <= j)
        {
            if (counter == j)
            {
                k++;
                out = realloc(out,k * sizeof(char*));
                out[j] = malloc(sizeof(char)*(1 + strlen(tab[i])));              
                out[j] = strdup("");
                out[j] = ft_strjoin(out[j],tab[i]);
                if (tab[i+1] == NULL)
                {
                    out[j+1] = NULL;   //we may have a problem in memorey we should use k not j
                    return(out);
                } 
                j++;
                i++;
                counter = 0;
            }
            if (counter != j)
            {
                s1 = strdup("");
                s2 = strdup("");
                s1 = ft_strjoin(s1,(char *)soundex(tab[i]));
                s2 = ft_strjoin(s2,(char *)soundex(out[counter]));
                if (strcmp(s1,s2) != 0)
                    counter++;
                if (strcmp(s1,s2) == 0)
                {
                    i++;
                    counter = 0;
                }
                if (tab[i] == NULL)
                    return (out);

            }
            free(s1);
            free(s2);
        }
    return (NULL);
}


//*****************************************************

char    **purge_Ngram(char *fichier)
{
    char **out;
    int k;
    int i;
    int j;
    int counter;
    int fd;

    fd = open(fichier,O_RDONLY);
    counter = 0;
    i = 0;
    j = 0;
    k = 2;
    if (tab[i] == NULL)
        return (NULL); 
    out = malloc(sizeof(char *)*k);
    out[j] = malloc(sizeof(char)*(1 + strlen(tab[i])));
    out[j] = strdup("");
    out[j] = ft_strjoin(out[j],tab[i]);
    i++;
    j++;
        while (counter <= j)
        {
            if (counter == j)
            {
                k++;
                out = realloc(out,k * sizeof(char*));
                out[j] = malloc(sizeof(char)*(1 + strlen(tab[i])));              
                out[j] = strdup("");
                out[j] = ft_strjoin(out[j],tab[i]);
                if (tab[i+1] == NULL)
                {
                    out[j+1] = NULL;   //we may have a problem in memorey we should use k not j
                    return(out);
                } 
                j++;
                i++;
                counter = 0;
            }
            if (counter != j)
            {
                if (ngram_distance(tab[i],out[counter],1) >= 0.75)
                {
                    i++;
                    counter = 0;
                }
                if (tab[i] == NULL)
                    return (out);
                if (ngram_distance(tab[i],out[counter],1) < 0.75)
                    counter++;
            }
        }
    return (NULL);
}
