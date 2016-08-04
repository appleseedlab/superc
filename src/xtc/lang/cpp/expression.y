/* keywords */
%token AUTO            DOUBLE          INT             STRUCT
%token BREAK           ELSE            LONG            SWITCH
%token CASE            ENUM            REGISTER        TYPEDEF
%token CHAR            EXTERN          RETURN          UNION
%token CONST           FLOAT           SHORT           UNSIGNED
%token CONTINUE        FOR             SIGNED          VOID
%token DEFAULT         GOTO            SIZEOF          VOLATILE
%token DO              IF              STATIC          WHILE

/* ANSI Grammar suggestions */
%token IDENTIFIER              STRINGliteral
%token FLOATINGconstant        INTEGERconstant        CHARACTERconstant
%token OCTALconstant           HEXconstant

/* New Lexical element, whereas ANSI suggested non-terminal */

%token TYPEDEFname /* Lexer will tell the difference between this and 
    an  Identifier!   An  Identifier  that is CURRENTLY in scope as a 
    typedef name is provided to the parser as a TYPEDEFname.*/

/* Multi-Character operators */
%token  ARROW  /** layout **/            /*    ->                              */
%token  ICR DECR         /*    ++      --                      */
%token  LS RS            /*    <<      >>                      */
%token  LE GE EQ NE      /*    <=      >=      ==      !=      */
%token  ANDAND OROR      /*    &&      ||                      */
%token  ELLIPSIS         /*    ...                             */

/* modifying assignment operators */
%token MULTassign  DIVassign    MODassign   /*   *=      /=      %=      */
%token PLUSassign  MINUSassign              /*   +=      -=              */
%token LSassign    RSassign                 /*   <<=     >>=             */
%token ANDassign   ERassign     ORassign    /*   &=      ^=      |=      */

/* punctuation */
%token LPAREN  /** layout **/
%token RPAREN  /** layout **/
%token COMMA  /** layout **/
%token HASH
%token DHASH
%token LBRACE  /** layout **/
%token RBRACE  /** layout **/
%token LBRACK  /** layout **/
%token RBRACK  /** layout **/
%token DOT  /** layout **/
%token AND
%token STAR
%token PLUS
%token MINUS
%token NEGATE
%token NOT
%token DIV
%token MOD
%token LT
%token GT
%token XOR
%token PIPE
%token QUESTION  /** layout **/
%token COLON  /** layout **/
%token SEMICOLON  /** layout **/
%token ASSIGN  /** layout **/

//tokens for gcc extensions
%token ASMSYM
%token _BOOL
%token _COMPLEX
%token RESTRICT
%token __ALIGNOF
%token __ALIGNOF__
%token ASM
%token __ASM
%token __ASM__
%token AT
%token USD
%token __ATTRIBUTE
%token __ATTRIBUTE__
%token __BUILTIN_OFFSETOF
%token __BUILTIN_TYPES_COMPATIBLE_P
%token __BUILTIN_VA_ARG
%token __BUILTIN_VA_LIST
%token __COMPLEX__
%token __CONST
%token __CONST__
%token __EXTENSION__
%token INLINE
%token __INLINE
%token __INLINE__
%token __LABEL__
%token __RESTRICT
%token __RESTRICT__
%token __SIGNED
%token __SIGNED__
%token __THREAD
%token TYPEOF
%token __TYPEOF
%token __TYPEOF__
%token __VOLATILE
%token __VOLATILE__

//preprocessor number catch-all token
%token PPNUM

//%token DOTSTAR
//%token DCOLON

%{
%}

%%

ConstantExpression: /** passthrough, complete **/
        ConditionalExpression
        ;

/* CONSTANTS */
Constant: /** passthrough, complete **/
        IntegerConstant
        | CharacterConstant
        ;

IntegerConstant:  /** complete **/
        FLOATINGconstant
        | INTEGERconstant
        | OCTALconstant
        | HEXconstant
        ;

CharacterConstant:  /** complete */
        CHARACTERconstant
        ;

/* EXPRESSIONS */
PrimaryExpression:  /** passthrough, complete **/
        PrimaryIdentifier
        | Constant
        | LPAREN ConstantExpression RPAREN
        ;

PrimaryIdentifier: /** complete **/
        Word
        ;

UnaryExpression:  /** passthrough, complete **/
        PrimaryExpression
        | UnaryMinusExpression
        | UnaryPlusExpression
        | LogicalNegationExpression
        | BitwiseNegationExpression
        | DefinedExpression
        ;

UnaryMinusExpression:  /** complete **/
        UnaryMinusOp UnaryExpression
        ;

UnaryMinusOp:  /** void **/
        MINUS
        ;

UnaryPlusExpression:  /** complete **/
        UnaryPlusOp UnaryExpression
        ;

UnaryPlusOp:  /** void **/
        PLUS
        ;

LogicalNegationExpression:  /** complete **/
        LogicalNegateOp UnaryExpression
        ;

