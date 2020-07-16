/*--------------------------------------------------------------------------------
    flex lexer file for reading files describing stages in the
    GeometricMaterial + Material + ShadingModel system ("shading files").
--------------------------------------------------------------------------------*/
%option noyywrap nodefault
    /* %option prefix="shading_file_yy" */

%{
    /* Code included at top */
    // Container for lexer data (https://github.com/Kicer86/photobroom/blob/master/tools/enum_to_string/enum.l)
    #define YYSTYPE std::string
    #include <string>
    #include <iostream>
    #include <stdio.h>
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
%}
    /* Exclusive states. */
%x CommentOneLine
%x CommentMultiLine



%%
. { 
    printf("choo\n");
}

%%
//     /* Code */
//     /* Pattern rules */
//     /* Single-line comments. */
// "//" { BEGIN CommentOneLine; }
// <CommentOneLine>. {
//     printf("One-line comment\n");
// }
// <CommentOneLine>"\n" { BEGIN INITIAL; }
//     /* Multi-line comments. */
//     /*     note: Multiline comment syntax inside multiline comments doesn't work. */
// "/*" { BEGIN CommentMultiLine; }
// <CommentMultiLine>. { /* */ }
// <CommentMultiLine>"\n" { /* */ }
// <CommentMultiLine>"*/" { BEGIN INITIAL; }
void yyerror(char *str)
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
