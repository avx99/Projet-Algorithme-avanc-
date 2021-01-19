#include "Tas.h"


//****************************************

char    *ft_lower(const char *str)
{
    char *s;
    int i;

    i  = 0;
    s = malloc(strlen(str)*sizeof(char));
    while (str[i])
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            s[i] = str[i] - ('A' - 'a');
        else
            s[i] = str[i];
        i++;
    } 
    return (s);
}

//****************************************

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

int		ft_strcmp(const char *s1, const char *s2)
{
	const char	*ptr1;
	const char	*ptr2;
	size_t			i;

	ptr1 = ft_lower(s1);
	ptr2 = ft_lower(s2);
	i = 0;
	while (ptr1[i] || ptr2[i])
	{
		if (ptr1[i] != ptr2[i])
		{

			return (ptr1[i] - ptr2[i]);
		
		}		
		i++;
	}
	return (0);
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


void swap_strings(char **s1, char **s2)
{
    char *temp = *s1;
        *s1 = *s2;
        *s2 = temp;
}

//****************************************************


void Ajout(char*s,char **tas)
{
    int i = 0;
    while(tas[i])
    {
        i++;
    }
    // tas[i] = strdup("");
    // tas[i] = ft_strjoin(tas[i],s);
    tas[i] = malloc(sizeof(char)*strlen(s));
    strcpy(tas[i],s);
    while(i>0 && ft_strcmp(tas[(i-1)/2],tas[i]) >= 0)
    {
        //echange
        swap_strings(&tas[(i-1)/2],&tas[i]);
        i = (i-1)/2;
    }
}


//****************************************************



char *ExtraireMin(char **tas)
{
    char *s;
    int index;
    int i;

    index = 0;
    i = 0;
    s = tas[0];
    while (tas[index])
        index++;
        if(--index > 0)
            tas[0] = tas[index];
    tas[index] = NULL;
    while ((((2 * i + 1)< index) && ft_strcmp(tas[2 * i + 1],tas[i]) < 0) || (((2 * i  + 2) < index) && ft_strcmp(tas[2 * i + 2],tas[i]) < 0))
    {
        if ((2 * i  + 2) >= index)
        {
                swap_strings(&tas[i],&tas[2 * i  + 1]);
                i = 2 * i  + 1;
                break ;

        }
        else
        {
            if (ft_strcmp(tas[2 * i + 1],tas[2 * i  + 2]) < 0)
            {
                swap_strings(&tas[i],&tas[2 * i  + 1]);
                i = 2 * i  + 1;
            }
            else
            {
                swap_strings(&tas[i],&tas[2 * i  + 2]);
                i = 2 * i  + 2;
            }
        }
    }
    return (s);
}

//****************************************************

char **LireToTas(char *fichier)
{
    int i = 0;
    int word_len = 0;
    int file_descriptor = open(fichier,O_RDONLY);
    //char *buffer;
    char buffer[1];
    char *string;
    int  n;
    //buffer = malloc(sizeof(char)*2);
    string = strdup("");
    //char **tas;
    tas = malloc(sizeof(char*));
    while((n=read(file_descriptor,buffer,1)))
    {
        buffer[n] = '\0';
        if(buffer[0] != '\n')
        {
            string = ft_strjoin(string,buffer);
            word_len++;
        }
        else
        {
            tas = realloc(tas,sizeof(char*)*(i+2));
            tas[i] = NULL;
            tas[i+1] = NULL;
            Ajout(string,tas);
            string = strdup("");
            i++;
            word_len = 0;
        }
    }
        tas[i] = malloc(sizeof(char)*word_len);
        strcpy(tas[i], string);
        tas = realloc(tas, (i+1) * sizeof(char*));
        tas[i + 1] = NULL;
    return (tas);
}

//****************************************************


char **MappingToTable(char *fichier)
{
    char **sorted_table;
    int i = 0;
    sorted_table = malloc(sizeof(char*)*2);
    LireToTas(fichier);
    while(tas[0])
    {
        sorted_table = realloc(sorted_table, sizeof(char*) * (i + 2));
        sorted_table[i] = ExtraireMin(tas);
        sorted_table[i + 1] = NULL;
        i++;
    }
    sorted_table[i] = NULL;
    return (sorted_table);
}



//****************************************************


char **purge_Levenshtein(char* fichier)
{
    int i=0;
    int j=0;
    char **out_table;
    char **tab;
    out_table = (char**)malloc(sizeof(char*)*2);
    out_table[1] = NULL;
    tab = MappingToTable(fichier);
    int z = 0;
    out_table[0] = strdup("");
    out_table[0] = ft_strjoin(out_table[0],tab[0]);
    i++;
    int x = 0;
    while(tab[i])
    {
        while(x>=0)
        {
            if(LevenshteinDistance(out_table[x],tab[i]) <= 0.8)
            {
               break;
            }
            else
            {
                j++;
                out_table = realloc(out_table,(2+j)*sizeof(char*));
                out_table[j] = malloc(sizeof(char)*strlen(tab[i]));
                out_table[j+1] = NULL;
                out_table[j] = strdup("");
                out_table[j] = ft_strjoin(out_table[j],tab[i]);
                x = -1;
            }
        }
        i++;
        x = j;
    }
    out_table[j+1] = NULL;
    return (out_table);
}



//****************************************************


char **purge_Jaro(char* fichier)
{
    int i=0;
    int j=0;
    char **out_table;
    char **tab;
    out_table = (char**)malloc(sizeof(char*)*2);
    out_table[1] = NULL;
    tab = MappingToTable(fichier);
    int z = 0;
    out_table[0] = strdup("");
    out_table[0] = ft_strjoin(out_table[0],tab[0]);
    i++;
    int x = 0;
    while(tab[i])
    {
        while(x>=0)
        {
            if(jaro_winkler_distance(out_table[x],tab[i]) >= 0.8)
            {
               break;
            }
            else
            {
                j++;
                out_table = realloc(out_table,(2+j)*sizeof(char*));
                out_table[j] = malloc(sizeof(char)*strlen(tab[i]));
                out_table[j+1] = NULL;
                out_table[j] = strdup("");
                out_table[j] = ft_strjoin(out_table[j],tab[i]);
                x = -1;
            }
        }
        i++;
        x = j;
    }
    out_table[j+1] = NULL;
    return (out_table);
}



//****************************************************



char **purge_Soundex(char* fichier)
{
    int i=0;
    int j=0;
    char *s1;
    char *s2;    
    char **out_table;
    char **tab;

    s1 = strdup("");
    s2 = strdup("");
    out_table = (char**)malloc(sizeof(char*)*2);
    out_table[1] = NULL;
    tab = MappingToTable(fichier);
    int z = 0;
    out_table[0] = strdup("");
    out_table[0] = ft_strjoin(out_table[0],tab[0]);
    i++;
    int x = 0;
    while(tab[i])
    {
        while(x>=0)
        {
            s1 = strdup("");
            s2 = strdup("");
            s1 = ft_strjoin(s1,(char *)soundex(out_table[x]));
            s2 = ft_strjoin(s2,(char *)soundex(tab[i]));
            if(ft_strcmp(s1,s2) == 0)
            {
                
               break;
            }
            else
            {
                j++;
                out_table = realloc(out_table,(2+j)*sizeof(char*));
                out_table[j] = malloc(sizeof(char)*strlen(tab[i]));
                out_table[j+1] = NULL;
                out_table[j] = strdup("");
                out_table[j] = ft_strjoin(out_table[j],tab[i]);
                x = -1;
            }
            free(s1);
            free(s2);
        }
        i++;
        x = j;
    }
    out_table[j+1] = NULL;
    return (out_table);
}

//****************************************************






char **purge_Ngram(char* fichier)
{
    int i=0;
    int j=0;
    char **out_table;
    char **tab;
    out_table = (char**)malloc(sizeof(char*)*2);
    out_table[1] = NULL;
    tab = MappingToTable(fichier);
    int z = 0;
    out_table[0] = strdup("");
    out_table[0] = ft_strjoin(out_table[0],tab[0]);
    i++;
    int x = 0;
    while(tab[i])
    {
        while(x>=0)
        {
            if(ngram_distance(out_table[x],tab[i],1) >= 0.75)
            {
               break;
            }
            else
            {
                j++;
                out_table = realloc(out_table,(2+j)*sizeof(char*));
                out_table[j] = malloc(sizeof(char)*strlen(tab[i]));
                out_table[j+1] = NULL;
                out_table[j] = strdup("");
                out_table[j] = ft_strjoin(out_table[j],tab[i]);
                x = -1;
            }
        }
        i++;
        x = j;
    }
    out_table[j+1] = NULL;
    return (out_table);
}
