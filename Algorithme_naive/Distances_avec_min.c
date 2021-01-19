#include "Set.h"

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

double      seuil(char *s1,char *s2)
{
    return(1.0 - ((double)(LevenshteinDistance(s1,s2))/maxi(strlen(s1),strlen(s2))));
}

static int max(int x, int y) {
    return x > y ? x : y;
}

static int min(int x, int y) {
    return x < y ? x : y;
}

double jaro_winkler_distance(const char *s, const char *a)
{
    int i, j, l;
    int m = 0, t = 0;
    int sl = strlen(s);
    int al = strlen(a);
    int sflags[sl], aflags[al];
    int range = max(0, max(sl, al) / 2 - 1);
    double dw;
    char *ss;
    char *aa;


    if (!sl || !al)
        return 0.0;

    ss = malloc(sl*sizeof(char));
    aa = malloc(al*sizeof(char));
    ss = ft_lower(s);
    aa = ft_lower(a);
    for (i = 0; i < al; i++)
        aflags[i] = 0;

    for (i = 0; i < sl; i++)
        sflags[i] = 0;

    /* calculate matching characters */
    for (i = 0; i < al; i++) {
        for (j = max(i - range, 0), l = min(i + range + 1, sl); j < l; j++) {
            if (aa[i] == ss[j] && !sflags[j]) {
                sflags[j] = 1;
                aflags[i] = 1;
                m++;
                break;
            }
        }
    }

    if (!m)
        return 0.0;

    /* calculate character transpositions */
    l = 0;
    for (i = 0; i < al; i++) {
        if (aflags[i] == 1) {
            for (j = l; j < sl; j++) {
                if (sflags[j] == 1) {
                    l = j + 1;
                    break;
                }
            }
            if (aa[i] != ss[j])
                t++;
        }
    }
    t /= 2;

    /* Jaro distance */
    dw = (((double)m / sl) + ((double)m / al) + ((double)(m - t) / m)) / 3.0;

    /* calculate common string prefix up to 4 chars */
    l = 0;
    for (i = 0; i < min(min(sl, al), 4); i++)
        if (ss[i] == aa[i])
            l++;

    /* Jaro-Winkler distance */
    dw = dw + (l * SCALING_FACTOR * (1 - dw));

    return dw;
}
//
//
//
//
//
//
//
//
//
//

int Min(int a, int b)
{
    return (a>b)? b:a;
}

int Max(int a, int b)
{
    return (a>b)? a:b;
}


// Livenshtein distance:

int Sub(char a , char b)
{
    return (a==b)? 0:1;
}

double LevenshteinDistance(char* x,char* y)
{
    int n,m;
    n = strlen(x);
    m = strlen(y);
    char *xx;
    char *yy;
    xx = ft_lower(x);
    yy = ft_lower(y);
    int T[n+1][m+1];
    T[0][0] = 0;
    for(int i=1;i < n+1;i++)
    {
        T[i][0] = T[i-1][0] + 1;
    }
    for(int j=1;j < m+1;j++)
    {
        T[0][j] = T[0][j-1] + 1;
    }
    for(int i=1;i<n+1;i++)
    {
        for(int j=1;j<m+1;j++)
        {
            T[i][j]=Min(T[i-1][j-1]+Sub(xx[i-1],yy[j-1]),Min(T[i-1][j]+1,T[i][j-1]+1));
        }
    }
    return (double)(T[n][m])/Max(n,m);
}
//
//
//
//
//
//
//
//
//
//
static char code[128] = { 0 };
void add_code(const char *s, int c)
{
	while (*s) {
		code[(int)*s] = code[0x20 ^ (int)*s] = c;
		s++;
	}
}


void init()
{
	static const char *cls[] =
		{ "AEIOU", "", "BFPV", "CGJKQSXZ", "DT", "L", "MN", "R", 0};
	int i;
	for (i = 0; cls[i]; i++)
		add_code(cls[i], i - 1);
}
 
/* returns a static buffer; user must copy if want to save
   result across calls */
