/*--------------------------------------------------------------------------------
    flex lexer file for reading files which describe stages in the
    GeometricMaterial + Material + ShadingModel system ("shading files").
--------------------------------------------------------------------------------*/
%option noyywrap nodefault
    /* %option prefix="shading_file_yy" */
%{
    /* Code included at top */
    // Container for lexer data (https://github.com/Kicer86/photobroom/blob/master/tools/enum_to_string/enum.l)
    #include "rendering/rendering.h"
    #include "shading_file.tab.hh"
    // The file stack, for #include(...) directives.
    // flex and bison, page 28
    struct FileStackEntry {
        FILE *file;
        FileStackEntry *prev;
        YY_BUFFER_STATE buffer_state; //page 26 for details on YY_BUFFER_STATE and flex's
        			      //defaults for getting a stream to lex from, with yyin.
    };
    struct FileStackEntry *g_file_stack_top = NULL;

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
%}
    /* Exclusive states. */
%x CommentOneLine
%x CommentMultiLine
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
"GLSL"" "*"\n".*"\n"" "*"END" {
    tprint("GLSL snippet:\n");
    yytext = strchr(yytext, '\n') + 1; // Ignore the GLSL line.
    strrchr(yytext, '\n')[1] = '\0'; // Ignore the END line.
    std::string *snippet = new std::string(yytext);
    yylval.string = snippet->c_str();
    if (TRACE) {
        printf("------------------------------------------------------------\n");
        printf("%s", yylval.string);
        printf("------------------------------------------------------------\n");
    }
    return GLSL_SNIPPET;
}

    /* Identifiers */
{NAME} {
    tprint("Identifier: %s\n", yytext);
    std::string *identifier = new std::string(yytext);
    yylval.string = identifier->c_str();
    printf("%s\n", yylval.string);
    return IDENTIFIER;
}
    /* Complete lexing if at the bottom of the file stack, or pop a file and continue lexing where the previous open file was left of. */
<<EOF>> {
    parse_shading_file_pop_file();
    if (g_file_stack_top == NULL) {
        tprint("Token stream ended.\n");
        yyterminate();
    }
}


%%
    /* Code */
void yyerror(ShadingFileASTNode **ast_root_out, char *str)
{
    std::cout << "yyerror: " << str;
}

void parse_shading_file_push_file(FILE *file)
{
    FileStackEntry *new_entry = (FileStackEntry *) malloc(sizeof(FileStackEntry));
    new_entry->file = file;
    new_entry->prev = g_file_stack_top;
    new_entry->buffer_state = yy_create_buffer(new_entry->file, YY_BUF_SIZE);
    yy_switch_to_buffer(new_entry->buffer_state);
    g_file_stack_top = new_entry;
}
void parse_shading_file_pop_file(void)
{
    if (g_file_stack_top == NULL) {
        fprintf(stderr, "ERROR: Attempted to pop from empty file-stack.\n");
        exit(EXIT_FAILURE);
    }
    FileStackEntry *to_free = g_file_stack_top;
    g_file_stack_top = g_file_stack_top->prev;
    fclose(to_free->file);
    yy_delete_buffer(to_free->buffer_state);
    free(to_free);

    // If the stack is still non-empty, then switch to the previous buffer.
    if (g_file_stack_top != NULL) yy_switch_to_buffer(g_file_stack_top->buffer_state);
}
