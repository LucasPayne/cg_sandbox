/*--------------------------------------------------------------------------------
    bison parser file for reading files describing stages in the
    GeometricMaterial + Material + ShadingModel system ("shading files").

BUGS:
PROBLEMS:
NOTES:
    C++ "new" is being used here a lot since it seems convenient for ASTs.
    std::vectors are being used instead of linked lists. Maybe this is convenient.
--------------------------------------------------------------------------------*/
%{
    /* Code included at top. */
    #include "rendering/rendering.h"
    #include "shading_file.yy.hh"

    // Errors must be handled by a user-supplied function, declared here.
    // The definition of this is in the lexer file, which is always linked with this parser file.
    void yyerror(char *str);
%}
    /* Token, union, type definitions. */
%union {
    ShadingFileDirective *directive;
    ShadingFile *subsection;
    ShadingOutput *output;
    ShadingParameter *parameter;
    std::vector<ShadingParameter *> shading_parameter_list;

    // std::string symbol; // identifier names, directive text, GLSL ... END text tokens.
}
%token <symbol> DIRECTIVE
%token <symbol> SECTION
%token <symbol> OUT
%token <symbol> IN
%token <symbol> UNIFORM
%token <symbol> GLSL_SNIPPET
%token <symbol> IDENTIFIER

%type <directive> Directive
%type <subsection> ShadingFile
%type <output> ShadingOutput
%type <parameter> OutputParameter
%type <parameter_list> OutputParameterList

%%
    /* Grammar rules. */
ShadingFile: /* type: ShadingFile* */
    ShadingFile ShadingFile {
        // $$ = new ShadingFile(); // new...
        // $$.children = // concat children
    }
|   Directive ShadingFile {
        // $$ = new ShadingFile();
        // $$->children.push_back(ShadingFileNode($1));
        // for (auto &child : $2->children) $$->children.push_back(child);
    }
|   SECTION IDENTIFIER '{' ShadingFile '}' {

    }
|   ShadingOutput {

    }
|   /* nothing */ {

    }

Directive: /* type: ShadingFileDirective* */
    DIRECTIVE {
         new ShadingFileDirective();
    }

ShadingOutput: /* type: ShadingOutput* */
    OUT IDENTIFIER IDENTIFIER '(' OutputParameterList ')' '{' GLSL_SNIPPET '}' {
        ShadingOutput *output = new ShadingOutput();
        output->inputs = std::vector<ShadingParameter>(0);
        output->outputs = std::vector<ShadingParameter>(0); //-is this necessary?
        for (ShadingParameter *parameter : $4) {
            if (parameter->kind == SHADING_PARAMETER_IN) {
                output->inputs.push_back(*parameter);
            } else { // otherwise SHADING_PARAMETER_UNIFORM
                output->uniforms.push_back(*parameter);
            }
            // !-Delete-! parameter.
            delete parameter;
        }
        output->snippet = $5;
        return output;
    }

OutputParameterList: /* type: std::vector<ShadingParameter *> */
    /* nothing */ {
        return std::vector<ShadingParameter *>(0);
    }
|   OutputParameter {
        return std::vector<ShadingParameter *> {$1};
    }
|   OutputParameterList "," OutputParameter {
        $1.push_back($2);
        return $2;
    }

OutputParameter: /* type: ShadingParameter* */
    IN IDENTIFIER IDENTIFIER {
        return new ShadingParameter($2, $3, SHADING_PARAMETER_IN);
    }
|   UNIFORM IDENTIFIER IDENTIFIER {
        return new ShadingParameter($2, $3, SHADING_PARAMETER_UNIFORM);
    }

%%
    /* Code. */

