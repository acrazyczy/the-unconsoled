grammar LTLlang;

formula
    : '!' formula                           # not_formula
    | 'G' formula                           # g_formula
    | 'F' formula                           # f_formula
    | 'X' formula                           # x_formula
    | formula op = (AndOp | OrOp) formula   # logic_formula
    | '->' formula                          # implication_formula
    | formula 'U' formula                   # u_formula
    | logicConstant                         # logic_const
    | Identifier                            # atomic_proposition
    | '(' formula ')'                       # formula_in_parentheses
    ;

logicConstant:
    True | False
    ;

Identifier
    : [a-zA-Z]+
    ;

AndOp
    : '/\\'
    ;

OrOp
    : '\\/'
    ;

True:
    'true'
    ;

False:
    'false'
    ;

WS : [ \t\n\r]+ -> skip ;