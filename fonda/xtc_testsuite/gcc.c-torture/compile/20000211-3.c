/* test analyzer, expected to pass*/
void f_clos(int x)

{        
        switch(x) {
                default:
                mumble:; // {{ dg-warning "defined but not used" }}
        }
}


