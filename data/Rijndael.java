/* $Id: Rijndael.java,v 1.1 2004/01/19 02:03:51 rgrimm Exp $
 *
 * Copyright (C) 1995-2000 The Cryptix Foundation Limited.
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
 * Rijndael --pronounced Reindaal-- is a symmetric cipher with a 128-bit
 * block size and variable key-size (128-, 192- and 256-bit).
 * <p>
 * Rijndael was designed by <a href="mailto:rijmen@esat.kuleuven.ac.be">Vincent
 * Rijmen</a> and <a href="mailto:daemen.j@protonworld.com">Joan Daemen</a>.
 * <p>
 * @version $Revision: 1.1 $
 * @author  Raif S. Naffah
 * @author  Paulo S. L. M. Barreto (pbarreto@cryptix.org)
 * @author  Jeroen C. van Gelderen (gelderen@cryptix.org)
 */
public final class Rijndael extends BlockCipher {

    private boolean 
        ROUNDS_12,
        ROUNDS_14;

    /** True if in decrypt mode */
    private boolean decrypt;

    /** Subkeys */
    private int[] K;

    /** (ROUNDS-1) * 4 */
    private int limit;


    public Rijndael() {
        super(BLOCK_SIZE);
    }


    protected void coreInit(Key key, boolean decrypt)
    throws InvalidKeyException
    {
        if( key==null )
            throw new InvalidKeyException("Key missing");

        if( !key.getFormat().equalsIgnoreCase("RAW") )
            throw new InvalidKeyException("Wrong format: RAW bytes needed");

        byte[] userkey = key.getEncoded();
        if(userkey == null)
            throw new InvalidKeyException("RAW bytes missing");

        int len = userkey.length ;
        if( len != 16 && len != 24 && len!=32 )
            throw new InvalidKeyException("Invalid user key length");

        this.decrypt = decrypt;

        this.K = makeKey(userkey, decrypt);
        if(decrypt) invertKey(this.K);

        ROUNDS_12 = (len >= 24);
        ROUNDS_14 = (len == 32);

        this.limit=getRounds(len)*4;
    }


    protected void coreCrypt(byte[] in, int inOffset, byte[] out, int outOffset)
    {
        if( decrypt )
            blockDecrypt(in, inOffset, out, outOffset);
        else
            blockEncrypt(in, inOffset, out, outOffset);
    }


// Constants and variables
//...........................................................................

    private static final int BLOCK_SIZE = 16; // block size in bytes

    private static final String SS =
        "\u637C\u777B\uF26B\u6FC5\u3001\u672B\uFED7\uAB76" +
        "\uCA82\uC97D\uFA59\u47F0\uADD4\uA2AF\u9CA4\u72C0" +
        "\uB7FD\u9326\u363F\uF7CC\u34A5\uE5F1\u71D8\u3115" +
        "\u04C7\u23C3\u1896\u059A\u0712\u80E2\uEB27\uB275" +
        "\u0983\u2C1A\u1B6E\u5AA0\u523B\uD6B3\u29E3\u2F84" +
        "\u53D1\u00ED\u20FC\uB15B\u6ACB\uBE39\u4A4C\u58CF" +
        "\uD0EF\uAAFB\u434D\u3385\u45F9\u027F\u503C\u9FA8" +
        "\u51A3\u408F\u929D\u38F5\uBCB6\uDA21\u10FF\uF3D2" +
        "\uCD0C\u13EC\u5F97\u4417\uC4A7\u7E3D\u645D\u1973" +
        "\u6081\u4FDC\u222A\u9088\u46EE\uB814\uDE5E\u0BDB" +
        "\uE032\u3A0A\u4906\u245C\uC2D3\uAC62\u9195\uE479" +
        "\uE7C8\u376D\u8DD5\u4EA9\u6C56\uF4EA\u657A\uAE08" +
        "\uBA78\u252E\u1CA6\uB4C6\uE8DD\u741F\u4BBD\u8B8A" +
        "\u703E\uB566\u4803\uF60E\u6135\u57B9\u86C1\u1D9E" +
        "\uE1F8\u9811\u69D9\u8E94\u9B1E\u87E9\uCE55\u28DF" +
        "\u8CA1\u890D\uBFE6\u4268\u4199\u2D0F\uB054\uBB16";

    private static final byte[]
        S  = new byte[256],
        Si = new byte[256];

