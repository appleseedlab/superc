/* $Id: Serpent.java,v 1.1 2004/01/19 02:03:51 rgrimm Exp $
 *
 * Copyright (C) 1997-2000 The Cryptix Foundation Limited.
 * All rights reserved.
 *
 * Use, modification, copying and distribution of this software is subject
 * the terms and conditions of the Cryptix General Licence. You should have
 * received a copy of the Cryptix General Licence along with this library;
 * if not, you can download a copy from http://www.cryptix.org/ .
 */
package cryptix.jce.provider.cipher;


import java.security.InvalidKeyException;
import java.security.Key;


/**
 * A bit-slice implementation in Java of the Serpent cipher.<p>
 *
 * Serpent is a 128-bit 32-round block cipher with variable key lengths,
 * including 128-, 192- and 256-bit
 * keys conjectured to be at least as secure as three-key triple-DES.<p>
 *
 * Serpent was designed by Ross Anderson, Eli Biham and Lars Knudsen as a
 * candidate algorithm for the NIST AES Quest.<p>
 *
 * References:<ol>
 *  <li>Serpent: A New Block Cipher Proposal. This paper was published in the
 *  proceedings of the "Fast Software Encryption Workshop No. 5" held in
 *  Paris in March 1998. LNCS, Springer Verlag.<p>
 *  <li>Reference implementation of the standard Serpent cipher written in C
 *  by <a href="http://www.cl.cam.ac.uk/~fms/"> Frank Stajano</a>.</ol><p>
 *
 * @version $Revision: 1.1 $
 * @author  Jeroen C. van Gelderen (gelderen@cryptix.org)
 * @author  Raif S. Naffah
 * @author  Serpent authors (Ross Anderson, Eli Biham and Lars Knudsen)
 */
public final class Serpent extends BlockCipher
{

// Constants
//...........................................................................

    private static final int
        BLOCK_SIZE = 16, // bytes in a data-block
        ROUNDS     = 32, // nbr of rounds
        PHI        = 0x9E3779B9; // (sqrt(5) - 1) * 2**31

    private boolean decrypt;

    private int[] K = new int[4 * (ROUNDS + 1)];


// Constructor
//...........................................................................

    public Serpent()
    {
        super(BLOCK_SIZE);
    }


// BlockCipher abstract method implementation
//...........................................................................

    protected void coreInit(Key key, boolean decrypt)
    throws InvalidKeyException
    {
        if( key==null )
            throw new InvalidKeyException("key: key is null");

        if( !key.getFormat().equalsIgnoreCase("RAW") )
            throw new InvalidKeyException("key: wrong format, RAW needed");

        byte[] userkey = key.getEncoded();
        if(userkey == null)
            throw new InvalidKeyException("RAW bytes missing");

        int len = userkey.length ;
        if( len != 16 && len != 24 && len!=32 )
            throw new InvalidKeyException("Invalid user key length");

        generateSubKeys(userkey);
        this.decrypt   = decrypt;
    }


    protected void coreCrypt(byte[] in, int inOffset, byte[] out, int outOffset)
    {
        if( decrypt )
            blockDecrypt(in, inOffset, out, outOffset);
        else
            blockEncrypt(in, inOffset, out, outOffset);
    }


    /**
     * An array of 8 (number of rounds/4) S boxes.<p>
     *
     * An S box is an array of 16 distinct quantities, each in the range 0-15.
     * A value v at position p for a given S box, implies that if this S box
     * is given on input a value p, it will return the value v.
     *
     * Original S box data below. We use a more compact encoding that is
     * expanded in a static initializer.
     *
     *  { 3, 8,15, 1,10, 6, 5,11,14,13, 4, 2, 7, 0, 9,12 }, // S0
     *  {15,12, 2, 7, 9, 0, 5,10, 1,11,14, 8, 6,13, 3, 4 }, // S1
     *  { 8, 6, 7, 9, 3,12,10,15,13, 1,14, 4, 0,11, 5, 2 }, // S2
     *  { 0,15,11, 8,12, 9, 6, 3,13, 1, 2, 4,10, 7, 5,14 }, // S3
     *  { 1,15, 8, 3,12, 0,11, 6, 2, 5, 4,10, 9,14, 7,13 }, // S4
     *  {15, 5, 2,11, 4,10, 9,12, 0, 3,14, 8,13, 6, 7, 1 }, // S5
     *  { 7, 2,12, 5, 8, 4, 6,11,14, 9, 1,15,13, 3,10, 0 }, // S6
     *  { 1,13,15, 0,14, 8, 2,11, 7, 4,12,10, 9, 3, 5, 6 }  // S7
     */
    private static final byte[][] Sbox;

    static
    {
        Sbox = new byte[8][16];

        String SBOX_INIT = "\u0038\u00f1\u00a6\u005b\u00ed\u0042\u0070\u009c" +
                           "\u00fc\u0027\u0090\u005a\u001b\u00e8\u006d\u0034" +
                           "\u0086\u0079\u003c\u00af\u00d1\u00e4\u000b\u0052" +
                           "\u000f\u00b8\u00c9\u0063\u00d1\u0024\u00a7\u005e" +
                           "\u001f\u0083\u00c0\u00b6\u0025\u004a\u009e\u007d" +
                           "\u00f5\u002b\u004a\u009c\u0003\u00e8\u00d6\u0071" +
                           "\u0072\u00c5\u0084\u006b\u00e9\u001f\u00d3\u00a0" +
                           "\u001d\u00f0\u00e8\u002b\u0074\u00ca\u0093\u0056";

        for(int i=0; i<8; i++)
            for(int j=0; j<16; )
            {
                int ci = (i*8) + (j/2);
                Sbox[i][j] = (byte)(SBOX_INIT.charAt(ci) >>> 4); j++;
                Sbox[i][j] = (byte)(SBOX_INIT.charAt(ci) & 0xF); j++;
            }
    }


// Implementation
//...........................................................................

