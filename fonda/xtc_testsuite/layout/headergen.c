#include <stdio.h>

#include "data.h"
#include "harness.h"

int main(void) {
  def(B);
  def(C);
  def(SC);
  def(UC);
  def(S);
  def(US);
  def(I);
  def(UI);
  def(L);
  def(UL);
  def(LL);
  def(ULL);
  def(F);
  def(D);
  def(LD);

  def(AB);
  def(AC);
  def(ASC);
  def(AUC);
  def(AS);
  def(AUS);
  def(AI);
  def(AUI);
  def(AL);
  def(AUL);
  def(ALL);
  def(AULL);
  def(AF);
  def(AD);
  def(ALD);

  def(BFB);
  def(BFBP);
  def(BFC);
  def(BFCP);
  def(BFS);
  def(BFSP);
  def(BFI);
  def(BFIP);
  def(BFL);
  def(BFLP);
  def(BFLL);
  def(BFLLP);
  def(SBA1024);
  def(SBA2048);
  def(BF1);
  def(BF1P);
  def(BF2);
  def(BF2P);
  def(BF3);
  def(BF3P);
  def(BF4);
  def(BF4P);
  def(BF5);
  def(BF5P);
  def(BF6);
  def(BF6P);
  def(BF7);
  def(BF7P);
  def(BF8);
  def(BF8P);
  def(BF9);
  def(BF9P);
  def(BF10);
  def(BF10P);
  def(BF11);
  def(BF11P);
  def(BF12);
  def(BF12P);
  def(BF13);
  def(BF13P);
  def(BF14);
  def(BF14P);
  def(BF15);
  def(BF15P);

  def_offset(S1, A, a);
  def_offset(S1, B, b);
  def_offset(S1, C, c);
  def_offset(S1, D, d);
  def_offset(S1, E, e);
  def_offset(S1, F, f);
  def_offset(S1, G, g);
  def_offset(S1, H, h);
  def_offset(S1, I, i);
  def_offset(S1, J, j);
  def_offset(S1, K, k);
  def_offset(S1, L, l);
  def_offset(S1, M, m);
  def_offset(S1, N, n);

  def_offset(S1P, A, a);
  def_offset(S1P, B, b);
  def_offset(S1P, C, c);
  def_offset(S1P, D, d);
  def_offset(S1P, E, e);
  def_offset(S1P, F, f);
  def_offset(S1P, G, g);
  def_offset(S1P, H, h);
  def_offset(S1P, I, i);
  def_offset(S1P, J, j);
  def_offset(S1P, K, k);
  def_offset(S1P, L, l);
  def_offset(S1P, M, m);
  def_offset(S1P, N, n);

  def_offset(S2, A, a);
  def_offset(S2, B, b);
  def_offset(S2, C, c);
  def_offset(S2, D, d);
  def_offset(S2, E, e);
  def_offset(S2, F, f);
  def_offset(S2, G, g);
  def_offset(S2, H, h);
  def_offset(S2, I, i);
  def_offset(S2, J, j);
  def_offset(S2, K, k);
  def_offset(S2, L, l);
  def_offset(S2, M, m);
  def_offset(S2, N, n);

  def_offset(S2P, A, a);
  def_offset(S2P, B, b);
  def_offset(S2P, C, c);
  def_offset(S2P, D, d);
  def_offset(S2P, E, e);
  def_offset(S2P, F, f);
  def_offset(S2P, G, g);
  def_offset(S2P, H, h);
  def_offset(S2P, I, i);
  def_offset(S2P, J, j);
  def_offset(S2P, K, k);
  def_offset(S2P, L, l);
  def_offset(S2P, M, m);
  def_offset(S2P, N, n);

  def(S3);
  def(S3P);

  def(S4);
  def_offset(S4, A, a);
  def_offset(S4, B, b);
  def_offset(S4, C, c);
  def_offset(S4, D, d);
  def_offset(S4, E_A, e.a);
  def_offset(S4, E_B, e.b);
  def_offset(S4, E_B_A, e.b.a);
  def_offset(S4, E_B_B, e.b.b);
  def_offset(S4, E_B_B_1, e.b.b[1]);
  def_offset(S4, E_B_B_1_A, e.b.b[1].a);
  def_offset(S4, E_B_B_1_A_2, e.b.b[1].a[2]);
  def_offset(S4, E_B_B_2, e.b.b[2]);
  def_offset(S4, F, f);

  def(S4P);
  def_offset(S4P, A, a);
  def_offset(S4P, B, b);
  def_offset(S4P, C, c);
  def_offset(S4P, D, d);
  def_offset(S4P, E_A, e.a);
  def_offset(S4P, E_B, e.b);
  def_offset(S4P, E_B_A, e.b.a);
  def_offset(S4P, E_B_B, e.b.b);
  def_offset(S4P, E_B_B_1, e.b.b[1]);
  def_offset(S4P, E_B_B_1_A, e.b.b[1].a);
  def_offset(S4P, E_B_B_1_A_2, e.b.b[1].a[2]);
  def_offset(S4P, E_B_B_2, e.b.b[2]);
  def_offset(S4P, F, f);

  return 0;
}