    private static final int[]
        T1 = new int[256],
        T2 = new int[256],
        T3 = new int[256],
        T4 = new int[256],
        T5 = new int[256],
        T6 = new int[256],
        T7 = new int[256],
        T8 = new int[256];

    private static final int[]
        U1 = new int[256],
        U2 = new int[256],
        U3 = new int[256],
        U4 = new int[256];

    private static final byte[] rcon = new byte[30];


// Static code - to intialise S-boxes and T-boxes
//...........................................................................

    static {
        int ROOT = 0x11B;
        int i, j = 0;

        for (i = 0; i < 256; i++) {
            int s, s2, s3, i2, i4, i8, i9, ib, id, ie, t;
            char c = SS.charAt(i >>> 1);
            S[i] = (byte)(((i & 1) == 0) ? c >>> 8 : c & 0xFF);
            s = S[i] & 0xFF;
            Si[s] = (byte)i;
            s2 = s << 1;
            if (s2 >= 0x100) {
                s2 ^= ROOT;
            }
            s3 = s2 ^ s;
            i2 = i << 1;
            if (i2 >= 0x100) {
                i2 ^= ROOT;
            }
            i4 = i2 << 1;
            if (i4 >= 0x100) {
                i4 ^= ROOT;
            }
            i8 = i4 << 1;
            if (i8 >= 0x100) {
                i8 ^= ROOT;
            }
            i9 = i8 ^ i;
            ib = i9 ^ i2;
            id = i9 ^ i4;
            ie = i8 ^ i4 ^ i2;

            T1[i] = t = (s2 << 24) | (s << 16) | (s << 8) | s3;
            T2[i] = (t >>>  8) | (t << 24);
            T3[i] = (t >>> 16) | (t << 16);
            T4[i] = (t >>> 24) | (t <<  8);

            T5[s] = U1[i] = t = (ie << 24) | (i9 << 16) | (id << 8) | ib;
            T6[s] = U2[i] = (t >>>  8) | (t << 24);
            T7[s] = U3[i] = (t >>> 16) | (t << 16);
            T8[s] = U4[i] = (t >>> 24) | (t <<  8);
        }
        //
        // round constants
        //
        int r = 1;
        rcon[0] = 1;
        for (i = 1; i < 30; i++) {
            r <<= 1;
            if (r >= 0x100) {
                r ^= ROOT;
            }
            rcon[i] = (byte)r;
        }

    }

//...........................................................................


