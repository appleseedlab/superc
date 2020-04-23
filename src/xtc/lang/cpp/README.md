## Troubleshooting

### When to rebuild the parser vs the type builder

The grammar only needs to be rebuilt if `c.y` is changed, i.e,

    make select-desugarer; make

Any changes to `TypeBuilder` alone can be rebuilt with just `make`, i.e.,

    `make`

### Tracing the parser

Sometimes, it may be difficult to tell from the AST which grammar
productions are being reduced (matched), and therefore whether its
expected semantic action is being executed.

To trace the parser, use `-showActions`.  To trace the forking and merging, use `-showFM`. For example,

    java xtc.lang.cpp.SuperC -showActions -showFM -printAST canonical_example.c

### Checking a single configuration's C file using the C preprocessor

Use `-U` and `-D` to undefined or define macros.  If we have a C file called `canonical_example.c`,

    int main() {
    #ifdef A
        int
    #else
        long
    #endif
        int
    #ifdef B
        x
    #else
        y
    #endif
        ;
    }

then we can preprocess for `A` on and `B` off using the `-E` to just preprocess:

    gcc -E -DA -UB canonical_example.c

Similarly, we can compile this configuration like so to see any type errors:

    gcc -DA -UB canonical_example.c


### Grammar changes not being seen

Try clobbering the parser intermediate files and rebuilding them

    make clobber-parsers; make parsers; make


#### Problems with the parse table conversion to Java

If the parser isn't working, diagnose it with

    java xtc.lang.cpp.SuperC -showActions file.c
    
If you see something like

    reducing ExternalDeclarationList with 257 frames
    
This means that there is likely something wrong with the parse tables.

Check the types of the tables in `c.tab.c` against the types assumed in `gen_tables.c`, e.g.,

    # in c.tab.c
    static const yytype_uint8 yytranslate[] =
    
    # in gen_tables.c
    print_uint16("yytranslate", yytranslate, YYMAXUTOK);
    
`gen_tables.c` needs to be changed to use `print_uint8` instead, i.e.,

    print_uint16("yytranslate", yytranslate, YYMAXUTOK);
