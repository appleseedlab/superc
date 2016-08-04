/* $Id: MessageDigestSpi.java,v 1.1 2004/01/19 02:03:51 rgrimm Exp $
 *
 * Copyright (C) 1995-1999 The Cryptix Foundation Limited.
 * All rights reserved.
 *
 * Use, modification, copying and distribution of this software is subject
 * the terms and conditions of the Cryptix General Licence. You should have
 * received a copy of the Cryptix General Licence along with this library;
 * if not, you can download a copy from http://www.cryptix.org/ .
 */
package java.security;


/**
 * JDK 1.1 compatibility layer: our hashes derive from the MessageDigestSpi
 * class which is not present in JDK 1.1.
 *
 * In JDK 1.2, MessageDigest extends MessageDigestSpi but in JDK 1.1, 
 * MessageDigestSpi extends MessageDigest. This is transparent, except 
 * for the fact that the 1.1 MessageDigest constructor needs a String 
 * representing the algorithm name. 
 *
 * For now we simply set the empty string (""). Should this become a 
 * problem,we can revert to 'compatibility mode' and derive our hashes 
 * from MessageDigest instead of from MessageDigestSpi.
 *
 * @version $Revision: 1.1 $
 * @author  Jeroen C. van Gelderen (gelderen@cryptix.org)
 */
public abstract class MessageDigestSpi
extends MessageDigest
{
    public MessageDigestSpi() 
    {
        super(""); // empty string (see above)
    }
}