    /**
     * Encrypt exactly one block of plaintext.
     */
    private void blockEncrypt(byte[] in, int inOffset, 
                              byte[] out, int outOffset) 
    {
        // plaintext to ints + key
        int keyOffset = 0;
        int t0   = ((in[inOffset++]       ) << 24 |
                    (in[inOffset++] & 0xFF) << 16 |
                    (in[inOffset++] & 0xFF) <<  8 |
                    (in[inOffset++] & 0xFF)        ) ^ K[keyOffset++];
        int t1   = ((in[inOffset++]       ) << 24 |
                    (in[inOffset++] & 0xFF) << 16 |
                    (in[inOffset++] & 0xFF) <<  8 |
                    (in[inOffset++] & 0xFF)        ) ^ K[keyOffset++];
        int t2   = ((in[inOffset++]       ) << 24 |
                    (in[inOffset++] & 0xFF) << 16 |
                    (in[inOffset++] & 0xFF) <<  8 |
                    (in[inOffset++] & 0xFF)        ) ^ K[keyOffset++];
        int t3   = ((in[inOffset++]       ) << 24 |
                    (in[inOffset++] & 0xFF) << 16 |
                    (in[inOffset++] & 0xFF) <<  8 |
                    (in[inOffset++] & 0xFF)        ) ^ K[keyOffset++];

        // apply round transforms
        while( keyOffset < limit ) {
            int a0, a1, a2;
            a0 = T1[(t0 >>> 24)       ] ^
                 T2[(t1 >>> 16) & 0xFF] ^
                 T3[(t2 >>>  8) & 0xFF] ^
                 T4[(t3       ) & 0xFF] ^ K[keyOffset++];
            a1 = T1[(t1 >>> 24)       ] ^
                 T2[(t2 >>> 16) & 0xFF] ^
                 T3[(t3 >>>  8) & 0xFF] ^
                 T4[(t0       ) & 0xFF] ^ K[keyOffset++];
            a2 = T1[(t2 >>> 24)       ] ^
                 T2[(t3 >>> 16) & 0xFF] ^
                 T3[(t0 >>>  8) & 0xFF] ^
                 T4[(t1       ) & 0xFF] ^ K[keyOffset++];
            t3 = T1[(t3 >>> 24)       ] ^
                 T2[(t0 >>> 16) & 0xFF] ^
                 T3[(t1 >>>  8) & 0xFF] ^
                 T4[(t2       ) & 0xFF] ^ K[keyOffset++];
            t0 = a0; t1 = a1; t2 = a2;
        }

        // last round is special
        int tt = K[keyOffset++];
        out[outOffset++] = (byte)(S[(t0 >>> 24)       ] ^ (tt >>> 24));
        out[outOffset++] = (byte)(S[(t1 >>> 16) & 0xFF] ^ (tt >>> 16));
        out[outOffset++] = (byte)(S[(t2 >>>  8) & 0xFF] ^ (tt >>>  8));
        out[outOffset++] = (byte)(S[(t3       ) & 0xFF] ^ (tt       ));
        tt = K[keyOffset++];
        out[outOffset++] = (byte)(S[(t1 >>> 24)       ] ^ (tt >>> 24));
        out[outOffset++] = (byte)(S[(t2 >>> 16) & 0xFF] ^ (tt >>> 16));
        out[outOffset++] = (byte)(S[(t3 >>>  8) & 0xFF] ^ (tt >>>  8));
        out[outOffset++] = (byte)(S[(t0       ) & 0xFF] ^ (tt       ));
        tt = K[keyOffset++];
        out[outOffset++] = (byte)(S[(t2 >>> 24)       ] ^ (tt >>> 24));
        out[outOffset++] = (byte)(S[(t3 >>> 16) & 0xFF] ^ (tt >>> 16));
        out[outOffset++] = (byte)(S[(t0 >>>  8) & 0xFF] ^ (tt >>>  8));
        out[outOffset++] = (byte)(S[(t1       ) & 0xFF] ^ (tt       ));
        tt = K[keyOffset++];
        out[outOffset++] = (byte)(S[(t3 >>> 24)       ] ^ (tt >>> 24));
        out[outOffset++] = (byte)(S[(t0 >>> 16) & 0xFF] ^ (tt >>> 16));
        out[outOffset++] = (byte)(S[(t1 >>>  8) & 0xFF] ^ (tt >>>  8));
        out[outOffset  ] = (byte)(S[(t2       ) & 0xFF] ^ (tt       ));
    }


