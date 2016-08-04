/* $Id: AlgorithmParameters.java,v 1.2 2009/09/24 20:42:18 rgrimm Exp $
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


import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;

import java.security.Provider;
import java.security.Security;

import java.security.spec.AlgorithmParameterSpec;
import java.security.spec.InvalidParameterSpecException;

import java.io.IOException;


/**
 * This is the java.security.AlgorithmParameters class for jdk1.1 compatibility.
 * Currently only the interfaces are designed, a few lines of code written.
 *
 * THIS IS UNDER DEVELOPMENT NOT TESTED YET (1999-24-12)!!!
 *
 * @author  Josef Hartmann
 * @version $Revision: 1.2 $
 */
public class AlgorithmParameters
{
	private AlgorithmParametersSpi paramSpi = null;
	private Provider provider = null;
	private String algorithm = null;
	private boolean isInitialized = false;


	protected AlgorithmParameters(AlgorithmParametersSpi paramSpi,
	                              Provider provider,
                                  String algorithm)
    {
		this.paramSpi  = paramSpi;
		this.provider  = provider;
		this.algorithm = algorithm;
	}


	public final String getAlgorithm()
	{
		return this.algorithm;
	}


    // FIXME: Use javax.crypto.Support.getImplementation() instead?
	public static AlgorithmParameters getInstance(String algorithm)
	                                        throws NoSuchAlgorithmException
	 {
		// Walk through installed providers and check for algorithm.
		// Take the first one which provides the specified algorithm.
		Provider [] allInstalledProviders = Security.getProviders();

		for (int i=0; i<allInstalledProviders.length; i++)
		{
			// pass current provider with algorithm to overloaded method.
			try
			{
				// FIXME: Does it make sense to pass the name of the provider
				//        and instanciating one again using the name.
				AlgorithmParameters ap = getInstance(algorithm, allInstalledProviders[i].getName());
				return ap;
			}
			catch (NoSuchAlgorithmException nsae)
			{
				throw new NoSuchAlgorithmException();
			}
			catch (NoSuchProviderException nspe)
			{
				// Is this the correct exception? Probably yes!
				throw new NoSuchAlgorithmException();
			}
		}

		// If we get there, no provider with specified algorithm was found.
        throw new NoSuchAlgorithmException();
    }


    public static AlgorithmParameters getInstance(String algorithm,
	                                              String provider)
	                                       throws NoSuchAlgorithmException,
                                                  NoSuchProviderException
    {
		AlgorithmParametersSpi algorithmSpi = null;
		// Provider string is null or empty; take the other method.
		if ((provider == null)||(provider.length()==0))
			return getInstance(algorithm);

		// Look for the provider.
		Provider tempProv = Security.getProvider(provider);
		if (tempProv == null)
			throw new NoSuchProviderException();

		// We got the provider, so let's look for the algorithm.
		String key = "AlgorithmParameters." + algorithm;
		String prop = tempProv.getProperty(key);
		if (prop==null)
		{
			throw new NoSuchAlgorithmException();
		}

		// Here we have a not yet verified property string.
		// Let's try to instantiate the class using the name stored in prop.
		try
		{
			algorithmSpi = (AlgorithmParametersSpi) Class.forName(prop).newInstance();
		}
		catch (ClassNotFoundException cnfe)
		{
			cnfe.printStackTrace();
			throw new NoSuchAlgorithmException();
		}
		catch (InstantiationException ie)
		{
			ie.printStackTrace();
			// FIXME: what to throw here??
		}
		catch (IllegalAccessException iae)
		{
			iae.printStackTrace();
			// FIXME: what to throw here?
		}

		// Now we have a provider and the algorithmSpi. So create a new AlgorithmObject and return it.
		return new AlgorithmParameters(algorithmSpi, tempProv, algorithm);
	}


	public final Provider getProvider()
	{
		return this.provider;
	}


	public final void init(AlgorithmParameterSpec paramSpec)
        throws InvalidParameterSpecException
    {
		this.paramSpi.engineInit(paramSpec);
		isInitialized = true;
		// FIXME: What throws the exception?
		// throw new InvalidParameterSpecException();
	}


	public final void init(byte[] params)
        throws IOException
    {
		this.paramSpi.engineInit(params);
		isInitialized = true;
		// FIXME: exception?
		// throw new IOException();
	}


	public final void init(byte[] params, String format)
        throws IOException
    {
		this.paramSpi.engineInit(params, format);
		isInitialized = true;
		// FIXME: How about the exception?
		// throw new IOException();
	}


	public final AlgorithmParameterSpec getParameterSpec(Class paramSpec)
        throws InvalidParameterSpecException
    {
		return this.paramSpi.engineGetParameterSpec(paramSpec);
	}


	public final byte[] getEncoded()
        throws IOException
    {
		if (isInitialized == false)
			throw new IOException();

		return this.paramSpi.engineGetEncoded();
	}


	public final byte[] getEncoded(String format)
        throws IOException
    {
		if (isInitialized == false)
			throw new IOException();

		return this.paramSpi.engineGetEncoded(format);
	}


	public final String toString()
	{
		// Return the spi. If the object has not been initialized return null.
		if (isInitialized == false)
		{
			return null;
		}
		else
		{
			return this.paramSpi.engineToString();
		}
	}
}