// conditional around headerTypeDeclaration and actionDeclaration
// after merging subparsers the first time, the "main"/"parent" node 
// isn't a conditional node because input is a list, so the stackframe
// merge appends to the list rather than create a conditional node

// Need to check if the production is a list, then get elements of the list and their conditional nodes

// at the end of the merge, actionDeclaration isn't part of the conditional node. Conditional node might be created
// somewhere else for actionDeclaration block (it is in the AST). Might be the case as in simpleHeaderDecl

#ifdef WITH_INT_SINK
header int_data_t {
    varbit<8032> data;
}
#endif

#ifdef WITH_INT_TRANSIT2
action helloThere (int j, int i) {
    int j = 5;
}
#endif
