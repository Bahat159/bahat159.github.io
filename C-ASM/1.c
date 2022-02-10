#include <stdlib.h>
#include <stdio.h>



#define LOWER 0 
#define UPPER 300 
#define STEP 20 
#define MAXLINE 1000 /* maximum input line length */
#define VERTICAL_TAB '\013' /* ASCII vertical tab */
#define BELL_ '\007' /* ASCII bell character */
#define VERTICALTAB '\xb' /* ASCII vertical tab in hexadecimal */
#define BELL_CHAR '\x7' /* ASCII bell character in hexadecimal */

int calculate_fahrenhite();
int calculate_fahr_with_for_loop();
int power_function_call_by_value(int base, int n);
int getline_input(char line[], int maxline);
void copy_to_from(char to[], char from[]);
int copy_and_getline_main();
int string_length(char s[]);
int convert_to_lower_char(int c);
int generate_random(void);
int binary_search(int x, int v[], int n);
int alphabet_to_integer(char s[]);
void shell_sort(int v[], int n);

enum boolean {NO, YES};
enum escapes { BELL = '\a', BACKSPACE = '\b', TAB = '\t', NEWLINE = '\n', VTAB = '\v', RETURN = '\r' };
enum months { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC }; /* FEB = 2, MAR = 3, etc. */


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
