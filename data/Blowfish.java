/* $Id: Blowfish.java,v 1.1 2004/01/19 02:03:50 rgrimm Exp $
 *
 * Ported to Java from the C-code reference implementation --part of
 * the SSL implementation 0.6.6-- written by Eric Young (eay@mincom.oz.au).
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
 * This class implements the Blowfish algorithm (standard, 16 round version).
 * Blowfish is a symmetric block cipher, with a 64-bit blocksize and a variable
 * key length (between 40 and 448 bits inclusive, in 8-bit increments).
 * <p>
 * References:<br>
 * <ul>
 * <li>Bruce Schneier,
 *     "Section 14.3 Blowfish,"
 *     Applied Cryptography, 2nd edition,
 *     John Wiley &amp; Sons, 1996</li>
 *
 * <li>Bruce Schneier,
 *     <a href="http://www.counterpane.com/bfsverlag.html">
 *     Description of a New Variable-Length Key, 64-Bit Cipher (Blowfish)</a>,
 *     Fast Software Encryption Cambridge Security Workshop Proceedings,
 *     Springer-Verlag, 1004, pp 191-204.</li>
 *
 * <li><a href="http://www.counterpane.com/blowfish.html">
 *     http://www.counterpane.com/blowfish.html</a></li>
 * </ul>
 * <p>
 * The implementation is heavily optimized (but we can still do better):<br>
 * <ul>
 * <li>The P-box and S-box data is encoded in a string to save on
 *     .class-file size</li>
 * <li>P-box entries are stored in individual integers Pxx</li>
 * <li>The loops have been unrolled
 * <li>Encryption & decryption use the same algorithm</li>
 * </ul>
 * <p>
 * Speed optimizations thanks to Peter Hjelt <mxv@iterate.com>.
 * Additional speed and size optimizations by gelderen <gelderen@cryptix.org>.
 *
 * @version $Revision: 1.1 $
 * @author  Systemics Ltd.
 * @author  David Hopwood
 * @author  Jeroen C. van Gelderen (gelderen@cryptix.org)
 * @author  Raif S. Naffah         (raif@cryptix.org)
 */
