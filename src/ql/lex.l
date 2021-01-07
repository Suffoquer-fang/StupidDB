%option noyywrap
%option caseless
%{

    #include "utils.h"
    #include "parser.tab.h"
    extern "C"
    {
        int yylex(void);
    };

%}

%%

, { return ','; }
[\n \t] {}
; { return ';'; } 
\. { return '.';}
\( {return '(';}
\) {return ')';}
\* { return '*';}
= { return EQ;}
\< {return LT;}
\> {return GT;}
\<= {return LE;}
\>= {return GE;}
\<\> {return NE;}
DATABASE  {return DATABASE;}
DATABASES	 {return DATABASES;}
TABLE { return TABLE;}
TABLES { return TABLES;}
SHOW { return SHOW; }
CREATE {return CREATE;}
DROP {return DROP;} 
USE  { return USE; }
PRIMARY  { return PRIMARY; }
KEY { return KEY; }
NOT { return NOT; }
NULL { return SQLNULL; }
INSERT { return INSERT; }
INTO { return INTO; }
VALUES { return VALUES; }
DELETE { return DELETE; }
FROM { return FROM; }
WHERE { return WHERE; }
UPDATE { return UPDATE; }
SET { return SET; }
SELECT { return SELECT; }
IS { return IS; }
INT { return TOKEN_INT; }
VARCHAR { return VARCHAR; }
DEFAULT { return DEFAULT; }
CONSTRAINT { return CONSTRAINT; }
CHANGE { return CHANGE; }
ALTER { return ALTER; }
ADD { return ADD; }
RENAME { return RENAME; }
DESC {return DESC; }
INDEX { return INDEX; }
AND { return AND; }
DATE { return DATE; }
FLOAT { return FLOAT; }
FOREIGN { return FOREIGN; }
REFERENCES {return REFERENCES; }
ON { return ON; }
TO { return TO; }



[A-Za-z][_0-9A-Za-z]* {
    yylval.id = yytext;
    return IDENTIFIER; 
}

-?[0-9]+ {
    yylval.id = yytext;
    // printf("got value int\n");
    return VALUE_INT;
}

(-?[0-9]+)(\.[0-9]+)? {
    yylval.id = yytext;
    // printf("got value float\n");
    return VALUE_FLOAT;
}

'[^']*' {
    yylval.id = yytext;
    yylval.id = yylval.id.substr(1, yylval.id.length() - 2);
    // printf("got value string\n");
    return VALUE_STRING;
}

%%
