## Troubleshooting

### Grammar changes not being seen

Try clobbering the parser intermediate files and rebuilding them

    make clobber-parsers; make parsers; make


#### Parse tables conversion to Java

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
