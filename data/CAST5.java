/* $Id: CAST5.java,v 1.1 2004/01/19 02:03:50 rgrimm Exp $
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
 * CAST5 (a.k.a. CAST-128) in Java, as per RFC 2144.
 * <p>
 * The author, Carlisle Adams (the CA in CAST, ST standing for Stafford
 * Tavares) describes CAST5 as:
 * <p>
 * <blockquote>
 *    "...a DES-like Substitution-Permutation Network (SPN) cryptosystem
 *    which appears to have good resistance to differential cryptanalysis,
 *    linear cryptanalysis, and related-key cryptanalysis. This cipher
 *    also possesses a number of other desirable cryptographic properties,
 *    including avalanche, Strict Avalanche Criterion (SAC), Bit
 *    Independence Criterion (BIC), no complementation property, and an
 *    absence of weak and semi-weak keys."
 * </blockquote>
 * <p>
 * CAST5 is a symmetric block cipher with a block-size of 8 bytes and
 * a variable key-size of up to 128 bits. Its authors and their employer
 * (Entrust Technologies, a Nortel majority-owned company) made it available
 * worldwide on a royalty-free basis for commercial and non-commercial uses.
 * <p>
 * The CAST5 encryption algorithm has been designed to allow a key size
 * that can vary from 40 bits to 128 bits, in 8-bit increments (that is, the
 * allowable key sizes are 40, 48, 56, 64, ..., 112, 120, and 128 bits. For
 * variable keysize operation, the specification is as follows:
 * <ol>
 *   <li> For key sizes up to and including 80 bits (i.e., 40, 48, 56, 64, 72,
 *        and 80 bits), the algorithm is exactly as specified but uses 12
 *        rounds instead of 16;
 *   <li> For key sizes greater than 80 bits, the algorithm uses the full 16
 *        rounds;
 *   <li> For key sizes less than 128 bits, the key is padded with zero bytes
 *        (in the rightmost, or least significant, positions) out to 128 bits
 *        (since the CAST5 key schedule assumes an input key of 128 bits).
 * </ol>
 * <p>
 * References:<br>
 * <ul>
 * <li>Carlisle Adams,
 *     <a href="http://www.ietf.org/rfc/html/rfc2144.html">
 *     RFC 2144</a>, May 1997.
 * </ul>
 * 
 * @version $Revision: 1.1 $
 * @author  Jeroen C. van Gelderen (gelderen@cryptix.org)
 * @author  Raif S. Naffah         (raif@cryptix.org)
 * @since   Cryptix 2.2.2
 */