    /**
     * Decrypt exactly one block of plaintext.
     */
    private void 
    blockDecrypt(byte[] in, int inOffset, byte[] out, int outOffset) {

        int keyOffset = 8;
        int t0, t1, t2, t3, a0, a1, a2;

        t0 = ((in[inOffset++]       ) << 24 |
              (in[inOffset++] & 0xFF) << 16 |
              (in[inOffset++] & 0xFF) <<  8 |
              (in[inOffset++] & 0xFF)        ) ^ K[4];
        t1 = ((in[inOffset++]       ) << 24 |
              (in[inOffset++] & 0xFF) << 16 |
              (in[inOffset++] & 0xFF) <<  8 |
              (in[inOffset++] & 0xFF)        ) ^ K[5];
        t2 = ((in[inOffset++]       ) << 24 |
              (in[inOffset++] & 0xFF) << 16 |
              (in[inOffset++] & 0xFF) <<  8 |
              (in[inOffset++] & 0xFF)        ) ^ K[6];
        t3 = ((in[inOffset++]       ) << 24 |
              (in[inOffset++] & 0xFF) << 16 |
              (in[inOffset++] & 0xFF) <<  8 |
              (in[inOffset  ] & 0xFF)        ) ^ K[7];

        if(ROUNDS_12) {
            a0 = T5[(t0>>>24)     ] ^ T6[(t3>>>16)&0xFF] ^
                 T7[(t2>>> 8)&0xFF] ^ T8[(t1     )&0xFF] ^ K[keyOffset++];
            a1 = T5[(t1>>>24)     ] ^ T6[(t0>>>16)&0xFF] ^
                 T7[(t3>>> 8)&0xFF] ^ T8[(t2     )&0xFF] ^ K[keyOffset++];
            a2 = T5[(t2>>>24)     ] ^ T6[(t1>>>16)&0xFF] ^
                 T7[(t0>>> 8)&0xFF] ^ T8[(t3     )&0xFF] ^ K[keyOffset++];
            t3 = T5[(t3>>>24)     ] ^ T6[(t2>>>16)&0xFF] ^
                 T7[(t1>>> 8)&0xFF] ^ T8[(t0     )&0xFF] ^ K[keyOffset++];
            t0 = T5[(a0>>>24)     ] ^ T6[(t3>>>16)&0xFF] ^
                 T7[(a2>>> 8)&0xFF] ^ T8[(a1     )&0xFF] ^ K[keyOffset++];
            t1 = T5[(a1>>>24)     ] ^ T6[(a0>>>16)&0xFF] ^
                 T7[(t3>>> 8)&0xFF] ^ T8[(a2     )&0xFF] ^ K[keyOffset++];
            t2 = T5[(a2>>>24)     ] ^ T6[(a1>>>16)&0xFF] ^
                 T7[(a0>>> 8)&0xFF] ^ T8[(t3     )&0xFF] ^ K[keyOffset++];
            t3 = T5[(t3>>>24)     ] ^ T6[(a2>>>16)&0xFF] ^
                 T7[(a1>>> 8)&0xFF] ^ T8[(a0     )&0xFF] ^ K[keyOffset++];

            if(ROUNDS_14) {
                a0 = T5[(t0>>>24)     ] ^ T6[(t3>>>16)&0xFF] ^
                     T7[(t2>>> 8)&0xFF] ^ T8[(t1     )&0xFF] ^ K[keyOffset++];
                a1 = T5[(t1>>>24)     ] ^ T6[(t0>>>16)&0xFF] ^
                     T7[(t3>>> 8)&0xFF] ^ T8[(t2     )&0xFF] ^ K[keyOffset++];
                a2 = T5[(t2>>>24)     ] ^ T6[(t1>>>16)&0xFF] ^
                     T7[(t0>>> 8)&0xFF] ^ T8[(t3     )&0xFF] ^ K[keyOffset++];
                t3 = T5[(t3>>>24)     ] ^ T6[(t2>>>16)&0xFF] ^
                     T7[(t1>>> 8)&0xFF] ^ T8[(t0     )&0xFF] ^ K[keyOffset++];
                t0 = T5[(a0>>>24)     ] ^ T6[(t3>>>16)&0xFF] ^
                     T7[(a2>>> 8)&0xFF] ^ T8[(a1     )&0xFF] ^ K[keyOffset++];
                t1 = T5[(a1>>>24)     ] ^ T6[(a0>>>16)&0xFF] ^
                     T7[(t3>>> 8)&0xFF] ^ T8[(a2     )&0xFF] ^ K[keyOffset++];
                t2 = T5[(a2>>>24)     ] ^ T6[(a1>>>16)&0xFF] ^
                     T7[(a0>>> 8)&0xFF] ^ T8[(t3     )&0xFF] ^ K[keyOffset++];
                t3 = T5[(t3>>>24)     ] ^ T6[(a2>>>16)&0xFF] ^
                     T7[(a1>>> 8)&0xFF] ^ T8[(a0     )&0xFF] ^ K[keyOffset++];
            }
        }
        a0 = T5[(t0>>>24)     ] ^ T6[(t3>>>16)&0xFF] ^
             T7[(t2>>> 8)&0xFF] ^ T8[(t1     )&0xFF] ^ K[keyOffset++];
        a1 = T5[(t1>>>24)     ] ^ T6[(t0>>>16)&0xFF] ^
             T7[(t3>>> 8)&0xFF] ^ T8[(t2     )&0xFF] ^ K[keyOffset++];
        a2 = T5[(t2>>>24)     ] ^ T6[(t1>>>16)&0xFF] ^
             T7[(t0>>> 8)&0xFF] ^ T8[(t3     )&0xFF] ^ K[keyOffset++];
        t3 = T5[(t3>>>24)     ] ^ T6[(t2>>>16)&0xFF] ^
             T7[(t1>>> 8)&0xFF] ^ T8[(t0     )&0xFF] ^ K[keyOffset++];
        t0 = T5[(a0>>>24)     ] ^ T6[(t3>>>16)&0xFF] ^
             T7[(a2>>> 8)&0xFF] ^ T8[(a1     )&0xFF] ^ K[keyOffset++];
        t1 = T5[(a1>>>24)     ] ^ T6[(a0>>>16)&0xFF] ^
             T7[(t3>>> 8)&0xFF] ^ T8[(a2     )&0xFF] ^ K[keyOffset++];
        t2 = T5[(a2>>>24)     ] ^ T6[(a1>>>16)&0xFF] ^
             T7[(a0>>> 8)&0xFF] ^ T8[(t3     )&0xFF] ^ K[keyOffset++];
        t3 = T5[(t3>>>24)     ] ^ T6[(a2>>>16)&0xFF] ^
             T7[(a1>>> 8)&0xFF] ^ T8[(a0     )&0xFF] ^ K[keyOffset++];
        a0 = T5[(t0>>>24)     ] ^ T6[(t3>>>16)&0xFF] ^
             T7[(t2>>> 8)&0xFF] ^ T8[(t1     )&0xFF] ^ K[keyOffset++];
        a1 = T5[(t1>>>24)     ] ^ T6[(t0>>>16)&0xFF] ^
             T7[(t3>>> 8)&0xFF] ^ T8[(t2     )&0xFF] ^ K[keyOffset++];
        a2 = T5[(t2>>>24)     ] ^ T6[(t1>>>16)&0xFF] ^
             T7[(t0>>> 8)&0xFF] ^ T8[(t3     )&0xFF] ^ K[keyOffset++];
        t3 = T5[(t3>>>24)     ] ^ T6[(t2>>>16)&0xFF] ^
             T7[(t1>>> 8)&0xFF] ^ T8[(t0     )&0xFF] ^ K[keyOffset++];
        t0 = T5[(a0>>>24)     ] ^ T6[(t3>>>16)&0xFF] ^
             T7[(a2>>> 8)&0xFF] ^ T8[(a1     )&0xFF] ^ K[keyOffset++];
        t1 = T5[(a1>>>24)     ] ^ T6[(a0>>>16)&0xFF] ^
             T7[(t3>>> 8)&0xFF] ^ T8[(a2     )&0xFF] ^ K[keyOffset++];
        t2 = T5[(a2>>>24)     ] ^ T6[(a1>>>16)&0xFF] ^
             T7[(a0>>> 8)&0xFF] ^ T8[(t3     )&0xFF] ^ K[keyOffset++];
        t3 = T5[(t3>>>24)     ] ^ T6[(a2>>>16)&0xFF] ^
             T7[(a1>>> 8)&0xFF] ^ T8[(a0     )&0xFF] ^ K[keyOffset++];
        a0 = T5[(t0>>>24)     ] ^ T6[(t3>>>16)&0xFF] ^
             T7[(t2>>> 8)&0xFF] ^ T8[(t1     )&0xFF] ^ K[keyOffset++];
        a1 = T5[(t1>>>24)     ] ^ T6[(t0>>>16)&0xFF] ^
             T7[(t3>>> 8)&0xFF] ^ T8[(t2     )&0xFF] ^ K[keyOffset++];
        a2 = T5[(t2>>>24)     ] ^ T6[(t1>>>16)&0xFF] ^
             T7[(t0>>> 8)&0xFF] ^ T8[(t3     )&0xFF] ^ K[keyOffset++];
        t3 = T5[(t3>>>24)     ] ^ T6[(t2>>>16)&0xFF] ^
             T7[(t1>>> 8)&0xFF] ^ T8[(t0     )&0xFF] ^ K[keyOffset++];
        t0 = T5[(a0>>>24)     ] ^ T6[(t3>>>16)&0xFF] ^
             T7[(a2>>> 8)&0xFF] ^ T8[(a1     )&0xFF] ^ K[keyOffset++];
        t1 = T5[(a1>>>24)     ] ^ T6[(a0>>>16)&0xFF] ^
             T7[(t3>>> 8)&0xFF] ^ T8[(a2     )&0xFF] ^ K[keyOffset++];
        t2 = T5[(a2>>>24)     ] ^ T6[(a1>>>16)&0xFF] ^
             T7[(a0>>> 8)&0xFF] ^ T8[(t3     )&0xFF] ^ K[keyOffset++];
        t3 = T5[(t3>>>24)     ] ^ T6[(a2>>>16)&0xFF] ^
             T7[(a1>>> 8)&0xFF] ^ T8[(a0     )&0xFF] ^ K[keyOffset++];
        a0 = T5[(t0>>>24)     ] ^ T6[(t3>>>16)&0xFF] ^
             T7[(t2>>> 8)&0xFF] ^ T8[(t1     )&0xFF] ^ K[keyOffset++];
        a1 = T5[(t1>>>24)     ] ^ T6[(t0>>>16)&0xFF] ^
             T7[(t3>>> 8)&0xFF] ^ T8[(t2     )&0xFF] ^ K[keyOffset++];
        a2 = T5[(t2>>>24)     ] ^ T6[(t1>>>16)&0xFF] ^
             T7[(t0>>> 8)&0xFF] ^ T8[(t3     )&0xFF] ^ K[keyOffset++];
        t3 = T5[(t3>>>24)     ] ^ T6[(t2>>>16)&0xFF] ^
             T7[(t1>>> 8)&0xFF] ^ T8[(t0     )&0xFF] ^ K[keyOffset++];
        t0 = T5[(a0>>>24)     ] ^ T6[(t3>>>16)&0xFF] ^
             T7[(a2>>> 8)&0xFF] ^ T8[(a1     )&0xFF] ^ K[keyOffset++];
        t1 = T5[(a1>>>24)     ] ^ T6[(a0>>>16)&0xFF] ^
             T7[(t3>>> 8)&0xFF] ^ T8[(a2     )&0xFF] ^ K[keyOffset++];
        t2 = T5[(a2>>>24)     ] ^ T6[(a1>>>16)&0xFF] ^
             T7[(a0>>> 8)&0xFF] ^ T8[(t3     )&0xFF] ^ K[keyOffset++];
        t3 = T5[(t3>>>24)     ] ^ T6[(a2>>>16)&0xFF] ^
             T7[(a1>>> 8)&0xFF] ^ T8[(a0     )&0xFF] ^ K[keyOffset++];
        a0 = T5[(t0>>>24)     ] ^ T6[(t3>>>16)&0xFF] ^
             T7[(t2>>> 8)&0xFF] ^ T8[(t1     )&0xFF] ^ K[keyOffset++];
        a1 = T5[(t1>>>24)     ] ^ T6[(t0>>>16)&0xFF] ^
             T7[(t3>>> 8)&0xFF] ^ T8[(t2     )&0xFF] ^ K[keyOffset++];
        a2 = T5[(t2>>>24)     ] ^ T6[(t1>>>16)&0xFF] ^
             T7[(t0>>> 8)&0xFF] ^ T8[(t3     )&0xFF] ^ K[keyOffset++];
        t3 = T5[(t3>>>24)     ] ^ T6[(t2>>>16)&0xFF] ^
             T7[(t1>>> 8)&0xFF] ^ T8[(t0     )&0xFF] ^ K[keyOffset++];

        t1 = K[0];
        out[outOffset++] = (byte)(Si[(a0 >>> 24)       ] ^ (t1 >>> 24));
        out[outOffset++] = (byte)(Si[(t3 >>> 16) & 0xFF] ^ (t1 >>> 16));
        out[outOffset++] = (byte)(Si[(a2 >>>  8) & 0xFF] ^ (t1 >>>  8));
        out[outOffset++] = (byte)(Si[(a1       ) & 0xFF] ^ (t1       ));
        t1 = K[1];
        out[outOffset++] = (byte)(Si[(a1 >>> 24)       ] ^ (t1 >>> 24));
        out[outOffset++] = (byte)(Si[(a0 >>> 16) & 0xFF] ^ (t1 >>> 16));
        out[outOffset++] = (byte)(Si[(t3 >>>  8) & 0xFF] ^ (t1 >>>  8));
        out[outOffset++] = (byte)(Si[(a2       ) & 0xFF] ^ (t1       ));
        t1 = K[2];
        out[outOffset++] = (byte)(Si[(a2 >>> 24)       ] ^ (t1 >>> 24));
        out[outOffset++] = (byte)(Si[(a1 >>> 16) & 0xFF] ^ (t1 >>> 16));
        out[outOffset++] = (byte)(Si[(a0 >>>  8) & 0xFF] ^ (t1 >>>  8));
        out[outOffset++] = (byte)(Si[(t3       ) & 0xFF] ^ (t1       ));
        t1 = K[3];
        out[outOffset++] = (byte)(Si[(t3 >>> 24)       ] ^ (t1 >>> 24));
        out[outOffset++] = (byte)(Si[(a2 >>> 16) & 0xFF] ^ (t1 >>> 16));
        out[outOffset++] = (byte)(Si[(a1 >>>  8) & 0xFF] ^ (t1 >>>  8));
        out[outOffset  ] = (byte)(Si[(a0       ) & 0xFF] ^ (t1       ));
    }


