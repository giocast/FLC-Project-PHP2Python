# FLC-Project-PHP2Python
Master degree project for Formal Languages and Compilers course: Flex/Bison transpiler from PHP to Python

In order to build and execute our transpiler, you need to follow this steps:

- Create into the project folder a text file with extension .php  containing PHP code (we also support the presence of HTML/JS/CSS code outside the PHP definition <?php … ?>)
- Open the terminal and move to the project folder
- Run the command bison -d php2python.y 
(Note: the -d “define” option allows definitions to be transferred to different header file  php2python.tab.h , in order to be included in other modules, such as the lexer file)
- Run the command flex php2python.l 
(Note: this execution produces the lex.yy.c file, useful in next command)
- Run the command gcc php2python.tab.c lex.yy.c -lfl
(Note: we use the standard gcc compiler. Also file tab.c is generated after the bison command. The -lfl option allows to obtain an executable file a.out)
- Run the command ./a.out < yourPHPscript.php
- Open the file output_translated.py to see the translated script (if no errors occur)
- Open the file abstract_tree.txt to see a representation of the AST (Abstract Syntax Tree)

