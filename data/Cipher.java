/* $Id: Cipher.java,v 1.1 2004/01/21 15:26:53 rgrimm Exp $
 *
 * Copyright (C) 1995-2000 The Cryptix Foundation Limited.
 * All rights reserved.
 *
 * Use, modification, copying and distribution of this software is subject
 * the terms and conditions of the Cryptix General Licence. You should have
 * received a copy of the Cryptix General Licence along with this library;
 * if not, you can download a copy from http://www.cryptix.org/ .
 */
package javax.crypto;


import java.security.AlgorithmParameters;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.Key;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.security.Provider;
import java.security.SecureRandom;
import java.security.Security;
import java.security.spec.AlgorithmParameterSpec;
import java.security.PublicKey;
import java.security.cert.Certificate;
import java.security.cert.X509Certificate;
import java.util.Iterator;

// XXX TODO: implement state


/**
 * @version $Revision: 1.1 $
 * @author  Jeroen C. van Gelderen (gelderen@cryptix.org)
 * @author  Paul Waserbrot (pw@cryptix.org)
 */
public class Cipher
{

// Static variables and constants
//...........................................................................

    /** Constants used for the init() methods */
    public static final int
        ENCRYPT_MODE = 1,
        DECRYPT_MODE = 2,
        PRIVATE_KEY  = 3,
        PUBLIC_KEY   = 4,
        SECRET_KEY   = 5,
        UNWRAP_MODE  = 6,
        WRAP_MODE    = 7;


// Instance variables
//...........................................................................

    /** The Cipher implementation we wrap */
    private final CipherSpi           spi;

    /** Our provider */
    private final Provider            provider;

    /** Our name */
    private final String              transformation;

    /** Our mechanism */
    // FIXME: I need to check something, to see if mechanism= null or not.
    // Until then, make it null... (pw)
    private final ExemptionMechanism  mechanism = null;

    private boolean isInitialized = false;

// Constructor
//...........................................................................

    /**
     * Constructs a Cipher wrapping the given cipherSpi.
     * <p>
     * This method should be private, but is not for backward compatibility.
     */
    protected
    Cipher(CipherSpi cipherSpi, Provider provider, String transformation)
    {
        this.spi            = cipherSpi;
        this.provider       = provider;
        this.transformation = transformation;
    }


    public String toString()
    {
        return "Cipher object: " + this.transformation;
        // SHA1withRSA<initialized for verifying>
    }


    // FIXME:
    // 1. Clean up and
    // 2. check for compatibility.
    // 3. Fix ignored exceptions
    // 4. Possibly merge with Support.java
    private static Object[]
    getCipherImplementation(String transformation, Provider p)
        throws NoSuchPaddingException
    {
        //
        // Extract name components from 'transformation'
        //
        String part_alg;
        String part_mode = "//"; // Default is invalid name
        String part_pad  = "//";

        int index_1 = transformation.indexOf('/');
        int index_2 = transformation.indexOf('/', index_1+1);

        if(index_1==-1)
            part_alg  = transformation;
        else if(index_2==-1)
            return null;
        else
        {
            part_alg  = transformation.substring(0, index_1);
            part_mode = transformation.substring(index_1+1, index_2);
            part_pad  = transformation.substring(index_2+1);
        }


        //
        // Try and get a class instance
        //
        try
        {
            CipherSpi spi;
            String    class_name;
            Object[]  res = new Object[2];

            res[1] = p;

            class_name = Support.getClassName("Cipher", transformation, p);
            if(class_name!=null)
            {
                res[0] = Class.forName(class_name).newInstance();
                return res;
            }
            class_name = Support.getClassName("Cipher",
                                              part_alg + "/" + part_mode, p);
            if(class_name!=null)
            {
                spi = (CipherSpi)Class.forName(class_name).newInstance();
                spi.engineSetPadding(part_pad);
                res[0] = spi;
                return res;
            }
            class_name = Support.getClassName("Cipher",
                                              part_alg + "//" + part_alg, p);
            if(class_name!=null)
            {
                spi = (CipherSpi)Class.forName(class_name).newInstance();
                spi.engineSetMode(part_mode);
                res[0] = spi;
                return res;
            }
            class_name = Support.getClassName("Cipher", part_alg, p);
            if(class_name!=null)
            {
                spi = (CipherSpi)Class.forName(class_name).newInstance();
                spi.engineSetMode(part_mode);
                spi.engineSetPadding(part_pad);
                res[0] = spi;
                return res;
            }
        }
        catch(NoSuchAlgorithmException e)
        {
        }
        catch(LinkageError e)
        {
            // FIXME: Throw a RuntimeException(?) with a sensible message????
        }
        catch(ClassNotFoundException e)
        {
            // FIXME: Throw a RuntimeException(?) with a sensible message????
        }
        catch(InstantiationException e)
        {
            // FIXME: Throw a RuntimeException(?) with a sensible message????
        }
        catch(IllegalAccessException e)
        {
            // FIXME: Throw a RuntimeException(?) with a sensible message????
        }
        return null;
    }


