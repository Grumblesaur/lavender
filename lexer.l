%{
/* lavender programming language
 * lexical analyzer
 * James Murphy
 * Evan May
 */

#include <stdio.h>
// #include "parser.tab.h" /* uncomment when this exists */

enum num_format {
  INTEGRAL,
  FLOATING,
  BOOLEAN
};

unsigned long linecount = 1;
num_format last_numeric;

%}


%option noyywrap

%%

"begin"       { return BEGIN_;   }
"end"         { return END;      }

"if"          { return IF;       }
"then"        { return THEN;     }
"else"        { return ELSE;     }

"while"       { return WHILE;    }
"for"         { return FOR;      }
"break"       { return BREAK;    }
"skip"        { return SKIP;     }
"return"      { return RETURN;   }

"."           { return STOP;     }
"?"           { return QUESTION; }
":"           { return COLON;    }
","           { return COMMA;    }
"("           { return OPAREN;   }
")"           { return CPAREN;   }
"["           { return OBRACK;   }
"]"           { return CBRACK;   }

"->"          { return ACCESS;   }

"exp"|"**"    { return POWER;    }
"log"|"%%"    { return LOG;      }

"not"|"!"     { return NOT;      }
"bnot"|"~"    { return BNOT;     }

"fdiv"|"//"   { return FDIV;     }
"div"|"/"     { return DIV;      }
"times"|"*"   { return TIMES;    }
"mod"|"%"     { return MOD;      }

"band"|"&"    { return BAND;     }
"bxor"|"^"    { return BXOR;     }
"bor"|"|"     { return BOR;      }

"plus"|"+"    { return PLUS;     }
"minus"|"-"   { return MINUS;    }

"lshift"|"<<" { return LSHIFT;   }
"rshift"|">>" { return RSHIFT;   }

"gt"|">"      { return GT;       }
"lt"|"<"      { return LT;       }
"eq"|"="      { return EQ;       }
"neq"|"<>"    { return NEQ;      }
"geq"|">="    { return GEQ;      }
"leq"|"<="    { return LEQ;      }

"and"|"&&"    { return AND;      }
"xor"|"^^"    { return XOR;      }
"or"|"||"     { return OR;       }
"imp"|"=>"    { return IMP;      }



"true" {
  yylval.boolean = 1;
  last_numeric = BOOLEAN;
  return NUMERIC;
}

"false" {
  yylval.boolean = 0;
  last_numeric = BOOLEAN;
  return numeric;
}

0|[1-9]+[0-9]* {
  yylval.integer = atol(yytext);
  last_numeric = INTEGRAL;
  return NUMERIC;
}

[0-9]*\.[0-9]+ {
  yylval.floating = atof
  last_numeric = FLOATING;
  return NUMERIC;
}
  

'(\\.|[^\\'])*' {
  yylval.string = yytext;
  return STRING;
}

\"(\\.|[^\\"])*\" {
  yylval.str = yytext;
  return STRING;
}

[$@;#][a-zA-Z0-9_] {
  yylval.identifier = yytext;
  return IDENTIFIER;
}

"#".*    { /* inline comment */ }
[ \t]+   ( /* whitespace */     }



