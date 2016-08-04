/* $Id: AsnOutputStream.java,v 1.1 2004/01/19 02:03:49 rgrimm Exp $
 *
 * Copyright (c) 2000 The Cryptix Foundation Limited. All rights reserved.
 */

package cryptix.jce.provider.asn;


import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStream;


/**
 * Class for writing DER-encoded AsnObjects to an OutputStream.
 *
 * @version $Revision: 1.1 $
 * @author  Jeroen C. van Gelderen (gelderen@cryptix.org)
 */
public final class AsnOutputStream {

// Instance variables
//............................................................................

    private final OutputStream os;


// Constructors and java.lang.Object overrides
//............................................................................

    /**
     * Convenience method that constructs an instance on top of an
     * internal ByteArrayOutputStream.
     */
    public AsnOutputStream() {
        this.os = new ByteArrayOutputStream();
    }


    /**
     * Constructs an instance on top of the given OutputStream.
     */
    public AsnOutputStream(OutputStream os) {
        this.os = os;
    }


// Public interface
//............................................................................

    /**
     * Calls flush() then close() on the underlying stream. Exceptions are
     * propagated up.
     *
     * @throws IOException
     *         When underlying stream does so.
     */
    public void close() throws IOException {
        this.os.flush();
        this.os.close();
    }


    /**
     * Calls flush() on the underlying stream. Exceptions are propagated up.
     *
     * @throws IOException
     *         When underlying stream does so.
     */
    public void flush() throws IOException {
        this.os.flush();
    }


    /**
     * Writes a DER-encoded AsnObject to the underlying stream.
     */
    public void write(AsnObject obj) throws IOException {
        obj.encode(this);
    }


    /**
     * Delegates to the underlying ByteArrayOutputStream if any.
     *
     * @throws IllegalStateException
     *         If the underlying stream is not a ByteArrayOutputStream.
     */
    public byte[] toByteArray() {

        if( !(this.os instanceof ByteArrayOutputStream) )
            throw new IllegalStateException(
                "Underlying stream is not instanceof ByteArrayOutputStream.");

        ByteArrayOutputStream baos = (ByteArrayOutputStream)this.os;
        return baos.toByteArray();
    }


// AsnObject.encode(...) callbacks and helpers
//............................................................................

    /**
     * Returns the number of bytes writeLength() will write when called 
     * with the given 'len'. Yes, ASN/DER encoding sucks, don't get me started.
     */
    /*package*/ int getLengthOfLength(int len) {
        if( len <= 127 )
            return 1;
        else if( len <= 0xFF )
            return 2;
        else if( len <= 0xFFFF )
            return 3;
        else if( len <= 0xFFFFFF )
            return 4;
        else
            return 5;
    }


    /*package*/ void writeByte(byte b) throws IOException {
        this.os.write(b&0xFF);
    }


    /*package*/ void writeBytes(byte[] data) throws IOException {
        this.os.write(data);
    }


    /**
     * Write a variable length length (yuk!) as per ASN.1/DER specification.
     */
    /*package*/ void writeLength(int len) throws IOException {

        if(len < 0 ) 
            throw new IllegalArgumentException("len: < 0");

        // shortcut for short form
        if(len <= 127) {
            this.os.write( (char)len );
            return;
        }

        // long form
        int lenOfLenData = getLengthOfLength(len) - 1;
        this.os.write( (byte)(lenOfLenData | 0x80) );
        while( lenOfLenData-- > 0 )
            this.os.write( (byte)(len >>> (lenOfLenData*8)) );
    }


    /*package*/ void writeType(byte type) throws IOException {
        this.os.write(type);
    }
}
