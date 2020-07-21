/*--------------------------------------------------------------------------------
    bison parser file for reading files describing stages in the
    GeometricMaterial + Material + ShadingModel system ("shading files").

BUGS:
PROBLEMS:
    String handling is not very good. The parser is non-reentrant and avoids explicit global variables
    only through parse-param. A class to encapsulate a file being parsed could be nice, allowing it to have its
    own symbol table, and destructor (cleaning the dynamic AST).
NOTES:
    C++ "new" is being used here a lot since it seems convenient for ASTs.
--------------------------------------------------------------------------------*/
%{
    /* Code included at top. */
    #include "rendering/rendering.h"
    using namespace ShadingFileDetails;
    #include "shading_file.yy.hh"
%}
    /* manual reference: https://www.gnu.org/software/bison/manual/html_node/Parser-Function.html */
%parse-param {ShadingFileASTNode **ast_root_out}
    /* Token, union, type definitions. */
%union {
    ShadingFileASTNode *node;
    ShadingFileASTDirective *directive;
    ShadingFileASTSection *section;
    ShadingFileASTOutput *output;
    ShadingFileASTParameter *parameter;
    const char *string;
}
%token <string> DIRECTIVE
%token SECTION
%token OUT
%token IN
%token UNIFORM
%token <string> GLSL_SNIPPET
%token <string> IDENTIFIER

%type <node> ShadingFile
%type <directive> Directive
%type <section> Section
%type <output> ShadingOutput
%type <parameter> OutputParameter
%type <parameter> OutputParameterList

%%
    /* Grammar rules. */
    /* Special-case root ShadingFile, just so the parse-param pointer to the AST can be given. */
ShadingFileRoot:
    ShadingFile {
        *ast_root_out = $1;
    }

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
        $$ = nullptr;
    }
    
Section: /* type: ShadingFileASTSection* : ShadingFileASTNode */
    SECTION IDENTIFIER '{' ShadingFile '}' {
        const char *section_name = $2;
        auto section_internals = $4;
        $$ = new ShadingFileASTSection(section_name);
        $$->first_child = section_internals;
    }

Directive: /* type: ShadingFileASTDirective* : ShadingFileASTNode */
    DIRECTIVE {
        const char *directive_text = $1;
        $$ = new ShadingFileASTDirective(directive_text);
    }

ShadingOutput: /* type: ShadingFileASTOutput* : ShadingFileASTNode */
    OUT IDENTIFIER IDENTIFIER '(' OutputParameterList ')' '{' GLSL_SNIPPET '}' {
        const char *type = $2;
        const char *name = $3;
        auto parameter_list = $5;
        const char *snippet = $8;
        $$ = new ShadingFileASTOutput(type, name, parameter_list, snippet);
    }

OutputParameterList: /* type: ShadingFileASTParameter* */
    /* nothing */ {
        $$ = nullptr;
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
        const char *type = $2;
        const char *name = $3;
        $$ = new ShadingFileASTParameter(type, name, SHADING_PARAMETER_IN);
    }
|   UNIFORM IDENTIFIER IDENTIFIER {
        const char *type = $2;
        const char *name = $3;
        $$ = new ShadingFileASTParameter(type, name, SHADING_PARAMETER_UNIFORM);
    }

%%
