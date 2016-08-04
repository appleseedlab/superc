/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2007 Robert Grimm
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
 * USA.
 */

#include "data.h"
#include "metadata.h"
#include "harness.h"

int main(void) {
  test(B);
  test(C);
  test(SC);
  test(UC);
  test(S);
  test(US);
  test(I);
  test(UI);
  test(L);
  test(UL);
  test(LL);
  test(ULL);
  test(F);
  test(D);
  test(LD);

  test(AB);
  test(AC);
  test(ASC);
  test(AUC);
  test(AS);
  test(AUS);
  test(AI);
  test(AUI);
  test(AL);
  test(AUL);
  test(ALL);
  test(AULL);
  test(AF);
  test(AD);
  test(ALD);

  test(BFB);
  test(BFBP);
  test(BFC);
  test(BFCP);
  test(BFS);
  test(BFSP);
  test(BFI);
  test(BFIP);
  test(BFL);
  test(BFLP);
  test(BFLL);
  test(BFLLP);
  test(SBA1024);
  test(SBA2048);
  test(BF1);
  test(BF1P);
  test(BF2);
  test(BF2P);
  test(BF3);
  test(BF3P);
  test(BF4);
  test(BF4P);
  test(BF5);
  test(BF5P);
  test(BF6);
  test(BF6P);
  test(BF7);
  test(BF7P);
  test(BF8);
  test(BF8P);
  test(BF9);
  test(BF9P);
  test(BF10);
  test(BF10P);
  test(BF11);
  test(BF11P);
  test(BF12);
  test(BF12P);
  test(BF13);
  test(BF13P);
  test(BF14);
  test(BF14P);
  test(BF15);
  test(BF15P);

  test_offset(S1, A, a);
  test_offset(S1, B, b);
  test_offset(S1, C, c);
  test_offset(S1, D, d);
  test_offset(S1, E, e);
  test_offset(S1, F, f);
  test_offset(S1, G, g);
  test_offset(S1, H, h);
  test_offset(S1, I, i);
  test_offset(S1, J, j);
  test_offset(S1, K, k);
  test_offset(S1, L, l);
  test_offset(S1, M, m);
  test_offset(S1, N, n);

  test_offset(S1P, A, a);
  test_offset(S1P, B, b);
  test_offset(S1P, C, c);
  test_offset(S1P, D, d);
  test_offset(S1P, E, e);
  test_offset(S1P, F, f);
  test_offset(S1P, G, g);
  test_offset(S1P, H, h);
  test_offset(S1P, I, i);
  test_offset(S1P, J, j);
  test_offset(S1P, K, k);
  test_offset(S1P, L, l);
  test_offset(S1P, M, m);
  test_offset(S1P, N, n);

  test_offset(S2, A, a);
  test_offset(S2, B, b);
  test_offset(S2, C, c);
  test_offset(S2, D, d);
  test_offset(S2, E, e);
  test_offset(S2, F, f);
  test_offset(S2, G, g);
  test_offset(S2, H, h);
  test_offset(S2, I, i);
  test_offset(S2, J, j);
  test_offset(S2, K, k);
  test_offset(S2, L, l);
  test_offset(S2, M, m);
  test_offset(S2, N, n);

  test_offset(S2P, A, a);
  test_offset(S2P, B, b);
  test_offset(S2P, C, c);
  test_offset(S2P, D, d);
  test_offset(S2P, E, e);
  test_offset(S2P, F, f);
  test_offset(S2P, G, g);
  test_offset(S2P, H, h);
  test_offset(S2P, I, i);
  test_offset(S2P, J, j);
  test_offset(S2P, K, k);
  test_offset(S2P, L, l);
  test_offset(S2P, M, m);
  test_offset(S2P, N, n);

  test(S3);
  test(S3P);

  test(S4);
  test_offset(S4, A, a);
  test_offset(S4, B, b);
  test_offset(S4, C, c);
  test_offset(S4, D, d);
  test_offset(S4, E_A, e.a);
  test_offset(S4, E_B, e.b);
  test_offset(S4, E_B_A, e.b.a);
  test_offset(S4, E_B_B, e.b.b);
  test_offset(S4, E_B_B_1, e.b.b[1]);
  test_offset(S4, E_B_B_1_A, e.b.b[1].a);
  test_offset(S4, E_B_B_1_A_2, e.b.b[1].a[2]);
  test_offset(S4, E_B_B_2, e.b.b[2]);
  test_offset(S4, F, f);

  test(S4P);
  test_offset(S4P, A, a);
  test_offset(S4P, B, b);
  test_offset(S4P, C, c);
  test_offset(S4P, D, d);
  test_offset(S4P, E_A, e.a);
  test_offset(S4P, E_B, e.b);
  test_offset(S4P, E_B_A, e.b.a);
  test_offset(S4P, E_B_B, e.b.b);
  test_offset(S4P, E_B_B_1, e.b.b[1]);
  test_offset(S4P, E_B_B_1_A, e.b.b[1].a);
  test_offset(S4P, E_B_B_1_A_2, e.b.b[1].a[2]);
  test_offset(S4P, E_B_B_2, e.b.b[2]);
  test_offset(S4P, F, f);

  return 0;
}
