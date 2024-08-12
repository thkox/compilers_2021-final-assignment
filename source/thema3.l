%option noyywrap
%{
#include <stdio.h>
int i = 0;
int j = 0;
int peaks_counter = 0;
char *s = " ";
int validation(int peaks);
%}
PEAK [A-Z]
%%
point+" "+{PEAK}{1}$ {printf("Accepted!!!\n");}
line+" "+{PEAK}{2}$ {validation(2);}
triangle+" "+{PEAK}{3}$ {validation(3);}
square+" "+{PEAK}{4}$ {validation(4);}
pentagon+" "+{PEAK}{5}$ {validation(5);}
hexagon+" "+{PEAK}{6}$ {validation(6);}
heptagon+" "+{PEAK}{7}$ {validation(7);}
octagon+" "+{PEAK}{8}$ {validation(8);}
.* printf("Please try again with the proper regural expression\n");
%%
int validation(int peaks)
{
  peaks_counter = 0;
  char *yycopy = yytext;
  for(i = yyleng - 1; i >= yyleng - peaks; --i)
  {
    yycopy[i];
    for(j = yyleng - 1; j >= yyleng - peaks; --j)
    {
        if (yycopy[i] == yycopy[j] && yycopy[i] != *s)
        {
          peaks_counter++;
        }
    }
  }
  if( peaks == peaks_counter && peaks != 1)
  {
    printf("Accepted!!!\n");
    return peaks_counter;
  }
  else
  {
    printf("You have insert one or more times the same letter for the peaks.\n");
    return 0;
  }
}

int main()
{
  printf("Exercise 3\n");
  printf("Please write the shape and the peaks that you want to validate:\n");
  yylex();
  return 0;
}
