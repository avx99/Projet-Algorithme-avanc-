#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>
#define SCALING_FACTOR 0.1
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


typedef struct l{
    char *content;
    int key;
}list;

typedef struct el
{
    char *content;
    int key;
    struct el *next;
}node;

int     word_number;


char        **MappingToSet(char *fichier);
node        **MappingToHashTable(char *fichier);
char        **purge_Soundex(char *fichier);
char        **purge_Jaro(char *fichier);
char        **purge_Levenshtein(char *fichier);
char        **purge_Ngram(char* fichier);
char	    *ft_strjoin(char *s1, char *s2);
void        write_tab_in_file(char **t,char *str);
list        *creat_list(char *fichier);
int         CalculHashe(char *str);
void        ajoutMot(node **hash_table,char *str);
//les distances
char const *soundex(const char *s);
double      ngram_distance (const char *source, const char *target, int n);
void        add_code(const char *s, int c);
void        init();
int         min2 (const int a, const int b);
int         min3 (const int a, const int b, const int c);
double      LevenshteinDistance(char *s, char *t);
double      jaro_winkler_distance(const char *s, const char *a);

#endif
