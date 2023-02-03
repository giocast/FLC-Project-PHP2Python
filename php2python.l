%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <stdbool.h>
	#include <ctype.h>
	#include <string.h>
	
	#include "php2python.tab.h"
	
	int lines_outside_php = 0;
	char *more_lines_comment;
	
	int counter_comments = 0;
%}

/* define php block state and comment state */ 
%x phpcode
%x phpcodecomments
%option noyywrap
%option yylineno

digit	[0-9]
id	\$([a-zA-Z_][a-zA-Z_0-9]*)
name	[a-zA-Z_][a-zA-Z0-9_]*
string (\"(\\.|[^"\\])*\"|\'(\\.|[^"\\])*\')
bool	([Tt][Rr][Uu][Ee]|[Ff][Aa][Ll][Ss][Ee])
array ([Aa][Rr][Rr][Aa][Yy])
arraypop ([Aa][Rr][Rr][Aa][Yy]_[Pp][Oo][Pp])
arraypush ([Aa][Rr][Rr][Aa][Yy]_[Pp][Uu][Ss][Hh])
arraysum ([Aa][Rr][Rr][Aa][Yy]_[Ss][Uu][Mm])
echo ([Ee][Cc][Hh][Oo])
print ([Pp][Rr][Ii][Nn][Tt])
if	([Ii][Ff])
else	([Ee][Ll][Ss][Ee])
elseif	([Ee][Ll][Ss][Ee][Ii][Ff])
switch	([Ss][Ww][Ii][Tt][Cc][Hh])
case	([Cc][Aa][Ss][Ee])
break	([Bb][Rr][Ee][Aa][Kk])
default	([Dd][Ee][Ff][Aa][Uu][Ll][Tt])
function	([Ff][Uu][Nn][Cc][Tt][Ii][Oo][Nn])
while	([Ww][Hh][Ii][Ll][Ee])
foreach	([Ff][Oo][Rr][Ee][Aa][Cc][Hh])
as	([Aa][Ss])
readline	([Rr][Ee][Aa][Dd][Ll][Ii][Nn][Ee])
sort	([Ss][Oo][Rr][Tt])
strlen ([Ss][Tt][Rr][Ll][Ee][Nn])
return ([Rr][Ee][Tt][Uu][Rr][Nn])
%%

