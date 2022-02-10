#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utility.h"


int main_with_command_line_argument(int argc, char *argv[]){
    int i;
    for (i = 1; i < argc; i++){
        printf("%s%s", argv[i], (i < argc -1 ) ? " ": "");
    }
    printf("\n");
    return 0;
}

int main_with_commandline_argument(int argc, char *argv[]){
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;
    while (--argc > 0 && (*++argv)[0] == '-'){
        while (c = *++argv[0]){
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                printf("find: illegal option %c\n", c);
                argc = 0;
                found = -1;
                break;
            }
        }
    }
    if (argc != 1){
        printf("Usage: find -x -n pattern\n");
    }
    else {
        printf("Line Pattern\n");
        printf("Program argument: [%s]\nProgram command line argument functional\n", *argv);
    }
    return 0;
}

int main(){
    char *s = "This is from Busari Habibullaah";
    char *t = "String comparison function implemented in pointers";
    char message[200] = "\nWelcome, Busari Habibullaah\nC/CPP/ASM Programming\nMalware analysis and Reverse Engineering";
    int check_return_value = 0;
    int month_name_by_number = 5;
    printf("\n%s\n",message);
    printf("===========End of Introduction==============\n");
    int string_length = string_length_with_pointer("Hello World");
    int space_to_allocate = 10000;
    char *allocated_space = memory_allocator(space_to_allocate);
    printf("String length input: %d\n", string_length);
    if (allocated_space){
        printf("Allocated Space from Memory: %d\n", *allocated_space);
    }
    else{
        printf("Unable to allocated space from memory!!\n");
    }
    int returned_value = string_compare(s, t);
    if(returned_value != check_return_value){
        printf("Returned Value: %d\n", returned_value);
    }
    char *monthname = month_name(month_name_by_number);
    printf("Month Name: %s\nMonth Number: %d\n", monthname, month_name_by_number);
    exit(0);
}

int calculate_fahrenhite(){
    int fahr, celcius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;

    while(fahr <= upper){
        celcius = 5 * (fahr-32);
        printf("%d\t%d\n", fahr, celcius);
        fahr = fahr + step;
    }
}

int calculate_fahr_with_for_loop(){
    int fahr;
    for (fahr = 0; fahr <= 300; fahr = fahr + 20)
    printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
}

int power_function_call_by_value(int base, int n){
    int p;

    for (p = 1; n > 0; --n){
        p = p * base;
        return p;
    }
}