    /**
     * Creates a Cipher that implements the given transformation.
     * <p>
     * This call will search all installed Providers in preference order and
     * returns the first matching transformation.
     * <p>
     * Transformation is specified as the triple "Algorithm/Mode/Padding".
     * We currently do not support transformation of type "Algorithm" with
     * defaults for mode and padding.
     *
     * @param   transformation
     *          The requested transformation.
     * @returns A Cipher implementing the requested transformation.
     * @throws  NoSuchAlgorithmException
     *          If the given Algorithm/Mode/<any> combination cannot be found.
     * @throws  NoSuchPaddingException
     *          If the given <any>/<any>/Padding cannot be found.
     */
    public static Cipher getInstance(String transformation)
    throws NoSuchAlgorithmException, NoSuchPaddingException
    {
        Provider[] providers = Security.getProviders();
        if( (providers==null) || (providers.length==0) )
            throw new NoSuchAlgorithmException("No providers installed");

        for(int i=0; i<providers.length; i++)
        {
            Object[] res = getCipherImplementation(transformation,
                                                   providers[i]);
            if(res != null)
                return new Cipher((CipherSpi)res[0],
                                  (Provider)res[1],
                                  transformation);
        }
        throw new NoSuchAlgorithmException(
            "Algorithm not found. [Cipher." + transformation + "]");
    }


    /**
     * Creates a Cipher that implements the given transformation.
     * <p>
     * This call searches the given provider only.
     * <p>
     * Transformation is specified as the triple "Algorithm/Mode/Padding".
     * We currently do not support transformation of type "Algorithm" with
     * defaults for mode and padding.
     *
     * @param   transformation
     *          The requested transformation.
     * @returns A Cipher implementing the requested transformation.
     * @throws  NoSuchAlgorithmException
     *          If the given Algorithm/Mode/<any> combination cannot be found.
     * @throws  NoSuchPaddingException
     *          If the given <any>/<any>/Padding cannot be found.
     * @throws  NoSuchProviderException
     *          If the given provider is not installed.
     */
    public static Cipher getInstance(String transformation, String provider)
    throws NoSuchAlgorithmException, NoSuchProviderException,
           NoSuchPaddingException
    {
        Provider p = Security.getProvider(provider);
        if(p==null)
            throw new NoSuchProviderException(
                "Provider not found. [" + provider + "]");

        Object[] res = getCipherImplementation(transformation, p);
        if(res != null)
            return new Cipher((CipherSpi)res[0],
                              (Provider)res[1],
                              transformation);

        throw new NoSuchAlgorithmException(
            "Algorithm not found. [Cipher." + transformation + "]");
    }


    /**
     * Returns this Cipher's Provider.
     */
    public final Provider getProvider()
    {
        return this.provider;
    }


    /**
     * Returns the name of the transformation implemented by this Cipher.
     */
    public final String getAlgorithm()
    {
        return this.transformation;
    }


    /**
     * Returns the block size if this Cipher, or 0 if the underlying
     * Cipher doesn't (yet) have a block size.
     */
    public final int getBlockSize()
    {
        return this.spi.engineGetBlockSize();
    }


    /**
     * Returns the maximum number of bytes that the next update() or
     * doFinal() operation can return, given the length of the input.
     * <p>
     * This basically returns the sum of buffered data, padding, and input.
     */
    public final int getOutputSize(int inputLen)
    throws IllegalStateException
    {
        if(inputLen < 0)
            throw new IllegalArgumentException("Input size must be >= 0");

        return this.spi.engineGetOutputSize(inputLen);
    }


