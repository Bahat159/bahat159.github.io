#define LOWER 0 
#define UPPER 300 
#define STEP 20 
#define MAXLINE 1000 /* maximum input line length */
#define VERTICAL_TAB '\013' /* ASCII vertical tab */
#define BELL_ '\007' /* ASCII bell character */
#define VERTICALTAB '\xb' /* ASCII vertical tab in hexadecimal */
#define BELL_CHAR '\x7' /* ASCII bell character in hexadecimal */
#define BUFSIZE 100
#define MAXVAL 100 /* maximum depth of val stack */

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

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
void reverse_string(char s[]);
int trim_character(char s[]);
int string_index(char s[], char t[]);
double ato_float(char s[]);
int ato_integer(char s[]);
void push_to_stack(double f);
double pop_from_stack(void);
int get_character(void);
void unget_character(int c);


enum boolean {NO, YES};
enum escapes { BELL = '\a', BACKSPACE = '\b', TAB = '\t', NEWLINE = '\n', VTAB = '\v', RETURN = '\r' };
enum months { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC }; /* FEB = 2, MAR = 3, etc. */