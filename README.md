Welcome to SMOL!
SMOL is an interpreted esoteric programming language, written in C.

Its interpreters source is made to be as small as I can make it (I managed to do it in 585 bytes) and according to my tests it runst 1'000'000'000 iterations loop 2 times faster than python does. Code itself is in src/small_main.c but you can find readable version with explanations here: src/main-manual.c If you want to compile SMOLs interpreter localy (for some reason), I would recomend you using gcc because other compilers may not work (g++ doesn't compile it)

How to run
You can run only code from file named "main.smol", placed within the same folder as an interpreter itself. But I highly recomend you to use BigSmol.exe (compiled from main-manual.c) because It has > operator and it can read from any file (not only main.smol) (P.S. SmallSmol.exe is compiled from original 585 bytes code)

Syntax
SMOL is democratic language!
you can do whatever you want, as far as each line contains 5 words, 4 symbols each, There is a line, witch starts with ENDC token and THERE ARE NO EMPTY LINES

SMOL has 3 command:

PRNT
JMPI
SETV
comand names should be the first word of the line. Otherwise they will be skipped. Everything else will be considered comment. Comments must also follow rules above

Concept of the void
Keyword SETV lets you change data on the void (array of 999 ints) Example of using SETV:

SETV 0001 0010 ++++ 0008
here we write 18 to second byte. (the void is 0-indexed) secont token is the address on the void. Nobody knows what will happend if you try to put something greater than 998 as an address . Third token represents first operand, Fourth token is an operator and the last is second operand.

To use data from the void you use v-syntax:

SETV 0010 v001 ++++ 0012
This line will put sum of data from 2 adrees and 12 to the 10th address in the void

v followed by an address on the void, gives you data inside that address!

Operators
To use operators, You only need first symbol be that operator!

SETV 0001 0010 ++++ 0008
SETV 0001 0010 +``` 0008
SETV 0001 0010 +%$@ 0008
SETV 0001 0010 +abc 0008
SETV 0001 0010 +1;( 0008
All this lines do the same, and it is true for all operators! But for good readability repeat same operator 4 times (just like first example)

SMOL supports following operators: + plus - minus / divition * multiplication % mod = logical equal (== in normal languages) < less than ! logical NOT

You might have noticed that Greater than is nowhere to be found. that is because: a > b is the same as !(a <= b)
a > b --->  !(a <= b)  --->  !(a < b OR a == b) - We can implement that in our code! (see somewhere later)

Also Logical OR is missing. But that is not a problem at all, because for data to be true it just need not to be zero. a || b in SMOL is a + b

Finally, logical NOT is unary operator so second operand can be anything:

SETV 0000 v123 !!!! abcd
SETV cool feature
You can use data inside address as address for another operation:

SETV 0012 0005 ++++ 0000
SETV v012 0001 ++++ 0008
This line will put 9 into address 5. If it doesnt make sence for you: First we put 5+0 to address 12, then we access value in 12 and get 5. And finaly we put 1+8 to 5.

Print to console
Keyword PRNT(shorten from Print Rint Nt T) is the only way to interact with user at runtime. There are two types of formatting output:

PRNT CHAR 0118 skip skip
and_ sec_ _is_ prnt numb
PRNT numb 0118 skip skip
I use UPPERCASE for keywords (the only right way) and lowercase for comments, and other stuff that interpreter doesnt care about. so if next token after PRNT is CHAR, 3rd token will be parsed and printed as ASCII symbol. First line will print v to console And if second token is something else (anything else), 3rd token will be printed as decimal integer. Second line will print 118 to console skip in the example is to fill up the line to 5 words (always remember the rules) and it is better to change it to "`" symbols as it is one of the smallest symbols, and code will be easier to read. (I will do it in next examples)

And we can also combine the void and PRNT:

PRNT numb v001 ```` ````
Complexity
JMPI is the 3rd and the last keyword. Its syntax is very easy: JMPI + number (0-> jump will not happend, else it will jump) + number (line of code to jump)