"<?php"	{printf("\n-----Found a PHP BLOCK-----\n"); BEGIN(phpcode); FILE *fptrline; fptrline = fopen("startLinePhp.txt", "w"); if(fptrline!=NULL) { fprintf(fptrline,"%d",lines_outside_php);} fclose(fptrline); return STARTPHP; }
<phpcode>{digit}+	{printf("\nFound a number into <?php ?> %d at line %d and of lenght %d\n",atoi(yytext),yylineno, yyleng); yylval.intval=atoi(yytext); return NUMBER;}
<phpcode>{string} {printf("\nFound a string into <?php ?> %s at line %d and of lenght %d\n",yytext,yylineno, yyleng); yylval.str = (char *) strdup(yytext); return STRING;}
<phpcode>{bool} {/*Make string e.g. TrUE lower case*/ 
char yytexttolow[yyleng];
strcpy(yytexttolow,yytext);
for (int i = 0; yytext[i] != '\0'; i++) {
        if(yytexttolow[i]==84 || yytexttolow[i]==82 || yytexttolow[i]==85 || yytexttolow[i]==69 || yytexttolow[i]==70 || yytexttolow[i]==65 || yytexttolow[i]==76 || yytexttolow[i]==83)
        {
        yytexttolow[i] = yytexttolow[i]+32;
        printf("\n\n\n\nBoolean to lower process: %s\n\n\n",yytexttolow);
        }
    }
printf("\nFound a bool into <?php ?> %s at line %d and of lenght %d\n",yytexttolow,yylineno, yyleng); yylval.str = (char *) strdup(yytexttolow); return BOOL;}
<phpcode>{id}	{printf("\nFound a variable into <?php ?> %s\n",yytext); yylval.id = (char *) strdup(yytext); return VARIABLE;}
<phpcode>\n	/* ignore */
<phpcode>\t	/* ignore */
<phpcode>"="	{return EQ;}
<phpcode>";"	{return SC;}
<phpcode>":"	{return CL;}
<phpcode>","	{return CM;}
<phpcode>"+"	{return PL;}
<phpcode>"-"	{return MN;}
<phpcode>"/"	{return DV;}
<phpcode>"*"	{return ML;}
<phpcode>"%"	{return MD;}
<phpcode>"."	{return CCTN;}
<phpcode>"=="	{return EEQ;}
<phpcode>"!="	{return NEQ;}
<phpcode>">"	{return GT;}
<phpcode>"<"	{return LT;}
<phpcode>">="	{return GE;}
<phpcode>"<="	{return LE;}
<phpcode>"&&"	{return AND;}
<phpcode>"||"	{return OR;}
<phpcode>"++"	{return PPL;}
<phpcode>"--"	{return MMN;}
<phpcode>"|"	{return SOR;}
<phpcode>"!"	{return NOT;}
<phpcode>"["	{return SQ1;}
<phpcode>"]"	{return SQ2;}
<phpcode>"("	{return RD1;}
<phpcode>")"	{return RD2;}
<phpcode>"{"	{return CR1;}
<phpcode>"}"	{return CR2;}
<phpcode>{foreach}	{return FRC;}
<phpcode>{as}	{return AS;}
<phpcode>{array}	{return ARR;}
<phpcode>{arraypop} {return APOP;}
<phpcode>{arraypush} {return APUS;}
<phpcode>{arraysum} {return ASUM;}
<phpcode>{echo}	{return ECH;}
<phpcode>{print}	{return PRT;}
<phpcode>{if}	{return IF;}
<phpcode>{else}	{return ELS;}
<phpcode>{elseif}	{return EIF;}
<phpcode>{switch}	{return SWH;}
<phpcode>{case}	{return CSE;}
<phpcode>{break}	{return BRK;}
<phpcode>{default}	{return DFT;}
<phpcode>{function}	{return FNC;}
<phpcode>{while}	{return WHL;}
<phpcode>{readline}	{return RDL;}
<phpcode>{sort}	{return SRT;}
<phpcode>{strlen}	{return SLE;}
<phpcode>{return} {return RTN;}
<phpcode>{name}	{printf("\nFound a name of function\n"); yylval.id = (char *) strdup(yytext); return NAME;}
<phpcode>"/*"	{printf("\n-----FOUND NEW COMMENT SECTION MORE LINES\n"); more_lines_comment = malloc(5000); more_lines_comment[0] = '\0'; strcat(more_lines_comment,"\"\"\""); BEGIN(phpcodecomments);}
<phpcode>"//".*	{printf("\n-----FOUND NEW COMMENT ONE LINE\n"); char *temp=malloc(strlen(yytext)+10); temp[0]='\0'; strcat(temp,"#"); strcat(temp,yytext+2); printf("\nTranslated comment %s\n",temp); if(counter_comments==0){yylval.str = (char *) strdup(temp);}else{yylval.str = (char *) strdup(temp);} counter_comments++; return COMMENT;}

<phpcode>"?"+">"	{BEGIN(INITIAL); return ENDPHP;}



<phpcodecomments>[^*\n]*	{/* match anything that is not a * */  strcat(more_lines_comment,yytext);}
<phpcodecomments>"*"+[^*/\n]*	{/* match * symbols not followed by / symbol */ strcat(more_lines_comment,yytext);}
<phpcodecomments>\n	{/* possible new lines */ strcat(more_lines_comment,"\n");}
<phpcodecomments>"*"+"/"	{strcat(more_lines_comment,"\"\"\""); if(counter_comments==0){yylval.str = (char *) strdup(more_lines_comment);}else{yylval.str = (char *) strdup(more_lines_comment);} counter_comments++; BEGIN(phpcode); return COMMENT; }

\n	{lines_outside_php++; }
