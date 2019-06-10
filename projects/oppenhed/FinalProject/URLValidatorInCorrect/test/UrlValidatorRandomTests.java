
//import java.io.BufferedReader;
//import java.io.File;
//import java.io.FileReader;
//import java.io.FileNotFoundException;
//import java.util.Random;
//import java.util.Scanner;

import junit.framework.TestCase;

public class UrlValidatorRandomTests extends TestCase {
	
	public UrlValidatorRandomTests(String name) {
		super(name);
	}
	
	private static final int TEST_COUNT = 10000;
	
	private static final RandomUrlGenerator randomUrlGenerator = new RandomUrlGenerator();
	
	public void testRandom() {
		
		System.out.println("********************************* RANDOM TESTING ******************************");
		String completesUrl = "://www.google.com";
		String startsUrl = "http://";
		
		System.out.println("------------------------- Testing Invalid Schemes --------------------------");
		for(int i = 0; i < TEST_COUNT; i++) {
			String urlPart = randomUrlGenerator.getInvalidScheme();
			String fullUrl = urlPart + completesUrl;
			System.out.println("TEST " + Integer.toString(i+1) + " TEST INPUT URL: " + fullUrl + " Expected: Invalid");
			long options = UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS;
		    UrlValidator urlValidator = new UrlValidator(options);
		    if(urlValidator.isValid(fullUrl)) {
		    	System.out.println("TEST " + Integer.toString(i+1) + " FAILED");
		    }
		    else {
		    	System.out.println("TEST " + Integer.toString(i+1) + " PASSED");
		    }
		    assertFalse(urlValidator.isValid(fullUrl));
		}
		System.out.println("------------------------- Testing Valid Schemes --------------------------");
		for(int i = 0; i < TEST_COUNT; i++) {
			String urlPart = randomUrlGenerator.getValidScheme();
			String fullUrl = urlPart + completesUrl;
			System.out.println("TEST " + Integer.toString(i+1) + " TEST INPUT URL: " + fullUrl + " Expected: Valid");
			long options = UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS;
		    UrlValidator urlValidator = new UrlValidator(options);
		    if(urlValidator.isValid(fullUrl)) {
		    	System.out.println("TEST " + Integer.toString(i+1) + " PASSED");
		    }
		    else {
		    	System.out.println("TEST " + Integer.toString(i+1) + " FAILED");
		    }
		    assertTrue(urlValidator.isValid(fullUrl));
		}
		System.out.println("------------------------- Testing Invalid Authorities --------------------------");
		for(int i = 0; i < TEST_COUNT; i++) {
			String urlPart = randomUrlGenerator.getInvalidAuthority();
			String fullUrl = startsUrl + urlPart;
			System.out.println("TEST " + Integer.toString(i+1) + " TEST INPUT URL: " + fullUrl + " Expected: Invalid");
			long options = UrlValidator.ALLOW_2_SLASHES + UrlValidator.NO_FRAGMENTS;
		    UrlValidator urlValidator = new UrlValidator(options);
		    if(urlValidator.isValid(fullUrl)) {
		    	System.out.println("TEST " + Integer.toString(i+1) + " FAILED");
		    }
		    else {
		    	System.out.println("TEST " + Integer.toString(i+1) + " PASSED");
		    }
		    assertFalse(urlValidator.isValid(fullUrl));
		}
		System.out.println("------------------------- Testing Valid Authorities --------------------------");
		for(int i = 0; i < TEST_COUNT; i++) {
			String urlPart = randomUrlGenerator.getValidAuthority();
			String fullUrl = startsUrl + urlPart;
			System.out.println("TEST " + Integer.toString(i+1) + " TEST INPUT URL: " + fullUrl + " Expected: Valid");
			long options = UrlValidator.ALLOW_2_SLASHES + UrlValidator.NO_FRAGMENTS;
		    UrlValidator urlValidator = new UrlValidator(options);
		    if(urlValidator.isValid(fullUrl)) {
		    	System.out.println("TEST " + Integer.toString(i+1) + " PASSED");
		    }
		    else {
		    	System.out.println("TEST " + Integer.toString(i+1) + " FAILED");
		    }
			assertTrue(urlValidator.isValid(fullUrl));
		}
	}
}
	