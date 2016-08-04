/* $Id: AsnSequence.java,v 1.1 2004/01/19 02:03:49 rgrimm Exp $
 *
 * Copyright (c) 2000 The Cryptix Foundation Limited. All rights reserved.
 */

package cryptix.jce.provider.asn;


import java.io.IOException;
import java.util.Vector;


/**
 * Immutable object representing an ASN.1 SEQUENCE.
 *
 * @version $Revision: 1.1 $
 * @author  Jeroen C. van Gelderen (gelderen@cryptix.org)
 */
public final class AsnSequence extends AsnObject
{
    private final AsnObject[] vals;


    /*package*/ AsnSequence(AsnInputStream is) throws IOException {
        super(AsnObject.TAG_SEQUENCE);

        int len = is.readLength();
        AsnInputStream sub_is = is.getSubStream( len );
        Vector vec = new Vector(3);
        while( sub_is.available() > 0 )
            vec.addElement( sub_is.read() );
        vec.copyInto(this.vals = new AsnObject[ vec.size() ]);
    }


    public AsnSequence(AsnObject[] vals) {
        super(AsnObject.TAG_SEQUENCE);

        this.vals = (AsnObject[])vals.clone();
    }


    public AsnSequence(AsnObject a, AsnObject b) {
        super(AsnObject.TAG_SEQUENCE);
        AsnObject[] objs = new AsnObject[2];
        objs[0] = a;
        objs[1] = b;
        this.vals = objs;
    }


    public String toString(String indent) {
        String s = indent + "SEQUENCE (" + this.vals.length +" elements):";
        for(int i=0; i<this.vals.length; i++)
            s += "\n" + this.vals[i].toString(indent + "    ");

        return s;
    }


    public AsnObject get(int index) {
        return this.vals[index];
    }


    public int size() {
        return this.vals.length;
    }


    /** Write out payload. */
    protected void encodePayload(AsnOutputStream os) throws IOException {
        for(int i=0; i<this.vals.length; i++)
            os.write(this.vals[i]);
    }


    protected int getEncodedLengthOfPayload(AsnOutputStream os) {
        int len = 0;
        for(int i=0; i<this.vals.length; i++)
            len += this.vals[i].getEncodedLength(os);

        return len;
    }
}
