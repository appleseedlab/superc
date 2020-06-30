
int main ( ) {
if ((defined CONFIG_B)) { /* from static conditional around function definition */
{ 
int x_R0 /* renamed from x */ ; 

int y_R1 /* renamed from y */ ; 
if ((defined CONFIG_B) && (defined CONFIG_C)) { /* from static conditional around statement */
y_R1 = 4 ; 
}
if ((defined CONFIG_B) && (defined CONFIG_A) && (defined CONFIG_C)) { /* from static conditional around statement */
x_R0 = y_R1 ; 
}
if ((defined CONFIG_B) && (defined CONFIG_A)) { /* from static conditional around statement */
x_R0 ++ ; 
}
if ((defined CONFIG_B) && (defined CONFIG_A)) { /* from static conditional around statement */
return x_R0 ; 
}
} 
}
}

