/* $Id: RSAPrivateKey.java,v 1.1 2004/01/19 02:03:51 rgrimm Exp $
 *
 * Copyright (C) 1995-2000 The Cryptix Foundation Limited.
 * All rights reserved.
 *
 * Use, modification, copying and distribution of this software is subject
 * the terms and conditions of the Cryptix General Licence. You should have
 * received a copy of the Cryptix General Licence along with this library;
 * if not, you can download a copy from http://www.cryptix.org/ .
 */
package java.security.interfaces;


import java.math.BigInteger;
import java.security.PrivateKey;


/**
 * @version $Revision: 1.1 $
 * @author  Jeroen C. van Gelderen (gelderen@cryptix.org)
 */
public interface RSAPrivateKey extends PrivateKey
{
    BigInteger getModulus();
    BigInteger getPrivateExponent();
}