    /**
     * Returns the IV associated with this Cipher, or null if this Cipher
     * doesn't (yet) have one.
     * <p>
     * This is a rather brain damaged convenience method, because there is
     * no corresponding setIV method (you need to use the ParameterSpec crap
     * instead).
     */
    public final byte[] getIV()
    {
        return this.spi.engineGetIV();
    }

    public final ExemptionMechanism getExemptionMechanism() 
    {
        return this.mechanism;
    }


    public final AlgorithmParameters getParameters()
    {
        return this.spi.engineGetParameters();
    }


    public final void init(int opmode, Key key)
    throws InvalidKeyException
    {
        this.spi.engineInit(opmode, key, new SecureRandom());
        isInitialized = true;
    }


    public final void init(int opmode, Key key, SecureRandom random)
    throws InvalidKeyException
    {
        this.spi.engineInit(opmode, key, random);
        isInitialized = true;
    }


    public final void init(int opmode, Key key, AlgorithmParameterSpec params)
    throws InvalidKeyException, InvalidAlgorithmParameterException
    {
        this.spi.engineInit(opmode, key, params, new SecureRandom());
        isInitialized = true;
    }


    public final void
    init(int opmode, Key key, AlgorithmParameterSpec params,
         SecureRandom random)
    throws InvalidKeyException, InvalidAlgorithmParameterException
    {
        this.spi.engineInit(opmode, key, params, random);
        isInitialized = true;
    }


    public final void init(int opmode, Key key, AlgorithmParameters params)
    throws InvalidKeyException, InvalidAlgorithmParameterException
    {
        this.spi.engineInit(opmode, key, params, new SecureRandom());
        isInitialized = true;
    }


    public final void init(int opmode, Key key, AlgorithmParameters params, 
                           SecureRandom random)
    throws InvalidKeyException, InvalidAlgorithmParameterException
    {
        this.spi.engineInit(opmode, key, params, random);
        isInitialized = true;
    }


    public final byte[] update(byte[] input)
    throws IllegalStateException
    {
        if(input == null)
            throw new IllegalArgumentException();

        return this.spi.engineUpdate(input, 0, input.length);
    }


    public final byte[] update(byte[] input, int inputOffset, int inputLen)
    throws IllegalStateException
    {
        return this.spi.engineUpdate(input, inputOffset, inputLen);
    }


    public final int
    update(byte[] input, int inputOffset, int inputLen, byte[] output)
    throws IllegalStateException, ShortBufferException
    {
        return this.spi.engineUpdate(input, inputOffset, inputLen, output, 0);
    }


    public final int
    update(byte[] input, int inputOffset, int inputLen,
           byte[] output, int outputOffset)
    throws IllegalStateException, ShortBufferException
    {
        return this.spi.engineUpdate(input, inputOffset, inputLen,
                                     output, outputOffset);
    }


    public final byte[] doFinal()
    throws IllegalStateException, IllegalBlockSizeException, BadPaddingException
    {
        return this.spi.engineDoFinal(null, 0, 0);
    }


    public final int
    doFinal(byte[] output, int outputOffset)
    throws IllegalStateException, IllegalBlockSizeException,
           ShortBufferException, BadPaddingException
    {
        return this.spi.engineDoFinal(null, 0, 0, output, outputOffset);
    }


    public final byte[]
    doFinal(byte[] input)
    throws IllegalStateException, IllegalBlockSizeException, BadPaddingException
    {
        return this.spi.engineDoFinal(input, 0, input.length);
    }


    public final byte[]
    doFinal(byte[] input, int inputOffset, int inputLen)
    throws IllegalStateException, IllegalBlockSizeException, BadPaddingException
    {
        return this.spi.engineDoFinal(input, inputOffset, inputLen);
    }


    public final int
    doFinal(byte[] input, int inputOffset, int inputLen, byte[] output)
    throws IllegalStateException, ShortBufferException,
           IllegalBlockSizeException, BadPaddingException
    {
        return this.spi.engineDoFinal(input, inputOffset, inputLen, output, 0);
    }


    public final int
    doFinal(byte[] input, int inputOffset, int inputLen,
            byte[] output, int outputOffset)
    throws IllegalStateException, ShortBufferException,
           IllegalBlockSizeException, BadPaddingException
    {
        return this.spi.engineDoFinal(input, inputOffset, inputLen, output, outputOffset);
    }

