#define X /* leading */ trimwhitespace /* trailing */
X 1 2 3
1 X 2 3
#undef X
#define X /* trailing */
x = X ;
x =X;
#undef X
#define Y 2 /* trailing */
y = Y ;
y =Y;
#undef X
#define Z(a) a /* trailing */
z = Z(1) ;
z =Z(1);
#undef X
#define A(a) Z(a) /* trailing */
a = A(2) ;
a =A(2);