    /**
     * Expand a user-supplied key material into a session key.
     *
     * @param key  The user-key bytes (multiples of 4) to use.
     */
    private final void generateSubKeys(byte[] key)
    {
        // compute prekeys w[]:
        // (a) from user key material
        this.K = new int[4 * (ROUNDS + 1)];
        int[] w = this.K;

        int limit  = key.length / 4;
        int offset = key.length - 1;
        int i, j, t;
        for (i = 0; i < limit; i++)
            w[i] = (key[offset--] & 0xFF)       |
                   (key[offset--] & 0xFF) <<  8 |
                   (key[offset--] & 0xFF) << 16 |
                   (key[offset--] & 0xFF) << 24;

        if (i < 8)
            w[i++] = 1;

        // (b) and expanding them to full 132 x 32-bit material
        // this is a literal implementation of the Serpent paper
        // (section 4 The Key Schedule, p.226)
        //
        // start by computing the first 8 values using the second
        // lot of 8 values as an intermediary buffer
        for (i = 8, j = 0; i < 16; i++)
        {
            t = w[j] ^ w[i-5] ^ w[i-3] ^ w[i-1] ^ PHI ^ j++;
            w[i] = t << 11 | t >>> 21;
        }

        // translate the buffer by -8
        for (i = 0, j = 8; i < 8; ) w[i++] = w[j++];

        limit = 4 * (ROUNDS + 1); // 132 for a 32-round Serpent

        // finish computing the remaining intermediary subkeys
        for ( ; i < limit; i++)
        {
            t = w[i-8] ^ w[i-5] ^ w[i-3] ^ w[i-1] ^ PHI ^ i;
            w[i] = t << 11 | t >>> 21;
        }

        // compute intermediary key. use the same array as prekeys
        int x0, x1, x2, x3, y0, y1, y2, y3, z;
        byte[] sb;
        for (i = 0; i < ROUNDS + 1; i++)
        {
            x0 = w[4*i    ];
            x1 = w[4*i + 1];
            x2 = w[4*i + 2];
            x3 = w[4*i + 3];
            y0 = y1 = y2 = y3 = 0;
            sb = Sbox[(ROUNDS + 3 - i) % 8];
            for (j = 0; j < 32; j++)
            {
                z = sb[((x0 >>> j) & 0x01)      |
                       ((x1 >>> j) & 0x01) << 1 |
                       ((x2 >>> j) & 0x01) << 2 |
                       ((x3 >>> j) & 0x01) << 3];
                y0 |= ( z        & 0x01) << j;
                y1 |= ((z >>> 1) & 0x01) << j;
                y2 |= ((z >>> 2) & 0x01) << j;
                y3 |= ((z >>> 3) & 0x01) << j;
            }
            w[4*i    ] = y0;
            w[4*i + 1] = y1;
            w[4*i + 2] = y2;
            w[4*i + 3] = y3;
        }
    }


