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
    ShadingFileASTNode *node;
    ShadingFileParameter *parameter;
}
%token <symbol> DIRECTIVE
%token <symbol> SECTION
%token <symbol> OUT
%token <symbol> IN
%token <symbol> UNIFORM
%token <symbol> GLSL_SNIPPET
%token <symbol> IDENTIFIER

%type <node> ShadingFile
%type <node> Directive
%type <node> Section
%type <node> ShadingOutput
%type <parameter> OutputParameter
%type <parameter> OutputParameterList

%%
    /* Grammar rules. */

ShadingFile: /* type: ShadingFileASTNode* */
    Section ShadingFile {
        $1->next = $2;
        $$ = $1;
    }
|   ShadingOutput ShadingFile {
        $1->next = $2;
        $$ = $1;
    }
|   Directive ShadingFile {
        $1->next = $2;
        $$ = $1;
    }
|   /* nothing */ {
        $$ = NULL;
    }
    
Section: /* type: ShadingFileASTSection* : ShadingFileASTNode */
    SECTION IDENTIFIER '{' ShadingFile '}' {
        auto &section_name = $2;
        auto &section_internals = $4;
        $$ = new ShadingFileASTSection(section_name);
        $$->first_child = section_internals;
    }

Directive: /* type: ShadingFileASTDirective* : ShadingFileASTNode */
    DIRECTIVE {
        auto &directive_text = $1;
        $$ = new ShadingFileDirective(directive_text);
    }

ShadingOutput: /* type: ShadingFileASTOutput* : ShadingFileASTNode */
    OUT IDENTIFIER IDENTIFIER '(' OutputParameterList ')' '{' GLSL_SNIPPET '}' {
        auto &type = $2;
        auto &name = $3;
        auto &parameter_list = $5;
        auto &snippet = $8;
        $$ = new ShadingFileASTOutput(type, name, snippet);
        ShadingFileASTParameter *cur = parameter_list;
        while (cur != NULL) {
            if (cur->kind == SHADING_PARAMETER_IN) {
                inputs.push_back(ShadingParameter(cur->type, cur->name, cur->kind);
            } else { // Should be SHADING_PARAMETER_UNIFORM
                uniforms.push_back(ShadingParameter(cur->type, cur->name, cur->kind);
            }
            auto tmp = cur->next;
            delete cur; // delete these nodes, as they are not linked into the final AST.
            cur = tmp;
        }
    }

OutputParameterList: /* type: ShadingFileASTParameter* */
    /* nothing */ {
        $$ = NULL;
    }
|   OutputParameter {
        $$ = $1;
    }
|   OutputParameter ',' OutputParameterList {
        $1->next = $3;
        $$ = $1;
    }

OutputParameter: /* type: ShadingFileASTParameter* */
    IN IDENTIFIER IDENTIFIER {
        $$ = new ShadingFileASTParameter($2, $3, SHADING_PARAMETER_IN);
    }
|   UNIFORM IDENTIFIER IDENTIFIER {
        $$ = new ShadingFileASTParameter($2, $3, SHADING_PARAMETER_UNIFORM);
    }

%%
    /* Code. */

