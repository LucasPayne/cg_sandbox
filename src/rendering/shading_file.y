/*--------------------------------------------------------------------------------
    bison parser file for reading files describing stages in the
    GeometricMaterial + Material + ShadingModel system ("shading files").
--------------------------------------------------------------------------------*/
%{
    /* Code included at top. */
    #define YYSTYPE std::string
    #include "rendering/rendering.h"
    #include "shading_file.yy.hh"

    // Errors must be handled by a user-supplied function, declared here.
    // The definition of this is in the lexer file, which is always linked with this parser file.
    void yyerror(char *str);
%}
    /* Token, union, type definitions. */
%union {
    int symbol;
    bool test;
    bool another_test;
}
%token <symbol> DIRECTIVE
%token <symbol> SECTION
%token <symbol> OUT
%token <symbol> IN
%token <symbol> UNIFORM
%token <symbol> GLSL_SNIPPET
%token <symbol> IDENTIFIER

%%
    /* Grammar rules. */
ShadingFile:
    ShadingFile ShadingFile {

    }
|   DIRECTIVE ShadingFile {

    }
|   SECTION IDENTIFIER '{' ShadingFile '}' {

    }
|   OUT IDENTIFIER IDENTIFIER '(' OutputParameterList ')' '{' GLSL_SNIPPET '}'
|   /* nothing */ {

    }

OutputParameterList:
    /* nothing */ {

    }
|   OutputParameter {

    }
|   OutputParameter ',' OutputParameterList {

    }

OutputParameter:
    IN IDENTIFIER IDENTIFIER {

    }
|   UNIFORM IDENTIFIER IDENTIFIER {

    }

%%
    /* Code. */

