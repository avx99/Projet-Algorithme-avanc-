#ifndef _SET_H_
#define _SET_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <time.h>
#define SCALING_FACTOR 0.1
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

char    **tab;
char    **MappingToSet(char *fichier);
char    **purge_Soundex(char *fichier);
char    **purge_Jaro(char *fichier);
char    **purge_Levenshtein(char *fichier);
char    **purge_Ngram(char *fichier);
char	*ft_strjoin(char *s1, char *s2);
void    write_tab_in_file(char **t,char *str);
//les distances
char const *soundex(const char *s);
void    add_code(const char *s, int c);
void    init();
double ngram_distance(const char *source, const char *target, int n);
//static  int max(int x, int y);
//static  int min(int x, int y);
int     min2 (const int a, const int b);
int     min3 (const int a, const int b, const int c);
double     LevenshteinDistance(char *s, char *t);
double  jaro_winkler_distance(const char *s, const char *a);
double      seuil(char *s1,char *s2);
int maxi(int x, int y);

#endif