LogicalNegateOp:  /** void **/
        NOT
        ;

BitwiseNegationExpression:  /** complete **/
        BitwiseNegateOp UnaryExpression
        ;

BitwiseNegateOp:  /** void **/
        NEGATE
        ;

DefinedExpression:  /** complete **/
        DefinedKeyword LPAREN PrimaryIdentifier RPAREN
        | DefinedKeyword PrimaryIdentifier
        ;

DefinedKeyword:  /** void **/
        IDENTIFIER CheckDefined
        ;

CheckDefined:  /** action **/
        ;

MultiplicativeExpression:  /** passthrough, complete **/
        UnaryExpression
        | MultiplicativeExpression STAR UnaryExpression
        | MultiplicativeExpression DIV UnaryExpression
        | MultiplicativeExpression MOD UnaryExpression
        ;

AdditiveExpression:  /** passthrough, complete **/
        MultiplicativeExpression
        | AdditiveExpression PLUS MultiplicativeExpression
        | AdditiveExpression MINUS MultiplicativeExpression
        ;

ShiftExpression:  /** passthrough, complete **/
        AdditiveExpression
        | ShiftExpression LS AdditiveExpression
        | ShiftExpression RS AdditiveExpression
        ;

RelationalExpression:  /** passthrough, complete **/
        ShiftExpression
        | RelationalExpression LT ShiftExpression
        | RelationalExpression GT ShiftExpression
        | RelationalExpression LE ShiftExpression
        | RelationalExpression GE ShiftExpression
        ;

EqualityExpression:  /** passthrough, complete **/
        RelationalExpression
        | EqualityExpression EQ RelationalExpression
        | EqualityExpression NE RelationalExpression
        ;

BitwiseAndExpression:  /** passthrough, complete **/
        EqualityExpression
        | BitwiseAndExpression BitwiseAndOp EqualityExpression
        ;

BitwiseAndOp:  /** void **/
        AND
        ;

BitwiseXorExpression:  /** passthrough, complete **/
        BitwiseAndExpression
        | BitwiseXorExpression BitwiseXorOp BitwiseAndExpression
        ;

BitwiseXorOp:  /** void **/
        XOR
        ;

BitwiseOrExpression:  /** passthrough, complete **/
        BitwiseXorExpression
        | BitwiseOrExpression BitwiseOrOp BitwiseXorExpression
        ;

BitwiseOrOp:  /** void **/
        PIPE
        ;

LogicalAndExpression:  /** passthrough, complete **/
        BitwiseOrExpression
        | LogicalAndExpression LogicalAndOp BitwiseOrExpression
        ;

LogicalAndOp:  /** void **/
        ANDAND
        ;

LogicalOrExpression:  /** passthrough, complete **/
        LogicalAndExpression
        | LogicalOrExpression LogicalOrOp LogicalAndExpression
        ;

LogicalOrOp:  /** void **/
        OROR
        ;

ConditionalExpression:  /** passthrough, complete **/
        LogicalOrExpression
        | LogicalOrExpression QUESTION ConstantExpression COLON
                ConditionalExpression
        | LogicalOrExpression QUESTION COLON  // ADDED gcc incomplete conditional
                ConditionalExpression
        ;

Word:  /** passthrough **/
        IDENTIFIER
        | AUTO
        | DOUBLE
        | INT
        | STRUCT
        | BREAK
        | ELSE
        | LONG
        | SWITCH
        | CASE
        | ENUM
        | REGISTER
        | TYPEDEF
        | CHAR
        | EXTERN
        | RETURN
        | UNION
        | CONST
        | FLOAT
        | SHORT
        | UNSIGNED
        | CONTINUE
        | FOR
        | SIGNED
        | VOID
        | DEFAULT
        | GOTO
        | SIZEOF
        | VOLATILE
        | DO
        | IF
        | STATIC
        | WHILE
        | ASMSYM
        | _BOOL
        | _COMPLEX
        | RESTRICT
        | __ALIGNOF
        | __ALIGNOF__
        | ASM
        | __ASM
        | __ASM__
        | __ATTRIBUTE
        | __ATTRIBUTE__
        | __BUILTIN_OFFSETOF
        | __BUILTIN_TYPES_COMPATIBLE_P
        | __BUILTIN_VA_ARG
        | __BUILTIN_VA_LIST
        | __COMPLEX__
        | __CONST
        | __CONST__
        | __EXTENSION__
        | INLINE
        | __INLINE
        | __INLINE__
        | __LABEL__
        | __RESTRICT
        | __RESTRICT__
        | __SIGNED
        | __SIGNED__
        | __THREAD
        | TYPEOF
        | __TYPEOF
        | __TYPEOF__
        | __VOLATILE
        | __VOLATILE__
        ;

%%

  public void CheckDefined(Subparser subparser) {
    if (! "defined".equals(subparser.stack.get(2).value.toString())) {
      subparser.lookahead.setError();
    }
  }
