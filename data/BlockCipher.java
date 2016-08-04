/* $Id: BlockCipher.java,v 1.1 2004/01/19 02:03:50 rgrimm Exp $
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


import java.security.AlgorithmParameters;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.Key;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.security.SecureRandom;
import java.security.spec.AlgorithmParameterSpec;
import java.security.spec.InvalidParameterSpecException;
import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.CipherSpi;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.ShortBufferException;



/**
 * <p>
 * A fully constructed Cipher instance looks like this:
 * <pre>
 * +------------------------------------------+
 * | CipherSpi (API methods)                  |
 * |                                          |
 * | +--------------------------------------+ |
 * | | Padding                              | |
 * | |                                      | |
 * | | +----------------------------------+ | |
 * | | | Mode                             | | |
 * | | |                                  | | |
 * | | | +------------------------------+ | | |
 * | | | | CipherSpi                    | | | |
 * | | | | (blockcipher implementation) | | | |
 * | | | |                              | | | |
 * | | | +------------------------------+ | | |
 * | | |                                  | | |
 * | | +----------------------------------+ | |
 * | |                                      | |
 * | +--------------------------------------+ |
 * |                                          |
 * +------------------------------------------+
 * </pre>
 *
 * @author  Jeroen C. van Gelderen (gelderen@cryptix.org)
 * @author  Paul Waserbrot (pw@cryptix.org)
 * @version $Revision: 1.1 $
 */