char const *soundex(const char *s)
{
	static char out[5];
	int c, prev, i;
    char *ss;
	
    ss = malloc(strlen(s)*sizeof(char));
  	ss = ft_lower(s);
    init();
	out[0] = out[4] = 0;
	if (!ss || !*ss) return out;
 
	out[0] = *ss++;
 
	/* first letter, though not coded, can still affect next letter: Pfister */
	prev = code[(int)out[0]];
	for (i = 1; *ss && i < 4; ss++) {
		if ((c = code[(int)*ss]) == prev) continue;
 
		if (c == -1) prev = 0;	/* vowel as separator */
		else if (c > 0) {
			out[i++] = c + '0';
			prev = c;
		}
	}
	while (i < 4) out[i++] = '0';
	return out;
}
//
//
//
//
//
//
//
//
//
//

char* substring(const char* s, int offset, int n)
{
 if (s == 0 || strlen(s) == 0 || strlen(s) < offset || strlen(s) < (offset + n)) {
 return 0;
 }
 return strndup(s + offset, n);
}
double ngram_distance(const char *source, const char *target, int n)
{
    char *s1;
    char *s2;
 int sl = strlen(source);
 int tl = strlen(target);

    s1 = ft_lower(source);
    s2 = ft_lower(target);
 if (sl == 0 || tl == 0) {
 if (sl == tl) {
 return 1;
 }
 else {
 return 0;
 }
 }
 int cost = 0;
 if (sl < n || tl < n) {
 int ni = MIN(sl, tl);
 int i;
 for (i = 0; i < ni; i++) {
 if (s1[i] == s2[i]) {
 cost++;
 }
 }
 return (double)cost / (double)MAX(sl, tl);
 }
 int sa_len = sl + n - 1;
 char* sa = calloc(sa_len + 1, sizeof(char));
 if (!sa) {
 return -1;
 }
 double* p; // 'previous' cost array, horizontally
 double* d; // cost array, horizontally
 double* _d; // placeholder to assist in swapping p and d

 // construct sa with prefix
 int i;
 for (i = 0; i < sa_len; i++) {
 if (i < n - 1) {
 sa[i] = 0 ; //add prefix
 }
 else {
 sa[i] = s1[i - n + 1];
 }
 }
 int p_d_len = sl + 1;
 p = calloc(p_d_len + 1, sizeof(double));
 if (!p) {
 free(sa);
 return -1;
 }
 d = calloc(p_d_len + 1, sizeof(double));
 if (!d) {
 free(sa);
 free(p);
 return -1;
 }

 // indexes into strings s and t
 i = 0; // iterates through s1
 int j = 0; // iterates through s2

 char* t_j = calloc(n + 1, sizeof(char)); // jth n-gram of t
 if (!t_j) {
 free(sa);
 free(p);
 free(d);
 return -1;
 }
 for (i = 0; i <= sl; i++) {
 p[i] = i;
 }

 for (j = 1; j <= tl; j++) {
 // construct t_j n-gram
 if (j < n) {
 int ti;
 for (ti = 0; ti < n - j; ti++) {
 t_j[ti] = 0; //add prefix
 }
 for (ti = n - j; ti < n; ti++) {
 t_j[ti] = s2[ti - (n - j)];
 }
 }
 else {
 free(t_j);
 t_j = substring(s2, j - n, n);
 }
 d[0] = j;
 for (i = 1; i <= sl; i++) {
 cost = 0;
 int tn = n;
 // compare sa to t_j
 int ni;
 for (ni = 0; ni < n; ni++) {
 if (sa[i - 1 + ni] != t_j[ni]) {
 cost++;
 }
 else if (sa[i - 1 + ni] == 0) { //discount matches on prefix
 tn--;
 }
 }
 double ec = (double)cost / (double)tn;
 // minimum of cell to the left+1, to the top+1, diagonally left and up +cost
 d[i] = MIN(MIN(d[i - 1] + 1, p[i] + 1), p[i - 1] + ec);
 }
 // copy current distance counts to 'previous row' distance counts
 _d = p;
 p = d;
 d = _d;
 }
 double p_sl = p[sl];
 free(p);
 free(d);
 free(t_j);
 free(sa);
 // our last action in the above loop was to switch d and p, so p now
 // actually has the most recent cost counts
 return 1.0 - (p_sl / (double)MAX(tl, sl));
}