public final class CAST5
extends BlockCipher
{

// Static variables and constants
//............................................................................

    /** Various constants */
    private static final int
        MIN_NOF_ROUNDS = 12,
        MAX_NOF_ROUNDS = 16,
        BLOCK_SIZE     =  8,
        DEFAULT_NOF_ROUNDS = MAX_NOF_ROUNDS;


    /** 
     * Compressed S-boxes. 
     * Compiled size from 33K to 21K. See Blowfish.java for more info. 
     */
    private static String 
    sS0="0\u00FB@\u00D4\u009F\u00A0\u00FF\u000Bk\u00EC\u00CD/?%\u008C"     +
        "z\u001E!?/\u009C\u0000M\u00D3`\u0003\u00E5@\u00CF\u009F\u00C9"    +
        "I\u00BF\u00D4\u00AF'\u0088\u00BB\u00BD\u00B5\u00E2\u0003@\u0090"  +
        "\u0098\u00D0\u0096unc\u00A0\u00E0\u0015\u00C3a\u00D2\u00C2\u00E7" +
        "f\u001D\"\u00D4\u00FF\u008E(h;o\u00C0\u007F\u00D0Y\u00FF#y\u00C8" +
        "w_P\u00E2C\u00C3@\u00D3\u00DF/\u0086V\u0088|\u00A4\u001A\u00A2"   +
        "\u00D2\u00BD-\u00A1\u00C9\u00E0\u00D64lH\u0019a\u00B7m\u0087"     +
        "\"T\u000F/*\u00BE2\u00E1\u00AAT\u0016k\"V\u008E:\u00A2\u00D3"     +
        "A\u00D0f\u00DB@\u00C8\u00A7\u00849/\u0000M\u00FF/-\u00B9\u00D2"   +
        "\u00DE\u0097\u0094?\u00ACJ\u0097\u00C1\u00D8RvD\u00B7\u00B5\u00F4"+
        "7\u00A7\u00B8,\u00BA\u00EF\u00D7Q\u00D1Yo\u00F7\u00F0\u00EDZ"     +
        "\tz\u001F\u0082{h\u00D0\u0090\u00EC\u00F5.\"\u00B0\u00C0T\u00BC"  +
        "\u008EY5Km/\u007FP\u00BBd\u00A2\u00D2fI\u0010\u00BE\u00E5\u0081"  +
        "-\u00B73\"\u0090\u00E9;\u0015\u009F\u00B4\u008E\u00E4\u0011K"     +
        "\u00FF4]\u00FDE\u00C2@\u00AD1\u0097?\u00C4\u00F6\u00D0.U\u00FC"   +
        "\u0081e\u00D5\u00B1\u00CA\u00AD\u00A1\u00AC-\u00AE\u00A2\u00D4"   +
        "\u00B7m\u00C1\u009B\u000CP\u0088\"@\u00F2\u000CnO8\u00A4\u00E4"   +
        "\u00BF\u00D7O[\u00A2rVL\u001D/\u00C5\u009CS\u0019\u00B9I\u00E3"   +
        "T\u00B0Fi\u00FE\u00B1\u00B6\u00AB\u008A\u00C7\u0013X\u00DDc\u0085"+
        "\u00C5E\u0011\u000F\u0093]WS\u008A\u00D5j9\u0004\u0093\u00E6"     +
        "=7\u00E0*T\u00F6\u00B3:x}_bv\u00A0\u00B5\u0019\u00A6\u00FC\u00DF" +
        "zB j)\u00F9\u00D4\u00D5\u00F6\u001B\u0018\u0091\u00BBr'^\u00AA"   +
        "P\u0081g8\u0090\u0010\u0091\u00C6\u00B5\u0005\u00EB\u0084\u00C7"  +
        "\u00CB\u008C*\u00D7Z\u000F\u0087J\u0014'\u00A2\u00D1\u0093k*"     +
        "\u00D2\u0086\u00AF\u00AAV\u00D2\u0091\u00D7\u0089C`B\\u\r\u0093"  +
        "\u00B3\u009E&\u0018q\u0084\u00C9l\u0000\u00B3-s\u00E2\u00BB\u0014"+
        "\u00A0\u00BE\u00BC<Tb7ydE\u009E\u00AB?2\u008B\u0082w\u0018\u00CF" +
        "\u0082Y\u00A2\u00CE\u00A6\u0004\u00EE\u0000.\u0089\u00FEx\u00E6"  +
        "?\u00AB\tP2_\u00F6\u00C2\u00818?\u0005ic\u00C5\u00C8v\u00CBZ"     +
        "\u00D6\u00D4\u0099t\u00C9\u00CA\u0018\r\u00CF8\u0007\u0082\u00D5" +
        "\u00C7\u00FA\\\u00F6\u008A\u00C3\u0015\u00115\u00E7\u009E\u0013"  +
        "G\u00DA\u0091\u00D0\u00F4\u000F\u0090\u0086\u00A7\u00E2A\u009E"   +
        "16bA\u0005\u001E\u00F4\u0095\u00AAW;\u0004J\u0080]\u008DT\u0083"  +
        "\u0000\u00D0\u00002*<\u00BFd\u00CD\u00DF\u00BAW\u00A6\u008Eu"     +
        "\u00C67+P\u00AF\u00D3A\u00A7\u00C12u\u0091Z\u000B\u00F5kT\u00BF"  +
        "\u00AB+\u000B\u0014&\u00ABL\u00C9\u00D7D\u009C\u00CD\u0082\u00F7" +
        "\u00FB\u00F2e\u00AB\u0085\u00C5\u00F3\u001BU\u00DB\u0094\u00AA"   +
        "\u00D4\u00E3$\u00CF\u00A4\u00BD?-\u00EA\u00A3\u00E2\u009E M\u0002"+
        "\u00C8\u00BD%\u00AC\u00EA\u00DFU\u00B3\u00D5\u00BD\u009E\u0098"   +
        "\u00E3\u00121\u00B2*\u00D5\u00ADl\u0095C)\u00DE\u00AD\u00BEE"     +
        "(\u00D8q\u000Fi\u00AAQ\u00C9\u000F\u00AAxk\u00F6\"Q?\u001E\u00AA" +
        "Q\u00A7\u009B*\u00D3D\u00CC{ZA\u00F0\u00D3|\u00FB\u00AD\u001B"    +
        "\u0006\u0095\u0005A\u00EC\u00E4\u0091\u00B4\u00C32\u00E6\u0003"   +
        "\"h\u00D4\u00C9`\n\u00CC\u00CE8~m\u00BFk\u00B1ljp\u00FBx\r\u0003" +
        "\u00D9\u00C9\u00D4\u00DF9\u00DE\u00E0\u0010c\u00DAG6\u00F4dZ"     +
        "\u00D3(\u00D8\u00B3G\u00CC\u0096u\u00BB\u000F\u00C3\u0098Q\u001B" +
        "\u00FBO\u00FB\u00CC5\u00B5\u008B\u00CFj\u00E1\u001F\n\u00BC\u00BF"+
        "\u00C5\u00FEJ\u00A7\n\u00EC\u0010\u00AC9W\n?\u0004D/a\u0088\u00B1"+
        "S\u00E09z.W'\u00CBy\u009C\u00EBA\u008F\u001C\u00AC\u00D6\u008D"   +
        "*\u00D3|\u0096\u0001u\u00CB\u009D\u00C6\u009D\u00FF\t\u00C7["     +
        "e\u00F0\u00D9\u00DB@\u00D8\u00EC\u000EwyGD\u00EA\u00D4\u00B1"     +
        "\u001C2t\u00DD$\u00CB\u009E~\u001CT\u00BD\u00F0\u0011D\u00F9"     +
        "\u00D2$\u000E\u00B1\u0096u\u00B3\u00FD\u00A3\u00AC7U\u00D4|'"     +
        "\u00AFQ\u00C8_MV\u0090u\u0096\u00A5\u00BB\u0015\u00E6X\u0003"     +
        "\u0004\u00F0\u00CA\u0004,\u00F1\u0001\u001A7\u00EA\u008D\u00BF"   +
        "\u00AA\u00DB5\u00BA>J5&\u00FF\u00A0\u00C3{M\t\u00BC0n\u00D9\u0098"+
        "\u00A5&fVH\u00F7%\u00FF^V\u009D\u000C\u00EDc\u00D0|c\u00B2\u00CF" +
        "p\u000BE\u00E1\u00D5\u00EAP\u00F1\u0085\u00A9(r\u00AF\u001F\u00BD"+
        "\u00A7\u00D4#Hp\u00A7\u0087\u000B\u00F3-;MyB\u00E0A\u0098\u000C"  +
        "\u00D0\u00ED\u00E7&G\r\u00B8\u00F8\u0081\u0081LGMj\u00D7|\u000C"  +
        "^\\\u00D1#\u0019Y8\u001Br\u0098\u00F5\u00D2\u00F4\u00DB\u00AB"    +
        "\u0083\u0086Sn/\u001E#\u0083q\u009C\u009E\u00BD\u0091\u00E0F"     +
        "\u009AVEn\u00DC9 \u000C \u00C8\u00C5q\u0096+\u00DA\u001C\u00E1"   +
        "\u00E6\u0096\u00FF\u00B1A\u00AB\u0008|\u00CA\u0089\u00B9\u001A"   +
        "i\u00E7\u0083\u0002\u00CCHC\u00A2\u00F7\u00C5yB\u009E\u00F4}"     +
        "B{\u0016\u009CZ\u00C9\u00F0I\u00DD\u008F\u000F\u0000\\\u0081"     +
        "e\u00BF",
    sS1="0\u00FB@\u00D4\u009F\u00A0\u00FF\u000Bk\u00EC\u00CD/?%\u008C"     +
        "z\u001E!?/\u009C\u0000M\u00D3`\u0003\u00E5@\u00CF\u009F\u00C9"    +
        "I\u00BF\u00D4\u00AF'\u0088\u00BB\u00BD\u00B5\u00E2\u0003@\u0090"  +
        "\u0098\u00D0\u0096unc\u00A0\u00E0\u0015\u00C3a\u00D2\u00C2\u00E7" +
        "f\u001D\"\u00D4\u00FF\u008E(h;o\u00C0\u007F\u00D0Y\u00FF#y\u00C8" +
        "w_P\u00E2C\u00C3@\u00D3\u00DF/\u0086V\u0088|\u00A4\u001A\u00A2"   +
        "\u00D2\u00BD-\u00A1\u00C9\u00E0\u00D64lH\u0019a\u00B7m\u0087"     +
        "\"T\u000F/*\u00BE2\u00E1\u00AAT\u0016k\"V\u008E:\u00A2\u00D3"     +
        "A\u00D0f\u00DB@\u00C8\u00A7\u00849/\u0000M\u00FF/-\u00B9\u00D2"   +
        "\u00DE\u0097\u0094?\u00ACJ\u0097\u00C1\u00D8RvD\u00B7\u00B5\u00F4"+
        "7\u00A7\u00B8,\u00BA\u00EF\u00D7Q\u00D1Yo\u00F7\u00F0\u00EDZ"     +
        "\tz\u001F\u0082{h\u00D0\u0090\u00EC\u00F5.\"\u00B0\u00C0T\u00BC"  +
        "\u008EY5Km/\u007FP\u00BBd\u00A2\u00D2fI\u0010\u00BE\u00E5\u0081"  +
        "-\u00B73\"\u0090\u00E9;\u0015\u009F\u00B4\u008E\u00E4\u0011K"     +
        "\u00FF4]\u00FDE\u00C2@\u00AD1\u0097?\u00C4\u00F6\u00D0.U\u00FC"   +
        "\u0081e\u00D5\u00B1\u00CA\u00AD\u00A1\u00AC-\u00AE\u00A2\u00D4"   +
        "\u00B7m\u00C1\u009B\u000CP\u0088\"@\u00F2\u000CnO8\u00A4\u00E4"   +
        "\u00BF\u00D7O[\u00A2rVL\u001D/\u00C5\u009CS\u0019\u00B9I\u00E3"   +
        "T\u00B0Fi\u00FE\u00B1\u00B6\u00AB\u008A\u00C7\u0013X\u00DDc\u0085"+
        "\u00C5E\u0011\u000F\u0093]WS\u008A\u00D5j9\u0004\u0093\u00E6"     +
        "=7\u00E0*T\u00F6\u00B3:x}_bv\u00A0\u00B5\u0019\u00A6\u00FC\u00DF" +
        "zB j)\u00F9\u00D4\u00D5\u00F6\u001B\u0018\u0091\u00BBr'^\u00AA"   +
        "P\u0081g8\u0090\u0010\u0091\u00C6\u00B5\u0005\u00EB\u0084\u00C7"  +
        "\u00CB\u008C*\u00D7Z\u000F\u0087J\u0014'\u00A2\u00D1\u0093k*"     +
        "\u00D2\u0086\u00AF\u00AAV\u00D2\u0091\u00D7\u0089C`B\\u\r\u0093"  +
        "\u00B3\u009E&\u0018q\u0084\u00C9l\u0000\u00B3-s\u00E2\u00BB\u0014"+
        "\u00A0\u00BE\u00BC<Tb7ydE\u009E\u00AB?2\u008B\u0082w\u0018\u00CF" +
        "\u0082Y\u00A2\u00CE\u00A6\u0004\u00EE\u0000.\u0089\u00FEx\u00E6"  +
        "?\u00AB\tP2_\u00F6\u00C2\u00818?\u0005ic\u00C5\u00C8v\u00CBZ"     +
        "\u00D6\u00D4\u0099t\u00C9\u00CA\u0018\r\u00CF8\u0007\u0082\u00D5" +
        "\u00C7\u00FA\\\u00F6\u008A\u00C3\u0015\u00115\u00E7\u009E\u0013"  +
        "G\u00DA\u0091\u00D0\u00F4\u000F\u0090\u0086\u00A7\u00E2A\u009E"   +
        "16bA\u0005\u001E\u00F4\u0095\u00AAW;\u0004J\u0080]\u008DT\u0083"  +
        "\u0000\u00D0\u00002*<\u00BFd\u00CD\u00DF\u00BAW\u00A6\u008Eu"     +
        "\u00C67+P\u00AF\u00D3A\u00A7\u00C12u\u0091Z\u000B\u00F5kT\u00BF"  +
        "\u00AB+\u000B\u0014&\u00ABL\u00C9\u00D7D\u009C\u00CD\u0082\u00F7" +
        "\u00FB\u00F2e\u00AB\u0085\u00C5\u00F3\u001BU\u00DB\u0094\u00AA"   +
        "\u00D4\u00E3$\u00CF\u00A4\u00BD?-\u00EA\u00A3\u00E2\u009E M\u0002"+
        "\u00C8\u00BD%\u00AC\u00EA\u00DFU\u00B3\u00D5\u00BD\u009E\u0098"   +
        "\u00E3\u00121\u00B2*\u00D5\u00ADl\u0095C)\u00DE\u00AD\u00BEE"     +
        "(\u00D8q\u000Fi\u00AAQ\u00C9\u000F\u00AAxk\u00F6\"Q?\u001E\u00AA" +
        "Q\u00A7\u009B*\u00D3D\u00CC{ZA\u00F0\u00D3|\u00FB\u00AD\u001B"    +
        "\u0006\u0095\u0005A\u00EC\u00E4\u0091\u00B4\u00C32\u00E6\u0003"   +
        "\"h\u00D4\u00C9`\n\u00CC\u00CE8~m\u00BFk\u00B1ljp\u00FBx\r\u0003" +
        "\u00D9\u00C9\u00D4\u00DF9\u00DE\u00E0\u0010c\u00DAG6\u00F4dZ"     +
        "\u00D3(\u00D8\u00B3G\u00CC\u0096u\u00BB\u000F\u00C3\u0098Q\u001B" +
        "\u00FBO\u00FB\u00CC5\u00B5\u008B\u00CFj\u00E1\u001F\n\u00BC\u00BF"+
        "\u00C5\u00FEJ\u00A7\n\u00EC\u0010\u00AC9W\n?\u0004D/a\u0088\u00B1"+
        "S\u00E09z.W'\u00CBy\u009C\u00EBA\u008F\u001C\u00AC\u00D6\u008D"   +
        "*\u00D3|\u0096\u0001u\u00CB\u009D\u00C6\u009D\u00FF\t\u00C7["     +
        "e\u00F0\u00D9\u00DB@\u00D8\u00EC\u000EwyGD\u00EA\u00D4\u00B1"     +
        "\u001C2t\u00DD$\u00CB\u009E~\u001CT\u00BD\u00F0\u0011D\u00F9"     +
        "\u00D2$\u000E\u00B1\u0096u\u00B3\u00FD\u00A3\u00AC7U\u00D4|'"     +
        "\u00AFQ\u00C8_MV\u0090u\u0096\u00A5\u00BB\u0015\u00E6X\u0003"     +
        "\u0004\u00F0\u00CA\u0004,\u00F1\u0001\u001A7\u00EA\u008D\u00BF"   +
        "\u00AA\u00DB5\u00BA>J5&\u00FF\u00A0\u00C3{M\t\u00BC0n\u00D9\u0098"+
        "\u00A5&fVH\u00F7%\u00FF^V\u009D\u000C\u00EDc\u00D0|c\u00B2\u00CF" +
        "p\u000BE\u00E1\u00D5\u00EAP\u00F1\u0085\u00A9(r\u00AF\u001F\u00BD"+
        "\u00A7\u00D4#Hp\u00A7\u0087\u000B\u00F3-;MyB\u00E0A\u0098\u000C"  +
        "\u00D0\u00ED\u00E7&G\r\u00B8\u00F8\u0081\u0081LGMj\u00D7|\u000C"  +
        "^\\\u00D1#\u0019Y8\u001Br\u0098\u00F5\u00D2\u00F4\u00DB\u00AB"    +
        "\u0083\u0086Sn/\u001E#\u0083q\u009C\u009E\u00BD\u0091\u00E0F"     +
        "\u009AVEn\u00DC9 \u000C \u00C8\u00C5q\u0096+\u00DA\u001C\u00E1"   +
        "\u00E6\u0096\u00FF\u00B1A\u00AB\u0008|\u00CA\u0089\u00B9\u001A"   +
        "i\u00E7\u0083\u0002\u00CCHC\u00A2\u00F7\u00C5yB\u009E\u00F4}"     +
        "B{\u0016\u009CZ\u00C9\u00F0I\u00DD\u008F\u000F\u0000\\\u0081"     +
        "e\u00BF",
    sS2="\u001F \u0010\u0094\u00EF\u000B\u00A7[i\u00E3\u00CF~9?C\u0080"    +
        "\u00FEa\u00CFz\u00EE\u00C5 zU\u0088\u009C\u0094r\u00FC\u0006"     +
        "Q\u00AD\u00A7\u00EFyN\u001Dr5\u00D5Zc\u00CE\u00DE\u00046\u00BA"   +
        "\u0099\u00C40\u00EF_\u000C\u0007\u0094\u0018\u00DC\u00DB}\u00A1"  +
        "\u00D6\u00EF\u00F3\u00A0\u00B5/{Y\u00E86\u0005\u00EE\u0015\u00B0" +
        "\u0094\u00E9\u00FF\u00D9\t\u00DCD\u0000\u0086\u00EF\u0094DY\u00BA"+
        "\u0083\u00CC\u00B3\u00E0\u00C3\u00CD\u00FB\u00D1\u00DAA\u0081"    +
        ";\t*\u00B1\u00F9\u0097\u00F1\u00C1\u00A5\u00E6\u00CF{\u0001B"     +
        "\r\u00DB\u00E4\u00E7\u00EF[%\u00A1\u00FFA\u00E1\u0080\u00F8\u0006"+
        "\u001F\u00C4\u0010\u0080\u0017\u009B\u00EEz\u00D3z\u00C6\u00A9"   +
        "\u00FEX0\u00A4\u0098\u00DE\u008B\u007Fw\u00E8?Ny\u0092\u0092"     +
        "i$\u00FA\u009F{\u00E1\u0013\u00C8[\u00AC\u00C4\u0000\u0083\u00D7" +
        "P5%\u00F7\u00EAa_b\u00141T\rUKc]h\u0011!\u00C8f\u00C3Y=c\u00CF"   +
        "s\u00CE\u00E24\u00C0\u00D4\u00D8~\u0087\\g+!\u0007\u001Fa\u0081"  +
        "9\u00F7b\u007F6\u001E0\u0084\u00E4\u00EBW;`/d\u00A4\u00D6:\u00CD" +
        "\u009C\u001B\u00BCF5\u009E\u0081\u0003-'\u0001\u00F5\u000C\u0099" +
        "\u0084z\u00B4\u00A0\u00E3\u00DFy\u00BAl\u00F3\u008C\u0010\u0084"  +
        "0\u0094%7\u00A9^\u00F4oo\u00FE\u00A1\u00FF;\u001F \u008C\u00FB"   +
        "j\u008FE\u008Ct\u00D9\u00E0\u00A2'N\u00C7:4\u00FC\u0088Oi>M\u00E8"+
        "\u00DF\u00EF\u000E\u0000\u00885Yd\u008D\u008AE8\u008C\u001D\u0080"+
        "Cfr\u001D\u009B\u00FD\u00A5\u0086\u0084\u00BB\u00E8%c3\u0084"     +
        "N\u0082\u0012\u0012\u008D\u0080\u0098\u00FE\u00D3?\u00B4\u00CE"   +
        "(\n\u00E1'\u00E1\u009B\u00A5\u00D5\u00A6\u00C2R\u00E4\u0097T"     +
        "\u00BD\u00C5\u00D6U\u00DD\u00EBfpdw\u0084\u000BM\u00A1\u00B6"     +
        "\u00A8\u0001\u0084\u00DB&\u00A9\u00E0\u00B5g\u0014!\u00F0C\u00B7" +
        "\u00E5\u00D0X`T\u00F00\u0084\u0006o\u00F4r\u00A3\u001A\u00A1"     +
        "S\u00DA\u00DCGU\u00B5b]\u00BFhV\u001B\u00E6\u0083\u00CAk\u0094"   +
        "-n\u00D2;\u00EC\u00CF\u0001\u00DB\u00A6\u00D3\u00D0\u00BA\u00B6"  +
        "\u0080=\\\u00AFw\u00A7\t3\u00B4\u00A3L9{\u00C8\u00D6^\u00E2+"     +
        "\u0095_\u000ES\u0004\u0081\u00EDoa \u00E7Cd\u00B4^\u0013x\u00DE"  +
        "\u0018c\u009B\u0088\u001C\u00A1\"\u00B9g&\u00D1\u0080I\u00A7"     +
        "\u00E8\"\u00B7\u00DA{^U-%Rr\u00D27y\u00D2\u0095\u001C\u00C6\r"    +
        "\u0089LH\u008C\u00B4\u0002\u001B\u00A4\u00FE[\u00A4\u00B0\u009F"  +
        "k\u001C\u00A8\u0015\u00CF\u00A2\u000C0\u0005\u0088q\u00DFc\u00B9" +
        "\u00DE/\u00CB\u000C\u00C6\u00C9\u00E9\u000B\u00EE\u00FFS\u00E3"   +
        "!E\u0017\u00B4T(5\u009Fc)<\u00EEA\u00E7)n\u001D-|P\u0004R\u0086"  +
        "\u001Ef\u0085\u00F3\u00F34\u0001\u00C60\u00A2,\u00951\u00A7\u0008"+
        "P`\u0093\u000F\u0013s\u00F9\u0084\u0017\u00A1&\u0098Y\u00ECd"     +
        "\\DR\u00C8w\u00A9\u00CD\u00FF3\u00A6\u00A0+\u0017A|\u00BA\u00D9"  +
        "\u00A2!\u0080\u0003oP\u00D9\u009C\u0008\u00CB?Ha\u00C2k\u00D7"    +
        "ed\u00A3\u00F6\u00AB\u00804&v%\u00A7^{\u00E4\u00E6\u00D1\u00FC"   +
        " \u00C7\u0010\u00E6\u00CD\u00F0\u00B6\u0080\u0017\u0084M;1\u00EE" +
        "\u00F8M~\u0008$\u00E4,\u00CBI\u00EB\u0084j;\u00AE\u008F\u00F7"    +
        "x\u0088\u00EE]`\u00F6z\u00F7Vs/\u00DD\\\u00DB\u00A1\u00161\u00C1" +
        "0\u00F6oC\u00B3\u00FA\u00ECT\u0015\u007F\u00D7\u00FA\u00EF\u0085" +
        "y\u00CC\u00D1R\u00DEX\u00DB/\u00FD^\u008F2\u00CE\u00190j\u00F9"   +
        "z\u0002\u00F0>\u00F8\u00991\u009A\u00D5\u00C2B\u00FA\u000F\u00A7" +
        "\u00E3\u00EB\u00B0\u00C6\u008EI\u0006\u00B8\u00DA#\u000C\u0080"   +
        "\u00820(\u00DC\u00DE\u00F3\u00C8\u00D3_\u00B1q\u0008\u008A\u001B" +
        "\u00C8\u00BE\u00C0\u00C5`a\u00A3\u00C9\u00E8\u00BC\u00A8\u00F5"   +
        "M\u00C7/\u00EF\u00FA\"\u0082.\u0099\u0082\u00C5p\u00B4\u00D8"     +
        "\u00D9N\u0089\u008B\u001C4\u00BC0\u001E\u0016\u00E6';\u00E9y"     +
        "\u00B0\u00FF\u00EA\u00A6a\u00D9\u00B8\u00C6\u0000\u00B2Hi\u00B7"  +
        "\u00FF\u00CE?\u0008\u00DC(;C\u00DA\u00F6Z\u00F7\u00E1\u0097\u0098"+
        "v\u0019\u00B7/\u008F\u001C\u009B\u00A4\u00DC\u00867\u00A0\u0016"  +
        "\u00A7\u00D3\u00B1\u009F\u00C3\u0093\u00B7\u00A7\u0013n\u00EB"    +
        "\u00C6\u00BC\u00C6>\u001AQ7B\u00EFh(\u00BCR\u0003e\u00D6-jw\u00AB"+
        "5'\u00EDK\u0082\u001F\u00D2\u0016\t\\n.\u00DB\u0092\u00F2\u00FB"  +
        "^\u00EA)\u00CB\u0014X\u0092\u00F5\u0091XO\u007FT\u0083i{&g\u00A8" +
        "\u00CC\u0085\u0019`H\u008CK\u00AC\u00EA\u00838`\u00D4\r#\u00E0"   +
        "\u00F9l8~\u008A\n\u00E6\u00D2I\u00B2\u0084`\u000C\u00D85s\u001D"  +
        "\u00DC\u00B1\u00C6G\u00ACLV\u00EA>\u00BD\u0081\u00B3#\u000E\u00AB"+
        "\u00B0d8\u00BC\u0087\u00F0\u00B5\u00B1\u00FA\u008F^\u00A2\u00B3"  +
        "\u00FC\u0018FB\n\u0003kzO\u00B0\u0089\u00BDd\u009D\u00A5\u0089"   +
        "\u00A3EA^\\\u0003\u0083#>];\u00B9C\u00D7\u0095r~m\u00D0|\u0006"   +
        "\u00DF\u00DF\u001Ell\u00C4\u00EFq`\u00A59s\u00BF\u00BEp\u0083"    +
        "\u0087v\u0005E#\u00EC\u00F1",
    sS3="\u008D\u00EF\u00C2@%\u00FA]\u009F\u00EB\u0090=\u00BF\u00E8\u0010" +
        "\u00C9\u0007G`\u007F\u00FF6\u009F\u00E4K\u008C\u001F\u00C6D\u00AE"+
        "\u00CE\u00CA\u0090\u00BE\u00B1\u00F9\u00BF\u00EE\u00FB\u00CA"     +
        "\u00EA\u00E8\u00CF\u0019PQ\u00DF\u0007\u00AE\u0092\u000E\u0088"   +
        "\u0006\u00F0\u00AD\u0005H\u00E1<\u008D\u0083\u0092p\u0010\u00D5"  +
        "\u0011\u0010}\u009F\u0007d}\u00B9\u00B2\u00E3\u00E4\u00D4=O("     +
        "^\u00B9\u00AF\u00A8 \u00FA\u00DE\u0082\u00E0\u00A0g&\u008B\u0082" +
        "ry.U?\u00B2\u00C0H\u009A\u00E2+\u00D4\u00EF\u0097\u0094\u0012"    +
        "^?\u00BC!\u00FF\u00FC\u00EE\u0082[\u001B\u00FD\u0092U\u00C5\u00ED"+
        "\u0012W\u00A2@N\u001A\u0083\u0002\u00BA\u00E0\u007F\u00FFR\u0082" +
        "F\u00E7\u008EW\u0014\u000E3s\u00F7\u00BF\u008C\u009F\u0081\u0088" +
        "\u00A6\u00FCN\u00E8\u00C9\u0082\u00B5\u00A5\u00A8\u00C0\u001D"    +
        "\u00B7W\u009F\u00C2dg\tO1\u00F2\u00BD?_@\u00FF\u00F7\u00C1\u001F" +
        "\u00B7\u008D\u00FC\u008Ek\u00D2\u00C1C{\u00E5\u009B\u0099\u00B0"  +
        "=\u00BF\u00B5\u00DB\u00C6Kc\u008D\u00C0\u00E6U\u0081\u009D\u0099" +
        "\u00A1\u0097\u00C8\u001CJ\u0001-n\u00C5\u0088J(\u00CC\u00C3o"     +
        "q\u00B8C\u00C2\u0013l\u0007C\u00F1\u0083\t\u0089<\u000F\u00ED"    +
        "\u00DD_/\u007F\u00E8P\u00D7\u00C0\u007F~\u0002P\u007F\u00BFZ"     +
        "\u00FB\u009A\u0004\u00A7G\u00D2\u00D0\u0016Q\u0019.\u00AFp\u00BF" +
        ">X\u00C3\u0013\u0080_\u00980.r|\u00C3\u00C4\n\u000F\u00B4\u0002"  +
        "\u000F\u007F\u00EF\u0082\u008C\u0096\u00FD\u00AD],*\u00AE\u008E"  +
        "\u00E9\u009AIP\u00DA\u0088\u00B8\u0084'\u00F4\u00A0\u001E\u00AC"  +
        "W\u0090yo\u00B4I\u0082R\u00DC\u0015\u00EF\u00BD}\u009B\u00A6"     +
        "rY}\u00AD\u00A8@\u00D8E\u00F5E\u0004\u00FA]t\u0003\u00E8>\u00C3"  +
        "\u0005O\u0091u\u001A\u0092Vi\u00C2#\u00EF\u00E9A\u00A9\u0003"     +
        "\u00F1.`'\r\u00F2\u0002v\u00E4\u00B6\u0094\u00FDet\u0092y\u0085"  +
        "\u00B2\u0082v\u00DB\u00CB\u0002w\u0081v\u00F8\u00AF\u0091\u008D"  +
        "NH\u00F7\u009E\u008Fam\u00DF\u00E2\u009D\u0084\u000E\u0084/}"     +
        "\u00834\u000C\u00E5\u00C8\u0096\u00BB\u00B6\u0082\u0093\u00B4"    +
        "\u00B1H\u00EF0<\u00AB\u0098O\u00AF(w\u009F\u00AF\u009B\u0092"     +
        "\u00DCV\r\"M\u001E \u00847\u00AA\u0088})\u00DC\u0096'V\u00D3"     +
        "\u00DC\u008B\u0090|\u00EE\u00B5\u001F\u00D2@\u00E7\u00C0|\u00E3"  +
        "\u00E5f\u00B4\u00A1\u00C3\u00E9a^<\u00F8 \u009D`\u0094\u00D1"     +
        "\u00E3\u00CD\u009C\u00A3A\\vF\u000E\u0000\u00EA\u0098;\u00D4"     +
        "\u00D6x\u0081\u00FDGW,\u00F7l\u00ED\u00D9\u00BD\u00A8\"\u009C"    +
        "\u0012}\u00AD\u00AAC\u008A\u0007N\u001F\u0097\u00C0\u0090\u0008"  +
        "\u001B\u00DB\u008A\u0093\u00A0~\u00BE\u00B98\u00CA\u0015\u0097"   +
        "\u00B0<\u00FF=\u00C2\u00C0\u00F8\u008D\u001A\u00B2\u00ECd8\u000E" +
        "Qh\u00CC{\u00FB\u00D9\u000F'\u0088\u0012I\u0001\u0081]\u00E5"     +
        "\u00FF\u00D4\u00DD~\u00F8jv\u00A2\u00E2\u0014\u00B9\u00A4\u0003"  +
        "h\u0092]\u0095\u008FK9\u00FF\u00FA\u00BA9\u00AE\u00E9\u00A4\u00FF"+
        "\u00D3\u000B\u00FA\u00F7\u0093;mI\u0086#\u0019<\u00BC\u00FA'"     +
        "buE\u0082\\\u00F4za\u00BD\u008B\u00A0\u00D1\u001EB\u00D1\u00CE"   +
        "\u00AD\u0004\u00F4\u0012~\u00A3\u0092\u0010B\u008D\u00B7\u0082"   +
        "r\u00A9r\u0092p\u00C4\u00A8\u0012}\u00E5\u000B([\u00A1\u00C8"     +
        "<b\u00F4O5\u00C0\u00EA\u00A5\u00E8\u0005\u00D21B\u0089)\u00FB"    +
        "\u00B4\u00FC\u00DF\u0082O\u00B6jS\u000E}\u00C1[\u001F\u0008\u001F"+
        "\u00AB\u0010\u0086\u0018\u00AE\u00FC\u00FD\u0008m\u00F9\u00FF"    +
        "(\u0089iK\u00CC\u0011#j\\\u00AE\u0012\u00DE\u00CAM,?\u008C\u00C5" +
        "\u00D2\u00D0-\u00FE\u00F8\u00EFX\u0096\u00E4\u00CFR\u00DA\u0095"  +
        "\u0015[gIJH\u008C\u00B9\u00B6\u00A8\u000C\\\u008F\u0082\u00BC"    +
        "\u0089\u00D3kE:`\u00947\u00EC\u0000\u00C9\u00A9DqRS\n\u0087K"     +
        "I\u00D7s\u00BC@|4g\u001C\u0002q~\u00F6O\u00EBU6\u00A2\u00D0/"     +
        "\u00FF\u00D2\u00BF`\u00C4\u00D4?\u0003\u00C0P\u00B4\u00EFm\u0007" +
        "G\u008C\u00D1\u0000n\u0018\u0088\u00A2\u00E5?U\u00B9\u00E6\u00D4" +
        "\u00BC\u00A2\u0004\u0080\u0016\u0097W83\u00D7 }g\u00DE\u000F"     +
        "\u008F=r\u00F8{3\u00AB\u00CCO3v\u0088\u00C5]{\u0000\u00A6\u00B0"  +
        "\u0094{\u0000\u0001W\u0000u\u00D2\u00F9\u00BB\u0088\u00F8\u0089"  +
        "B\u0001\u009EBd\u00A5\u00FF\u0085c\u0002\u00E0r\u00DB\u00D9+"     +
        "\u00EE\u0097\u001Bin\u00A2/\u00DE_\u0008\u00AE+\u00AFzam\u00E5"   +
        "\u00C9\u0087g\u00CF\u001F\u00EB\u00D2a\u00EF\u00C8\u00C2\u00F1"   +
        "\u00AC%q\u00CC\u00829\u00C2g!L\u00B8\u00B1\u00E5\u0083\u00D1"     +
        "\u00B7\u00DC>b\u007F\u0010\u00BD\u00CE\u00F9\n\\8\u000F\u00F0"    +
        "D=`nm\u00C6`T:IW'\u00C1H+\u00E9\u008A\u001D\u008A\u00B4\u0017"    +
        "8 \u00E1\u00BE$\u00AF\u0096\u00DA\u000FhE\u0084%\u0099\u0083"     +
        ";\u00E5`\rE}(/\u0093P\u00834\u00B3b\u00D9\u001D\u0011 +m\u008D"   +
        "\u00A0d+\u001E1\u009C0Z\u0000R\u00BC\u00E6\u0088\u001B\u0003"     +
        "X\u008A\u00F7\u00BA\u00EF\u00D5AB\u00ED\u009C\u00A41\\\u0011"     +
        "\u00832>\u00C5\u00DF\u00EFF6\u00A13\u00C5\u0001\u00E9\u00D3S"     +
        "\u001C\u00EE57\u0083",
    sS4="\u009D\u00B3\u0004 \u001F\u00B6\u00E9\u00DE\u00A7\u00BE{\u00EF"   +
        "\u00D2s\u00A2\u0098JO{\u00DBd\u00AD\u008CW\u0085Q\u0004C\u00FA"   +
        "\u0002\u000E\u00D1~(z\u00FF\u00E6\u000F\u00B6c\t_5\u00A1y\u00EB"  +
        "\u00F1 \u00FD\u0005\u009DCd\u0097\u00B7\u00B1\u00F3d\u001Fc$"     +
        "\u001EJ\u00DF(\u0014\u007F_O\u00A2\u00B8\u00CD\u00C9C\u0000@"     +
        "\u000C\u00C3\" \u00FD\u00D3\u000B0\u00C0\u00A57O\u001D-\u0000"    +
        "\u00D9$\u0014{\u0015\u00EEM\u0011\u001A\u000F\u00CAQgq\u00FF"     +
        "\u0090L-\u0019_\u00FE\u001A\u0005d_\u000C\u0013\u00FE\u00FE\u0008"+
        "\u001B\u0008\u00CA\u0005\u0017\u0001!\u0080S\u0001\u0000\u00E8"   +
        ">^\u00FE\u00AC\u009A\u00F4\u00F8\u007F\u00E7'\u0001\u00D2\u00B8"  +
        "\u00EE_\u0006\u00DFBa\u00BB\u009E\u009B\u008Ar\u0093\u00EA%\u00CE"+
        "\u0084\u00FF\u00DF\u00F5q\u0088\u0001=\u00D6K\u0004\u00A2o&;"     +
        "~\u00D4\u0084\u0000T~\u00EB\u00E6DmL\u00A0l\u00F3\u00D6\u00F5"    +
        "&I\u00AB\u00DF\u00AE\u00A0\u00C7\u00F563\u008C\u00C1P?~\u0093"    +
        "\u00D3w a\u0011\u00B68\u00E1rP\u000E\u0003\u00F8\u000E\u00B2"     +
        "\u00BB\u00AB\u00E0P.\u00EC\u008Dw\u00DEW\u0097\u001E\u0081\u00E1" +
        "OgF\u00C93T\u0000i 1\u008F\u0008\u001D\u00BB\u0099\u00FF\u00C3"   +
        "\u0004\u00A5M5\u0018\u0005\u007F=\\\u00E3\u00A6\u00C8f\u00C6"     +
        "][\u00CC\u00A9\u00DA\u00ECo\u00EA\u009F\u0092o\u0091\u009FF\""    +
        "/9\u0091F}\u00A5\u00BFm\u008E\u0011C\u00C4OC\u0095\u0083\u0002"   +
        "\u00D0!N\u00EB\u0002 \u0083\u00B8?\u00B6\u0018\u000C\u0018\u00F8" +
        "\u0093\u001E(\u0016X\u00E6&Hn>\u008B\u00D7\u008Aptw\u00E4\u00C1"  +
        "\u00B5\u0006\u00E0|\u00F3-\n%y\t\u008B\u0002\u00E4\u00EA\u00BB"   +
        "\u0081(\u0012;#i\u00DE\u00AD8\u0015t\u00CA\u0016\u00DF\u0087"     +
        "\u001Bb!\u001C@\u00B7\u00A5\u001A\u009E\u00F9\u0000\u00147{\u0004"+
        "\u001E\u008A\u00C8\t\u0011@\u0003\u00BDY\u00E4\u00D2\u00E3\u00D1" +
        "V\u00D5O\u00E8v\u00D5/\u0091\u00A3@U{\u00E8\u00DE\u0000\u00EA"    +
        "\u00E4\u00A7\u000C\u00E5\u00C2\u00ECM\u00B4\u00BB\u00A6\u00E7"    +
        "V\u00BD\u00FF\u00DD3i\u00AC\u00EC\u0017\u00B05\u0006W#'\u0099"    +
        "\u00AF\u00C8\u00B0V\u00C8\u00C3\u0091ke\u0081\u001C^\u0014a\u0019"+
        "n\u0085\u00CBu\u00BE\u0007\u00C0\u0002\u00C22Uw\u0089?\u00F4"     +
        "\u00EC[\u00BF\u00C9-\u00D0\u00EC;%\u00B7\u0080\u001A\u00B7\u008D" +
        "m;$ \u00C7c\u00EF\u00C3f\u00A5\u00FC\u009C8(\u0080\n\u00CE2\u0005"+
        "\u00AA\u00C9T\u008A\u00EC\u00A1\u00D7\u00C7\u0004\u001A\u00FA"    +
        "2\u001D\u0016bZg\u0001\u0090,\u009BuzT1\u00D4w\u00F7\u0091&\u00B0"+
        "16\u00CCo\u00DB\u00C7\u000B\u008BF\u00D9\u00E6jHV\u00E5Zy\u0002"  +
        "jL\u00EBRC~\u00FF/\u008Fv\u00B4\r\u00F9\u0080\u00A5\u0086t\u00CD" +
        "\u00E3\u00ED\u00DA\u0004\u00EB\u0017\u00A9\u00BE\u0004,\u0018"    +
        "\u00F4\u00DF\u00B7t\u007F\u009D\u00AB*\u00F7\u00B4\u00EF\u00C3"   +
        "M .\tk|\u0017A\u00A2T\u00E5\u00B6\u00A05!=B\u00F6,\u001C|&a\u00C2"+
        "\u00F5\u000FeR\u00DA\u00F9\u00D2\u00C21\u00F8%\u0013\u000Fi\u00D8"+
        "\u0016\u007F\u00A2\u0004\u0018\u00F2\u00C8\u0000\u001A\u0096"     +
        "\u00A6\r\u0015&\u00ABc1\\!^\nr\u00ECI\u00BA\u00FE\u00FD\u0018"    +
        "y\u0008\u00D9\u008D\r\u00BD\u00861\u0011p\u00A7>\u009Bd\u000C"    +
        "\u00CC>\u0010\u00D7\u00D5\u00CA\u00D3\u00B6\u000C\u00AE\u00C3"    +
        "\u0088\u00F70\u0001\u00E1lr\u008A\u00FFq\u00EA\u00E2\u00A1\u001F" +
        "\u009A\u00F3n\u00CF\u00CB\u00D1/\u00C1\u00DE\u0084\u0017\u00AC"   +
        "\u0007\u00BEk\u00CBD\u00A1\u00D8\u008B\u009B\u000FV\u00019\u0088" +
        "\u00C3\u00B1\u00C5/\u00CA\u00B4\u00BE1\u00CD\u00D8x(\u0006\u0012" +
        "\u00A3\u00A4\u00E2o}\u00E52X\u00FD~\u00B6\u00D0\u001E\u00E9\u0000"+
        "$\u00AD\u00FF\u00C2\u00F4\u0099\u000F\u00C5\u0097\u0011\u00AA"    +
        "\u00C5\u0000\u001D{\u0095\u0082\u00E5\u00E7\u00D2\u0010\u0098"    +
        "s\u00F6\u0000a0\u0096\u00C3-\u0095!\u00AD\u00A1!\u00FF)\u0090"    +
        "\u0084\u0015\u007F\u00BB\u0097\u007F\u00AF\u009E\u00B3\u00DB"     +
        ")\u00C9\u00ED*\\\u00E2\u00A4e\u00A70\u00F3,\u00D0\u00AA?\u00E8"   +
        "\u008A\\\u00C0\u0091\u00D4\u009E,\u00E7\u000C\u00E4T\u00A9\u00D6" +
        "\n\u00CD\u0086\u0001_\u0019\u0019w\u0007\u0091\u0003\u00DE\u00A0" +
        ":\u00F6x\u00A8V^\u00DE\u00E3V\u00DF!\u00F0\\\u00BE\u008Bu\u00E3"  +
        "\u0087\u00B3\u00C5\u0006Q\u00B8\u00A5\u00C3\u00EF\u00D8\u00EE"    +
        "\u00B6\u00D2\u00E5#\u00BEw\u00C2\u0015E)/i\u00EF\u00DF\u00AF"     +
        "\u00E6z\u00FB\u00F4p\u00C4\u00B2\u00F3\u00E0\u00EB[\u00D6\u00CC"  +
        "\u0098v9\u00E4F\u000C\u001F\u00DA\u00858\u0019\u0087\u0083/\u00CA"+
        "\u0000sg\u00A9\u0091D\u00F8)k)\u009EI/\u00C2\u0095\u0092f\u00BE"  +
        "\u00AB\u00B5gni\u009B\u00D3\u00DD\u00DA\u00DF~\u0005/\u00DB%"     +
        "p\u001C\u001B^Q\u00EE\u00F6S$\u00E6j\u00FC\u00E3l\u0003\u0016"    +
        "\u00CC\u0004\u0086D!>\u00B7\u00DCY\u00D0ye)\u001F\u00CC\u00D6"    +
        "\u00FDCA\u00829y\u0093+\u00CD\u00F6\u00B6W\u00C3MN\u00DF\u00D2"   +
        "\u0082z\u00E5)\u000C<\u00B9Sk\u0085\u001E \u00FE\u00983U~\u0013"  +
        "\u00EC\u00F0\u00B0\u00D3\u00FF\u00B3r?\u0085\u00C5\u00C1\n\u00EF" +
        "~\u00D2",
    sS5="~\u00C9\u000C\u0004,nt\u00B9\u009B\u000Ef\u00DF\u00A63y\u0011"    +
        "\u00B8j\u007F\u00FF\u001D\u00D3X\u00F5D\u00DD\u009DD\u00171\u0016"+
        "\u007F\u0008\u00FB\u00F1\u00FA\u00E7\u00F5\u0011\u00CC\u00D2"     +
        "\u0005\u001B\u0000sZ\u00BA\u0000*\u00B7\"\u00D88c\u0081\u00CB"    +
        "\u00AC\u00F6$:i\u00BE\u00FDz\u00E6\u00A2\u00E7\u007F\u00F0\u00C7" +
        " \u00CD\u00C4IH\u0016\u00CC\u00F5\u00C1\u00808\u0085\u0016@\u0015"+
        "\u00B0\u00A8H\u00E6\u008B\u0018\u00CBL\u00AA\u00DE\u00FF_H\n"     +
        "\u0001\u0004\u0012\u00B2\u00AA%\u0098\u0014\u00FCA\u00D0\u00EF"   +
        "\u00E2N@\u00B4\u008D$\u008E\u00B6\u00FB\u008D\u00BA\u001C\u00FE"  +
        "A\u00A9\u009B\u0002\u001AU\n\u0004\u00BA\u008Fe\u00CBrQ\u00F4"    +
        "\u00E7\u0095\u00A5\u0017%\u00C1\u0006\u00EC\u00D7\u0097\u00A5"    +
        "\u0098\n\u00C59\u00B9\u00AAMy\u00FEj\u00F2\u00F3\u00F7ch\u00AF"   +
        "\u0080@\u00ED\u000C\u009EV\u0011\u00B4\u0095\u008B\u00E1\u00EB"   +
        "Z\u0088\u0087\t\u00E6\u00B0\u00D7\u00E0qVN)\u00FE\u00A7cf\u00E5"  +
        "-\u0002\u00D1\u00C0\u0000\u00C4\u00AC\u008E\u0005\u0093w\u00F5"   +
        "q\u000C\u00057*W\u00855\u00F2\"a\u00BE\u0002\u00D6B\u00A0\u00C9"  +
        "\u00DF\u0013\u00A2\u0080t\u00B5[\u00D2h!\u0099\u00C0\u00D4!\u00E5"+
        "\u00ECS\u00FB<\u00E8\u00C8\u00AD\u00ED\u00B3(\u00A8\u007F\u00C9"  +
        "=\u0095\u0099\u0081\\\u001F\u00F9\u0000\u00FE8\u00D3\u0099\u000C" +
        "N\u00FF\u000B\u0006$\u0007\u00EA\u00AA/O\u00B1O\u00B9iv\u0090"    +
        "\u00C7\u0095\u0005\u00B0\u00A8\u00A7t\u00EFU\u00A1\u00FF\u00E5"   +
        "\u009C\u00A2\u00C2\u00A6\u00B6-'\u00E6jBc\u00DFe\u0000\u001F"     +
        "\u000E\u00C5\tf\u00DF\u00DDU\u00BC)\u00DE\u0006U\u0091\u001E"     +
        "s\u009A\u0017\u00AF\u0089u2\u00C7\u0091\u001C\u0089\u00F8\u0094"  +
        "h\r\u0001\u00E9\u0080RGU\u00F4\u0003\u00B6<\u00C9\u000C\u00C8"    +
        "D\u00B2\u00BC\u00F3\u00F0\u00AA\u0087\u00AC6\u00E9\u00E5:t&\u0001"+
        "\u00B3\u00D8+\u001A\u009EtId\u00EE-~\u00CD\u00DB\u00B1\u00DA"     +
        "\u0001\u00C9I\u0010\u00B8h\u00BF\u0080\r&\u00F3\u00FD\u0093B"     +
        "\u00ED\u00E7\u0004\u00A5\u00C2\u0084cg7\u00B6P\u00F5\u00B6\u0016" +
        "\u00F2Gf\u00E3\u008E\u00CA6\u00C1\u0013n\u0005\u00DB\u00FE\u00F1" +
        "\u0083\u0091\u00FB\u0088z7\u00D6\u00E7\u00F7\u00D4\u00C7\u00FB"   +
        "}\u00C90c\u00FC\u00DF\u00B6\u00F5\u0089\u00DE\u00EC)A\u00DA&"     +
        "\u00E4f\u0095\u00B7Vd\u0019\u00F6T\u00EF\u00C5\u00D0\u008DX\u00B7"+
        "H\u0092T\u0001\u00C1\u00BA\u00CB\u007F\u00E5\u00FFU\u000F\u00B6"  +
        "\u00080I[\u00B5\u00D0\u00E8\u0087\u00D7.Z\u00ABjn\u00E1\":f\u00CE"+
        "\u00C6+\u00F3\u00CD\u009E\u0008\u0085\u00F9h\u00CB>G\u0008l\u0001"+
        "\u000F\u00A2\u001D\u00E8 \u00D1\u008Bi\u00DE\u00F3\u00F6Ww\u00FA" +
        "\u0002\u00C3\u00F6@~\u00DA\u00C3\u00CB\u00B3\u00D5P\u0017\u0093"  +
        "\u0008M\u00B0\u00D7\u000E\u00BA\n\u00B3x\u00D5\u00D9Q\u00FB\u000C"+
        "\u00DE\u00D7\u00DAVA$\u00BB\u00E4\u0094\u00CA\u000BV\u000FWU"     +
        "\u00D1\u00E0\u00E1\u00E5na\u0084\u00B5\u00BEX\n$\u009F\u0094"     +
        "\u00F7K\u00C0\u00E3'\u0088\u008E\u009F{Ua\u00C3\u00DC\u0002\u0080"+
        "\u0005hw\u0015dlk\u00D7D\u0090M\u00B3f\u00B4\u00F0\u00A3\u00C0"   +
        "\u00F1d\u008Ai~\u00D5\u00AFI\u00E9/\u00F60\u009E7O,\u00B65j\u0085"+
        "\u0080\u0085sI\u0091\u00F8@v\u00F0\u00AE\u0002\u0008;\u00E8M"     +
        "(B\u001C\u009ADH\u0094\u0006snL\u00B8\u00C1\t)\u0010\u008B\u00C9" +
        "_\u00C6}\u0086\u009C\u00F4\u0013Oao.w\u0011\u008D\u00B3\u001B"    +
        "+\u00E1\u00AA\u0090\u00B4r<\u00A5\u00D7\u0017}\u0016\u001B\u00BA" +
        "\u009C\u00AD\u0090\u0010\u00AFF+\u00A2\u009F\u00E4Y\u00D2E\u00D3" +
        "EY\u00D9\u00F2\u00DA\u0013\u00DB\u00C6T\u0087\u00F3\u00E4\u00F9"  +
        "N\u0017mHo\t|\u0013\u00EAc\u001D\u00A5\u00C7D_s\u0082\u0017V"     +
        "\u0083\u00F4\u00CD\u00C6j\u0097p\u00BE\u0002\u0088\u00B3\u00CD"   +
        "\u00CFrn]\u00D2\u00F3 \u0093`yE\u009B\u0080\u00A5\u00BE`\u00E2"   +
        "\u00DB\u00A9\u00C21\u0001\u00EB\u00A51\\\"NB\u00F2\u001C\\\u0015" +
        "r\u00F6r\u001B,\u001A\u00D2\u00FF\u00F3\u008C%@N2N\u00D7/@g\u00B7"+
        "\u00FD\u0005#\u0013\u008E\\\u00A3\u00BCx\u00DC\u000F\u00D6nu"     +
        "\u0092\"\u0083xMk\u0017X\u00EB\u00B1nD\tO\u0085?H\u001D\u0087"    +
        "\u00FC\u00FE\u00AE{w\u00B5\u00FFv\u008C#\u0002\u00BF\u00AA\u00F4" +
        "uV_F\u00B0*+\t(\u0001=8\u00F5\u00F7\u000C\u00A8\u001F6R\u00AF"    +
        "J\u008Af\u00D5\u00E7\u00C0\u00DF;\u0008t\u0095\u0005Q\u0010\u001B"+
        "Z\u00D7\u00A8\u00F6\u001E\u00D5\u00ADl\u00F6\u00E4y u\u0081\u0084"+
        "\u00D0\u00CE\u00FAe\u0088\u00F7\u00BEXJ\u0004h&\u000F\u00F6\u00F8"+
        "\u00F3\u00A0\u009C\u007FpSF\u00AB\u00A0\\\u00E9l(\u00E1v\u00ED"   +
        "\u00A3k\u00AC0\u007F7h)\u00D2\u00856\u000F\u00A9\u0017\u00E3"     +
        "\u00FE*$\u00B7\u0097g\u00F5\u00A9k \u00D6\u00CD%\u0095h\u00FF"    +
        "\u001E\u00BFuUD,\u00F1\u009F\u0006\u00BE\u00F9\u00E0e\u009A\u00EE"+
        "\u00B9I\u001D4\u0001\u0007\u0018\u00BB0\u00CA\u00B8\u00E8\"\u00FE"+
        "\u0015\u0088W\t\u0083u\u000EbI\u00DAb~U^v\u00FF\u00A8\u00B1S"     +
        "EFmG\u00DE\u0008\u00EF\u00E9\u00E7\u00D4",
    sS6="\u00F6\u00FA\u008F\u009D,\u00ACl\u00E1L\u00A3Hg\u00E23\u007F"     +
        "|\u0095\u00DB\u0008\u00E7\u0001hC\u00B4\u00EC\u00ED\\\u00BC2"     +
        "US\u00AC\u00BF\u009F\t`\u00DF\u00A1\u00E2\u00ED\u0083\u00F0W"     +
        "\u009Dc\u00ED\u0086\u00B9\u001A\u00B6\u00A6\u00B8\u00DE^\u00BE"   +
        "9\u00F3\u008F\u00F72\u0089\u0089\u00B183\u00F1Ia\u00C0\u0019"     +
        "7\u00BD\u00F5\u0006\u00C6\u00DA\u00E4b^~\u00A3\u0008\u00EA\u0099" +
        "N#\u00E3<y\u00CB\u00D7\u00CCH\u00A1Cg\u00A3\u0014\u0096\u0019"    +
        "\u00FE\u00C9K\u00D5\u00A1\u0014\u0017J\u00EA\u00A0\u0018f\u00A0"  +
        "\u0084\u00DB-\t\u00A8Ho\u00A8\u0088aJ)\u0000\u00AF\u0098\u0001"   +
        "fY\u0091\u00E1\u0099(c\u00C8\u00F3\u000C`.x\u00EF<\u00D0\u00D5"   +
        "\u00192\u00CF\u000F\u00EC\u0014\u00F7\u00CA\u0007\u00D2\u00D0"    +
        "\u00A8 r\u00FDA\u0019~\u0093\u0005\u00A6\u00B0\u00E8k\u00E3\u00DA"+
        "t\u00BE\u00D3\u00CD7-\u00A5<L\u007FDH\u00DA\u00B5\u00D4@m\u00BA"  +
        "\u000E\u00C3\u00089\u0019\u00A7\u009F\u00BA\u00EE\u00D9I\u00DB"   +
        "\u00CF\u00B0Ng\u000CS\\=\u009C\u0001d\u00BD\u00B9A,\u000Ecj\u00BA"+
        "}\u00D9\u00CD\u00EAos\u0088\u00E7\u000B\u00C7b5\u00F2\u009A\u00DB"+
        "\\L\u00DD\u008D\u00F0\u00D4\u008D\u008C\u00B8\u0081S\u00E2\u0008" +
        "\u00A1\u0098f\u001A\u00E2\u00EA\u00C8(L\u00AF\u0089\u00AA\u0092"  +
        "\u0082#\u00934\u00BES;:!\u00BF\u0016CK\u00E3\u009A\u00EA9\u0006"  +
        "\u00EF\u00E8\u00C3n\u00F8\u0090\u00CD\u00D9\u0080\"m\u00AE\u00C3" +
        "@\u00A4\u00A3\u00DF~\u009C\t\u00A6\u0094\u00A8\u0007[|^\u00CC"    +
        "\"\u001D\u00B3\u00A6\u009Ai\u00A0/h\u0081\u008AT\u00CE\u00B2"     +
        ")oS\u00C0\u0084:\u00FE\u00896U%\u00BF\u00E6\u008A\u00B4b\u008A"   +
        "\u00BC\u00CF\".\u00BF%\u00ACoH\u00A9\u00A9\u0093\u0087S\u00BD"    +
        "\u00DBe\u00E7o\u00FB\u00E7\u00E9g\u00FDx\u000B\u00A95c\u008E"     +
        "4+\u00C1\u00E8\u00A1\u001B\u00E9I\u0080t\r\u00C8\u0008}\u00FC"    +
        "\u008D\u00E4\u00BF\u0099\u00A1\u0011\u0001\u00A0\u007F\u00D3"     +
        "yu\u00DAZ&\u00C0\u00E8\u001F\u0099O\u0095(\u00CD\u0089\u00FD"     +
        "3\u009F\u00ED\u00B8x4\u00BF_\u0004Em\"%\u0086\u0098\u00C9\u00C4"  +
        "\u00C8;-\u00C1V\u00BEOb\u008D\u00AAW\u00F5^\u00C5\u00E2\"\n\u00BE"+
        "\u00D2\u0091n\u00BFN\u00C7[\u0095$\u00F2\u00C3\u00C0B\u00D1]"     +
        "\u0099\u00CD\r\u007F\u00A0{n'\u00FF\u00A8\u00DC\u008A\u00F0s"     +
        "E\u00C1\u0006\u00F4\u001E#/5\u0016#\u0086\u00E6\u00EA\u0089&"     +
        "33\u00B0\u0094\u0015~\u00C6\u00F27+t\u00AFi%s\u00E4\u00E9\u00A9"  +
        "\u00D8H\u00F3\u0016\u0002\u0089:b\u00EF\u001D\u00A7\u0087\u00E2"  +
        "8\u00F3\u00A5\u00F6vt6HS \u0095\u0010cEvi\u008D\u00B6\u00FA\u00D4"+
        "\u0007Y*\u00F9P6\u00F75#L\u00FBn\u0087}\u00A4\u00CE\u00C0l\u0015" +
        "-\u00AA\u00CB\u0003\u0096\u00A8\u00C5\r\u00FE]\u00FC\u00D7\u0007" +
        "\u00AB\t!\u00C4/\u0089\u00DF\u00F0\u00BB_\u00E2\u00BExD\u008F"    +
        "O3uF\u0013\u00C9+\u0005\u00D0\u008DH\u00B9\u00D5\u0085\u00DC"     +
        "\u0004\u0094A\u00C8\t\u008F\u009B}\u00ED\u00E7\u0086\u00C3\u009A" +
        "3sBA\u0000\u0005j\t\u0017Q\u000E\u00F3\u00C8\u00A6\u0089\u0000"   +
        "r\u00D6( v\u0082\u00A9\u00A9\u00F7\u00BE\u00BF2g\u009D\u00D4"     +
        "[[u\u00B3S\u00FD\u0000\u00CB\u00B0\u00E3X\u0083\u000F\"\n\u001F"  +
        "\u008F\u00B2\u0014\u00D3r\u00CF\u0008\u00CC<J\u0013\u008C\u00F6"  +
        "1f\u0006\u001C\u0087\u00BE\u0088\u00C9\u008F\u0088`b\u00E3\u0097" +
        "G\u00CF\u008Ez\u00B6\u00C8R\u0083<\u00C2\u00AC\u00FB?\u00C0i"     +
        "vN\u008F\u0002Rd\u00D81M\u00DA8p\u00E3\u001EfTY\u00C1\t\u0008"    +
        "\u00F0Q0!\u00A5l[h\u00B7\u0082/\u008A\u00A00\u0007\u00CD>tq\u009E"+
        "\u00EF\u00DC\u0087&\u0081\u00073@\u00D4~C/\u00D9\u000C^\u00C2"    +
        "A\u0088\t(l\u00F5\u0092\u00D8\u0091\u0008\u00A90\u00F6\u0095"     +
        "~\u00F3\u0005\u00B7\u00FB\u00FF\u00BD\u00C2f\u00E9oo\u00E4\u00AC" +
        "\u0098\u00B1s\u00EC\u00C0\u00BC`\u00B4*\u00954\u0098\u00DA\u00FB" +
        "\u00A1\u00AE\u0012-K\u00D76\u000F%\u00FA\u00AB\u00A4\u00F3\u00FC" +
        "\u00EB\u00E2\u0096\u0091#%\u007F\u000C=\u0093H\u00AFI6\u0014"     +
        "\u0000\u00BC\u00E8\u0081oJ8\u0014\u00F2\u0000\u00A3\u00F9@C\u009C"+
        "zT\u00C2\u00BCpOW\u00DAA\u00E7\u00F9\u00C2Z\u00D3:T\u00F4\u00A0"  +
        "\u0084\u00B1\u007FU\u0005Y5|\u00BE\u00ED\u00BD\u0015\u00C8\u007F" +
        "\u0097\u00C5\u00AB\u00BAZ\u00C7\u00B5\u00B6\u00F6\u00DE\u00AF"    +
        ":G\u009C:S\u0002\u00DA%e=~jT&\u008DIQ\u00A4w\u00EAP\u0017\u00D5"  +
        "[\u00D7\u00D2]\u0088D\u0013lv\u0004\u0004\u00A8\u00C8\u00B8\u00E5"+
        "\u00A1!\u00B8\u001A\u0092\u008A`\u00EDXi\u0097\u00C5[\u0096\u00EA"+
        "\u00EC\u0099\u001B)\u0093Y\u0013\u0001\u00FD\u00B7\u00F1\u0008"   +
        "\u008E\u008D\u00FA\u009A\u00B6\u00F6\u00F5;L\u00BF\u009FJ]\u00E3" +
        "\u00AB\u00E6\u0005\u001D5\u00A0\u00E1\u00D8U\u00D3kL\u00F1\u00F5" +
        "D\u00ED\u00EB\u00B0\u00E95$\u00BE\u00BB\u008F\u00BD\u00A2\u00D7"  +
        "b\u00CFI\u00C9/T8\u00B5\u00F31q(\u00A4TH9)\u0005\u00A6[\u001D"    +
        "\u00B8\u0085\u001C\u0097\u00BD\u00D6u\u00CF/",
    sS7="\u0085\u00E0@\u00193+\u00F5gf-\u00BF\u00FF\u00CF\u00C6V\u0093"    +
        "*\u008D\u007Fo\u00AB\u009B\u00C9\u0012\u00DE`\u0008\u00A1 (\u00DA"+
        "\u001F\u0002'\u00BC\u00E7Md)\u0016\u0018\u00FA\u00C3\u0000P\u00F1"+
        "\u008B\u0082,\u00B2\u00CB\u0011\u00B22\u00E7\\K6\u0095\u00F2"     +
        "\u00B2\u0087\u0007\u00DE\u00A0_\u00BC\u00F6\u00CDA\u0081\u00E9"   +
        "\u00E1P!\u000C\u00E2N\u00F1\u00BD\u00B1h\u00C3\u0081\u00FD\u00E4" +
        "\u00E7\u0089\\y\u00B0\u00D8\u001E\u008B\u00FDCMIP\u00018\u00BE"   +
        "CA\u0091<\u00EE\u001D\u0092\u00A7\u009C?\u0008\u0097f\u00BE\u00BA"+
        "\u00EE\u00AD\u00F4\u0012\u0086\u00BE\u00CF\u00B6\u00EA\u00CB"     +
        "\u0019&`\u00C2\u0000ue\u00BD\u00E4d$\u001Fz\u0082H\u00DC\u00A9"   +
        "\u00C3\u00B3\u00ADf(\u0013`\u0086\u000B\u00D8\u00DF\u00A85m\u001C"+
        "\u00F2\u0010w\u0089\u00BE\u00B3\u00B2\u00E9\u00CE\u0005\u0002"    +
        "\u00AA\u008F\u000B\u00C05\u001E\u0016k\u00F5*\u00EB\u0012\u00FF"  +
        "\u0082\u00E3Hi\u0011\u00D3Mu\u0016N{:\u00FF_Cg\u001B\u009C\u00F6" +
        "\u00E07I\u0081\u00AC\u00833Bf\u00CE\u008C\u0093A\u00B7\u00D0"     +
        "\u00D8T\u00C0\u00CB:l\u0088G\u00BC()G%\u00BA7\u00A6j\u00D2+z"     +
        "\u00D6\u001F\u001E\u000C\\\u00BA\u00FAD7\u00F1\u0007\u00B6\u00E7" +
        "\u0099bB\u00D2\u00D8\u0016\n\u0096\u0012\u0088\u00E1\u00A5\u00C0" +
        "n\u0013t\u009Egr\u00FC\u0008\u001A\u00B1\u00D19\u00F7\u00F9X"     +
        "7E\u00CF\u0019\u00DFX\u00BE\u00C3\u00F7V\u00C0n\u00BA0\u0007"     +
        "!\u001B$E\u00C2\u0088)\u00C9^1\u007F\u00BC\u008E\u00C5\u0011"     +
        "8\u00BCF\u00E9\u00C6\u00E6\u00FA\u0014\u00BA\u00E8XJ\u00ADN\u00BC"+
        "FF\u008FP\u008Bx)C_\u00F1$\u0018;\u0082\u001D\u00BA\u009F\u00AF"  +
        "\u00F6\u000F\u00F4\u00EA,Nm\u0016\u00E3\u0092d\u0092TJ\u008B"     +
        "\u0000\u009BO\u00C3\u00AB\u00A6\u008C\u00ED\u009A\u00C9ox\u0006"  +
        "\u00A5\u00B7\u009A\u00B2\u0085nn\u001A\u00EC<\u00A9\u00BE\u0083"  +
        "\u0086\u0088\u000E\u0008\u0004\u00E9U\u00F1\u00BEV\u00E7\u00E5"   +
        "6;\u00B3\u00A1\u00F2]\u00F7\u00DE\u00BB\u0085a\u00FE\u0003<\u0016"+
        "tb3<\u0003L(\u00DAm\u000Cty\u00AA\u00C5l<\u00E4\u00E1\u00ADQ"     +
        "\u00F0\u00C8\u0002\u0098\u00F8\u00F3Z\u0016&\u00A4\u009F\u00EE"   +
        "\u00D8+)\u001D8/\u00E3\u000CO\u00B9\u009A\u00BB2Wx>\u00C6\u00D9"  +
        "{nw\u00A6\u00A9\u00CBe\u008B\\\u00D4R0\u00C7+\u00D1@\u008B`\u00C0"+
        ">\u00B7\u00B9\u0006\u008Dx\u00A37T\u00F4\u00F40\u00C8}\u00C8"     +
        "\u00A7\u0013\u0002\u00B9m\u008C2\u00EB\u00D4\u00E7\u00BE\u00BE"   +
        "\u008B\u009D-yy\u00FB\u0006\u00E7\"S\u0008\u008Bu\u00CFw\u0011"   +
        "\u00EF\u008D\u00A4\u00E0\u0083\u00C8X\u008DkxoZc\u0017\u00A6"     +
        "\u00FA\\\u00F7\u00A0]\u00DA\u00003\u00F2\u008E\u00BF\u00B0\u00F5" +
        "\u00B9\u00C3\u0010\u00A0\u00EA\u00C2\u0080\u0008\u00B9vz\u00A3"   +
        "\u00D9\u00D2\u00B0y\u00D3B\u0017\u0002\u001Aq\u008D\u009A\u00C6"  +
        "3j'\u0011\u00FD`C\u0080P\u00E3\u0006\u0099\u0008\u00A8=\u007F"    +
        "\u00ED\u00C4\u0082m+\u00EFN\u00EB\u0084vH\u008D\u00CF%6\u00C9"    +
        "\u00D5f(\u00E7NA\u00C2a\n\u00CA=I\u00A9\u00CF\u00BA\u00E3\u00B9"  +
        "\u00DF\u00B6_\u008D\u00E6\u0092\u00AE\u00AFd:\u00C7\u00D5\u00E6"  +
        "\u009E\u00A8\u0005\t\u00F2+\u0001}\u00A4\u0017?p\u00DD\u001E"     +
        "\u0016\u00C3\u0015\u00E0\u00D7\u00F9P\u00B1\u00B8\u0087+\u009F"   +
        "O\u00D5bZ\u00BA\u0082j\u0001yb.\u00C0\u001B\u009C\u0015H\u008A"   +
        "\u00A9\u00D7\u0016\u00E7@@\u0005Z,\u0093\u00D2\u009A\"\u00E3"     +
        "-\u00BF\u009A\u0005\u0087E\u00B94S\u00DC\u001E\u00D6\u0099)n"     +
        "Il\u00FFo\u001C\u009FI\u0086\u00DF\u00E2\u00ED\u0007\u00B8rB"     +
        "\u00D1\u0019\u00DE~\u00AE\u0005>V\u001A\u0015\u00ADo\u008Cfb"     +
        "l\u001CqT\u00C2L\u00EA\u0008+*\u0093\u00EB)9\u0017\u00DC\u00B0"   +
        "\u00F0X\u00D4\u00F2\u00AE\u009E\u00A2\u0094\u00FBR\u00CFVL\u0098" +
        "\u0083\u00FEf.\u00C4\u0005\u0081v9S\u00C3\u0001\u00D6i.\u00D3"    +
        "\u00A0\u00C1\u0008\u00A1\u00E7\u0016\u000E\u00E4\u00F2\u00DF"     +
        "\u00A6i>\u00D2\u0085t\u0090F\u0098L+\u000E\u00DDOuvV]93x\u00A1"   +
        "2#O=2\u001C]\u00C3\u00F5\u00E1\u0094K&\u0093\u0001\u00C7\u009F"   +
        "\u0002/<\u0099~~^O\u0095\u0004?\u00FA\u00FB\u00BDv\u00F7\u00AD"   +
        "\u000E)f\u0093\u00F4=\u001F\u00CEo\u00C6\u001EE\u00BE\u00D3\u00B5"+
        "\u00AB4\u00F7+\u00F9\u00B7\u001B\u00044\u00C0Nr\u00B5gU\u0092"    +
        "\u00A3=\u00B5\"\u0093\u0001\u00CF\u00D2\u00A8\u007F`\u00AE\u00B7" +
        "g\u0018\u00148k0\u00BC\u00C3=8\u00A0\u00C0}\u00FD\u0016\u0006"    +
        "\u00F2\u00C3cQ\u009BX\u009D\u00D3\u0090Ty\u00F8\u00E6\u001C\u00B8"+
        "\u00D6G\u0097\u00FDa\u00A9\u00EAwY\u00F4-WS\u009DV\u009AX\u00CF"  +
        "\u00E8Nc\u00ADF.\u001Bxe\u0080\u00F8~\u00F3\u0081y\u0014\u0091"   +
        "\u00DAU\u00F4@\u00A20\u00F3\u00D1\u0098\u008F5\u00B6\u00E3\u0018" +
        "\u00D2?\u00FAP\u00BC=@\u00F0!\u00C3\u00C0\u00BD\u00AEIX\u00C2"    +
        "LQ\u008F6\u00B2\u0084\u00B1\u00D3p\u000F\u00ED\u00CE\u0083\u0087" +
        "\u008D\u00DA\u00DA\u00F2\u00A2y\u00C7\u0094\u00E0\u001B\u00E8"    +
        "\u0090qoK\u0095K\u008A\u00A3",
    sS8="\u00E2\u00160\r\u00BB\u00DD\u00FF\u00FC\u00A7\u00EB\u00DA\u00BD"  +
        "5d\u0080\u0095w\u0089\u00F8\u00B7\u00E6\u00C1\u0012\u001B\u000E"  +
        "$\u0016\u0000\u0005,\u00E8\u00B5\u0011\u00A9\u00CF\u00B0\u00E5"   +
        "\u0095/\u0011\u00EC\u00E7\u0099\n\u0093\u0086\u00D1t*B\u0093"     +
        "\u001Cv\u00E3\u0081\u0011\u00B1-\u00EF:7\u00DD\u00DD\u00FC\u00DE" +
        "\u009A\u00DE\u00B1\n\u000C\u00C3,\u00BE\u0019p)\u0084\u00A0\t"    +
        "@\u00BB$:\u000F\u00B4\u00D17\u00CF\u00B4Ny\u00F0\u0004\u009E"     +
        "\u00ED\u00FD\u000B\u0015\u00A1]H\r1h\u008B\u00BB\u00DEZf\u009D"   +
        "\u00EDB\u00C7\u00EC\u00E81?\u008F\u0095\u00E7r\u00DF\u0019\u001B" +
        "u\u00803\r\u0094\u0007BQ\\}\u00CD\u00FA\u00AB\u00BEmc\u00AA@"     +
        "!d\u00B3\u0001\u00D4\n\u0002\u00E7\u00D1\u00CASW\u001D\u00AE"     +
        "z1\u0082\u00A2\u0012\u00A8\u00DD\u00EC\u00FD\u00AA3]\u0017oC"     +
        "\u00E8q\u00FBF\u00D48\u0012\u0090\"\u00CE\u0094\u009A\u00D4\u00B8"+
        "Gi\u00AD\u0096[\u00D8b\u0082\u00F3\u00D0Uf\u00FB\u0097g\u0015"    +
        "\u00B8\u000BN\u001D[G\u00A0L\u00FD\u00E0o\u00C2\u008E\u00C4\u00B8"+
        "W\u00E8rndzx\u00FC\u0099\u0086]D`\u008B\u00D5\u0093l \u000E\u0003"+
        "9\u00DC_\u00F6]\u000B\u0000\u00A3\u00AEc\u00AF\u00F2~\u008B\u00D6"+
        "2p\u0010\u008C\u000C\u00BB\u00D3PI)\u0098\u00DF\u0004\u0098\u000C"+
        "\u00F4*\u009Bm\u00F4\u0091\u009E~\u00DDS\u0006\u0091\u0085HX"     +
        "\u00CB~\u0007;t\u00EF.R/\u00FF\u00B1\u00D2G\u0008\u00CC\u001C"    +
        "~'\u00CD\u00A4\u00EB![<\u00F1\u00D2\u00E2\u0019\u00B4z8BOv\u0018" +
        "5\u0085`9\u009D\u0017\u00DE\u00E7'\u00EB5\u00E6\u00C9\u00AF\u00F6"+
        "{6\u00BA\u00F5\u00B8\t\u00C4g\u00CD\u00C1\u0089\u0010\u00B1\u00E1"+
        "\u001D\u00BF{\u0006\u00CD\u001A\u00F8qp\u00C6\u0008-^3T\u00D4"    +
        "\u00DEIZd\u00C6\u00D0\u0006\u00BC\u00C0\u00C6,=\u00D0\r\u00B3"    +
        "p\u008F\u008F4w\u00D5\u001BB&Ob\u000F$\u00B8\u00D2\u00BF\u0015"   +
        "\u00C1\u00B7\u009EF\u00A5%d\u00F8\u00D7\u00E5N>7\u0081`x\u0095"   +
        "\u00CD\u00A5\u0085\u009C\u0015\u00A5\u00E6E\u0097\u0088\u00C3"    +
        "{\u00C7_\u00DB\u0007\u00BA\u000C\u0006v\u00A3\u00AB\u007F\"\u009B"+
        "\u001E1\u0084.{$%\u009F\u00D7\u00F8\u00BE\u00F4r\u0083_\u00FC"    +
        "\u00B8m\u00F4\u00C1\u00F2\u0096\u00F5\u00B1\u0095\u00FD\n\u00F0"  +
        "\u00FC\u00B0\u00FE\u0013L\u00E2Pm=O\u009B\u0012\u00EA\u00F2\u0015"+
        "\u00F2%\u00A2#so\u009F\u00B4\u00C4(%\u00D0Iy4\u00C7\u0013\u00F8"  +
        "\u00C4a\u0081\u0087\u00EAzn\u0098|\u00D1n\u00FC\u00146\u0087"     +
        "l\u00F1TA\u0007\u00BE\u00DE\u00EE\u0014V\u00E9\u00AF'\u00A0J"     +
        "\u00A4A<\u00F7\u00C8\u0099\u0092\u00EC\u00BA\u00E6\u00DDg\u0001"  +
        "m\u0015\u0016\u0082\u00EB\u00A8B\u00EE\u00DF\u00FD\u00BA`\u00B4"  +
        "\u00F1\u0090{u \u00E3\u0003\u000F$\u00D8\u00C2\u009E\u00E19g"     +
        ";\u00EF\u00A6?\u00B8q\u00870T\u00B6\u00F2\u00CF;\u009F2dB\u00CB"  +
        "\u0015\u00A4\u00CC\u00B0\u001AE\u0004\u00F1\u00E4}\u008D\u0084"   +
        "J\u001B\u00E5\u00BA\u00E7\u00DF\u00DCB\u00CB\u00DAp\u00CD}\u00AE" +
        "\nW\u00E8[z\u00D5?Z\u00F6 \u00CFM\u008C\u00CE\u00A4\u00D4(y\u00D1"+
        "0\u00A44\u0086\u00EB\u00FB3\u00D3\u00CD\u00DCw\u0085;S7\u00EF"    +
        "\u00FC\u00B5\u00C5\u0006\u0087x\u00E5\u0080\u00B3\u00E6Nh\u00B8"  +
        "\u00F4\u00C5\u00C8\u00B3~\r\u0080\u009E\u00A29\u008F\u00EB|\u0013"+
        "*O\u0094C\u00B7\u0095\u000E/\u00EE}\u001C\"6\u0013\u00BD\u00DD"   +
        "\u0006\u00CA\u00A27\u00DF\u0093+\u00C4$\u0082\u0089\u00AC\u00F3"  +
        "\u00EB\u00C3W\u0015\u00F6\u00B7\u00EF4x\u00DD\u00F2gao\u00C1"     +
        "H\u00CB\u00E4\u0090R\u0081^^A\u000F\u00AB\u00B4\u008A$e.\u00DA"   +
        "\u007F\u00A4\u00E8{@\u00E4\u00E9\u008E\u00A0\u0084X\u0089\u00E9"  +
        "\u00E1\u00EF\u00D3\u0090\u00FC\u00DD\u0007\u00D3[\u00DBHV\u0094"  +
        "8\u00D7\u00E5\u00B2Wr\u0001\u0001s\u000E\u00DE\u00BC[d1\u0013"    +
        "\u0094\u0091~OP</\u00BAdo\u0012\u0082u#\u00D2J\u00E0w\u0096\u0095"+
        "\u00F9\u00C1z\u008Fz[!!\u00D1\u0087\u00B8\u0096)&:M\u00BAQ\u000C" +
        "\u00DF\u0081\u00F4|\u009F\u00AD\u0011c\u00ED\u00EA{Ye\u001A\u0000"+
        "rn\u0011@0\u0092\u0000\u00DAmwJ\u000C\u00DDa\u00AD\u001FF\u0003"  +
        "`[\u00DF\u00B0\u009E\u00ED\u00C3d\"\u00EB\u00E6\u00A8\u00CE\u00E7"+
        "\u00D2\u008A\u00A0\u00E76\u00A0Ud\u00A6\u00B9\u0010\u00852\t"     +
        "\u00C7\u00EB\u008F7-\u00E7\u0005\u00CA\u0089QW\u000F\u00DF\t"     +
        "\u0082+\u00BDi\u001Al\u00AA\u0012\u00E4\u00F2\u0087E\u001C\u000F" +
        "\u00E0\u00F6\u00A2z:\u00DAH\u0019L\u00F1vO\rw\u001C+g\u00CD\u00B1"+
        "V5\r\u0083\u0084Y8\u00FA\u000FB9\u009E\u00F36\u0099{\u0007\u000E" +
        "\u0084\t=J\u00A9>a\u0083`\u00D8{\u001F\u00A9\u008B\u000C\u0011"   +
        "I8,\u00E9v%\u00A5\u0006\u0014\u00D1\u00B7\u000E%$K\u000Cv\u0083"  +
        "GX\u009E\u008D\u0082\r Y\u00D1\u00A4f\u00BB\u001E\u00F8\u00DA"    +
        "\n\u0082\u0004\u00F1\u00910\u00BAnN\u00C0\u0099&Qd\u001E\u00E7"   +
        "#\rP\u00B2\u00AD\u0080\u00EA\u00EEh\u0001\u008D\u00B2\u00A2\u0083"+
        "\u00EA\u008B\u00F5\u009E";


    /** 8 S-boxes */
    private static final int[] S0, S1, S2, S3, S4, S5, S6, S7, S8;


    /** 
     * Expand a String of compressed S-box data and return an
     * S-box with uncompressed data.
     */
    private static int[] expand(String in) 
    {
        int[] S = new int[256];
        for(int i=0, j=0; i<S.length; i++)
            S[i] = (in.charAt(j++) << 24) | 
                   (in.charAt(j++) << 16) |
                   (in.charAt(j++) <<  8) | 
                   (in.charAt(j++)      );
        return S;
    }


    /**
     * Initialize the S-boxes by expanding them from the compressed data.
     * Zero out the references (sS*) to the compressed data as we no
     * longer need them.
     */
    static 
    {
        S0 = expand(sS0); sS0 = null;
        S1 = expand(sS1); sS1 = null;
        S2 = expand(sS2); sS2 = null;
        S3 = expand(sS3); sS3 = null;
        S4 = expand(sS4); sS4 = null;
        S5 = expand(sS5); sS5 = null;
        S6 = expand(sS6); sS6 = null;
        S7 = expand(sS7); sS7 = null;
        S8 = expand(sS8); sS8 = null;
    }


// Instance variables
//............................................................................

    /** We are in decrypt mode */
    private boolean decrypt;
    
    /** Number of rounds (depends on key length) */
    private int rounds = DEFAULT_NOF_ROUNDS;

    /** Masking session keys. */
    private int
        Km0, Km1, Km2,  Km3,  Km4,  Km5,  Km6,  Km7,
        Km8, Km9, Km10, Km11, Km12, Km13, Km14, Km15;

    /** Rotation session keys. */
    private int
        Kr0, Kr1, Kr2,  Kr3,  Kr4,  Kr5,  Kr6,  Kr7,
        Kr8, Kr9, Kr10, Kr11, Kr12, Kr13, Kr14, Kr15;


// Constructors
//............................................................................

    public CAST5 () 
    {
        super(BLOCK_SIZE);
    }


// Implementation of abstract methods
//............................................................................

    /** Initializes this cipher using the specified key. */
    protected void coreInit(Key key, boolean decrypt)
    throws InvalidKeyException
    {
        this.decrypt = decrypt;
        makeKey(key);
    }


    /** Encrypt or decrypt a single data block */
    protected void coreCrypt(byte[] in, int inOffset, byte[] out, int outOffset)
    {
        if(decrypt)
            blockDecrypt(in, inOffset, out, outOffset);
        else
            blockEncrypt(in, inOffset, out, outOffset);
    }


// Private parts
//............................................................................

    /**
     * Expands a user key to a working CAST5 128-bit key --by
     * padding it with 0x00 if it's shorter than 16 bytes--
     * and generates the masking and rotation keypairs for
     * the block cipher.
     *
     * @param  key The user key object.
     * @exception  KeyException
     *     when one of the following occurs:<ul>
     *         <li>The user key object is null;
     *         <li>The decoded byte array form of the user key is
     *         zero long;
     *         <li>The decoded user key is shorter than 40 bits or
     *         longer than 128 bits.</ul>
     */
    private void makeKey (Key key)
    throws InvalidKeyException 
    {
        byte[] userkey = key.getEncoded();
        if (userkey == null)
            throw new InvalidKeyException("Null user key");

        int len = userkey.length;
        if (len < 5 || len > 16)
            throw new InvalidKeyException("Invalid user key length");

        rounds = (len < 11) ? MIN_NOF_ROUNDS : MAX_NOF_ROUNDS;

        byte[] kk = new byte[16];
        System.arraycopy(userkey, 0, kk, 0, len);

        int x0x1x2x3 = (kk[ 0] & 0xFF) << 24 | (kk[ 1] & 0xFF) << 16 |
                       (kk[ 2] & 0xFF) <<  8 | (kk[ 3] & 0xFF),
            x4x5x6x7 = (kk[ 4] & 0xFF) << 24 | (kk[ 5] & 0xFF) << 16 |
                       (kk[ 6] & 0xFF) <<  8 | (kk[ 7] & 0xFF),
            x8x9xAxB = (kk[ 8] & 0xFF) << 24 | (kk[ 9] & 0xFF) << 16 |
                       (kk[10] & 0xFF) <<  8 | (kk[11] & 0xFF),
            xCxDxExF = (kk[12] & 0xFF) << 24 | (kk[13] & 0xFF) << 16 |
                       (kk[14] & 0xFF) <<  8 | (kk[15] & 0xFF),
            z0z1z2z3, z4z5z6z7, z8z9zAzB, zCzDzEzF,
            z0, z1, z2, z3, z4, z5, z6, z7, z8, z9, zA, zB, zC, zD, zE, zF,
            x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, xA, xB, xC, xD, xE, xF;
        int[] b;

        b = unscramble(x0x1x2x3); x0 = b[0]; x1 = b[1]; x2 = b[2]; x3 = b[3];
        b = unscramble(x4x5x6x7); x4 = b[0]; x5 = b[1]; x6 = b[2]; x7 = b[3];
        b = unscramble(x8x9xAxB); x8 = b[0]; x9 = b[1]; xA = b[2]; xB = b[3];
        b = unscramble(xCxDxExF); xC = b[0]; xD = b[1]; xE = b[2]; xF = b[3];

        z0z1z2z3 = x0x1x2x3 ^ S5[xD] ^ S6[xF] ^ S7[xC] ^ S8[xE] ^ S7[x8];
        b = unscramble(z0z1z2z3); z0 = b[0]; z1 = b[1]; z2 = b[2]; z3 = b[3];
        z4z5z6z7 = x8x9xAxB ^ S5[z0] ^ S6[z2] ^ S7[z1] ^ S8[z3] ^ S8[xA];
        b = unscramble(z4z5z6z7); z4 = b[0]; z5 = b[1]; z6 = b[2]; z7 = b[3];
        z8z9zAzB = xCxDxExF ^ S5[z7] ^ S6[z6] ^ S7[z5] ^ S8[z4] ^ S5[x9];
        b = unscramble(z8z9zAzB); z8 = b[0]; z9 = b[1]; zA = b[2]; zB = b[3];
        zCzDzEzF = x4x5x6x7 ^ S5[zA] ^ S6[z9] ^ S7[zB] ^ S8[z8] ^ S6[xB];
        b = unscramble(zCzDzEzF); zC = b[0]; zD = b[1]; zE = b[2]; zF = b[3];

        Km0 = S5[z8] ^ S6[z9] ^ S7[z7] ^ S8[z6] ^ S5[z2];
        Km1 = S5[zA] ^ S6[zB] ^ S7[z5] ^ S8[z4] ^ S6[z6];
        Km2 = S5[zC] ^ S6[zD] ^ S7[z3] ^ S8[z2] ^ S7[z9];
        Km3 = S5[zE] ^ S6[zF] ^ S7[z1] ^ S8[z0] ^ S8[zC];

        x0x1x2x3 = z8z9zAzB ^ S5[z5] ^ S6[z7] ^ S7[z4] ^ S8[z6] ^ S7[z0];
        b = unscramble(x0x1x2x3); x0 = b[0]; x1 = b[1]; x2 = b[2]; x3 = b[3];
        x4x5x6x7 = z0z1z2z3 ^ S5[x0] ^ S6[x2] ^ S7[x1] ^ S8[x3] ^ S8[z2];
        b = unscramble(x4x5x6x7); x4 = b[0]; x5 = b[1]; x6 = b[2]; x7 = b[3];
        x8x9xAxB = z4z5z6z7 ^ S5[x7] ^ S6[x6] ^ S7[x5] ^ S8[x4] ^ S5[z1];
        b = unscramble(x8x9xAxB); x8 = b[0]; x9 = b[1]; xA = b[2]; xB = b[3];
        xCxDxExF = zCzDzEzF ^ S5[xA] ^ S6[x9] ^ S7[xB] ^ S8[x8] ^ S6[z3];
        b = unscramble(xCxDxExF); xC = b[0]; xD = b[1]; xE = b[2]; xF = b[3];

        Km4 = S5[x3] ^ S6[x2] ^ S7[xC] ^ S8[xD] ^ S5[x8];
        Km5 = S5[x1] ^ S6[x0] ^ S7[xE] ^ S8[xF] ^ S6[xD];
        Km6 = S5[x7] ^ S6[x6] ^ S7[x8] ^ S8[x9] ^ S7[x3];
        Km7 = S5[x5] ^ S6[x4] ^ S7[xA] ^ S8[xB] ^ S8[x7];

        z0z1z2z3 = x0x1x2x3 ^ S5[xD] ^ S6[xF] ^ S7[xC] ^ S8[xE] ^ S7[x8];
        b = unscramble(z0z1z2z3); z0 = b[0]; z1 = b[1]; z2 = b[2]; z3 = b[3];
        z4z5z6z7 = x8x9xAxB ^ S5[z0] ^ S6[z2] ^ S7[z1] ^ S8[z3] ^ S8[xA];
        b = unscramble(z4z5z6z7); z4 = b[0]; z5 = b[1]; z6 = b[2]; z7 = b[3];
        z8z9zAzB = xCxDxExF ^ S5[z7] ^ S6[z6] ^ S7[z5] ^ S8[z4] ^ S5[x9];
        b = unscramble(z8z9zAzB); z8 = b[0]; z9 = b[1]; zA = b[2]; zB = b[3];
        zCzDzEzF = x4x5x6x7 ^ S5[zA] ^ S6[z9] ^ S7[zB] ^ S8[z8] ^ S6[xB];
        b = unscramble(zCzDzEzF); zC = b[0]; zD = b[1]; zE = b[2]; zF = b[3];

        Km8 =  S5[z3] ^ S6[z2] ^ S7[zC] ^ S8[zD] ^ S5[z9];
        Km9 =  S5[z1] ^ S6[z0] ^ S7[zE] ^ S8[zF] ^ S6[zC];
        Km10 = S5[z7] ^ S6[z6] ^ S7[z8] ^ S8[z9] ^ S7[z2];
        Km11 = S5[z5] ^ S6[z4] ^ S7[zA] ^ S8[zB] ^ S8[z6];

        x0x1x2x3 = z8z9zAzB ^ S5[z5] ^ S6[z7] ^ S7[z4] ^ S8[z6] ^ S7[z0];
        b = unscramble(x0x1x2x3); x0 = b[0]; x1 = b[1]; x2 = b[2]; x3 = b[3];
        x4x5x6x7 = z0z1z2z3 ^ S5[x0] ^ S6[x2] ^ S7[x1] ^ S8[x3] ^ S8[z2];
        b = unscramble(x4x5x6x7); x4 = b[0]; x5 = b[1]; x6 = b[2]; x7 = b[3];
        x8x9xAxB = z4z5z6z7 ^ S5[x7] ^ S6[x6] ^ S7[x5] ^ S8[x4] ^ S5[z1];
        b = unscramble(x8x9xAxB); x8 = b[0]; x9 = b[1]; xA = b[2]; xB = b[3];
        xCxDxExF = zCzDzEzF ^ S5[xA] ^ S6[x9] ^ S7[xB] ^ S8[x8] ^ S6[z3];
        b = unscramble(xCxDxExF); xC = b[0]; xD = b[1]; xE = b[2]; xF = b[3];

        Km12 = S5[x8] ^ S6[x9] ^ S7[x7] ^ S8[x6] ^ S5[x3];
        Km13 = S5[xA] ^ S6[xB] ^ S7[x5] ^ S8[x4] ^ S6[x7];
        Km14 = S5[xC] ^ S6[xD] ^ S7[x3] ^ S8[x2] ^ S7[x8];
        Km15 = S5[xE] ^ S6[xF] ^ S7[x1] ^ S8[x0] ^ S8[xD];

        // The remaining half is identical to what is given above, carrying
        // on from the last created x0..xF to generate keys K17 - K32. These
        // keys will be used as the 'rotation' keys and as such only the five
        // least significant bits are to be considered.

        z0z1z2z3 = x0x1x2x3 ^ S5[xD] ^ S6[xF] ^ S7[xC] ^ S8[xE] ^ S7[x8];
        b = unscramble(z0z1z2z3); z0 = b[0]; z1 = b[1]; z2 = b[2]; z3 = b[3];
        z4z5z6z7 = x8x9xAxB ^ S5[z0] ^ S6[z2] ^ S7[z1] ^ S8[z3] ^ S8[xA];
        b = unscramble(z4z5z6z7); z4 = b[0]; z5 = b[1]; z6 = b[2]; z7 = b[3];
        z8z9zAzB = xCxDxExF ^ S5[z7] ^ S6[z6] ^ S7[z5] ^ S8[z4] ^ S5[x9];
        b = unscramble(z8z9zAzB); z8 = b[0]; z9 = b[1]; zA = b[2]; zB = b[3];
        zCzDzEzF = x4x5x6x7 ^ S5[zA] ^ S6[z9] ^ S7[zB] ^ S8[z8] ^ S6[xB];
        b = unscramble(zCzDzEzF); zC = b[0]; zD = b[1]; zE = b[2]; zF = b[3];

        Kr0 = (S5[z8] ^ S6[z9] ^ S7[z7] ^ S8[z6] ^ S5[z2]) & 0x1F;
        Kr1 = (S5[zA] ^ S6[zB] ^ S7[z5] ^ S8[z4] ^ S6[z6]) & 0x1F;
        Kr2 = (S5[zC] ^ S6[zD] ^ S7[z3] ^ S8[z2] ^ S7[z9]) & 0x1F;
        Kr3 = (S5[zE] ^ S6[zF] ^ S7[z1] ^ S8[z0] ^ S8[zC]) & 0x1F;

        x0x1x2x3 = z8z9zAzB ^ S5[z5] ^ S6[z7] ^ S7[z4] ^ S8[z6] ^ S7[z0];
        b = unscramble(x0x1x2x3); x0 = b[0]; x1 = b[1]; x2 = b[2]; x3 = b[3];
        x4x5x6x7 = z0z1z2z3 ^ S5[x0] ^ S6[x2] ^ S7[x1] ^ S8[x3] ^ S8[z2];
        b = unscramble(x4x5x6x7); x4 = b[0]; x5 = b[1]; x6 = b[2]; x7 = b[3];
        x8x9xAxB = z4z5z6z7 ^ S5[x7] ^ S6[x6] ^ S7[x5] ^ S8[x4] ^ S5[z1];
        b = unscramble(x8x9xAxB); x8 = b[0]; x9 = b[1]; xA = b[2]; xB = b[3];
        xCxDxExF = zCzDzEzF ^ S5[xA] ^ S6[x9] ^ S7[xB] ^ S8[x8] ^ S6[z3];
        b = unscramble(xCxDxExF); xC = b[0]; xD = b[1]; xE = b[2]; xF = b[3];

        Kr4 = (S5[x3] ^ S6[x2] ^ S7[xC] ^ S8[xD] ^ S5[x8]) & 0x1F;
        Kr5 = (S5[x1] ^ S6[x0] ^ S7[xE] ^ S8[xF] ^ S6[xD]) & 0x1F;
        Kr6 = (S5[x7] ^ S6[x6] ^ S7[x8] ^ S8[x9] ^ S7[x3]) & 0x1F;
        Kr7 = (S5[x5] ^ S6[x4] ^ S7[xA] ^ S8[xB] ^ S8[x7]) & 0x1F;

        z0z1z2z3 = x0x1x2x3 ^ S5[xD] ^ S6[xF] ^ S7[xC] ^ S8[xE] ^ S7[x8];
        b = unscramble(z0z1z2z3); z0 = b[0]; z1 = b[1]; z2 = b[2]; z3 = b[3];
        z4z5z6z7 = x8x9xAxB ^ S5[z0] ^ S6[z2] ^ S7[z1] ^ S8[z3] ^ S8[xA];
        b = unscramble(z4z5z6z7); z4 = b[0]; z5 = b[1]; z6 = b[2]; z7 = b[3];
        z8z9zAzB = xCxDxExF ^ S5[z7] ^ S6[z6] ^ S7[z5] ^ S8[z4] ^ S5[x9];
        b = unscramble(z8z9zAzB); z8 = b[0]; z9 = b[1]; zA = b[2]; zB = b[3];
        zCzDzEzF = x4x5x6x7 ^ S5[zA] ^ S6[z9] ^ S7[zB] ^ S8[z8] ^ S6[xB];
        b = unscramble(zCzDzEzF); zC = b[0]; zD = b[1]; zE = b[2]; zF = b[3];

        Kr8 =  (S5[z3] ^ S6[z2] ^ S7[zC] ^ S8[zD] ^ S5[z9]) & 0x1F;
        Kr9 =  (S5[z1] ^ S6[z0] ^ S7[zE] ^ S8[zF] ^ S6[zC]) & 0x1F;
        Kr10 = (S5[z7] ^ S6[z6] ^ S7[z8] ^ S8[z9] ^ S7[z2]) & 0x1F;
        Kr11 = (S5[z5] ^ S6[z4] ^ S7[zA] ^ S8[zB] ^ S8[z6]) & 0x1F;

        x0x1x2x3 = z8z9zAzB ^ S5[z5] ^ S6[z7] ^ S7[z4] ^ S8[z6] ^ S7[z0];
        b = unscramble(x0x1x2x3); x0 = b[0]; x1 = b[1]; x2 = b[2]; x3 = b[3];
        x4x5x6x7 = z0z1z2z3 ^ S5[x0] ^ S6[x2] ^ S7[x1] ^ S8[x3] ^ S8[z2];
        b = unscramble(x4x5x6x7); x4 = b[0]; x5 = b[1]; x6 = b[2]; x7 = b[3];
        x8x9xAxB = z4z5z6z7 ^ S5[x7] ^ S6[x6] ^ S7[x5] ^ S8[x4] ^ S5[z1];
        b = unscramble(x8x9xAxB); x8 = b[0]; x9 = b[1]; xA = b[2]; xB = b[3];
        xCxDxExF = zCzDzEzF ^ S5[xA] ^ S6[x9] ^ S7[xB] ^ S8[x8] ^ S6[z3];
        b = unscramble(xCxDxExF); xC = b[0]; xD = b[1]; xE = b[2]; xF = b[3];

        Kr12 = (S5[x8] ^ S6[x9] ^ S7[x7] ^ S8[x6] ^ S5[x3]) & 0x1F;
        Kr13 = (S5[xA] ^ S6[xB] ^ S7[x5] ^ S8[x4] ^ S6[x7]) & 0x1F;
        Kr14 = (S5[xC] ^ S6[xD] ^ S7[x3] ^ S8[x2] ^ S7[x8]) & 0x1F;
        Kr15 = (S5[xE] ^ S6[xF] ^ S7[x1] ^ S8[x0] ^ S8[xD]) & 0x1F;
    }


    /**
     * Assuming the input is a 32-bit block organised as: b31b30b29...b0,
     * returns an array of 4 Java ints, containing from position 0 onward
     * the values: {b31b30b29b28, b27b26b25b24, ... , b3b2b1b0}.
     *
     * @param  x    a 32-bit block
     * @return an array of 4 ints, each being the contents of an 8-bit
     *         block from the input.
     */
    private static final int[] unscramble (int x) 
    {
        return new int[]
          { (x >>> 24) & 0xFF, (x >>> 16) & 0xFF, (x >>> 8) & 0xFF, x & 0xFF };
    }


    /**
     * The full encryption algorithm is given in the following four steps.
     * <p>
     * INPUT:  plaintext m1...m64; key K = k1...k128.<br>
     * OUTPUT: ciphertext c1...c64.
     * <ol>
     *   <li> (key schedule) Compute 16 pairs of subkeys {Kmi, Kri}
     *        from a user key (see makeKey() method).
     *   <li> (L0,R0) <-- (m1...m64).  (Split the plaintext into left
     *        and right 32-bit halves L0 = m1...m32 and R0 = m33...m64.).
     *   <li> (16 rounds) for i from 1 to 16, compute Li and Ri as
     *        follows:
     *     <ul>
     *       <li> Li = Ri-1;
     *       <li> Ri = Li-1 ^ F(Ri-1,Kmi,Kri), where F is defined in
     *            method F() --f is of Type 1, Type 2, or Type 3, depending
     *            on i, and ^ being the bitwise XOR function.
     *     </ul>
     *   <li> c1...c64 <-- (R16,L16). (Exchange final blocks L16, R16
     *        and concatenate to form the ciphertext.)
     * </ol>
     * <p>
     * Decryption is identical to the encryption algorithm given
     * above, except that the rounds (and therefore the subkey pairs)
     * are used in reverse order to compute (L0,R0) from (R16,L16).
     * <p>
     * Looking at the iterations/rounds in pairs we have:
     * <pre>
     * (1a)    Li = Ri-1;
     * (1b)    Ri = Li-1 ^ Fi(Ri-1);
     * (2a)    Li+1 = Ri;
     * (2b)    Ri+1 = Li ^ Fi+1(Ri);
     * </pre>
     * which by substituting (2a) in (2b) becomes
     * <pre>
     * (2c)    Ri+1 = Li ^ Fi+1(Li+1);
     * </pre>
     * by substituting (1b) in (2a) and (1a) in (2c), we get:
     * <pre>
     * (3a)    Li+1 = Li-1 ^ Fi(Ri-1);
     * (3b)    Ri+1 = Ri-1 ^ Fi+1(Li+1);
     * </pre>
     * Using only one couple of variables L and R, initialised to L0 and
     * R0 respectively, the assignments for each pair of rounds become:
     * <pre>
     * (4a)    L ^= Fi(R);
     * (4b)    R ^= Fi+1(L);
     * </pre>
     *
     * @param  in      contains the plain-text 64-bit block.
     * @param  off     start index within input where data is considered.
     * @param  out     will contain the cipher-text block.
     * @param  outOff  index in out where cipher-text starts.
     */
    private void blockEncrypt (byte[] in, int off, byte[] out, int outOff) 
    {
        int L = (in[off++] & 0xFF) << 24 |
                (in[off++] & 0xFF) << 16 |
                (in[off++] & 0xFF) <<  8 |
                (in[off++] & 0xFF),
            R = (in[off++] & 0xFF) << 24 |
                (in[off++] & 0xFF) << 16 |
                (in[off++] & 0xFF) <<  8 |
                (in[off  ] & 0xFF);

        L ^= f1(R, Km0,  Kr0);
        R ^= f2(L, Km1,  Kr1);      // round 2
        L ^= f3(R, Km2,  Kr2);
        R ^= f1(L, Km3,  Kr3);      // round 4
        L ^= f2(R, Km4,  Kr4);
        R ^= f3(L, Km5,  Kr5);      // round 6
        L ^= f1(R, Km6,  Kr6);
        R ^= f2(L, Km7,  Kr7);      // round 8
        L ^= f3(R, Km8,  Kr8);
        R ^= f1(L, Km9,  Kr9);      // round 10
        L ^= f2(R, Km10, Kr10);
        R ^= f3(L, Km11, Kr11);     // round 12
        if (rounds == MAX_NOF_ROUNDS) 
        {
            L ^= f1(R, Km12, Kr12);
            R ^= f2(L, Km13, Kr13); // round 14
            L ^= f3(R, Km14, Kr14);
            R ^= f1(L, Km15, Kr15); // round 16
        }
        out[outOff++] = (byte)(R >>> 24);
        out[outOff++] = (byte)(R >>> 16);
        out[outOff++] = (byte)(R >>>  8);
        out[outOff++] = (byte) R;
        out[outOff++] = (byte)(L >>> 24);
        out[outOff++] = (byte)(L >>> 16);
        out[outOff++] = (byte)(L >>>  8);
        out[outOff  ] = (byte) L;
    }

    /**
     * Decrypts a 64-bit block by applying the formulae and sub-keys
     * in reverse order to that of the encryption.
     *
     * @param  input   contains the cipher-text 64-bit block.
     * @param  offset  start index within input where data is considered.
     * @param  out     will contain the plain-text block.
     * @param  outOff  index in out where plain-text starts.
     */
    private void blockDecrypt (byte[] in, int off, byte[] out, int outOff) 
    {
        int L = (in[off    ] & 0xFF) << 24 |
                (in[off + 1] & 0xFF) << 16 |
                (in[off + 2] & 0xFF) <<  8 |
                (in[off + 3] & 0xFF),
            R = (in[off + 4] & 0xFF) << 24 |
                (in[off + 5] & 0xFF) << 16 |
                (in[off + 6] & 0xFF) <<  8 |
                (in[off + 7] & 0xFF);

        if (rounds == MAX_NOF_ROUNDS) 
        {
            L ^= f1(R, Km15, Kr15);
            R ^= f3(L, Km14, Kr14);
            L ^= f2(R, Km13, Kr13);
            R ^= f1(L, Km12, Kr12);
        }
        L ^= f3(R, Km11, Kr11);
        R ^= f2(L, Km10, Kr10);
        L ^= f1(R, Km9,  Kr9);
        R ^= f3(L, Km8,  Kr8);
        L ^= f2(R, Km7,  Kr7);
        R ^= f1(L, Km6,  Kr6);
        L ^= f3(R, Km5,  Kr5);
        R ^= f2(L, Km4,  Kr4);
        L ^= f1(R, Km3,  Kr3);
        R ^= f3(L, Km2,  Kr2);
        L ^= f2(R, Km1,  Kr1);
        R ^= f1(L, Km0,  Kr0);

        out[outOff++] = (byte)(R >>> 24);
        out[outOff++] = (byte)(R >>> 16);
        out[outOff++] = (byte)(R >>>  8);
        out[outOff++] = (byte) R;
        out[outOff++] = (byte)(L >>> 24);
        out[outOff++] = (byte)(L >>> 16);
        out[outOff++] = (byte)(L >>>  8);
        out[outOff  ] = (byte) L;
    }

    private final int f1 (int I, int m, int r) 
    {
        I = m + I;
        I = I << r | I >>> (32 - r);
        return (((S1[(I >>> 24) & 0xFF]) ^ S2[(I >>> 16) & 0xFF]) - 
                                        S3[(I >>>  8) & 0xFF]) + S4[I & 0xFF];
    }
    
    private final int f2 (int I, int m, int r) 
    {
        I = m ^ I;
        I = I << r | I >>> (32 - r);
        return (((S1[(I >>> 24) & 0xFF]) - S2[(I >>> 16) & 0xFF]) + 
                                        S3[(I >>>  8) & 0xFF]) ^ S4[I & 0xFF];
    }
    private final int f3 (int I, int m, int r) 
    {
        I = m - I;
        I = I << r | I >>> (32 - r);
        return (((S1[(I >>> 24) & 0xFF]) + S2[(I >>> 16) & 0xFF]) ^ 
                                        S3[(I >>>  8) & 0xFF]) - S4[I & 0xFF];
    }
}
