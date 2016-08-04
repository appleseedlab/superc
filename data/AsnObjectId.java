/* $Id: AsnObjectId.java,v 1.1 2004/01/19 02:03:49 rgrimm Exp $
 *
 * Copyright (c) 2000 The Cryptix Foundation Limited. All rights reserved.
 */

package cryptix.jce.provider.asn;


import java.io.IOException;


/**
 * Immutable object representing an ASN.1 OBJECT ID.
 *
 * XXX: Invariant checking needed.
 *
 * @version $Revision: 1.1 $
 * @author  Jeroen C. van Gelderen (gelderen@cryptix.org)
 */
public final class AsnObjectId extends AsnObject
{
    private static final int[]
        _rsaEncryption                   = { 1, 2, 840, 113549, 1, 1, 1 },
        _md4WithRSAEncryption            = { 1, 2, 840, 113549, 1, 1, 3 },
        _md5WithRSAEncryption            = { 1, 2, 840, 113549, 1, 1, 4 },
        _sha1WithRSAEncryption           = { 1, 2, 840, 113549, 1, 1, 5 },
        _rsaOAEPEncryptionSET            = { 1, 2, 840, 113549, 1, 1, 6 },

        // RSADSI digest algorithms
        _id_hmacWithSHA1       = { 1, 2, 840, 113549, 2, 7 },

        // RSADSI encryption algorithms
        _rc2_CBC               = { 1, 2, 840, 113549, 3, 2 },
        _des_EDE3_CBC          = { 1, 2, 840, 113549, 3, 7 },
        _rc5_CBC_PAD           = { 1, 2, 840, 113549, 3, 9 },

        _pbeWithMD2AndDES_CBC  = { 1, 2, 840, 113549, 1, 5,  1 },
        _pbeWithMD5AndDES_CBC  = { 1, 2, 840, 113549, 1, 5,  3 },
        _pbeWithMD2AndRC2_CBC  = { 1, 2, 840, 113549, 1, 5,  4 },
        _pbeWithMD5AndRC2_CBC  = { 1, 2, 840, 113549, 1, 5,  6 },
        _pbeWithSHA1AndDES_CBC = { 1, 2, 840, 113549, 1, 5, 10 },
        _pbeWithSHA1AndRC2_CBC = { 1, 2, 840, 113549, 1, 5, 11 },
        _id_PBKDF2             = { 1, 2, 840, 113549, 1, 5, 12 },
        _id_PBES2              = { 1, 2, 840, 113549, 1, 5, 13 },
        _id_PBMAC1             = { 1, 2, 840, 113549, 1, 5, 14 };

    /**
     * Commonly used OBJECT IDs.
     */
    public static final AsnObjectId
        OID_rsaEncryption        = new AsnObjectId(_rsaEncryption),
        OID_md5WithRSAEncryption = new AsnObjectId(_md5WithRSAEncryption);


    /**
     * Array containing individual OBJECT IDENTIFIER components.
     *
     * <p>Invariant: two or more elements, no element is negative, 2nd element
     * smaller than (40*first).
     */
    private final int[] components;


//............................................................................

    public AsnObjectId(AsnInputStream is) throws IOException {
        super(AsnObject.TAG_OBJECT_ID);

        int len = is.readLength();
        if( len < 2 )
            throw new IOException("Invalid OBJECT_ID.");

        byte[] payload = is.readBytes(len);
        this.components = decodePayload(payload);
    }


    public AsnObjectId(int[] components) {
        super(AsnObject.TAG_OBJECT_ID);

        if( components.length < 2 )
            throw new IllegalArgumentException("Less than 2 components.");

        if( components[0] < 0 || components[0] > 2 )
            throw new IllegalArgumentException("First comp must be 0, 1 or 2.");

        if( components[1] >= (components[0]*40) )
            throw new IllegalArgumentException("Scnd comp >= (First comp*40).");

        for(int i=0; i<components.length; i++)
            if( components[i] < 0 )
                throw new IllegalArgumentException("Negative comp ("+i+").");

        this.components = (int[])components.clone();
    }

//............................................................................

    private static int[] decodePayload(byte[] payload) {
        int compCount = 2;
        for(int i=1; i<payload.length; i++)
            if ((payload[i] & 0x80)==0x00) compCount++;

        int[] comps = new int[compCount];
        comps[0] = payload[0] / 40;
        comps[1] = payload[0] % 40;

        int payloadOff = 1;
        for( int i=2; i<comps.length; i++) {
            int c = 0;
            byte b;
            do {
                b = payload[payloadOff++];
                c = (c << 7) | (b&0x7F);
            } while( (b&0x80) == 0x80 );
            comps[i] = c;
        }
        return comps;
    }


    public String toString(String indent) {
        String res = "OBJECT ID { ";
        for( int i=0; i<this.components.length; i++ )
            res = res + this.components[i] + " ";
        return indent + res + "}";
    }


    public static void main(String[] argv) throws Exception {

        int[] comps = { 1, 2, 840 };
        AsnObjectId o = new AsnObjectId(comps);

        AsnOutputStream aos = new AsnOutputStream();
        aos.write(o);
        byte[] enc = aos.toByteArray();

        AsnInputStream ais = new AsnInputStream(enc);
        AsnObject oo = ais.read();
        System.out.println(oo);
    }




    /** Write out payload. */
    protected void encodePayload(AsnOutputStream os) throws IOException {

        os.writeByte( (byte)(40*components[0] + components[1]) );
        for(int i=2; i<components.length; i++)
            this.writeComponent( os, components[i] );
    }


    /** 
     * Returns no. of bytes encodePayload will write out when called on
     * the given AsnOutputStream. Payload length does NOT include length.
     */
    protected int getEncodedLengthOfPayload(AsnOutputStream os) {

        int len = 1; // first two are special
        for(int i=2; i<this.components.length; i++)
            len += getEncodedComponentLen( this.components[i] );

        return len;
    }


    private void writeComponent(AsnOutputStream os, int c) throws IOException {
        int len = getEncodedComponentLen(c);
        for(int i=len-1; i>0; i--)
            os.writeByte( (byte)((c>>>i*7) | 0x80) );

        os.writeByte( (byte)(c&0x7F) );
    }


    private static int getEncodedComponentLen(int c) {
        if( c < 0 )
            throw new IllegalArgumentException("c: < 0");
        else if( c <= 0x7F )
            return 1;
        else if( c <= 0x3FFF )
            return 2;
        else if( c <= 0x1FFFFF )
            return 3;
        else if( c <= 0xFFFFFFF )
            return 4;
        else
            return 5;
    }
}