    /**
     * Encrypt exactly one block of plaintext.
     *
     * @param  in         The plaintext.
     * @param  inOffset   Index of in from which to start considering data.
     * @param  sessionKey The session key to use for encryption.
     * @return The ciphertext generated from a plaintext using the session key.
     */
    private final void blockEncrypt(byte[] in, int inOffset,
                                    byte[] out, int outOffset)
    {
        int x3 = (in[inOffset++] & 0xFF) << 24 |
                 (in[inOffset++] & 0xFF) << 16 |
                 (in[inOffset++] & 0xFF) <<  8 |
                 (in[inOffset++] & 0xFF);
        int x2 = (in[inOffset++] & 0xFF) << 24 |
                 (in[inOffset++] & 0xFF) << 16 |
                 (in[inOffset++] & 0xFF) <<  8 |
                 (in[inOffset++] & 0xFF);
        int x1 = (in[inOffset++] & 0xFF) << 24 |
                 (in[inOffset++] & 0xFF) << 16 |
                 (in[inOffset++] & 0xFF) <<  8 |
                 (in[inOffset++] & 0xFF);
        int x0 = (in[inOffset++] & 0xFF) << 24 |
                 (in[inOffset++] & 0xFF) << 16 |
                 (in[inOffset++] & 0xFF) <<  8 |
                 (in[inOffset++] & 0xFF);

        int y0=0, y1=0, y2=0, y3=0, z;

        int t00, t01, t02, t03, t04, t05, t06, t07, t08, t09, t10;
        int t11, t12, t13, t14, t15, t16, t17, t18, t19;

        int idxK = 0;

        for(int i=0; i<4; i++)
        {
            x0 ^=  K[ idxK++ ];
            x1 ^=  K[ idxK++ ];
            x2 ^=  K[ idxK++ ];
            x3 ^=  K[ idxK++ ];

            // S0:   3  8 15  1 10  6  5 11 14 13  4  2  7  0  9 12
            // depth = 5,7,4,2, Total gates=18
            t01 = x1  ^ x2 ;
            t02 = x0  | x3 ;
            t03 = x0  ^ x1 ;
            y3  = t02 ^ t01;
            t05 = x2  | y3 ;
            t06 = x0  ^ x3 ;
            t07 = x1  | x2 ;
            t08 = x3  & t05;
            t09 = t03 & t07;
            y2  = t09 ^ t08;
            t11 = t09 & y2 ;
            t12 = x2  ^ x3 ;
            t13 = t07 ^ t11;
            t14 = x1  & t06;
            t15 = t06 ^ t13;
            y0  =     ~ t15;
            t17 = y0  ^ t14;
            y1  = t12 ^ t17;

            x0  = ((((y0))<<(13))| (((y0))>>>(32-(13)))) ;
            x2  = ((((y2))<<(3))| (((y2))>>>(32-(3)))) ;
            x1  =   y1  ^   x0  ^   x2 ;
            x3  =   y3  ^   x2  ^ (x0)<<3;
            x1  = ((((x1))<<(1))| (((x1))>>>(32-(1)))) ;
            x3  = ((((x3))<<(7))| (((x3))>>>(32-(7)))) ;
            x0  =   x0  ^   x1  ^   x3 ;
            x2  =   x2  ^   x3  ^ (x1 <<7);
            x0  = ((((x0))<<(5))| (((x0))>>>(32-(5)))) ;
            x2  = ((((x2))<<(22))| (((x2))>>>(32-(22))))  ;
            x0 ^=  K[ idxK++ ];
            x1 ^=  K[ idxK++ ];
            x2 ^=  K[ idxK++ ];
            x3 ^=  K[ idxK++ ];

            // S1:  15 12  2  7  9  0  5 10  1 11 14  8  6 13  3  4
            // depth = 10,7,3,5, Total gates=18
            t01 = x0  | x3 ;
            t02 = x2  ^ x3 ;
            t03 =     ~ x1 ;
            t04 = x0  ^ x2 ;
            t05 = x0  | t03;
            t06 = x3  & t04;
            t07 = t01 & t02;
            t08 = x1  | t06;
            y2  = t02 ^ t05;
            t10 = t07 ^ t08;
            t11 = t01 ^ t10;
            t12 = y2  ^ t11;
            t13 = x1  & x3 ;
            y3  =     ~ t10;
            y1  = t13 ^ t12;
            t16 = t10 | y1 ;
            t17 = t05 & t16;
            y0  = x2  ^ t17;

            x0  = ((((y0))<<(13))| (((y0))>>>(32-(13)))) ;
            x2  = ((((y2))<<(3))| (((y2))>>>(32-(3)))) ;
            x1  =   y1  ^   x0  ^   x2 ;
            x3  =   y3  ^   x2  ^ (x0)<<3;
            x1  = ((((x1))<<(1))| (((x1))>>>(32-(1)))) ;
            x3  = ((((x3))<<(7))| (((x3))>>>(32-(7)))) ;
            x0  =   x0  ^   x1  ^   x3 ;
            x2  =   x2  ^   x3  ^ (x1 <<7);
            x0  = ((((x0))<<(5))| (((x0))>>>(32-(5)))) ;
            x2  = ((((x2))<<(22))| (((x2))>>>(32-(22))))  ;
            x0 ^=  K[ idxK++ ];
            x1 ^=  K[ idxK++ ];
            x2 ^=  K[ idxK++ ];
            x3 ^=  K[ idxK++ ] ;

            // S2:   8  6  7  9  3 12 10 15 13  1 14  4  0 11  5  2
            // depth = 3,8,11,7, Total gates=16
            t01 = x0  | x2 ;
            t02 = x0  ^ x1 ;
            t03 = x3  ^ t01;
            y0  = t02 ^ t03;
            t05 = x2  ^ y0 ;
            t06 = x1  ^ t05;
            t07 = x1  | t05;
            t08 = t01 & t06;
            t09 = t03 ^ t07;
            t10 = t02 | t09;
            y1  = t10 ^ t08;
            t12 = x0  | x3 ;
            t13 = t09 ^ y1 ;
            t14 = x1  ^ t13;
            y3  =     ~ t09;
            y2  = t12 ^ t14;

            x0  = ((((y0))<<(13))| (((y0))>>>(32-(13)))) ;
            x2  = ((((y2))<<(3))| (((y2))>>>(32-(3)))) ;
            x1  =   y1  ^   x0  ^   x2 ;
            x3  =   y3  ^   x2  ^ (x0)<<3;
            x1  = ((((x1))<<(1))| (((x1))>>>(32-(1)))) ;
            x3  = ((((x3))<<(7))| (((x3))>>>(32-(7)))) ;
            x0  =   x0  ^   x1  ^   x3 ;
            x2  =   x2  ^   x3  ^ (x1 <<7);
            x0  = ((((x0))<<(5))| (((x0))>>>(32-(5)))) ;
            x2  = ((((x2))<<(22))| (((x2))>>>(32-(22))))  ;
            x0 ^=  K[ idxK++ ];
            x1 ^=  K[ idxK++ ];
            x2 ^=  K[ idxK++ ];
            x3 ^=  K[ idxK++ ];

            // S3:   0 15 11  8 12  9  6  3 13  1  2  4 10  7  5 14
            // depth = 8,3,5,5, Total gates=18 */
            t01 = x0  ^ x2 ;
            t02 = x0  | x3 ;
            t03 = x0  & x3 ;
            t04 = t01 & t02;
            t05 = x1  | t03;
            t06 = x0  & x1 ;
            t07 = x3  ^ t04;
            t08 = x2  | t06;
            t09 = x1  ^ t07;
            t10 = x3  & t05;
            t11 = t02 ^ t10;
            y3  = t08 ^ t09;
            t13 = x3  | y3 ;
            t14 = x0  | t07;
            t15 = x1  & t13;
            y2  = t08 ^ t11;
            y0  = t14 ^ t15;
            y1  = t05 ^ t04;

            x0  = ((((y0))<<(13))| (((y0))>>>(32-(13)))) ;
            x2  = ((((y2))<<(3))| (((y2))>>>(32-(3)))) ;
            x1  =   y1  ^   x0  ^   x2 ;
            x3  =   y3  ^   x2  ^ (x0)<<3;
            x1  = ((((x1))<<(1))| (((x1))>>>(32-(1)))) ;
            x3  = ((((x3))<<(7))| (((x3))>>>(32-(7)))) ;
            x0  =   x0  ^   x1  ^   x3 ;
            x2  =   x2  ^   x3  ^ (x1 <<7);
            x0  = ((((x0))<<(5))| (((x0))>>>(32-(5)))) ;
            x2  = ((((x2))<<(22))| (((x2))>>>(32-(22))))  ;
            x0 ^=  K[ idxK++ ];
            x1 ^=  K[ idxK++ ];
            x2 ^=  K[ idxK++ ];
            x3 ^=  K[ idxK++ ];

            // S4:   1 15  8  3 12  0 11  6  2  5  4 10  9 14  7 13
            // depth = 6,7,5,3, Total gates=19

            t01 = x0  | x1 ;
            t02 = x1  | x2 ;
            t03 = x0  ^ t02;
            t04 = x1  ^ x3 ;
            t05 = x3  | t03;
            t06 = x3  & t01;
            y3  = t03 ^ t06;
            t08 = y3  & t04;
            t09 = t04 & t05;
            t10 = x2  ^ t06;
            t11 = x1  & x2 ;
            t12 = t04 ^ t08;
            t13 = t11 | t03;
            t14 = t10 ^ t09;
            t15 = x0  & t05;
            t16 = t11 | t12;
            y2  = t13 ^ t08;
            y1  = t15 ^ t16;
            y0  =     ~ t14;

            x0  = ((((y0))<<(13))| (((y0))>>>(32-(13)))) ;
            x2  = ((((y2))<<(3))| (((y2))>>>(32-(3)))) ;
            x1  =   y1  ^   x0  ^   x2 ;
            x3  =   y3  ^   x2  ^ (x0)<<3;
            x1  = ((((x1))<<(1))| (((x1))>>>(32-(1)))) ;
            x3  = ((((x3))<<(7))| (((x3))>>>(32-(7)))) ;
            x0  =   x0  ^   x1  ^   x3 ;
            x2  =   x2  ^   x3  ^ (x1 <<7);
            x0  = ((((x0))<<(5))| (((x0))>>>(32-(5)))) ;
            x2  = ((((x2))<<(22))| (((x2))>>>(32-(22))))  ;
            x0 ^=  K[ idxK++ ];
            x1 ^=  K[ idxK++ ];
            x2 ^=  K[ idxK++ ];
            x3 ^=  K[ idxK++ ];

            // S5:  15  5  2 11  4 10  9 12  0  3 14  8 13  6  7  1
            // depth = 4,6,8,6, Total gates=17
            t01 = x1  ^ x3 ;
            t02 = x1  | x3 ;
            t03 = x0  & t01;
            t04 = x2  ^ t02;
            t05 = t03 ^ t04;
            y0  =     ~ t05;
            t07 = x0  ^ t01;
            t08 = x3  | y0 ;
            t09 = x1  | t05;
            t10 = x3  ^ t08;
            t11 = x1  | t07;
            t12 = t03 | y0 ;
            t13 = t07 | t10;
            t14 = t01 ^ t11;
            y2  = t09 ^ t13;
            y1  = t07 ^ t08;
            y3  = t12 ^ t14;

            x0  = ((((y0))<<(13))| (((y0))>>>(32-(13)))) ;
            x2  = ((((y2))<<(3))| (((y2))>>>(32-(3)))) ;
            x1  =   y1  ^   x0  ^   x2 ;
            x3  =   y3  ^   x2  ^ (x0)<<3;
            x1  = ((((x1))<<(1))| (((x1))>>>(32-(1)))) ;
            x3  = ((((x3))<<(7))| (((x3))>>>(32-(7)))) ;
            x0  =   x0  ^   x1  ^   x3 ;
            x2  =   x2  ^   x3  ^ (x1 <<7);
            x0  = ((((x0))<<(5))| (((x0))>>>(32-(5)))) ;
            x2  = ((((x2))<<(22))| (((x2))>>>(32-(22))))  ;
            x0 ^=  K[ idxK++ ];
            x1 ^=  K[ idxK++ ];
            x2 ^=  K[ idxK++ ];
            x3 ^=  K[ idxK++ ];

            // S6:   7  2 12  5  8  4  6 11 14  9  1 15 13  3 10  0
            // depth = 8,3,6,3, Total gates=19
            t01 = x0  & x3 ;
            t02 = x1  ^ x2 ;
            t03 = x0  ^ x3 ;
            t04 = t01 ^ t02;
            t05 = x1  | x2 ;
            y1  =     ~ t04;
            t07 = t03 & t05;
            t08 = x1  & y1 ;
            t09 = x0  | x2 ;
            t10 = t07 ^ t08;
            t11 = x1  | x3 ;
            t12 = x2  ^ t11;
            t13 = t09 ^ t10;
            y2  =     ~ t13;
            t15 = y1  & t03;
            y3  = t12 ^ t07;
            t17 = x0  ^ x1 ;
            t18 = y2  ^ t15;
            y0  = t17 ^ t18;

            x0  = ((((y0))<<(13))| (((y0))>>>(32-(13)))) ;
            x2  = ((((y2))<<(3))| (((y2))>>>(32-(3)))) ;
            x1  =   y1  ^   x0  ^   x2 ;
            x3  =   y3  ^   x2  ^ (x0)<<3;
            x1  = ((((x1))<<(1))| (((x1))>>>(32-(1)))) ;
            x3  = ((((x3))<<(7))| (((x3))>>>(32-(7)))) ;
            x0  =   x0  ^   x1  ^   x3 ;
            x2  =   x2  ^   x3  ^ (x1 <<7);
            x0  = ((((x0))<<(5))| (((x0))>>>(32-(5)))) ;
            x2  = ((((x2))<<(22))| (((x2))>>>(32-(22))))  ;
            x0 ^=  K[ idxK++ ];
            x1 ^=  K[ idxK++ ];
            x2 ^=  K[ idxK++ ];
            x3 ^=  K[ idxK++ ];

            // S7:   1 13 15  0 14  8  2 11  7  4 12 10  9  3  5  6
            // depth = 10,7,10,4, Total gates=19
            t01 = x0  & x2 ;
            t02 =     ~ x3 ;
            t03 = x0  & t02;
            t04 = x1  | t01;
            t05 = x0  & x1 ;
            t06 = x2  ^ t04;
            y3  = t03 ^ t06;
            t08 = x2  | y3 ;
            t09 = x3  | t05;
            t10 = x0  ^ t08;
            t11 = t04 & y3 ;
            y1  = t09 ^ t10;
            t13 = x1  ^ y1 ;
            t14 = t01 ^ y1 ;
            t15 = x2  ^ t05;
            t16 = t11 | t13;
            t17 = t02 | t14;
            y0  = t15 ^ t17;
            y2  = x0  ^ t16;

            if( i==3 )
                break;

            x0  = ((((y0))<<(13))| (((y0))>>>(32-(13)))) ;
            x2  = ((((y2))<<(3))| (((y2))>>>(32-(3)))) ;
            x1  =   y1  ^   x0  ^   x2 ;
            x3  =   y3  ^   x2  ^ (x0)<<3;
            x1  = ((((x1))<<(1))| (((x1))>>>(32-(1)))) ;
            x3  = ((((x3))<<(7))| (((x3))>>>(32-(7)))) ;
            x0  =   x0  ^   x1  ^   x3 ;
            x2  =   x2  ^   x3  ^ (x1 <<7);
            x0  = ((((x0))<<(5))| (((x0))>>>(32-(5)))) ;
            x2  = ((((x2))<<(22))| (((x2))>>>(32-(22))))  ;
        }

        y0 ^=  K[ idxK++ ];
        y1 ^=  K[ idxK++ ];
        y2 ^=  K[ idxK++ ];
        y3 ^=  K[ idxK   ];

        out[outOffset++] = (byte)(y3 >>> 24);
        out[outOffset++] = (byte)(y3 >>> 16);
        out[outOffset++] = (byte)(y3 >>>  8);
        out[outOffset++] = (byte)(y3       );

        out[outOffset++] = (byte)(y2 >>> 24);
        out[outOffset++] = (byte)(y2 >>> 16);
        out[outOffset++] = (byte)(y2 >>>  8);
        out[outOffset++] = (byte)(y2       );

        out[outOffset++] = (byte)(y1 >>> 24);
        out[outOffset++] = (byte)(y1 >>> 16);
        out[outOffset++] = (byte)(y1 >>>  8);
        out[outOffset++] = (byte)(y1       );

        out[outOffset++] = (byte)(y0 >>> 24);
        out[outOffset++] = (byte)(y0 >>> 16);
        out[outOffset++] = (byte)(y0 >>>  8);
        out[outOffset  ] = (byte)(y0       );
    }


