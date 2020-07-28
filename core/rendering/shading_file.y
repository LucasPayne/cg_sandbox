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
    ShadingFileASTBlock *block;
    ShadingFileASTBlockEntry *block_entry;
    const char *string;
    unsigned int unsigned_int;
}
%token <string> DIRECTIVE
%token SECTION
%token BLOCK
%token OUT
%token IN
%token UNIFORM
%token <string> GLSL_SNIPPET
%token <string> IDENTIFIER
%token <unsigned_int> UNSIGNED_INT

%type <node> ShadingFile
%type <directive> Directive
%type <section> Section
%type <block> Block
%type <block_entry> BlockEntry
%type <block_entry> BlockEntries
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
|   Block ShadingFile {
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

Block: /* type ShadingFileASTBlock* : ShadingFileASTNode */
    BLOCK IDENTIFIER '{' BlockEntries '}' {
        const char *block_name = $2;
        auto block_entries = $4;
        $$ = new ShadingFileASTBlock(block_name);
        $$->first_entry = block_entries;
    }
BlockEntries: /* type: ShadingFileASTBlockEntry* */
    /* nothing */ {
        $$ = nullptr;
    }
|   BlockEntry BlockEntries {
        $1->next_entry = $2;
        $$ = $1;
    }
BlockEntry: /* type: ShadingFileASTBlockEntry* */
    IDENTIFIER IDENTIFIER ';' {
        // Regular entry, e.g. "vec4 color;"
        const char *type = $1;
        const char *name = $2;
        $$ = new ShadingFileASTBlockEntry(type, name);
    }
|   IDENTIFIER IDENTIFIER '[' UNSIGNED_INT ']' ';' {
        // Array entry with integer literal array size, e.g.
        //     "vec4 colors[3];"
        const char *type = $1;
        const char *name = $2;
        const unsigned int array_length = $4;
        $$ = new ShadingFileASTBlockEntry(type, name, array_length);
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
