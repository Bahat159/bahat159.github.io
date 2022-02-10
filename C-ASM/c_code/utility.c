#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utility.h"


int main(){
    int i = 1;
    long testvalue = 150;
    char message[22] = {"This is a test message"};

    printf("\nBusari Habibullaah back to C/CPP Programming language\n");
    printf("\n{%s}\n",message);
    printf("%ld\n", testvalue);
    printf("=============with While Loop================\n");
    calculate_fahrenhite();
    printf("==============With For Loop=================\n");
    /*calculate_fahr_with_for_loop(); */

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

