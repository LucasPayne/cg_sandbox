/*--------------------------------------------------------------------------------
    flex lexer file for reading files which describe stages in the
    GeometricMaterial + Material + ShadingModel system ("shading files").
BUGS:
PROBLEMS:
    Dynamically allocated strings, global buffer for reading GLSL snippets...
THINGS/NOTES:
--------------------------------------------------------------------------------*/
%option noyywrap nodefault
    /* %option prefix="shading_file_yy" */
%{
    /* Code included at top */
    // Container for lexer data (https://github.com/Kicer86/photobroom/blob/master/tools/enum_to_string/enum.l)
    #include "rendering/rendering.h"
    using namespace ShadingFileDetails;
    #include "shading_file.tab.hh"

    // Set TRACE to 1 to view trace output when scanning.
    #include <stdarg.h>
    #define TRACE 1
    //--Empty inlines will still definitely have side-effect parameters evaluated.
    static inline void tprint(const char *format, ...)
    {
    #if TRACE
        va_list args;
        va_start(args, format);
        printf("FLEX: ");
        vprintf(format, args);
        va_end(args);
    #endif
    }
    // Macro for tracing encountered keywords.
    #define KEYWORD() tprint("%s\n", yytext);

    // Global buffer for reading in glsl snippets during lexing.
    static std::vector<char> g_snippet(0);
%}
    /* Exclusive states. */
%x CommentOneLine
%x CommentMultiLine
%x GLSLCapture
    /* Pattern macros. */
NAME    [_A-Za-z]+[_A-Za-z0-9]*

%%
    /* Pattern rules */
    /* Single-line comments. */
"//" {
    tprint("Begin one-line comment.\n");
    BEGIN CommentOneLine;
}
^\s*"#".*$ {
    // Read the directive into the symbol table (everything after the #).
    std::string *directive = new std::string(strchr(yytext, '#') + 1);
    yylval.string = directive->c_str();
    tprint("Directive: %s\n", yylval.string);
    return DIRECTIVE;
}
<CommentOneLine>. { /* */ }
<CommentOneLine>"\n" { BEGIN INITIAL; }
    /* Multi-line comments. */
    /*     note: Multiline comment syntax inside multiline comments doesn't work. */
"/*" { 
    tprint("Begin multi-line comment.\n");
    BEGIN CommentMultiLine;
}
<CommentMultiLine>. { /* */ }
<CommentMultiLine>"\n" { /* */ }
<CommentMultiLine>"*/" { 
    tprint("End multi-line comment.\n");
    BEGIN INITIAL;
}
    /* Eat whitespace and newlines. */
"\n"|" " { /* */}
    /* Keywords */
"section" {
    KEYWORD();
    return SECTION;
}
"out" {
    KEYWORD();
    return OUT;
}
"in" {
    KEYWORD();
    return IN;
}
"uniform" {
    KEYWORD();
    return UNIFORM;
}
"{" {
    KEYWORD();
    return '{';
}
"}" {
    KEYWORD();
    return '}';
}
"(" {
    KEYWORD();
    return '(';
}
")" {
    KEYWORD();
    return ')';
}
"," {
    KEYWORD();
    return ',';
}
"GLSL" {
    tprint("GLSL snippet:\n");
    g_snippet.clear();
    BEGIN GLSLCapture;
}
<GLSLCapture>(" "|"\n")"END" {
    g_snippet.push_back('\0'); // remember the null terminator!
    std::string *snippet = new std::string(&g_snippet[0]);
    yylval.string = snippet->c_str();
    printf("------------------------------------------------------------\n");
    printf("%s\n", yylval.string);
    printf("------------------------------------------------------------\n");
    g_snippet.clear();
    BEGIN INITIAL;
    return GLSL_SNIPPET;
}
<GLSLCapture>.|"\n" {
    g_snippet.push_back(yytext[0]); //-push_back for a char buffer...
}

    /* Identifiers */
{NAME} {
    tprint("Identifier: %s\n", yytext);
    std::string *identifier = new std::string(yytext);
    yylval.string = identifier->c_str();
    printf("%s\n", yylval.string);
    return IDENTIFIER;
}
<<EOF>> {
    tprint("Token stream ended.\n");
    yyterminate();
}


%%
    /* Code */
void yyerror(ShadingFileASTNode **ast_root_out, char *str)
{
    std::cout << "yyerror: " << str;
}