    /**
     * Expand a user-supplied key material into a session key.
     *
     * @param key The 128/192/256-bit user-key to use.
     * @exception InvalidKeyException  If the key is invalid.
     */
    private static int[] makeKey( byte[] keyBytes, boolean decrypt )
    throws InvalidKeyException 
    {
        int ROUNDS          = getRounds(keyBytes.length);
        int ROUND_KEY_COUNT = (ROUNDS + 1) * 4;

        int[] K = new int[ROUND_KEY_COUNT];

        int KC = keyBytes.length / 4; // keylen in 32-bit elements
        int[] tk = new int[KC];

        int i, j;

        // copy user material bytes into temporary ints
        for (i = 0, j = 0; i < KC; )
            tk[i++] = (keyBytes[j++]       ) << 24 |
                      (keyBytes[j++] & 0xFF) << 16 |
                      (keyBytes[j++] & 0xFF) <<  8 |
                      (keyBytes[j++] & 0xFF);

        // copy values into round key arrays
        int t = 0;
        for ( ; t < KC; t++) K[t] = tk[t];

        int tt, rconpointer = 0;
        while (t < ROUND_KEY_COUNT) {
            // extrapolate using phi (the round key evolution function)
            tt = tk[KC - 1];
            tk[0] ^= (S[(tt >>> 16) & 0xFF]       ) << 24 ^
                     (S[(tt >>>  8) & 0xFF] & 0xFF) << 16 ^
                     (S[(tt       ) & 0xFF] & 0xFF) <<  8 ^
                     (S[(tt >>> 24)       ] & 0xFF)       ^
                     (rcon[rconpointer++]         ) << 24;
            if (KC != 8)
                for (i = 1, j = 0; i < KC; ) tk[i++] ^= tk[j++];
            else {
                for (i = 1, j = 0; i < KC / 2; ) tk[i++] ^= tk[j++];
                tt = tk[KC / 2 - 1];
                tk[KC / 2] ^= (S[(tt       ) & 0xFF] & 0xFF)       ^
                              (S[(tt >>>  8) & 0xFF] & 0xFF) <<  8 ^
                              (S[(tt >>> 16) & 0xFF] & 0xFF) << 16 ^
                              (S[(tt >>> 24)       ]       ) << 24;
                for (j = KC / 2, i = j + 1; i < KC; ) tk[i++] ^= tk[j++];
            }

            // copy values into round key arrays
            for (j = 0; (j < KC) && (t < ROUND_KEY_COUNT); j++, t++)
                K[t] = tk[j];
        }

        return K;
    }


