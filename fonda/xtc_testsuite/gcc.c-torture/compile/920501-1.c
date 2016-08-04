// {{ dg-preprocess "Need preprocessing" }}
#ifndef NO_LABEL_VALUES
a(){int**b[]={&&c};c:;}
#else
int x;
#endif
