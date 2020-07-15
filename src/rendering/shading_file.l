/*--------------------------------------------------------------------------------
    flex lexer file for reading files describing stages in the
    GeometricMaterial + Material + ShadingModel system ("shading files").
--------------------------------------------------------------------------------*/
%option noyywrap nodefault
    /* %option prefix="shading_file_yy" */

%{
    /* Code inserted at top */
    // Container for lexer data (https://github.com/Kicer86/photobroom/blob/master/tools/enum_to_string/enum.l)
    #define YYSTYPE std::string
    #include <string>
    #include <iostream>
    #include <stdio.h>
    #include "shading_file.tab.hh"
    
    // Errors must be handled by a user-supplied function, declared here.
    void yyerror(char *str);
%}

%%
    /* Pattern rules */
%%
    /* Code */
void yyerror(char *str)
{
    std::cout << "ERROR: " << str;
}
