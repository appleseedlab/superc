// conditional around headerTypeDeclaration
// getSecondChildOfConditional returns optAnnotations here as well (similar as conditionalSurroundParserStatement.p4)

#ifdef WITH_INT_SINK
header int_data_t {
    varbit<8032> data;
}
#endif

action helloThere (int j, int i) {
    int j = 5;
}