    /**
     * Decrypt exactly one block of ciphertext.
     *
     * @param  in         The ciphertext.
     * @param  inOffset   Index of in from which to start considering data.
     * @param  sessionKey The session key to use for decryption.
     * @return The plaintext generated from a ciphertext using the session key.
     */
    private final void blockDecrypt(byte[] in, int inOffset,
                                    byte[] out, int outOffset)
    {
        int x3 = (in[inOffset++] & 0xFF) << 24 |
                 (in[inOffset++] & 0xFF) << 16 |
                 (in[inOffset++] & 0xFF) <<  8 |
                 (in[inOffset++] & 0xFF);
        int x2 = (in[inOffset++] & 0xFF) << 24 |
                 (in[inOffset++] & 0xFF) << 16 |
                 (in[inOffset++] & 0xFF) <<  8 |
                 (in[inOffset++] & 0xFF);
        int x1 = (in[inOffset++] & 0xFF) << 24 |
                 (in[inOffset++] & 0xFF) << 16 |
                 (in[inOffset++] & 0xFF) <<  8 |
                 (in[inOffset++] & 0xFF);
        int x0 = (in[inOffset++] & 0xFF) << 24 |
                 (in[inOffset++] & 0xFF) << 16 |
                 (in[inOffset++] & 0xFF) <<  8 |
                 (in[inOffset++] & 0xFF);

        int y0=0, y1=0, y2=0, y3=0, z;
        int t00, t01, t02, t03, t04, t05, t06, t07, t08, t09, t10;
        int t11, t12, t13, t14, t15, t16, t17, t18, t19;

        int idxK = 32*4+3;

        x3 ^=  K[ idxK-- ];
        x2 ^=  K[ idxK-- ];
        x1 ^=  K[ idxK-- ];
        x0 ^=  K[ idxK-- ];

        for(int i=0; i<4; i++)
        {
            // InvS7:   3  0  6 13  9 14 15  8  5 12 11  7 10  1  4  2
            // depth = 9,7,3,3, Total gates=18
            t01 = x0  & x1 ;
            t02 = x0  | x1 ;
            t03 = x2  | t01;
            t04 = x3  & t02;
            y3  = t03 ^ t04;
            t06 = x1  ^ t04;
            t07 = x3  ^ y3 ;
            t08 =     ~ t07;
            t09 = t06 | t08;
            t10 = x1  ^ x3 ;
            t11 = x0  | x3 ;
            y1  = x0  ^ t09;
            t13 = x2  ^ t06;
            t14 = x2  & t11;
            t15 = x3  | y1 ;
            t16 = t01 | t10;
            y0  = t13 ^ t15;
            y2  = t14 ^ t16;

            y3 ^=  K[ idxK-- ];
            y2 ^=  K[ idxK-- ];
            y1 ^=  K[ idxK-- ];
            y0 ^=  K[ idxK-- ];

            x2  = ((((   y2  ))<<(32-(  22 )))| (((   y2  ))>>>(  22 ))) ;
            x0  = ((((  y0  ))<<(32-(  5 )))| (((  y0  ))>>>(  5 ))) ;
            x2  =   x2  ^   y3  ^ (  y1 <<7);
            x0  =   x0  ^   y1  ^   y3 ;
            x3  = ((((   y3  ))<<(32-(  7 )))| (((   y3  ))>>>(  7 ))) ;
            x1  = ((((   y1  ))<<(32-(  1 )))| (((   y1  ))>>>(  1 ))) ;
            x3  =   x3  ^   x2  ^ (  x0 )<<3;
            x1  =   x1  ^   x0  ^   x2 ;
            x2  = ((((   x2  ))<<(32-(  3 )))| (((   x2  ))>>>(  3 ))) ;
            x0  = ((((   x0  ))<<(32-(  13 )))| (((   x0  ))>>>(  13 )))  ;

            // InvS6:  15 10  1 13  5  3  6  0  4  9 14  7  2 12  8 11
            // depth = 5,3,8,6, Total gates=19
            t01 = x0  ^ x2 ;
            t02 =     ~ x2 ;
            t03 = x1  & t01;
            t04 = x1  | t02;
            t05 = x3  | t03;
            t06 = x1  ^ x3 ;
            t07 = x0  & t04;
            t08 = x0  | t02;
            t09 = t07 ^ t05;
            y1  = t06 ^ t08;
            y0  =     ~ t09;
            t12 = x1  & y0 ;
            t13 = t01 & t05;
            t14 = t01 ^ t12;
            t15 = t07 ^ t13;
            t16 = x3  | t02;
            t17 = x0  ^ y1 ;
            y3  = t17 ^ t15;
            y2  = t16 ^ t14;

            y3 ^=  K[ idxK-- ];
            y2 ^=  K[ idxK-- ];
            y1 ^=  K[ idxK-- ];
            y0 ^=  K[ idxK-- ];

            x2  = ((((   y2  ))<<(32-(  22 )))| (((   y2  ))>>>(  22 ))) ;
            x0  = ((((  y0  ))<<(32-(  5 )))| (((  y0  ))>>>(  5 ))) ;
            x2  =   x2  ^   y3  ^ (  y1 <<7);
            x0  =   x0  ^   y1  ^   y3 ;
            x3  = ((((   y3  ))<<(32-(  7 )))| (((   y3  ))>>>(  7 ))) ;
            x1  = ((((   y1  ))<<(32-(  1 )))| (((   y1  ))>>>(  1 ))) ;
            x3  =   x3  ^   x2  ^ (  x0 )<<3;
            x1  =   x1  ^   x0  ^   x2 ;
            x2  = ((((   x2  ))<<(32-(  3 )))| (((   x2  ))>>>(  3 ))) ;
            x0  = ((((   x0  ))<<(32-(  13 )))| (((   x0  ))>>>(  13 )))  ;

            // InvS5:   8 15  2  9  4  1 13 14 11  6  5  3  7 12 10  0
            // depth = 4,6,9,7, Total gates=17
            t01 = x0  & x3 ;
            t02 = x2  ^ t01;
            t03 = x0  ^ x3 ;
            t04 = x1  & t02;
            t05 = x0  & x2 ;
            y0  = t03 ^ t04;
            t07 = x0  & y0 ;
            t08 = t01 ^ y0 ;
            t09 = x1  | t05;
            t10 =     ~ x1 ;
            y1  = t08 ^ t09;
            t12 = t10 | t07;
            t13 = y0  | y1 ;
            y3  = t02 ^ t12;
            t15 = t02 ^ t13;
            t16 = x1  ^ x3 ;
            y2  = t16 ^ t15;

            y3 ^=  K[ idxK-- ];
            y2 ^=  K[ idxK-- ];
            y1 ^=  K[ idxK-- ];
            y0 ^=  K[ idxK-- ];

            x2  = ((((   y2  ))<<(32-(  22 )))| (((   y2  ))>>>(  22 ))) ;
            x0  = ((((  y0  ))<<(32-(  5 )))| (((  y0  ))>>>(  5 ))) ;
            x2  =   x2  ^   y3  ^ (  y1 <<7);
            x0  =   x0  ^   y1  ^   y3 ;
            x3  = ((((   y3  ))<<(32-(  7 )))| (((   y3  ))>>>(  7 ))) ;
            x1  = ((((   y1  ))<<(32-(  1 )))| (((   y1  ))>>>(  1 ))) ;
            x3  =   x3  ^   x2  ^ (  x0 )<<3;
            x1  =   x1  ^   x0  ^   x2 ;
            x2  = ((((   x2  ))<<(32-(  3 )))| (((   x2  ))>>>(  3 ))) ;
            x0  = ((((   x0  ))<<(32-(  13 )))| (((   x0  ))>>>(  13 )))  ;

            // InvS4:   5  0  8  3 10  9  7 14  2 12 11  6  4 15 13  1
            // depth = 6,4,7,3, Total gates=17
            t01 = x1  | x3 ;
            t02 = x2  | x3 ;
            t03 = x0  & t01;
            t04 = x1  ^ t02;
            t05 = x2  ^ x3 ;
            t06 =     ~ t03;
            t07 = x0  & t04;
            y1  = t05 ^ t07;
            t09 = y1  | t06;
            t10 = x0  ^ t07;
            t11 = t01 ^ t09;
            t12 = x3  ^ t04;
            t13 = x2  | t10;
            y3  = t03 ^ t12;
            t15 = x0  ^ t04;
            y2  = t11 ^ t13;
            y0  = t15 ^ t09;

            y3 ^=  K[ idxK-- ];
            y2 ^=  K[ idxK-- ];
            y1 ^=  K[ idxK-- ];
            y0 ^=  K[ idxK-- ];

            x2  = ((((   y2  ))<<(32-(  22 )))| (((   y2  ))>>>(  22 ))) ;
            x0  = ((((  y0  ))<<(32-(  5 )))| (((  y0  ))>>>(  5 ))) ;
            x2  =   x2  ^   y3  ^ (  y1 <<7);
            x0  =   x0  ^   y1  ^   y3 ;
            x3  = ((((   y3  ))<<(32-(  7 )))| (((   y3  ))>>>(  7 ))) ;
            x1  = ((((   y1  ))<<(32-(  1 )))| (((   y1  ))>>>(  1 ))) ;
            x3  =   x3  ^   x2  ^ (  x0 )<<3;
            x1  =   x1  ^   x0  ^   x2 ;
            x2  = ((((   x2  ))<<(32-(  3 )))| (((   x2  ))>>>(  3 ))) ;
            x0  = ((((   x0  ))<<(32-(  13 )))| (((   x0  ))>>>(  13 )))  ;

            // InvS3:   0  9 10  7 11 14  6 13  3  5 12  2  4  8 15  1
            // depth = 3,6,4,4, Total gates=17
            t01 = x2  | x3 ;
            t02 = x0  | x3 ;
            t03 = x2  ^ t02;
            t04 = x1  ^ t02;
            t05 = x0  ^ x3 ;
            t06 = t04 & t03;
            t07 = x1  & t01;
            y2  = t05 ^ t06;
            t09 = x0  ^ t03;
            y0  = t07 ^ t03;
            t11 = y0  | t05;
            t12 = t09 & t11;
            t13 = x0  & y2 ;
            t14 = t01 ^ t05;
            y1  = x1  ^ t12;
            t16 = x1  | t13;
            y3  = t14 ^ t16;

            y3 ^=  K[ idxK-- ];
            y2 ^=  K[ idxK-- ];
            y1 ^=  K[ idxK-- ];
            y0 ^=  K[ idxK-- ];

            x2  = ((((   y2  ))<<(32-(  22 )))| (((   y2  ))>>>(  22 ))) ;
            x0  = ((((  y0  ))<<(32-(  5 )))| (((  y0  ))>>>(  5 ))) ;
            x2  =   x2  ^   y3  ^ (  y1 <<7);
            x0  =   x0  ^   y1  ^   y3 ;
            x3  = ((((   y3  ))<<(32-(  7 )))| (((   y3  ))>>>(  7 ))) ;
            x1  = ((((   y1  ))<<(32-(  1 )))| (((   y1  ))>>>(  1 ))) ;
            x3  =   x3  ^   x2  ^ (  x0 )<<3;
            x1  =   x1  ^   x0  ^   x2 ;
            x2  = ((((   x2  ))<<(32-(  3 )))| (((   x2  ))>>>(  3 ))) ;
            x0  = ((((   x0  ))<<(32-(  13 )))| (((   x0  ))>>>(  13 )))  ;

            // InvS2:  12  9 15  4 11 14  1  2  0  3  6 13  5  8 10  7
            // depth = 3,6,8,3, Total gates=18
            t01 = x0  ^ x3 ;
            t02 = x2  ^ x3 ;
            t03 = x0  & x2 ;
            t04 = x1  | t02;
            y0  = t01 ^ t04;
            t06 = x0  | x2 ;
            t07 = x3  | y0 ;
            t08 =     ~ x3 ;
            t09 = x1  & t06;
            t10 = t08 | t03;
            t11 = x1  & t07;
            t12 = t06 & t02;
            y3  = t09 ^ t10;
            y1  = t12 ^ t11;
            t15 = x2  & y3 ;
            t16 = y0  ^ y1 ;
            t17 = t10 ^ t15;
            y2  = t16 ^ t17;

            y3 ^=  K[ idxK-- ];
            y2 ^=  K[ idxK-- ];
            y1 ^=  K[ idxK-- ];
            y0 ^=  K[ idxK-- ];

            x2  = ((((   y2  ))<<(32-(  22 )))| (((   y2  ))>>>(  22 ))) ;
            x0  = ((((  y0  ))<<(32-(  5 )))| (((  y0  ))>>>(  5 ))) ;
            x2  =   x2  ^   y3  ^ (  y1 <<7);
            x0  =   x0  ^   y1  ^   y3 ;
            x3  = ((((   y3  ))<<(32-(  7 )))| (((   y3  ))>>>(  7 ))) ;
            x1  = ((((   y1  ))<<(32-(  1 )))| (((   y1  ))>>>(  1 ))) ;
            x3  =   x3  ^   x2  ^ (  x0 )<<3;
            x1  =   x1  ^   x0  ^   x2 ;
            x2  = ((((   x2  ))<<(32-(  3 )))| (((   x2  ))>>>(  3 ))) ;
            x0  = ((((   x0  ))<<(32-(  13 )))| (((   x0  ))>>>(  13 )))  ;

            // InvS1:   5  8  2 14 15  6 12  3 11  4  7  9  1 13 10  0
            // depth = 7,4,5,3, Total gates=18
            t01 = x0  ^ x1 ;
            t02 = x1  | x3 ;
            t03 = x0  & x2 ;
            t04 = x2  ^ t02;
            t05 = x0  | t04;
            t06 = t01 & t05;
            t07 = x3  | t03;
            t08 = x1  ^ t06;
            t09 = t07 ^ t06;
            t10 = t04 | t03;
            t11 = x3  & t08;
            y2  =     ~ t09;
            y1  = t10 ^ t11;
            t14 = x0  | y2 ;
            t15 = t06 ^ y1 ;
            y3  = t01 ^ t04;
            t17 = x2  ^ t15;
            y0  = t14 ^ t17;

            y3 ^=  K[ idxK-- ];
            y2 ^=  K[ idxK-- ];
            y1 ^=  K[ idxK-- ];
            y0 ^=  K[ idxK-- ];

            x2  = ((((   y2  ))<<(32-(  22 )))| (((   y2  ))>>>(  22 ))) ;
            x0  = ((((  y0  ))<<(32-(  5 )))| (((  y0  ))>>>(  5 ))) ;
            x2  =   x2  ^   y3  ^ (  y1 <<7);
            x0  =   x0  ^   y1  ^   y3 ;
            x3  = ((((   y3  ))<<(32-(  7 )))| (((   y3  ))>>>(  7 ))) ;
            x1  = ((((   y1  ))<<(32-(  1 )))| (((   y1  ))>>>(  1 ))) ;
            x3  =   x3  ^   x2  ^ (  x0 )<<3;
            x1  =   x1  ^   x0  ^   x2 ;
            x2  = ((((   x2  ))<<(32-(  3 )))| (((   x2  ))>>>(  3 ))) ;
            x0  = ((((   x0  ))<<(32-(  13 )))| (((   x0  ))>>>(  13 )))  ;

            // InvS0:  13  3 11  0 10  6  5 12  1 14  4  7 15  9  8  2
            // depth = 8,4,3,6, Total gates=19
            t01 = x2  ^ x3 ;
            t02 = x0  | x1 ;
            t03 = x1  | x2 ;
            t04 = x2  & t01;
            t05 = t02 ^ t01;
            t06 = x0  | t04;
            y2  =     ~ t05;
            t08 = x1  ^ x3 ;
            t09 = t03 & t08;
            t10 = x3  | y2 ;
            y1  = t09 ^ t06;
            t12 = x0  | t05;
            t13 = y1  ^ t12;
            t14 = t03 ^ t10;
            t15 = x0  ^ x2 ;
            y3  = t14 ^ t13;
            t17 = t05 & t13;
            t18 = t14 | t17;
            y0  = t15 ^ t18;

            y3 ^=  K[ idxK-- ];
            y2 ^=  K[ idxK-- ];
            y1 ^=  K[ idxK-- ];
            y0 ^=  K[ idxK-- ];

            if( i==3 )
                break;

            x2  = ((((   y2  ))<<(32-(  22 )))| (((   y2  ))>>>(  22 ))) ;
            x0  = ((((  y0  ))<<(32-(  5 )))| (((  y0  ))>>>(  5 ))) ;
            x2  =   x2  ^   y3  ^ (  y1 <<7);
            x0  =   x0  ^   y1  ^   y3 ;
            x3  = ((((   y3  ))<<(32-(  7 )))| (((   y3  ))>>>(  7 ))) ;
            x1  = ((((   y1  ))<<(32-(  1 )))| (((   y1  ))>>>(  1 ))) ;
            x3  =   x3  ^   x2  ^ (  x0 )<<3;
            x1  =   x1  ^   x0  ^   x2 ;
            x2  = ((((   x2  ))<<(32-(  3 )))| (((   x2  ))>>>(  3 ))) ;
            x0  = ((((   x0  ))<<(32-(  13 )))| (((   x0  ))>>>(  13 )))  ;
        }

        out[outOffset++] = (byte)(y3 >>> 24);
        out[outOffset++] = (byte)(y3 >>> 16);
        out[outOffset++] = (byte)(y3 >>>  8);
        out[outOffset++] = (byte)(y3       );

        out[outOffset++] = (byte)(y2 >>> 24);
        out[outOffset++] = (byte)(y2 >>> 16);
        out[outOffset++] = (byte)(y2 >>>  8);
        out[outOffset++] = (byte)(y2       );

        out[outOffset++] = (byte)(y1 >>> 24);
        out[outOffset++] = (byte)(y1 >>> 16);
        out[outOffset++] = (byte)(y1 >>>  8);
        out[outOffset++] = (byte)(y1       );

        out[outOffset++] = (byte)(y0 >>> 24);
        out[outOffset++] = (byte)(y0 >>> 16);
        out[outOffset++] = (byte)(y0 >>>  8);
        out[outOffset  ] = (byte)(y0       );
    }
}