    private static void invertKey(int[] K) {

        for(int i=0; i<K.length/2-4;i+=4) {
            int jj0 = K[i+0];
            int jj1 = K[i+1];
            int jj2 = K[i+2];
            int jj3 = K[i+3];
            K[i+0] = K[K.length-i-4+0];
            K[i+1] = K[K.length-i-4+1];
            K[i+2] = K[K.length-i-4+2];
            K[i+3] = K[K.length-i-4+3];
            K[K.length-i-4+0] = jj0;
            K[K.length-i-4+1] = jj1;
            K[K.length-i-4+2] = jj2;
            K[K.length-i-4+3] = jj3;
        }
        
        for (int r = 4; r < K.length-4; r++) {
            int tt = K[r];
            K[r] = U1[(tt >>> 24) & 0xFF] ^
                   U2[(tt >>> 16) & 0xFF] ^
                   U3[(tt >>>  8) & 0xFF] ^
                   U4[ tt         & 0xFF];
        }

        int j0 = K[K.length-4];
        int j1 = K[K.length-3];
        int j2 = K[K.length-2];
        int j3 = K[K.length-1];
        for( int i=K.length-1; i>3; i-- ) K[i] = K[i-4];
        K[0] = j0;
        K[1] = j1;
        K[2] = j2;
        K[3] = j3;
    }


    /**
     * Return The number of rounds for a given Rijndael keysize.
     *
     * @param keySize  The size of the user key material in bytes.
     *                 MUST be one of (16, 24, 32).
     * @return         The number of rounds.
     */
    private static int getRounds( int keySize ) {
        return (keySize >> 2) + 6;
    }
}