JMPI 0001 0003 ```` ````
this line will always jump on the 4th line of code when reached (lines are 0-indexed) We can use the void as any of the number (or both)

REAL CODE EXAMPLES
Obviously starting with basic Hello, World!

PRNT CHAR 0072 ```H ````
PRNT CHAR 0101 ```e ````
PRNT CHAR 0108 ```l ````
PRNT CHAR 0108 ```l ````
PRNT CHAR 0111 ```o ````
PRNT CHAR 0044 ```, ````
PRNT CHAR 0032 ```` ````
PRNT CHAR 0087 ```W ````
PRNT CHAR 0111 ```o ````
PRNT CHAR 0114 ```r ````
PRNT CHAR 0108 ```l ````
PRNT CHAR 0100 ```d ````
PRNT CHAR 0033 ```! ````
PRNT CHAR 0010 ``\n ````
ENDC ```` ```` ```` ````
countdown (10 -> 1)

SETV 0000 0010 ++++ 0000
PRNT numb v000 ```` ````
PRNT CHAR 0010 ``\n ````
SETV 0000 v000 ---- 0001
JMPI v000 0001 ```` ````
ENDC ```` ```` ```` ````
countup (0 -> 10)

SETV 0000 0000 ++++ 0000
PRNT numb v000 ```` ````
PRNT CHAR 0010 ``\n ````
SETV 0000 v000 ++++ 0001
SETV 0001 v000 <<<< 0011
JMPI v001 0001 ```` ````
ENDC ```` ```` ```` ````
I really hope you understood it all because here real code comes!

the implementation of Greater than operator + concept of functions in SMOL, prints 1 if v001 > v002

SETV 0000 0004 ++++ 0000
JMPI 0001 0011 ++++ 0000
```` ```` ```` ```` ````
func >>>> arg: v001 v002
```` ret: v003 ```` ````
SETV 0003 v001 <<<< v002
SETV 0004 v001 ==== v002
SETV 0003 v003 ++++ v004
SETV 0003 v003 !!!! ````
JMPI 0001 0015 -ret back
```` ```` ```` func end`
```` ```` ```` ```` ````
SETV 0001 0008 ++++ 0000
SETV 0002 0002 ++++ 0000
JMPI 0001 v000 func call
PRNT numb v003 prnt res`
ENDC ```` ```` ```` ````
This function has a problem: It returns back to a hardcoded spot, so it can be called only in one place. Following code does not have this issue:

SETV 0000 0004 ++++ 0000
JMPI 0001 0018 ```` ````
```` ```` ```` ```` ````
func >>>> arg: v001 v002
```` ret: v003 ```` ````
```` ret` tree ind: v006
SETV 0003 v001 <<<< v002
SETV 0004 v001 ==== v002
SETV 0003 v003 ++++ v004
SETV 0003 v003 !!!! ````
```` ```` ```` func end`
func >>>> ret` tree ````
SETV 0005 v006 ==== 0001
JMPI v005 0023 ```` ````
SETV 0005 v006 ==== 0002
JMPI v005 0029 ```` ````
```` func ret` tree end`
PRNT numb v006 ```` ````
SETV 0001 0008 ++++ 0000
SETV 0002 0002 ++++ 0000
SETV 0006 0001 ++++ 0000
JMPI 0001 v000 func call
```` ```` ```` ```` ````
PRNT numb v003 prnt res`
PRNT CHAR 0010 ``\n ````
```` ```` ```` ```` ````
SETV 0001 0001 ++++ 0000
SETV 0002 0010 ++++ 0000
SETV 0006 0002 ++++ 0000
JMPI 0001 v000 func call
```` ```` ```` ```` ````
PRNT numb v003 prnt res`
ENDC ```` ```` ```` ````
block func ret tree contains all places from where we call it. We only need to put right index into v006! go check examples/ to see more smol programms!