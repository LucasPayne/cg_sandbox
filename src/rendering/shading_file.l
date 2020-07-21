/*--------------------------------------------------------------------------------
    flex lexer file for reading files which describe stages in the
    GeometricMaterial + Material + ShadingModel system ("shading files").
BUGS:
PROBLEMS:
    Dynamically allocated strings, global buffer for reading GLSL snippets...
THINGS/NOTES:

references:
    Setting up flex to read from a std::istream.
    https://stackoverflow.com/questions/9628099/c-istream-with-lex

    Flex and Bison, p125, YY_INPUT
        YY_INPUT(buf, result, max_size)
      Whenever the scanner needs more input and the buffer is empty, it invokes
      YY_INPUT, where buf and max_size are the buffer and its size, respectively,
      and result is where to put the actual amount read or zero at EOF.
      (pass in result as-is, since this is a macro).

      The main situation where redefining YY_INPUT is useful is when reading from
      and input source that is neither a string nor a stdio file.
--------------------------------------------------------------------------------*/
%option noyywrap nodefault
    /* "stdinit not required - since using streams" - stackexchange post */
%option nostdinit
    /* %option prefix="shading_file_yy" */
%{
    /* Code included at top */
    // Container for lexer data (https://github.com/Kicer86/photobroom/blob/master/tools/enum_to_string/enum.l)
    #include "rendering/rendering.h"
    using namespace ShadingFileDetails;
    #include "shading_file.tab.hh"

    // Set TRACE to 1 to view trace output when scanning.
    #include <stdarg.h>
    #define TRACE 0
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

    // Global pointer to a std::istream that the generated lexer will read from.
    extern std::istream *g_istream;
    // Redefine the YY_INPUT macro to read from the global std::istream. RESULT must hold the number of characters read,
    // or zero at EOF.
    //     reference: https://stackoverflow.com/questions/9628099/c-istream-with-lex
    // -This stops once one line is read, supposedly for interactive input, which doesn't seem useful in this case.
    #define YY_INPUT(BUFFER,RESULT,MAX_SIZE) {\
        ( RESULT ) = 0;\
        while (1) {\
            int c = g_istream->get();\
            if (g_istream->eof()) break;\
            ( BUFFER )[( RESULT )++] = c;\
            if (( RESULT ) == (MAX_SIZE) || c == '\n') break;\
        }\
    }
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
    tprint("------------------------------------------------------------\n");
    tprint("%s\n", yylval.string);
    tprint("------------------------------------------------------------\n");
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
    tprint("%s\n", yylval.string);
    return IDENTIFIER;
}
<<EOF>> {
    tprint("Token stream ended.\n");
    yyterminate();
}


%%
    /* Code */
std::istream *g_istream = nullptr;
void shading_file_lexer_set_istream(std::istream &stream)
{
    g_istream = &stream;
}
void yyerror(ShadingFileASTNode **ast_root_out, char *str)
{
    std::cout << "yyerror: " << str;
}
