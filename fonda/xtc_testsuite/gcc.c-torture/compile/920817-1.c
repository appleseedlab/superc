int v;static inline f(){return 0;}g(){return f();}void h(){return v++;} // {{ dg-warning "function returning void" }}