/* getline() */
int getline_input(char s[],int lim){
    int c, i;
    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i){
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* copy() */
void copy_to_from(char to[], char from[]){
    int i;
    i = 0;

    while ((to[i] = from[i]) != '\0'){
        ++i;
    }
}


int copy_and_getline_main(){
    int len; /* current line length */
    int max; /* maximum length seen so far */
    char line[MAXLINE]; /* current input line */
    char longest[MAXLINE]; /* longest line saved here */

    max = 0;
    while((len = getline_input(line, MAXLINE)) > 0){
        if (len > max){
            max = len;
            copy_to_from(longest, line);
        }
    }
    if (max > 0){
        printf("%s", longest);
    }
    return 0;
}

int string_length(char s[]){
    int i;
    while (s[i] != '\0'){
        ++i;
    }
    return i;
}

int convert_to_lower_char(int c){
    if (c >= 'A' && c <= 'Z'){
        return c + 'a' - 'A';
    }
    else {
        return c;
    }
}

unsigned long int next = 1;
/* rand: return pseudo-random integer on 0..32767 */
int generate_random(void){
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % 32768;
}

void s_rand(unsigned int seed){
    next = seed;
}


int binary_search(int x, int v[], int n){
    int low, high, mid;

    low = 0;
    high = n - 1;
    while(low <= high){
        mid = (low + high) / 2;
        if (x < v[mid]){
            high = mid + 1;
        }
        else if (x > v[mid]){
            low = mid + 1;
        }
        else {
            return mid;
        }
    }
    return -1;   /* no match */
}

/* atoi() */
int alphabet_to_integer(char s[]){
    int i, n, sign;

    for (i = 0; isspace(s[i]); i++){
        ;
    }
    sign = (s[i] == '-') ? -1 : 1;
    if(s[i] == '+' || s[i] == '-'){
        i++;
    }
    for (n = 0; isdigit(s[i]); i++){
        n = 10 * n + (s[i] - '0');
    }
    return sign * n;
}

void shell_sort(int v[], int n){
    int gap, i, j, temp;

    for(gap = n/2; gap > 0; gap /= 2){
        for (i = gap; i< n; i++){
            for (j=i-gap; j>=0 && v[j] > v[j+gap]; j -= gap){
                temp = v[j];
                v[j] = v[j+gap];
                v[j+gap] = temp;
            }
        }
    }
}

void reverse_string(char s[]){
    int c,i,j;

    for(i = 0, j = strlen(s) - 1; i < j; i++, j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int trim_character(char s[]){
    int n;
    for (n = string_length(s)-1; n >= 0; n--){
        if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
        break;
    }
    s[n+1] = '\0';
    return n;
}

/* Function */

/* string_index: return index of t in s, -1 if none */
int string_index(char s[], char t[]){
    int i, j, k;
    for (i = 0; s[i] != '\0'; i++) {
        for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
        ;
        if (k > 0 && t[k] == '\0'){
            return i;
        }
    }
    return -1;
}

/* ato_float: convert string s to double */
double ato_float(char s[]){
    double val, power;
    int i, sign;
    for (i = 0; isspace(s[i]); i++){
        ;
    }
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-'){
        i++;
    }
    for (val = 0.0; isdigit(s[i]); i++){
        val = 10.0 * val + (s[i] - '0');
    }
    if (s[i] == '.'){
        i++;
    }
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    return sign * val / power;
}

int ato_integer(char s[]){
    double ato_float(char s[]);
    return (int) ato_float(s);
}


/* push: push f onto value stack */
void push_to_stack(double f){
    if (sp < MAXVAL){
        val[sp++] = f;
    }
    else{
        printf("error: stack full, can't push %g\n", f);
    }
}

/* pop: pop and return top value from stack */
double pop_from_stack(void){
    if (sp > 0){
        return val[--sp];
    }
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* get a (possibly pushed-back) character */
int get_character(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void unget_character(int c) {
    if (bufp >= BUFSIZE){
        printf("ungetch: too many characters\n");
    }
    else{
        buf[bufp++] = c;
    }
}

/* Recursion */

void print_in_decimal_places(int n){
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n / 10){
        print_in_decimal_places(n / 10);
        putchar(n % 10 + '0');
    }
}


/* quick_sort: sort v[left]...v[right] into increasing order */
void quick_sort(int v[], int left, int right){
    int i, last;
    void swap_data(int v[], int i, int j);
    if (left >= right){   /* do nothing if array contains */
        return;          /* fewer than two elements */
    }
    swap_data(v, left, (left + right)/2); /* move partition elem */
    last = left; /* to v[0] */
    for (i = left + 1; i <= right; i++){
        if (v[i] < v[left]){
            swap_data(v, ++last, i);
        }
    }
    swap_data(v, left, last); /* restore partition elem */
    quick_sort(v, left, last-1);
    quick_sort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap_data(int v[], int i, int j){
    int temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


/* Pointers and Function Arguments */

void swap_data_with_pointer(int *px, int *py){
    int temp;

    temp = *px;
    *px = *py;
    *py = temp;
}

/* getint: get next integer from input into *pn */
int get_integer(int *pn){
    int c, sign;

    while(isspace(c = get_character())){
        ;
    }
    if (!isdigit(c) && c != EOF && c != '+' && c != '-'){
        unget_character(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if(c == '+' || c == '-'){
        c = get_character();
    }
    for (*pn = 0; isdigit(c); c = get_character()){
        *pn = 10 * *pn + (c - '0');
    }
    *pn *= sign;
    if(c != EOF){
        unget_character(c);
    }
    return c;
}

/* Pointers and Arrays */


/* strlen: return length of string s */
int string_length_with_pointer(char *s){
    int n;
    for(n = 0; *s != '\0'; s++){
        n++;
    }
    return n;
}


char *memory_allocator(int n){
    if (allocbuf + ALLOCSIZE - allocp >= n){
        allocp += n;
        return allocp - n;
    }
    else{
        return 0;
    }
}

void after_use_free(char *p){
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE){
        allocp = p;
    }
}

/* Character Pointers and Functions */

void copy_to_from_using_pointer(char *s, char *t){
    while((*s = *t) != '\0'){
        ;
    }
}


int string_compare(char *s, char *t){
    for(; *s == *t; s++, t++){
        if(*s == '\0'){
            return 0;
        }
    }
    return *s - *t;
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day){
    int i, leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for(i = 1; i < month; i++){
        day += daytab[leap][i];
    }
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday){
    int i, leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; yearday > daytab[leap][i]; i++){
        yearday -= daytab[leap][i];
    }
    *pmonth = i;
    *pday = yearday;
}

/* Initialization of Pointer Arrays */
char *month_name(int n){
    static char *name[] = {
        "Illegal month",
        "January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"
    };
    return (n < 1 || n > 12) ? name[0] : name[n];
}

/* numcmp: compare s1 and s2 numerically */
int numb_compare(char *s1, char *s2){
    double v1, v2;
    v1 = ato_float(s1);
    v2 = ato_float(s2);

    if(v1 < v2){
        return -1;
    }
    else if(v1 > v2){
        return 1;
    }
    else {
        return 0;
    }
}

/* Complicated Declarations */
/*
int *f();           f: function returning pointer to int 
int (*pf)();        pf: pointer to function returning int 
char **argv;        argv: pointer to char
int (*daytab)[13]   daytab: pointer to array[13] of int
int *daytab[13]     daytab: array[13] of pointer to int
void *comp()        comp: function returning pointer to void
*/


int get_token(void){
    int c, get_character(void);
    void unget_character(int);
    char *p = token;

    while((c = get_character()) == ' ' || c == '\t'){
        ;
    }
    if (c == '('){
        if ((c = get_character()) == ')'){
            copy_to_from_using_pointer(token, " () ");
            return tokentype = PARENS;
        }
        else {
            unget_character(c);
            return tokentype = '(';
        }
    }
    else if(c == '['){
        for(*p++ = c; (*p++ = get_character()) != ']';){
            ;
        }
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c)){
        for (*p++ = c; isalnum(c = get_character()); ){
            *p++ = c;
        }
        *p = '\0';
        unget_character(c);
        return tokentype = NAME;
    }
    else {
        return tokentype = c;
    }
}

void parse_declarator(void){
    int ns;
    for (ns = 0; get_token() == '*';){    /* count *'s */
        ns++;
    }
    parse_direct_declarator();
    while(ns-- > 0){
        strcat(out, " pointer to");
    }
}

void parse_direct_declarator(void){
    int type;
    if(tokentype == '('){
        parse_declarator();
        if (tokentype != ')'){
            printf("error: missing ) \n");
        }
        else if(tokentype == NAME){    /* variable name */
            copy_to_from_using_pointer(name, token);
        }
    }
    else {
        printf("eror: expected name or (parse_declarator)\n");
    }
    while((type = get_token()) == PARENS || type == BRACKETS){
        if (type = PARENS){
            strcat(out, " function returning");
        }
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}
