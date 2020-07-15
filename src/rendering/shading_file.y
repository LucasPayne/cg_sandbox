/*--------------------------------------------------------------------------------
    bison parser file for reading files describing stages in the
    GeometricMaterial + Material + ShadingModel system ("shading files").
--------------------------------------------------------------------------------*/
%{
    /* Code included at top. */
    #define YYSTYPE std::string
    #include <string>
    #include <iostream>
    #include <stdio.h>
    #include "shading_file.yy.hh"

    // Errors must be handled by a user-supplied function, declared here.
    // The definition of this is in the lexer file, which is always linked with this parser file.
    void yyerror(char *str);
%}
    /* Token, union, type definitions. */
%token <symbol> NICE

%%
    /* Grammar rules. */
Wow:
    NICE NICE NICE {
        printf("Nice\n");
    }
%%
    /* Code. */

