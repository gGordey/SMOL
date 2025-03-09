// this is an expanded version of classicsmol interpreter, made so you can read this code and understand how exactely classicsmol works
// obviously it works a bit different because in original code I used logical expressions as 'if' statements
// but here, for readability I made code as understandable as I can.
// At the very end of this file you can read about some tricks I used to make the smaller and smaller
#include <stdio.h>
#define TOK(x) *(code+c+x) // c is always pointing to the first token in the line, so TOK(0) is keyword itself, TOK(1) in next etc.
#define pint(location) location%16+(location>>8)%16*10+(location>>16)%16*100
// pint is made just to optimaze space usage, and dont repeat same code
#define PARSE(location) (location>>24==118?space[pint(location)]:pint(location)+(location>>24)%16*1000)
// PARSE macro converts binary representation of nuber to decimal:
// 0x30323034 => 204 (go check ASCII table)
// if the first symbol is 'v' (aka 118 (aka 0x76)), macro will return what's inside that spot in space array
#define operator(o) PARSE(TOK(2))o PARSE(TOK(4)) // returns an expression with 'o' beeng operator (e.g. operator(%)  --->   5 % 2)
#define opname :TOK(3)>>24== // I am not going to use this macro here for goods of readabillily
#define W while(TOK(0)!=0x454e4443) // this loop is used twice (reading from file and running code) so why dont we preprocessor it?
int c = 0, i = 0, ch_bff; // c <=> cursor_position
int code[9995];
int space[999];
int main(int argc, char** argv) { // here I decided to add file name as an argument so you dont have to name file 'main.smol' 
    if (argc == 1) {
        printf("no file given!");
        return -1;
    }
    FILE* f = fopen(*(argv+1), "r");
    // reading data from file
    // compressed version: 
    //  while(T(0)!=0x454e4443)(b=fgetc(f))!=10&&b!=32&&(T(0)+=b<<24-i++*8)||(c+=i%4<1);
    while (TOK(0) != 0x454E4443) {
        ch_bff = fgetc(f);
        if (ch_bff != ' ' && ch_bff != '\n') {
            TOK(0) += ch_bff << (24 - i++ * 8);
        } 
        else {
            if (i % 4 == 0) {
                ++c; 
            }
        }
    }
    fclose(f); // this line is kinda unnessesery, so original code doesnt have it
    c = 0;
    while (TOK(0) != 0x454e4443) {
        // JMPI keyword
        // compressed version:
        //  T(0)==0x4A4D5049&&P(T(1))&&(c=P(T(2))*5)
        if (TOK(0) == 0x4A4D5049 && PARSE(TOK(1)) > 0) { // Token == 'JMPI' 
            PARSE(TOK(1)) && (c = PARSE(TOK(2))*5);
        }
        // PRNT keyword
        // compressed:
        //  T(0)==0x50524E54&&printf(T(1)==0x43484152?"%c":"%d",P(T(2)))
        if (TOK(0) == 0x50524E54) { // Token == 'PRNT'
            if (TOK(1) == 0x43484152) // Next toket == 'CHAR'
                printf("%c", PARSE(TOK(2)));
            else 
                printf("%d", PARSE(TOK(2)));
        }
        // SETV keyword
        // originaly:
        //  T(0)==0x53455456&&(s[P(T(1))]=0?1 t 43?_(+)t 45?_(-)t 47?_(/)t 37?_(%)t 42?_(*)t 61?_(==)t 38?_(&&)t 60?_(<)t 33?!P(T(2)):0);
        // here "t" is "opname" macro ond "_" is "operator" macro
        if (TOK(0)==0x53455456) {
            space[PARSE(TOK(1))] = 
            TOK(3)>>24 == '+' ? operator(+) :
            TOK(3)>>24 == '-' ? operator(-) :
            TOK(3)>>24 == '/' ? operator(/) :
            TOK(3)>>24 == '%' ? operator(%) :
            TOK(3)>>24 == '*' ? operator(*) :
            TOK(3)>>24 == '=' ? operator(==):
            TOK(3)>>24 == '&' ? operator(&&):
            TOK(3)>>24 == '<' ? operator(<) :
            TOK(3)>>24 == '>' ? operator(<) : // original code doesnt have this operator, but I added it here
            TOK(3)>>24 == '!' ? !PARSE(TOK(2)):
            0;
        }
        c += 5;
    }
}
/*

    Some of staff I used when golfing this code:

    First of all: Macros. They can replace code with with one symbol!
    For example "W" macro. It replaces `while(TOK(0)!=0x454e4443)` one symbol for 25. -24 bytes per one usage.
    Macro PARSE (P in original code) uses "pint", witch is another macro.
    TOK (T in original) is the most cammon macro is this code. It saves 4 bytes (in original code):
        T(1) is clearly less than *(d+c+1)  (d is code[])

    Second, You dont need to specify data type! compile will auto make it int! (yes, compile warns you but who cares)
    also you dont have to return value from int function.
    so this is the smallest counter we can get (25 bytes):
    c;main(){c++<10&&main();}

    This counter also have logical expression insted of `if` statement.
    It is third and last thing I want to talk about: Replacing `if` with `&&` and `?:`
        a && b && c && d
    lets have a look at this line: `a` will be checked is it true or not. If it is - `b` will be ckecked. If at some point expression is false
    we wont continue checking it.
    It can be writen like this:
        if (a) {
            if (b) {
                if (c) {
                    d;
                }
            }
        }
    `?:`  operator is simply `if` - `else`
    a ? b : c
    =
    if (a) {
        b
    }
    else {
        c
    }
*/