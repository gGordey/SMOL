#include<stdio.h>
#define T(x)*(d+c+x)
#define p(l)l%16+(l>>8)%16*10+(l>>16)%16*100
#define P(l)(l>>24==118?s[p(l)]:p(l)+(l>>24)%16*1000)
#define _(o)P(T(2))o P(T(4))
#define t:T(3)>>24==
#define W while(T(0)!=0x454e4443)
c,i,b,d[9995],s[999];main(){FILE*f=fopen("main.smol","r");W(b=fgetc(f))!=10&&b!=32&&(T(0)+=b<<24-i++*8)||(c+=i%4<1);c=0;W{T(0)==0x4A4D5049&&P(T(1))&&(c=P(T(2))*5);T(0)==0x50524E54&&printf(T(1)==0x43484152?"%c":"%d",P(T(2)));T(0)==0x53455456&&(s[P(T(1))]=0?1 t 43?_(+)t 45?_(-)t 47?_(/)t 37?_(%)t 42?_(*)t 61?_(==)t 38?_(&&)t 60?_(<)t 33?!P(T(2)):0);c+=5;}}