    public final void 
    init(int opmode, Certificate certificate)
    throws InvalidKeyException 
    {
        this.init(opmode, certificate, new SecureRandom());
        isInitialized = true;
    }

    public final void 
    init(int opmode, Certificate certificate, SecureRandom random)
    throws InvalidKeyException
    {
        /*
         * Snipped from the JCE API, will be removed when finished.
         * 
         * Initializes this cipher with the public key from the given 
         * certificate and a source of randomness. 
         *
         * The cipher is initialized for one of the following four 
         * operations: encryption, decryption, key wrapping or key
         * unwrapping, depending on the value of opmode. 
         *
         * If the certificate is of type X.509 and has a key usage 
         * extension field marked as critical, and the value of the key 
         * usage extension field implies that the public key in the 
         * certificate and its corresponding private key are not supposed 
         * to be used for the operation represented by the value of opmode, 
         * an InvalidKeyException is thrown. 
         *
         * If this cipher requires any algorithm parameters that cannot be 
         * derived from the public key in the given certificate, the 
         * underlying cipher implementation is supposed to generate the 
         * required parameters itself (using provider-specific default or 
         * random values) if it is being initialized for encryption or key 
         * wrapping, and raise an InvalidKeyException if it is being 
         * initialized for decryption or key unwrapping. The generated
         * parameters can be retrieved using engineGetParameters or 
         * engineGetIV (if the parameter is an IV). 
         *
         * If this cipher (including its underlying feedback or padding 
         * scheme) requires any random bytes (e.g., for parameter 
         * generation), it will get them from random. 
         *
         * Note that when a Cipher object is initialized, it loses all 
         * previously-acquired state. In other words, initializing a Cipher 
         * is equivalent to creating a new instance of that Cipher and 
         * initializing it.
         * Parameters:
         * opmode - the operation mode of this cipher (this is one of the 
         * following: ENCRYPT_MODE, DECRYPT_MODE, WRAP_MODE or UNWRAP_MODE)
         * certificate - the certificate
         * random - the source of randomness
         * Throws:
         * java.security.InvalidKeyException - if the public key in the 
         * given certificate is inappropriate for initializing this cipher, 
         * or this cipher is being initialized for decryption or unwrapping 
         * keys and requires algorithm parameters that cannot be determined 
         * from the public key in the given certificate, or the keysize of 
         * the public key in the given certificate has a keysize that exceeds 
         * the maximum allowable keysize (as determined by the configured 
         * jurisdiction policy files).
         */
        if (certificate instanceof X509Certificate) {
            // Get the extensions
            Iterator it = ((X509Certificate)certificate).getCriticalExtensionOIDs().iterator();
            // Check to see if key usage is marked critical
            // go through all oids and check for OID = 2.5.29.15

            // Check whether the opmode corresponds to the key usage
            boolean [] boa = ((X509Certificate)certificate).getKeyUsage();
            /* The ASN.1 of KeyUsage is
             * KeyUsage ::= BIT STRING {
             *   digitalSignature        (0),
             *   nonRepudiation          (1),
             *   keyEncipherment         (2),
             *   dataEncipherment        (3),
             *   keyAgreement            (4),
             *   keyCertSign             (5),
             *   cRLSign                 (6),
             *   encipherOnly            (7),
             *   decipherOnly            (8) }
             */
        }
        PublicKey pk = certificate.getPublicKey();
        this.spi.engineInit(opmode, pk, random);
        isInitialized = true;
    }

    public final byte[] 
    wrap(java.security.Key key)
    throws IllegalStateException, IllegalBlockSizeException, 
    InvalidKeyException 
    {
        if (!isInitialized)
            throw new IllegalStateException("Cipher not initialized!");

        return this.spi.engineWrap(key);
    }

    public final Key 
    unwrap(byte[] wrappedKey, String wrappedKeyAlgorithm, int wrappedKeyType)
    throws IllegalStateException, InvalidKeyException,
    NoSuchAlgorithmException
    {
        if (!isInitialized)
            throw new IllegalStateException("Cipher not initialized!");

        return this.spi.engineUnwrap(wrappedKey, wrappedKeyAlgorithm, 
                                     wrappedKeyType);
    }
}