public final class Blowfish
extends BlockCipher 
{

// Static variables and constants
// ...................................................................

    /** Compressed initial values for the P-box and S-boxes */
    private static final String
    cP= "$?j\u0088\u0085\u00A3\u0008\u00D3\u0013\u0019\u008A.\u0003psD"     +
        "\u00A4\u00098\")\u009F1\u00D0\u0008.\u00FA\u0098\u00ECNl\u0089"    +
        "E(!\u00E68\u00D0\u0013w\u00BETf\u00CF4\u00E9\u000Cl\u00C0\u00AC"   +
        ")\u00B7\u00C9|P\u00DD?\u0084\u00D5\u00B5\u00B5G\u0009\u0017\u0092" +
        "\u0016\u00D5\u00D9\u0089y\u00FB\u001B",
    cS= "\u00D11\u000B\u00A6\u0098\u00DF\u00B5\u00AC/\u00FDr\u00DB\u00D0"     +
        "\u001A\u00DF\u00B7\u00B8\u00E1\u00AF\u00EDj&~\u0096\u00BA|\u0090E"   +
        "\u00F1,\u007F\u0099$\u00A1\u0099G\u00B3\u0091l\u00F7\u0008\u0001"    +
        "\u00F2\u00E2\u0085\u008E\u00FC\u0016ci \u00D8qWNi\u00A4X\u00FE"      +
        "\u00A3\u00F4\u0093=~\r\u0095t\u008Fr\u008E\u00B6Xq\u008B\u00CDX"     +
        "\u0082\u0015J\u00EE{T\u00A4\u001D\u00C2ZY\u00B5\u009C0\u00D59*\u00F2"+
        "`\u0013\u00C5\u00D1\u00B0#(`\u0085\u00F0\u00CAAy\u0018\u00B8\u00DB8" +
        "\u00EF\u008Ey\u00DC\u00B0`:\u0018\u000El\u009E\u000E\u008B\u00B0"    +
        "\u001E\u008A>\u00D7\u0015w\u00C1\u00BD1K'x\u00AF/\u00DAU`\\`\u00E6"  +
        "U%\u00F3\u00AAU\u00AB\u0094WH\u0098bc\u00E8\u0014@U\u00CA9j*\u00AB"  +
        "\u0010\u00B6\u00B4\u00CC\\4\u0011A\u00E8\u00CE\u00A1T\u0086\u00AF|r" +
        "\u00E9\u0093\u00B3\u00EE\u0014\u0011co\u00BC*+\u00A9\u00C5]t\u00181" +
        "\u00F6\u00CE\\>\u0016\u009B\u0087\u0093\u001E\u00AF\u00D6\u00BA3l$"  +
        "\u00CF\\z2S\u0081(\u0095\u0086w;\u008FH\u0098kK\u00B9\u00AF\u00C4"   +
        "\u00BF\u00E8\u001Bf(!\u0093a\u00D8\t\u00CC\u00FB!\u00A9\u0091H|"     +
        "\u00AC`]\u00EC\u00802\u00EF\u0084]]\u00E9\u0085u\u00B1\u00DC&#\u0002"+
        "\u00EBe\u001B\u0088#\u0089>\u0081\u00D3\u0096\u00AC\u00C5\u000Fmo"   +
        "\u00F3\u0083\u00F4B9.\u000BD\u0082\u00A4\u0084 \u0004i\u00C8\u00F0J" +
        "\u009E\u001F\u009B^!\u00C6hB\u00F6\u00E9l\u009Ag\u000C\u009Ca\u00AB" +
        "\u00D3\u0088\u00F0jQ\u00A0\u00D2\u00D8T/h\u0096\u000F\u00A7(\u00ABQ3"+
        "\u00A3n\u00EF\u000Bl\u0013z;\u00E4\u00BA;\u00F0P~\u00FB*\u0098\u00A1"+
        "\u00F1e\u001D9\u00AF\u0001vf\u00CAY>\u0082C\u000E\u0088\u008C\u00EE" +
        "\u0086\u0019Eo\u009F\u00B4}\u0084\u00A5\u00C3;\u008B^\u00BE\u00E0ou" +
        "\u00D8\u0085\u00C1 s@\u001AD\u009FV\u00C1j\u00A6N\u00D3\u00AAb6?w"   +
        "\u0006\u001B\u00FE\u00DFrB\u009B\u0002=7\u00D0\u00D7$\u00D0\n\u0012H"+
        "\u00DB\u000F\u00EA\u00D3I\u00F1\u00C0\u009B\u0007Sr\u00C9\u0080"     +
        "\u0099\u001B{%\u00D4y\u00D8\u00F6\u00E8\u00DE\u00F7\u00E3\u00FEP"    +
        "\u001A\u00B6yL;\u0097l\u00E0\u00BD\u0004\u00C0\u0006\u00BA\u00C1"    +
        "\u00A9O\u00B6@\u009F`\u00C4^\\\u009E\u00C2\u0019j$ch\u00FBo\u00AF>lS"+
        "\u00B5\u00139\u00B2\u00EB;R\u00ECom\u00FCQ\u001F\u009B0\u0095,\u00CC"+
        "\u0081ED\u00AF^\u00BD\t\u00BE\u00E3\u00D0\u0004\u00DE3J\u00FDf\u000F"+
        "(\u0007\u0019.K\u00B3\u00C0\u00CB\u00A8WE\u00C8t\u000F\u00D2\u000B_9"+
        "\u00B9\u00D3\u00FB\u00DBUy\u00C0\u00BD\u001A`2\n\u00D6\u00A1\u0000"  +
        "\u00C6@,ryg\u009F%\u00FE\u00FB\u001F\u00A3\u00CC\u008E\u00A5\u00E9"  +
        "\u00F8\u00DB2\"\u00F8<u\u0016\u00DF\u00FDak\u0015/P\u001E\u00C8"     +
        "\u00AD\u0005R\u00AB2=\u00B5\u00FA\u00FD#\u0087`S1{H>\u0000\u00DF"    +
        "\u0082\u009E\\W\u00BB\u00CAo\u008C\u00A0\u001A\u0087V.\u00DF\u0017i" +
        "\u00DB\u00D5B\u00A8\u00F6(~\u00FF\u00C3\u00ACg2\u00C6\u008COUsi['"   +
        "\u00B0\u00BB\u00CAX\u00C8\u00E1\u00FF\u00A3]\u00B8\u00F0\u0011\u00A0"+
        "\u0010\u00FA=\u0098\u00FD!\u0083\u00B8J\u00FC\u00B5l-\u00D1\u00D3["  +
        "\u009AS\u00E4y\u00B6\u00F8Ee\u00D2\u008EI\u00BCK\u00FB\u0097\u0090"  +
        "\u00E1\u00DD\u00F2\u00DA\u00A4\u00CB~3b\u00FB\u0013A\u00CE\u00E4"    +
        "\u00C6\u00E8\u00EF \u00CA\u00DA6wL\u0001\u00D0~\u009E\u00FE+\u00F1"  +
        "\u001F\u00B4\u0095\u00DB\u00DAM\u00AE\u0090\u0091\u0098\u00EA\u00AD" +
        "\u008Eqk\u0093\u00D5\u00A0\u00D0\u008E\u00D1\u00D0\u00AF\u00C7%"     +
        "\u00E0\u008E<[/\u008Eu\u0094\u00B7\u008F\u00F6\u00E2\u00FB\u00F2"    +
        "\u0012+d\u0088\u0088\u00B8\u0012\u0090\r\u00F0\u001CO\u00AD^\u00A0h" +
        "\u008F\u00C3\u001C\u00D1\u00CF\u00F1\u0091\u00B3\u00A8\u00C1\u00AD//"+
        "\"\u0018\u00BE\u000E\u0017w\u00EAu-\u00FE\u008B\u0002\u001F\u00A1"   +
        "\u00E5\u00A0\u00CC\u000F\u00B5ot\u00E8\u0018\u00AC\u00F3\u00D6\u00CE"+
        "\u0089\u00E2\u0099\u00B4\u00A8O\u00E0\u00FD\u0013\u00E0\u00B7|\u00C4"+
        ";\u0081\u00D2\u00AD\u00A8\u00D9\u0016_\u00A2f\u0080\u0095w\u0005"    +
        "\u0093\u00CCs\u0014!\u001A\u0014w\u00E6\u00AD ew\u00B5\u00FA\u0086"  +
        "\u00C7TB\u00F5\u00FB\u009D5\u00CF\u00EB\u00CD\u00AF\u000C{>\u0089"   +
        "\u00A0\u00D6A\u001B\u00D3\u00AE\u001E~I\u0000%\u000E- q\u00B3^\"h"   +
        "\u0000\u00BBW\u00B8\u00E0\u00AF$d6\u009B\u00F0\t\u00B9\u001EUc\u0091"+
        "\u001DY\u00DF\u00A6\u00AAx\u00C1C\u0089\u00D9ZS\u007F }[\u00A2\u0002"+
        "\u00E5\u00B9\u00C5\u0083&\u0003vb\u0095\u00CF\u00A9\u0011\u00C8"     +
        "\u0019hNsJA\u00B3G-\u00CA{\u0014\u00A9J\u001BQ\u0000R\u009AS)\u0015" +
        "\u00D6\u000FW?\u00BC\u009B\u00C6\u00E4+`\u00A4v\u0081\u00E6t\u0000"  +
        "\u0008\u00BAo\u00B5W\u001B\u00E9\u001F\u00F2\u0096\u00ECk*\r\u00D9"  +
        "\u0015\u00B6ce!\u00E7\u00B9\u00F9\u00B6\u00FF4\u0005.\u00C5\u0085VdS"+
        "\u00B0-]\u00A9\u009F\u008F\u00A1\u0008\u00BAG\u0099n\u0085\u0007j"   +
        "Kzp\u00E9\u00B5\u00B3)D\u00DBu\t.\u00C4\u0019&#\u00ADn\u00A6\u00B0"  +
        "I\u00A7\u00DF}\u009C\u00EE`\u00B8\u008F\u00ED\u00B2f\u00EC\u00AA"    +
        "\u008Cqi\u009A\u0017\u00FFVdRl\u00C2\u00B1\u009E\u00E1\u00196\u0002" +
        "\u00A5u\tL)\u00A0Y\u0013@\u00E4\u0018:>?T\u0098\u009A[B\u009Dek"     +
        "\u008F\u00E4\u00D6\u0099\u00F7?\u00D6\u00A1\u00D2\u009C\u0007\u00EF" +
        "\u00E80\u00F5M-8\u00E6\u00F0%]\u00C1L\u00DD \u0086\u0084p\u00EB&c"   +
        "\u0082\u00E9\u00C6\u0002\u001E\u00CC^\thk?>\u00BA\u00EF\u00C9<\u0097"+
        "\u0018\u0014kjp\u00A1h\u007F5\u0084R\u00A0\u00E2\u0086\u00B7\u009CS" +
        "\u0005\u00AAP\u00077>\u0007\u0084\u001C\u007F\u00DE\u00AE\\\u008E}D" +
        "\u00ECW\u0016\u00F2\u00B8\u00B0:\u00DA7\u00F0P\u000C\r\u00F0\u001C"  +
        "\u001F\u0004\u0002\u0000\u00B3\u00FF\u00AE\u000C\u00F5\u001A<\u00B5t"+
        "\u00B2%\u0083zX\u00DC\t!\u00BD\u00D1\u0091\u0013\u00F9|\u00A9/\u00F6"+
        "\u00942Gs\"\u00F5G\u0001:\u00E5\u00E5\u00817\u00C2\u00DA\u00DC\u00C8"+
        "\u00B5v4\u009A\u00F3\u00DD\u00A7\u00A9DaF\u000F\u00D0\u0003\u000E"   +
        "\u00EC\u00C8\u00C7>\u00A4u\u001EA\u00E28\u00CD\u0099;\u00EA\u000E/"  +
        "2\u0080\u00BB\u00A1\u0018>\u00B31NT\u008B8Om\u00B9\u0008oB\r\u0003"  +
        "\u00F6\n\u0004\u00BF,\u00B8\u0012\u0090$\u0097|yVy\u00B0r\u00BC"     +
        "\u00AF\u0089\u00AF\u00DE\u009Aw\u001F\u00D9\u0093\u0008\u0010\u00B3" +
        "\u008B\u00AE\u0012\u00DC\u00CF?.U\u0012r\u001F.kq$P\u001A\u00DD"     +
        "\u00E6\u009F\u0084\u00CD\u0087zXG\u0018t\u0008\u00DA\u0017\u00BC"    +
        "\u009F\u009A\u00BC\u00E9K}\u008C\u00ECz\u00EC:\u00DB\u0085\u001D"    +
        "\u00FAc\tCf\u00C4d\u00C3\u00D2\u00EF\u001C\u0018G2\u0015\u00D9\u0008"+
        "\u00DDC;7$\u00C2\u00BA\u0016\u0012\u00A1MC*e\u00C4QP\u0094\u0000"    +
        "\u0002\u0013:\u00E4\u00DDq\u00DF\u00F8\u009E\u00101NU\u0081\u00ACw"  +
        "\u00D6_\u0011\u0019\u009B\u00045V\u00F1\u00D7\u00A3\u00C7k<\u0011"   +
        "\u0018;Y$\u00A5\t\u00F2\u008F\u00E6\u00ED\u0097\u00F1\u00FB\u00FA"   +
        "\u009E\u00BA\u00BF,\u001E\u0015<n\u0086\u00E3Ep\u00EA\u00E9o\u00B1"  +
        "\u0086\u000E^\nZ>*\u00B3w\u001F\u00E7\u001CN=\u0006\u00FA)e\u00DC"   +
        "\u00B9\u0099\u00E7\u001D\u000F\u0080>\u0089\u00D6Rf\u00C8%.L\u00C9x" +
        "\u009C\u0010\u00B3j\u00C6\u0015\u000E\u00BA\u0094\u00E2\u00EAx\u00A5"+
        "\u00FC<S\u001E\n-\u00F4\u00F2\u00F7N\u00A76\u001D+=\u00199&\u000F"   +
        "\u0019\u00C2y`R#\u00A7\u0008\u00F7\u0013\u0012\u00B6\u00EB\u00AD"    +
        "\u00FEn\u00EA\u00C3\u001Ff\u00E3\u00BCE\u0095\u00A6{\u00C8\u0083"    +
        "\u00B1\u007F7\u00D1\u0001\u008C\u00FF(\u00C32\u00DD\u00EF\u00BElZ"   +
        "\u00A5eX!\u0085h\u00AB\u0098\u0002\u00EE\u00CE\u00A5\u000F\u00DB/"   +
        "\u0095;*\u00EF}\u00AD[n/\u0084\u0015!\u00B6()\u0007ap\u00EC\u00DDGu" +
        "a\u009F\u0015\u0010\u0013\u00CC\u00A80\u00EBa\u00BD\u0096\u00034"    +
        "\u00FE\u001E\u00AA\u0003c\u00CF\u00B5s\\\u0090Lp\u00A29\u00D5\u009E" +
        "\u009E\u000B\u00CB\u00AA\u00DE\u0014\u00EE\u00CC\u0086\u00BC`b,"     +
        "\u00A7\u009C\u00AB\\\u00AB\u00B2\u00F3\u0084nd\u008B\u001E\u00AF"    +
        "\u0019\u00BD\u00F0\u00CA\u00A0#i\u00B9eZ\u00BBP@hZ2<*\u00B4\u00B31"  +
        "\u009E\u00E9\u00D5\u00C0!\u00B8\u00F7\u009BT\u000B\u0019\u0087_"     +
        "\u00A0\u0099\u0095\u00F7\u0099~b=}\u00A8\u00F87\u0088\u009A\u0097"   +
        "\u00E3-w\u0011\u00ED\u0093_\u0016h\u0012\u0081\u000E5\u0088)\u00C7"  +
        "\u00E6\u001F\u00D6\u0096\u00DE\u00DF\u00A1xX\u00BA\u0099W\u00F5"     +
        "\u0084\u00A5\u001B\"rc\u009B\u0083\u00C3\u00FF\u001A\u00C2F\u0096"   +
        "\u00CD\u00B3\n\u00EBS.0T\u008F\u00D9H\u00E4m\u00BC1(X\u00EB\u00F2"   +
        "\u00EF4\u00C6\u00FF\u00EA\u00FE(\u00EDa\u00EE|<s]J\u0014\u00D9\u00E8"+
        "d\u00B7\u00E3B\u0010]\u0014 >\u0013\u00E0E\u00EE\u00E2\u00B6\u00A3"  +
        "\u00AA\u00AB\u00EA\u00DBlO\u0015\u00FA\u00CBO\u00D0\u00C7B\u00F4B"   +
        "\u00EFj\u00BB\u00B5eO;\u001DA\u00CD!\u0005\u00D8\u001Ey\u009E\u0086" +
        "\u0085M\u00C7\u00E4KGj=\u0081bP\u00CFb\u00A1\u00F2[\u008D&F\u00FC"   +
        "\u0088\u0083\u00A0\u00C1\u00C7\u00B6\u00A3\u007F\u0015$\u00C3i\u00CB"+
        "t\u0092G\u0084\u008A\u000BV\u0092\u00B2\u0085\t[\u00BF\u0000\u00AD"  +
        "\u0019H\u009D\u0014b\u00B1t#\u0082\u000E\u0000XB\u008D*\u000CU\u00F5"+
        "\u00EA\u001D\u00AD\u00F4>#?pa3r\u00F0\u0092\u008D\u0093~A\u00D6_"    +
        "\u00EC\u00F1l\";\u00DB|\u00DE7Y\u00CB\u00EEt`@\u0085\u00F2\u00A7"    +
        "\u00CEw2n\u00A6\u0007\u0080\u0084\u0019\u00F8P\u009E\u00E8\u00EF"    +
        "\u00D8Ua\u00D9\u00975\u00A9i\u00A7\u00AA\u00C5\u000C\u0006\u00C2Z"   +
        "\u0004\u00AB\u00FC\u0080\u000B\u00CA\u00DC\u009EDz.\u00C3E4\u0084"   +
        "\u00FD\u00D5g\u0005\u000E\u001E\u009E\u00C9\u00DBs\u00DB\u00D3\u0010"+
        "U\u0088\u00CDg_\u00DAy\u00E3gC@\u00C5\u00C44eq>8\u00D8=(\u00F8\u009E"+
        "\u00F1m\u00FF \u0015>!\u00E7\u008F\u00B0=J\u00E6\u00E3\u009F+\u00DB" +
        "\u0083\u00AD\u00F7\u00E9=Zh\u0094\u0081@\u00F7\u00F6L&\u001C\u0094i)"+
        "4A\u0015 \u00F7v\u0002\u00D4\u00F7\u00BC\u00F4k.\u00D4\u00A2\u0000h" +
        "\u00D4\u0008$q3 \u00F4jC\u00B7\u00D4\u00B7P\u0000a\u00AF\u001E9"     +
        "\u00F6.\u0097$EF\u0014!Ot\u00BF\u008B\u0088@M\u0095\u00FC\u001D"     +
        "\u0096\u00B5\u0091\u00AFp\u00F4\u00DD\u00D3f\u00A0/E\u00BF\u00BC\t"  +
        "\u00EC\u0003\u00BD\u0097\u0085\u007F\u00ACm\u00D01\u00CB\u0085\u0004"+
        "\u0096\u00EB'\u00B3U\u00FD9A\u00DA%G\u00E6\u00AB\u00CA\n\u009A(Px%S" +
        "\u0004)\u00F4\n,\u0086\u00DA\u00E9\u00B6m\u00FBh\u00DC\u0014b\u00D7H"+
        "i\u0000h\u000E\u00C0\u00A4'\u00A1\u008D\u00EEO?\u00FE\u00A2\u00E8"   +
        "\u0087\u00AD\u008C\u00B5\u008C\u00E0\u0006z\u00F4\u00D6\u00B6\u00AA" +
        "\u00CE\u001E|\u00D37_\u00EC\u00CEx\u00A3\u0099@k*B \u00FE\u009E5"    +
        "\u00D9\u00F3\u0085\u00B9\u00EE9\u00D7\u00AB;\u0012N\u008B\u001D"     +
        "\u00C9\u00FA\u00F7Km\u0018V&\u00A3f1\u00EA\u00E3\u0097\u00B2:n\u00FA"+
        "t\u00DD[C2hA\u00E7\u00F7\u00CAx \u00FB\u00FB\n\u00F5N\u00D8\u00FE"   +
        "\u00B3\u0097E@V\u00AC\u00BAH\u0095'US:: \u0083\u008D\u0087\u00FEk"   +
        "\u00A9\u00B7\u00D0\u0096\u0095KU\u00A8g\u00BC\u00A1\u0015\u009AX"    +
        "\u00CC\u00A9)c\u0099\u00E1\u00DB3\u00A6*JV?1%\u00F9^\u00F4~\u001C"   +
        "\u0090)1|\u00FD\u00F8\u00E8\u0002\u0004'/p\u0080\u00BB\u0015\\\u0005"+
        "(,\u00E3\u0095\u00C1\u0015H\u00E4\u00C6m\"H\u00C1\u0013?\u00C7\u000F"+
        "\u0086\u00DC\u0007\u00F9\u00C9\u00EEA\u0004\u001F\u000F@Gy\u00A4]"   +
        "\u0088n\u00172_Q\u00EB\u00D5\u009B\u00C0\u00D1\u00F2\u00BC\u00C1"    +
        "\u008FA\u00115d%{x4`*\u009C`\u00DF\u00F8\u00E8\u00A3\u001Fcl\u001B"  +
        "\u000E\u0012\u00B4\u00C2\u0002\u00E12\u009E\u00AFfO\u00D1\u00CA"     +
        "\u00D1\u0081\u0015k#\u0095\u00E03>\u0092\u00E1;$\u000Bb\u00EE\u00BE" +
        "\u00B9\"\u0085\u00B2\u00A2\u000E\u00E6\u00BA\r\u0099\u00DEr\u000C"   +
        "\u008C-\u00A2\u00F7(\u00D0\u0012xE\u0095\u00B7\u0094\u00FDd}\u0008b" +
        "\u00E7\u00CC\u00F5\u00F0TI\u00A3o\u0087}H\u00FA\u00C3\u009D\u00FD'"  +
        "\u00F3>\u008D\u001E\nGcA\u0099.\u00FFt:on\u00AB\u00F4\u00F8\u00FD7"  +
        "\u00A8\u0012\u00DC`\u00A1\u00EB\u00DD\u00F8\u0099\u001B\u00E1L\u00DB"+
        "nk\r\u00C6{U\u0010mg,7'e\u00D4;\u00DC\u00D0\u00E8\u0004\u00F1)\r"    +
        "\u00C7\u00CC\u0000\u00FF\u00A3\u00B59\u000F\u0092i\u000F\u00ED\u000B"+
        "f{\u009F\u00FB\u00CE\u00DB}\u009C\u00A0\u0091\u00CF\u000B\u00D9"     +
        "\u0015^\u00A3\u00BB\u0013/\u0088Q[\u00AD${\u0094y\u00BFv;\u00D6"     +
        "\u00EB79.\u00B3\u00CC\u0011Yy\u0080&\u00E2\u0097\u00F4.1-hB\u00AD"   +
        "\u00A7\u00C6j+;\u0012uL\u00CCx.\u00F1\u001Cj\u0012B7\u00B7\u0092Q"   +
        "\u00E7\u0006\u00A1\u00BB\u00E6K\u00FBcP\u001Ak\u0010\u0018\u0011"    +
        "\u00CA\u00ED\u00FA=%\u00BD\u00D8\u00E2\u00E1\u00C3\u00C9DB\u0016Y\n" +
        "\u0012\u0013\u0086\u00D9\u000C\u00ECn\u00D5\u00AB\u00EA*d\u00AFgN"   +
        "\u00DA\u0086\u00A8_\u00BE\u00BF\u00E9\u0088d\u00E4\u00C3\u00FE\u009D"+
        "\u00BC\u0080W\u00F0\u00F7\u00C0\u0086`x{\u00F8`\u0003`M\u00D1\u00FD" +
        "\u0083F\u00F68\u001F\u00B0wE\u00AE\u0004\u00D76\u00FC\u00CC\u0083Bk3"+
        "\u00F0\u001E\u00ABq\u00B0\u0080A\u0087<\u0000^_w\u00A0W\u00BE\u00BD" +
        "\u00E8\u00AE$UFB\u0099\u00BFX.aNX\u00F4\u008F\u00F2\u00DD\u00FD"     +
        "\u00A2\u00F4t\u00EF8\u0087\u0089\u00BD\u00C2Sf\u00F9\u00C3\u00C8"    +
        "\u00B3\u008Et\u00B4u\u00F2UF\u00FC\u00D9\u00B9z\u00EB&a\u008B\u001D" +
        "\u00DF\u0084\u0084j\u000Ey\u0091_\u0095\u00E2FnY\u008E \u00B4Wp"     +
        "\u008C\u00D5U\u0091\u00C9\u0002\u00DEL\u00B9\u000B\u00AC\u00E1\u00BB"+
        "\u0082\u0005\u00D0\u0011\u00A8bHut\u00A9\u009E\u00B7\u007F\u0019"    +
        "\u00B6\u00E0\u00A9\u00DC\tf-\t\u00A1\u00C42F3\u00E8Z\u001F\u0002\t"  +
        "\u00F0\u00BE\u008CJ\u0099\u00A0%\u001Dn\u00FE\u0010\u001A\u00B9="    +
        "\u001D\u000B\u00A5\u00A4\u00DF\u00A1\u0086\u00F2\u000F(h\u00F1i"     +
        "\u00DC\u00B7\u00DA\u0083W9\u0006\u00FE\u00A1\u00E2\u00CE\u009BO"     +
        "\u00CD\u007FRP\u0011^\u0001\u00A7\u0006\u0083\u00FA\u00A0\u0002"     +
        "\u00B5\u00C4\r\u00E6\u00D0'\u009A\u00F8\u008C'w?\u0086A\u00C3`L"     +
        "\u0006a\u00A8\u0006\u00B5\u00F0\u0017z(\u00C0\u00F5\u0086\u00E0"     +
        "\u0000`X\u00AA0\u00DC}b\u0011\u00E6\u009E\u00D7#8\u00EAcS\u00C2"     +
        "\u00DD\u0094\u00C2\u00C2\u00164\u00BB\u00CB\u00EEV\u0090\u00BC\u00B6"+
        "\u00DE\u00EB\u00FC}\u00A1\u00CEY\u001Dvo\u0005\u00E4\tK|\u0001\u0088"+
        "9r\n=|\u0092|$\u0086\u00E3r_rM\u009D\u00B9\u001A\u00C1[\u00B4\u00D3" +
        "\u009E\u00B8\u00FC\u00EDTUx\u0008\u00FC\u00A5\u00B5\u00D8=|\u00D3M"  +
        "\u00AD\u000F\u00C4\u001EP\u00EF^\u00B1a\u00E6\u00F8\u00A2\u0085"     +
        "\u0014\u00D9lQ\u0013<o\u00D5\u00C7\u00E7V\u00E1N\u00C46*\u00BF\u00CE"+
        "\u00DD\u00C6\u00C87\u00D7\u009A24\u0092c\u0082\u0012g\u000E\u00FA"   +
        "\u008E@`\u0000\u00E0:9\u00CE7\u00D3\u00FA\u00F5\u00CF\u00AB\u00C2w7Z"+
        "\u00C5-\u001B\\\u00B0g\u009EO\u00A37B\u00D3\u0082'@\u0099\u00BC"     +
        "\u009B\u00BE\u00D5\u0011\u008E\u009D\u00BF\u000Fs\u0015\u00D6-\u001C"+
        "~\u00C7\u0000\u00C4{\u00B7\u008C\u001Bk!\u00A1\u0090E\u00B2n\u00B1"  +
        "\u00BEj6n\u00B4WH\u00AB/\u00BC\u0094ny\u00C6\u00A3v\u00D2eI\u00C2"   +
        "\u00C8S\u000F\u00F8\u00EEF\u008D\u00DE}\u00D5s\n\u001DL\u00D0M\u00C6"+
        ")9\u00BB\u00DB\u00A9\u00BAFP\u00AC\u0095&\u00E8\u00BE^\u00E3\u0004"  +
        "\u00A1\u00FA\u00D5\u00F0j-Q\u009Ac\u00EF\u008C\u00E2\u009A\u0086"    +
        "\u00EE\"\u00C0\u0089\u00C2\u00B8C$.\u00F6\u00A5\u001E\u0003\u00AA"   +
        "\u009C\u00F2\u00D0\u00A4\u0083\u00C0a\u00BA\u009B\u00E9jM\u008F"     +
        "\u00E5\u0015P\u00BAd[\u00D6(&\u00A2\u00F9\u00A7::\u00E1K\u00A9\u0095"+
        "\u0086\u00EFUb\u00E9\u00C7/\u00EF\u00D3\u00F7R\u00F7\u00DA?\u0004oiw"+
        "\u00FA\nY\u0080\u00E4\u00A9\u0015\u0087\u00B0\u0086\u0001\u009B\t"   +
        "\u00E6\u00AD;>\u00E5\u0093\u00E9\u0090\u00FDZ\u009E4\u00D7\u0097,"   +
        "\u00F0\u00B7\u00D9\u0002+\u008BQ\u0096\u00D5\u00AC:\u0001}\u00A6}"   +
        "\u00D1\u00CF>\u00D6|}-(\u001F\u009F%\u00CF\u00AD\u00F2\u00B8\u009BZ" +
        "\u00D6\u00B4rZ\u0088\u00F5L\u00E0)\u00ACq\u00E0\u0019\u00A5\u00E6G"  +
        "\u00B0\u00AC\u00FD\u00ED\u0093\u00FA\u009B\u00E8\u00D3\u00C4\u008D(;"+
        "W\u00CC\u00F8\u00D5f)y\u0013.(x_\u0001\u0091\u00EDu`U\u00F7\u0096"   +
        "\u000ED\u00E3\u00D3^\u008C\u0015\u0005m\u00D4\u0088\u00F4m\u00BA"    +
        "\u0003\u00A1a%\u0005d\u00F0\u00BD\u00C3\u00EB\u009E\u0015<\u0090W"   +
        "\u00A2\u0097'\u001A\u00EC\u00A9:\u0007*\u001B?m\u009B\u001Ec!\u00F5" +
        "\u00F5\u009Cf\u00FB&\u00DC\u00F3\u0019u3\u00D9(\u00B1U\u00FD\u00F5"  +
        "\u0003V4\u0082\u008A\u00BA<\u00BB(Qw\u0011\u00C2\n\u00D9\u00F8\u00AB"+
        "\u00CCQg\u00CC\u00AD\u0092_M\u00E8\u0017Q80\u00DC\u008E7\u009DXb"    +
        "\u0093 \u00F9\u0091\u00EAz\u0090\u00C2\u00FB>{\u00CEQ!\u00CEdwO"     +
        "\u00BE2\u00A8\u00B6\u00E3~\u00C3)=FH\u00DESid\u0013\u00E6\u0080"     +
        "\u00A2\u00AE\u0008\u0010\u00DDm\u00B2$i\u0085-\u00FD\t\u0007!f\u00B3"+
        "\u009AF\ndE\u00C0\u00DDXl\u00DE\u00CF\u001C \u00C8\u00AE[\u00BE"     +
        "\u00F7\u00DD\u001BX\u008D@\u00CC\u00D2\u0001\u007Fk\u00B4\u00E3"     +
        "\u00BB\u00DD\u00A2j~:Y\u00FFE>5\nD\u00BC\u00B4\u00CD\u00D5r\u00EA"   +
        "\u00CE\u00A8\u00FAd\u0084\u00BB\u008Df\u0012\u00AE\u00BF<oG\u00D2"   +
        "\u009B\u00E4cT/]\u009E\u00AE\u00C2w\u001B\u00F6Ncpt\u000E\r\u008D"   +
        "\u00E7[\u0013W\u00F8r\u0016q\u00AFS}]@@\u00CB\u0008N\u00B4\u00E2"    +
        "\u00CC4\u00D2Fj\u0001\u0015\u00AF\u0084\u00E1\u00B0\u0004(\u0095"    +
        "\u0098:\u001D\u0006\u00B8\u009F\u00B4\u00CEn\u00A0Ho?;\u00825 \u00AB"+
        "\u0082\u0001\u001A\u001DK'r'\u00F8a\u0015`\u00B1\u00E7\u0093?\u00DC" +
        "\u00BB:y+4E%\u00BD\u00A0\u00889\u00E1Q\u00CEyK/2\u00C9\u00B7\u00A0"  +
        "\u001F\u00BA\u00C9\u00E0\u001C\u00C8~\u00BC\u00C7\u00D1\u00F6\u00CF" +
        "\u0001\u0011\u00C3\u00A1\u00E8\u00AA\u00C7\u001A\u0090\u0087I\u00D4O"+
        "\u00BD\u009A\u00D0\u00DA\u00DE\u00CB\u00D5\n\u00DA8\u00039\u00C3*"   +
        "\u00C6\u00916g\u008D\u00F91|\u00E0\u00B1+O\u00F7\u009EY\u00B7C\u00F5"+
        "\u00BB:\u00F2\u00D5\u0019\u00FF'\u00D9E\u009C\u00BF\u0097\",\u0015"  +
        "\u00E6\u00FC*\u000F\u0091\u00FCq\u009B\u0094\u0015%\u00FA\u00E5"     +
        "\u0093a\u00CE\u00B6\u009C\u00EB\u00C2\u00A8dY\u0012\u00BA\u00A8"     +
        "\u00D1\u00B6\u00C1\u0007^\u00E3\u0005j\u000C\u0010\u00D2Pe\u00CB"    +
        "\u0003\u00A4B\u00E0\u00ECn\u000E\u0016\u0098\u00DB;L\u0098\u00A0"    +
        "\u00BE2x\u00E9d\u009F\u001F\u00952\u00E0\u00D3\u0092\u00DF\u00D3"    +
        "\u00A04+\u0089q\u00F2\u001E\u001B\ntAK\u00A34\u008C\u00C5\u00BEq "   +
        "\u00C3v2\u00D8\u00DF5\u009F\u008D\u009B\u0099/.\u00E6\u000BoG\u000F" +
        "\u00E3\u00F1\u001D\u00E5L\u00DAT\u001E\u00DA\u00D8\u0091\u00CEby"    +
        "\u00CF\u00CD>~o\u0016\u0018\u00B1f\u00FD,\u001D\u0005\u0084\u008F"   +
        "\u00D2\u00C5\u00F6\u00FB\"\u0099\u00F5#\u00F3W\u00A62v#\u0093\u00A8" +
        "51V\u00CC\u00CD\u0002\u00AC\u00F0\u0081bZu\u00EB\u00B5n\u00166\u0097"+
        "\u0088\u00D2s\u00CC\u00DE\u0096b\u0092\u0081\u00B9I\u00D0LP\u0090"   +
        "\u001Bq\u00C6V\u0014\u00E6\u00C6\u00C7\u00BD2z\u0014\nE\u00E1\u00D0" +
        "\u0006\u00C3\u00F2{\u009A\u00C9\u00AAS\u00FDb\u00A8\u000F\u0000"     +
        "\u00BB%\u00BF\u00E25\u00BD\u00D2\u00F6q\u0012i\u0005\u00B2\u0004"    +
        "\u0002\"\u00B6\u00CB\u00CF|\u00CDv\u009C+S\u0011>\u00C0\u0016@\u00E3"+
        "\u00D38\u00AB\u00BD`%G\u00AD\u00F0\u00BA8 \u009C\u00F7F\u00CEvw"     +
        "\u00AF\u00A1\u00C5 u``\u0085\u00CB\u00FEN\u008A\u00E8\u008D\u00D8z"  +
        "\u00AA\u00F9\u00B0L\u00F9\u00AA~\u0019H\u00C2\\\u0002\u00FB\u008A"   +
        "\u008C\u0001\u00C3j\u00E4\u00D6\u00EB\u00E1\u00F9\u0090\u00D4\u00F8i"+
        "\u00A6\\\u00DE\u00A0?\t%-\u00C2\u0008\u00E6\u009F\u00B7Na2\u00CEw"   +
        "\u00E2[W\u008F\u00DF\u00E3:\u00C3r\u00E6";


    /** Self eplanatory constants */
    private static final int
        ROUNDS              =    16,
        BLOCK_SIZE          =     8,
        MIN_USER_KEY_LENGTH =  40/8,  // given in bytes from a value in bits
        MAX_USER_KEY_LENGTH = 448/8;  // given in bytes from a value in bits


    /** P-box and S-boxes */
    private static final int[]
        sP = new int[ROUNDS+2],
        sS = new int[1024];


    /**
     * Expand the compressed (see above) data into the P-box and S-boxes.
     *
     * We use the lower 8 bits of every character. Every four characters
     * make up one 32-bit integer.
     *
     * FIXME: Encoding this in 7-bits per byte would be better because of Sun's
     * internal .class file's UTF8 format. This requires a special decoder...
     * Still this is better than Cryptix IJCE 3.0.3 for which the .class
     * file was 61KB (this one yields 11KB). --gelderen
     */
    static 
    {
        for(int i=0, j=0; i<sP.length; i++)
            sP[i] = (cP.charAt(j++) << 24) |
                    (cP.charAt(j++) << 16) |
                    (cP.charAt(j++) <<  8) |
                    (cP.charAt(j++)      );

        for(int i=0, j=0; i<sS.length; i++)
            sS[i] = (cS.charAt(j++) << 24) |
                    (cS.charAt(j++) << 16) |
                    (cS.charAt(j++) <<  8) |
                    (cS.charAt(j++)      );
    }


// Instance variables
// ...................................................................

    /** P-box, used during key-setup */
    private final int[] P  = new int[ROUNDS + 2];


    /**
     * Individual ints representing the session key taken from int[] P.
     * We use these as a speedup instead of the P-array itself.
     */
    private int
        K00, K01, K02, K03, K04, K05, K06, K07, K08,
        K09, K10, K11, K12, K13, K14, K15, K16, K17;


    /** 4 S-boxes */
    private final int[]
        S0 = new int[256],
        S1 = new int[256],
        S2 = new int[256],
        S3 = new int[256];


// Constructor
// ...................................................................

    public Blowfish() 
    {
        super(BLOCK_SIZE);
    }



// BPI Methods
// ...................................................................


    /**
     * Initialize the object for encryption or decryption, given a Key.
     * <p>
     * This method expects a key with algorithm 'Blowfish' and
     * format 'RAW'. Both are case insensitive.
     * <p>
     * FIXME: checks need overhaul (or moved out to superclass).
     *
     * @param  key      key
     * @param  decrypt  true for decrypt mode, false for encrypt mode
     *
     * @throws InvalidKeyException when key==null or getAlgorithm()!=Blowfish
     *         or getFormat()!=RAW or getEncoded()==null or size<40 or
     *         size>448
     */
    protected void coreInit(Key key, boolean decrypt)
    throws InvalidKeyException
    {
        if( key==null )
            throw new InvalidKeyException("Key missing");

        if( !key.getAlgorithm().equalsIgnoreCase("Blowfish") )
            throw new InvalidKeyException("Wrong algorithm: Blowfish required");

        if( !key.getFormat().equalsIgnoreCase("RAW") )
            throw new InvalidKeyException("Wrong format: RAW bytes needed");

        byte[] userkey = key.getEncoded();
        if(userkey == null)
            throw new InvalidKeyException("RAW bytes missing");

        int len = userkey.length ;
        if(len < MIN_USER_KEY_LENGTH || len > MAX_USER_KEY_LENGTH)
            throw new InvalidKeyException("Invalid user key length");


        // Initialize ourselves (S0, S1, S2, S3) from the huge static S-box
        System.arraycopy(sS,   0, S0, 0, 256);
        System.arraycopy(sS, 256, S1, 0, 256);
        System.arraycopy(sS, 512, S2, 0, 256);
        System.arraycopy(sS, 768, S3, 0, 256);


        // Initialize our P-box from the static copy
        System.arraycopy(sP , 0, P , 0, ROUNDS+2);


        // Merge key into P-box.
        // Depends on correct key-size !!
        int ri;
        for (int i = 0, j = 0; i < ROUNDS + 2; i++) 
        {
            ri = 0;
            for (int k = 0; k < 4; k++) 
            {
                ri = (ri << 8) | (userkey[j++] & 0xFF);
                j %= len;
            }
            P[i] ^= ri;
        }

        // Generate the P-array & S-boxes
        keyEncrypt(0, 0, P, 0);
        for (int i = 2; i < ROUNDS + 2; i += 2)
            keyEncrypt(P[i - 2], P[i - 1], P, i);

        keyEncrypt(P[ROUNDS], P[ROUNDS + 1], S0, 0);
        for (int i = 2; i < 256; i += 2)
            keyEncrypt(S0[i - 2], S0[i - 1], S0, i);

        keyEncrypt(S0[254], S0[255], S1, 0);
        for (int i = 2; i < 256; i += 2)
            keyEncrypt(S1[i - 2], S1[i - 1], S1, i);

        keyEncrypt(S1[254], S1[255], S2, 0);
        for (int i = 2; i < 256; i += 2)
            keyEncrypt(S2[i - 2], S2[i - 1], S2, i);

        keyEncrypt(S2[254], S2[255], S3, 0);
        for (int i = 2; i < 256; i += 2)
            keyEncrypt(S3[i - 2], S3[i - 1], S3, i);


        // Store subkeys in individual instance variables for speedup
        if(decrypt) 
        {
            K00 = P[17]; K01 = P[16]; K02 = P[15]; K03 = P[14]; K04 = P[13];
            K05 = P[12]; K06 = P[11]; K07 = P[10]; K08 = P[ 9]; K09 = P[ 8];
            K10 = P[ 7]; K11 = P[ 6]; K12 = P[ 5]; K13 = P[ 4]; K14 = P[ 3];
            K15 = P[ 2]; K16 = P[ 1]; K17 = P[ 0];
        } 
        else 
        {
            K00 = P[ 0]; K01 = P[ 1]; K02 = P[ 2]; K03 = P[ 3]; K04 = P[ 4];
            K05 = P[ 5]; K06 = P[ 6]; K07 = P[ 7]; K08 = P[ 8]; K09 = P[ 9];
            K10 = P[10]; K11 = P[11]; K12 = P[12]; K13 = P[13]; K14 = P[14];
            K15 = P[15]; K16 = P[16]; K17 = P[17];

        }
    }


    /**
     * Encrypt or decrypt a single block of data.
     *
     * @param in        array containing datablock to be encrypted
     * @param inOffset  where the datablock starts
     * @param out       array where the output is to be stored
     * @param outOffset where the output should start
     */
    protected void coreCrypt(byte[] in, int inOffset, byte[] out, int outOffset)
    {

        int L = (in[inOffset++]       ) << 24 |
                (in[inOffset++] & 0xFF) << 16 |
                (in[inOffset++] & 0xFF) <<  8 |
                (in[inOffset++] & 0xFF);
        int R = (in[inOffset++]       ) << 24 |
                (in[inOffset++] & 0xFF) << 16 |
                (in[inOffset++] & 0xFF) <<  8 |
                (in[inOffset  ] & 0xFF);

        L ^= K00;
        R ^= (((S0[L >>> 24] + S1[(L >>> 16) & 0xFF]) ^ S2[(L >>> 8) & 0xFF]) + S3[L & 0xFF]) ^ K01;
        L ^= (((S0[R >>> 24] + S1[(R >>> 16) & 0xFF]) ^ S2[(R >>> 8) & 0xFF]) + S3[R & 0xFF]) ^ K02;
        R ^= (((S0[L >>> 24] + S1[(L >>> 16) & 0xFF]) ^ S2[(L >>> 8) & 0xFF]) + S3[L & 0xFF]) ^ K03;
        L ^= (((S0[R >>> 24] + S1[(R >>> 16) & 0xFF]) ^ S2[(R >>> 8) & 0xFF]) + S3[R & 0xFF]) ^ K04;
        R ^= (((S0[L >>> 24] + S1[(L >>> 16) & 0xFF]) ^ S2[(L >>> 8) & 0xFF]) + S3[L & 0xFF]) ^ K05;
        L ^= (((S0[R >>> 24] + S1[(R >>> 16) & 0xFF]) ^ S2[(R >>> 8) & 0xFF]) + S3[R & 0xFF]) ^ K06;
        R ^= (((S0[L >>> 24] + S1[(L >>> 16) & 0xFF]) ^ S2[(L >>> 8) & 0xFF]) + S3[L & 0xFF]) ^ K07;
        L ^= (((S0[R >>> 24] + S1[(R >>> 16) & 0xFF]) ^ S2[(R >>> 8) & 0xFF]) + S3[R & 0xFF]) ^ K08;
        R ^= (((S0[L >>> 24] + S1[(L >>> 16) & 0xFF]) ^ S2[(L >>> 8) & 0xFF]) + S3[L & 0xFF]) ^ K09;
        L ^= (((S0[R >>> 24] + S1[(R >>> 16) & 0xFF]) ^ S2[(R >>> 8) & 0xFF]) + S3[R & 0xFF]) ^ K10;
        R ^= (((S0[L >>> 24] + S1[(L >>> 16) & 0xFF]) ^ S2[(L >>> 8) & 0xFF]) + S3[L & 0xFF]) ^ K11;
        L ^= (((S0[R >>> 24] + S1[(R >>> 16) & 0xFF]) ^ S2[(R >>> 8) & 0xFF]) + S3[R & 0xFF]) ^ K12;
        R ^= (((S0[L >>> 24] + S1[(L >>> 16) & 0xFF]) ^ S2[(L >>> 8) & 0xFF]) + S3[L & 0xFF]) ^ K13;
        L ^= (((S0[R >>> 24] + S1[(R >>> 16) & 0xFF]) ^ S2[(R >>> 8) & 0xFF]) + S3[R & 0xFF]) ^ K14;
        R ^= (((S0[L >>> 24] + S1[(L >>> 16) & 0xFF]) ^ S2[(L >>> 8) & 0xFF]) + S3[L & 0xFF]) ^ K15;
        L ^= (((S0[R >>> 24] + S1[(R >>> 16) & 0xFF]) ^ S2[(R >>> 8) & 0xFF]) + S3[R & 0xFF]) ^ K16;
        R ^= K17;

        out[outOffset++] = (byte)(R >>> 24);
        out[outOffset++] = (byte)(R >>> 16);
        out[outOffset++] = (byte)(R >>>  8);
        out[outOffset++] = (byte)(R       );
        out[outOffset++] = (byte)(L >>> 24);
        out[outOffset++] = (byte)(L >>> 16);
        out[outOffset++] = (byte)(L >>>  8);
        out[outOffset  ] = (byte)(L       );
    }


// Internals
// ...................................................................

    /**
     * Perform a Blowfish encryption.
     *
     * This method is only called by the <code>makeKey</code> method to
     * generate the key schedule from user data. It outputs the result to an
     * int array.
     *
     * @param L         left half (32-bit) of the plain text block.
     * @param R         right half (32-bit) of the plain text block.
     * @param out       the int array where the result will be saved.
     * @param outOff    where the data starts in the byte array.
     */
    private void keyEncrypt(int L, int R, int[] out, int outOff)
    {
        L ^= P[0];
        for(int i = 0; i < ROUNDS; ) 
        {
            R ^= (((S0[L >>> 24] + S1[(L >>> 16) & 0xFF]) ^ S2[(L >>>  8) & 0xFF]) + S3[L & 0xFF]) ^ P[++i];
            L ^= (((S0[R >>> 24] + S1[(R >>> 16) & 0xFF]) ^ S2[(R >>>  8) & 0xFF]) + S3[R & 0xFF]) ^ P[++i];
        }
        out[outOff++] = R ^ P[ROUNDS + 1];
        out[outOff  ] = L;
    }
}