public abstract class BlockCipher
extends CipherSpi
{

// Variables and constants
//............................................................................

    /** State */
    private int state = STATE_UNINITIALIZED;
    private static final int
        STATE_UNINITIALIZED = 0,
        STATE_DECRYPT       = 1,
        STATE_ENCRYPT       = 2;


    /** Our blocksize */
    private final int BLOCK_SIZE;


    /** Our key. We need it when we reset ourselves. */
    private Key key;


    /** What algorithm is used */
    private String algorithm;


    private Padding padding;


    private Mode mode;


// Constructors and Object() methods
//............................................................................

    /**
     * Construct a new BlockCipher (CipherSpi) with an zero-length name ""
     * and given block size.
     */
    protected BlockCipher(int blockSize)
    {
        this("", blockSize);
    }


    /**
     * Construct a new BlockCipher (CipherSpi) with the given name and
     * block size.
     */
    protected BlockCipher(String algorithm, int blockSize)
    {
        super();

        BLOCK_SIZE     = blockSize;
        this.algorithm = algorithm;

        try
        {
            // set default mode and padding
            this.mode    = Mode.getInstance("ECB", this);
            this.padding = Padding.getInstance("None", this.mode);
        }
        catch(NoSuchPaddingException e)
        {
            throw new InternalError(
                "PANIC: Installation corrupt, default padding not available.");
        }
        catch(NoSuchAlgorithmException E)
        {
            throw new InternalError(
                "PANIC: Installation corrupt, default mode not available.");
        }
    }


    /**
     * Always throws a CloneNotSupportedException (cloning of ciphers is not
     * supported for security reasons).
     */
    public final Object clone() throws CloneNotSupportedException
    {
        throw new CloneNotSupportedException();
    }


// CipherSPI implementation
//............................................................................

    protected final void engineSetMode(String mode)
    throws NoSuchAlgorithmException
    {
        this.mode = Mode.getInstance( mode, this );
    }


    protected final void engineSetPadding(String padding)
    throws NoSuchPaddingException
    {
        this.padding = Padding.getInstance( padding, this.mode );
    }


    protected final int engineGetBlockSize()
    {
        return padding.getBlockSize();
    }


    protected int engineGetKeySize(Key key)
    throws InvalidKeyException
    {
        if( key==null )
            throw new IllegalArgumentException("Key missing");

        if( !key.getFormat().equalsIgnoreCase("RAW") )
            throw new InvalidKeyException("Wrong format: RAW bytes needed");

        byte[] userkey = key.getEncoded();
        if(userkey == null)
            throw new InvalidKeyException("RAW bytes missing");

        return (userkey.length * 8);
    }


    /**
     * Returns the length in bytes that an output buffer would need to be in
     * order to hold the result of the next update or doFinal operation, given
     * the input length <code>inputLen</code> (in bytes).
     *
     * This call takes into account any unprocessed (buffered) data from a
     * previous update call(s), and padding.
     *
     * The actual output length of the next <code>update or doFinal</code> call
     * may be smaller than the length returned by this method. For ciphers with
     * a padding, calling the update method will generally return less data
     * than predicted by this function.
     *
     * @param  inputLen the length in bytes.
     *
     * @return the maximum amount of data that the cipher will return.
     */
    protected final int engineGetOutputSize(int inputLen)
    {
        return padding.getOutputSize(inputLen);
    }


    /**
     * Returns a copy of the initialization vector (IV) used in this cipher.
     *
     * @return A copy of the IV  or null if this cipher does not have an IV or
     *         null if the IV has not yet been set.
     */
    protected final byte[] engineGetIV()
    {
        return padding.getIV();
    }



    protected final AlgorithmParameters engineGetParameters()
    {
        AlgorithmParameterSpec aps = padding.getParamSpec();

        if (aps == null)
            return (AlgorithmParameters) null;

        // Fix the parameters
        AlgorithmParameters ap = null;
        try
        {
           ap = AlgorithmParameters.getInstance(algorithm, "CryptixCrypto");
           ap.init(aps);
        }
        catch(InvalidParameterSpecException e)
        {
               throw new RuntimeException("PANIC: Unreachable code reached.");
        }
        catch(NoSuchAlgorithmException e)
        {
               throw new RuntimeException("PANIC: Unreachable code reached.");
        }
        catch(NoSuchProviderException e)
        {
               throw new RuntimeException("PANIC: Unreachable code reached.");
        }
        return ap;
    }


    /**
     * Initialize this blockcipher for encryption or decryption.
     *
     * If the cipher requires randomness, it is taken from <code>random</code>.
     * Randomness is required for modes that use IVs and might be required for
     * some padding schemes.
     *
     * @param opmode Cipher.ENCRYPT_MODE or Cipher.DECRYPT_MODE.
     * @param key    secret key
     * @param random source of randomness
     */
    protected final void engineInit(int opmode, Key key, SecureRandom random)
    throws InvalidKeyException
    {
        AlgorithmParameterSpec aps = padding.getParamSpec();
        try
        {
               this.engineInit(opmode, key, aps, random);
        }
        catch (InvalidAlgorithmParameterException e)
        {
           throw new InternalError("Unreachable code reached.");
        }
    }


    protected final void
    engineInit(int opmode, Key key, AlgorithmParameterSpec params,
               SecureRandom random)
    throws InvalidKeyException, InvalidAlgorithmParameterException
    {
        boolean decrypt = ( opmode==Cipher.DECRYPT_MODE ); // FIXME?
        padding.init(decrypt, key, params, random);
    }


    protected final void // FIXME: add this to cipher suite?? (pw)
    engineInit(int opmode, Key key, AlgorithmParameters params,
               SecureRandom random)
    throws InvalidKeyException, InvalidAlgorithmParameterException
    {
        throw new RuntimeException("Not supported on this cipher.");
    }


    protected final int
    engineUpdate(byte[] input, int inputOffset, int inputLen,
                 byte[] output, int outputOffset)
    throws ShortBufferException
    {
        if (inputLen == 0)
           return 0;
        return padding.update(input, inputOffset, inputLen,
                              output, outputOffset);
    }



    /** Implemented in terms of engineUpdate(byte[], int, int, byte[], int) */
    protected final byte[]
    engineUpdate(byte[] input, int inputOffset, int inputLen)
    {
        if (inputLen == 0)
           return null;
        try
        {
            byte[] tmp  = new byte[this.engineGetOutputSize(inputLen)];
            int i = this.engineUpdate(input, inputOffset, inputLen, tmp, 0);
            if (i != tmp.length)
            {
               byte [] t = new byte[i];
               System.arraycopy(tmp, 0, t, 0, i);
               tmp = t;
            }
            return tmp;
        }
        catch(ShortBufferException e)
        {
            throw new RuntimeException("PANIC: Unreachable code reached.");
        }
    }


    /**
     * @throws BadPaddingException
     *         (decryption only) if padding is expected but not found at the
     *         end of the data or the padding is found but corrupt
     * @throws IllegalBlockSizeException
     *         if no padding is specified and the input data is not a multiple
     *         of the blocksize.
     * @throws ShortBufferException if the given buffer is to short to hold
     *         the result.
     */
    protected final int
    engineDoFinal(byte[] input, int inputOffset, int inputLen,
                  byte[] output, int outputOffset)
    throws ShortBufferException, IllegalBlockSizeException, BadPaddingException
    {
        return padding.doFinal(input, inputOffset, inputLen,
                               output, outputOffset);
    }


    /**
     * Implemented in terms of engineDoFinal(byte[], int, int, byte[], int)
     *
     * @throws BadPaddingException
     *         (decryption only) if padding is expected but not found at the
     *         end of the data.
     * @throws IllegalBlockSizeException
     *         if no padding is specified and the input data is not a multiple
     *         of the blocksize.
     */
    protected final byte[]
    engineDoFinal(byte[] input, int inputOffset, int inputLen)
    throws IllegalBlockSizeException, BadPaddingException
    {
        try
        {
            byte[] tmp  = new byte[this.engineGetOutputSize(inputLen)];
            int i = this.engineDoFinal(input, inputOffset, inputLen, tmp, 0);
            if (i != tmp.length)
            {
                byte [] t = new byte[i];
                System.arraycopy(tmp, 0, t, 0, i);
                tmp = t;
            }

            return tmp;
        }
        catch(ShortBufferException e)
        {
            throw new RuntimeException("PANIC: Unreachable code reached.");
        }
    }



// Abstract BPI methods
//
// The abstract methods are overridden by the actual cipher implementations
// The core* methods are called from within the Mode* classes
//.............................................................................

    abstract void coreInit(Key key, boolean decrypt)
    throws InvalidKeyException;


    /**
     * Encrypt a given buffer. in and out can point to the same buffer if
     *   (outOffset == inOffset) || (outOffset >= (inOffset+coreGetBlockSize))
     * That is: the buffers may not partially overlap...
     */
    abstract void coreCrypt(byte[] in, int inOffset, byte[] out, int outOffset);


    int coreGetBlockSize()
    {
        return BLOCK_SIZE;
    }
}
