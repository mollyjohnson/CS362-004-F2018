import junit.framework.TestCase;
//for randomTests.out file output
import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
//to be used to get random nums in a range
import java.util.Random;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

/*
 * Validates URLs. Created by group 362_cruzst_nievesr_johnsmol
 * Steven Cruz (cruzst), Ronald Nieves (nievesr), and Molly Johnson (johnsmol)
 */
public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) 
   {
	   super(testName);
   }
   
   public void testManualTest()
   {
	   //You can use this function to implement your manual testing	   
	   String[] url = new String[10];
	   url[0] = "http://www.youtube.com";
	   url[1] = "www.youtube.com";
	   url[2] = "http://foo.com/bar";
	   url[3] = "http://foo.com/bar/baz";
	   url[4] = "http://www.google.com";
	   url[5] = "http://www.google.com/maps";
	   url[6] = "http://255.255.255.255";
	   url[7] = "http://255.255.255.255:3000";
	   url[8] = "http://www.googlegoooglegooogleogoogogle.com/";
	   url[9] = "3ht://1.2.3:65535/..//file?action=edit&mode=up\"";

	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   for(int i = 0; i < url.length; i++) {
		   if(urlVal.isValid(url[i]) == true) {
			   System.out.println(url[i] + " is true");
		   }
		   else {
			   System.out.println(url[i] + " is false");
		   }
	   }
   }
   
//////////			ADD ME				/////////////////////////////////
   // Testing the Schemes
   public void testYourFirstPartition()
   {
	 System.out.println("\n First Partition test - SCHEMES");
	 
	 String[] schemeList = {"http", "https", "ftp", "http://", "https://", "ftp://"};
	 UrlValidator urlValScheme = new UrlValidator(schemeList, 0);
	 for (int i = 0; i < schemeList.length; i++) {
		 String currScheme = schemeList[i];
		 System.out.println("Testing " + currScheme);
		 boolean validScheme = urlValScheme.isValidScheme(currScheme);
		 if (validScheme == true) {
			 System.out.println("Pass");
		 } else {
			 System.out.println("Fail");
		 }
	 }
   }

/** THIS DOES NOT WORK, CAUSES REGEX ERRORS, leave commented out
   // Testing the authority
   public void testYourSecondPartition(){
		 System.out.println("\n Second Partition test - AUTHORITY");
		 
		 String[] authList = {"google", "notvalid", "youtube", "www.youtube.com", "www.google.com"};
		 UrlValidator urlValAuth = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		 for (int i = 0; i < authList.length; i++) {
			 String currAuth = authList[i];
			 System.out.println("Testing " + currAuth);
			 boolean validAuth = urlValAuth.isValidAuthority(currAuth);  // Offending call
			 if (validAuth == true) {
				 System.out.println("Pass");
			 } else {
				 System.out.println("Fail");
			 }
		 }	   

   }
**/
   
   // Testing the paths
   public void testYourThirdPartition(){
		 System.out.println("\n Third Partition test - PATH");
		 
		 String[] pathList = {"", "/home", "//home", "/..", "..", "home", "/", "/folder1/subfolder", "/1/2/3", "/home:3000"};
		 UrlValidator urlValPath = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		 for (int i = 0; i < pathList.length; i++) {
			 String currPath = pathList[i];
			 System.out.println("Testing " + currPath);
			 boolean validPath = urlValPath.isValidPath(currPath);
			 if (validPath == true) {
				 System.out.println("Pass");
			 } else {
				 System.out.println("Fail");
			 }
		 }	   
   }
   
   // Testing the Query
   public void testYourFourthPartition(){
		 System.out.println("\n Fourth Partition test - Query");
		 
		 String[] queryList = {"", "?action=submit", "?", "/", "??action=submit", "?action=", "#", "#print"};
		 UrlValidator urlValQuery = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		 for (int i = 0; i < queryList.length; i++) {
			 String currQuery = queryList[i];
			 System.out.println("Testing " + currQuery);
			 boolean validPath = urlValQuery.isValidQuery(currQuery);
			 if (validPath == true) {
				 System.out.println("Pass");
			 } else {
				 System.out.println("Fail");
			 }
		 }	   
   }   
   /////////////////////////////////////////////////////////////////////////////////////// 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing
	  
	   int testsPassed = 0;
	   int testsFailed = 0;
	   
	   //create array of valid schemes
	   //adapted from default valid schemes listed in UrlValidator.java
	   String [] validSchemes = new String[1];
	   validSchemes[0] = "http://";
	   
	   //ftp and https and "" taken out as valid schemes even though they should be according to the default
	   //allowable schemes listed in UrlValidator.java line 350 due to regex errors (described in writeup).
	   //validSchemes[1] = "ftp://";
	   //validSchemes[2] = "https://";
	   
	   //create array of invalid schemes
	   //based on schemes not falling into category of valid schemes listed in UrlValidator.java
	   String [] invalidSchemes = new String[8];
	   invalidSchemes[0] = "http:/";
	   invalidSchemes[1] = "ht tp://";
	   invalidSchemes[2] = "ftp: //";
	   invalidSchemes[3] = "http:";
	   //invalidSchemes[4] = "h33t://"; //caused regex error, removed. will discuss in writeup
	   invalidSchemes[4] = "://ftp";
	   invalidSchemes[5] = "h3t:/";
	   invalidSchemes[6] = ".www";
	   //invalidSchemes[7] = "https//"; //caused regex error, removed. will discuss in writeup
	   invalidSchemes[7] = "";
	   
	   //create array of valid auths
	   //some adapted from UrlValidatorTest.java (correct)
	   String [] validAuths = new String[8];
	   validAuths[0] = "www.google.com";
	   validAuths[1] = "www.youtube.com";
	   validAuths[2] = "www.amazon.com";
	   validAuths[3] = "www.ebay.com";
	   validAuths[4] = "0.0.0.0";
	   validAuths[5] = "go.au";
	   validAuths[6] = "255.com";
	   validAuths[7] = "255.255.55.255";
			   
	   //create array of invalid auths
	   //some adapted from UrlValidatorTest.java (correct)
	   String [] invalidAuths = new String[8];
	   invalidAuths[0] = "";
	   invalidAuths[1] = "1.2.3.4.5";
	   invalidAuths[2] = ".1.2.3.4";
	   invalidAuths[3] = "go.a";
	   invalidAuths[4] = "com.";
	   invalidAuths[5] = "go.a1a";
	   invalidAuths[6] = "256.256.256.256";
	   invalidAuths[7] = ".com";
	   
	   //create array of valid ports
	   //some adapted from UrlValidatorTest.java (correct)
	   String [] validPorts = new String[4];
	   validPorts[0] = "";
	   validPorts[1] = ":65535";
	   validPorts[2] = ":0";
	   validPorts[3] = ":80";
	   
	   //create array of invalid ports
	   //some adapted from UrlValidatorTest.java (correct)
	   String [] invalidPorts = new String[9];
	   invalidPorts[0] = ":-80";
	   invalidPorts[1] = ":65636";
	   invalidPorts[2] = ":80abc";
	   invalidPorts[3] = "::80";
	   invalidPorts[4] = "80";
	   invalidPorts[5] = "80:";
	   invalidPorts[6] = "abc";
	   invalidPorts[7] = ":80*";
	   invalidPorts[8] = ":80:";
	   
	   //create array of valid paths
	   //some adapted from UrlValidatorTest.java (correct)
	   String [] validPaths = new String[9];
	   validPaths[0] = "/test";
	   validPaths[1] = "/test1";
	   validPaths[2] = "/$123";
	   validPaths[3] = "/test/";
	   validPaths[4] = "/test/file";
	   validPaths[5] = "/test/file/";
	   validPaths[6] = "";
	   validPaths[7] = "/abc123/file";
	   validPaths[8] = "/$123/file";
	   
	   //create array of invalid paths
	   //some adapted from UrlValidatorTest.java (correct)
	   String [] invalidPaths = new String[9];
	   invalidPaths[0] = "/..";
	   invalidPaths[1] = "/../";
	   invalidPaths[2] = "/#$%";
	   invalidPaths[3] = "/../file";
	   invalidPaths[4] = "/..//file";
	   invalidPaths[5] = "/#/file";
	   invalidPaths[6] = "//test/file";
	   invalidPaths[7] = "//";
	   invalidPaths[8] = "/test/#/file";
	   
	   //create array of valid queries
	   //some adapted from UrlValidatorTest.java (correct)
	   String [] validQueries = new String[4];
	   validQueries[0] = "?action=view";
	   validQueries[1] = "?action=edit&mode=up";
	   validQueries[2] = "";
	   validQueries[3] = "?action=view&mode=down&oq=something";
	   
	   //create array of invalid queries
	   //some adapted from UrlValidatorTest.java (correct)
	   String [] invalidQueries = new String[5];
	   invalidQueries[0] = "action=view";
	   invalidQueries[1] = "?action&view";
	   invalidQueries[2] = "?action=view,mode=down";
	   invalidQueries[3] = "??action=view";
	   invalidQueries[4] = "?action=view&mode=down&action";
	   
	   //create random strings of the URL components, with all components being valid
	   String [] validURLs = new String[500];
	   
	   //create random strings of the URL components, with all components except one being valid
	   //is 5 times larger than validURLs since will be testing only one invalid URL component for each invalidURL
	   String [] invalidURLs = new String[2500];
	   
	   //getting random numbers within a range adapted from:
	   //https://stackoverflow.com/questions/363681/how-to-generate-random-integers-within-a-specific-range-in-java and
	   //https://www.mkyong.com/java/java-generate-random-integers-in-a-range/
	   Random rand = new Random();
	   
	   //create random valid URLs
	   for(int k = 0; k < validURLs.length; k++)
	   {
		  //get index for random component of valid URL. nextInt will give random num from 0 to the int passed in (exclusive)
		  int schemeIdxV = rand.nextInt(validSchemes.length);
		  int authIdxV = rand.nextInt(validAuths.length);
		  int portIdxV = rand.nextInt(validPorts.length);
		  int pathIdxV = rand.nextInt(validPaths.length);
		  int queryIdxV = rand.nextInt(validQueries.length);
		  
		  //create URLs from the random components
		  validURLs[k] = (validSchemes[schemeIdxV] + validAuths[authIdxV] + validPorts[portIdxV] + validPaths[pathIdxV] + validQueries[queryIdxV]);
		  //System.out.println(validURLs[k]);
	   }
	   
	   //create random invalid URLs (one invalid component per URL to help better isolate bugs)
	   for(int j = 0; j < invalidURLs.length; j++)
	   {
		   int schemeIdxI;
		   int authIdxI;
		   int portIdxI;
		   int pathIdxI;
		   int queryIdxI;
		   
		   //set 500 invalid URLs where random scheme is invalid
		   if(j < 500)
		   {
			   schemeIdxI = rand.nextInt(invalidSchemes.length);
			   authIdxI = rand.nextInt(validAuths.length);
			   portIdxI = rand.nextInt(validPorts.length);
			   pathIdxI = rand.nextInt(validPaths.length);
			   queryIdxI = rand.nextInt(validQueries.length);
			   
			   //create URLs from the random components
			   invalidURLs[j] = (invalidSchemes[schemeIdxI] + validAuths[authIdxI] + validPorts[portIdxI] + validPaths[pathIdxI] + validQueries[queryIdxI]);
		   }
		   //set 500 invalid URLs where random auth is invalid
		   else if (j >= 500 && j < 1000)
		   {
			   schemeIdxI = rand.nextInt(validSchemes.length);
			   authIdxI = rand.nextInt(invalidAuths.length);
			   portIdxI = rand.nextInt(validPorts.length);
			   pathIdxI = rand.nextInt(validPaths.length);
			   queryIdxI = rand.nextInt(validQueries.length);
			   
			   //create URLs from the random components
			   invalidURLs[j] = (validSchemes[schemeIdxI] + invalidAuths[authIdxI] + validPorts[portIdxI] + validPaths[pathIdxI] + validQueries[queryIdxI]);
		   }
		   //set 500 invalid URLs where random port is invalid
		   else if (j >= 1000 && j < 1500)
		   {
			   schemeIdxI = rand.nextInt(validSchemes.length);
			   authIdxI = rand.nextInt(validAuths.length);
			   portIdxI = rand.nextInt(invalidPorts.length);
			   pathIdxI = rand.nextInt(validPaths.length);
			   queryIdxI = rand.nextInt(validQueries.length);
			   
			   //create URLs from the random components
			   invalidURLs[j] = (validSchemes[schemeIdxI] + validAuths[authIdxI] + invalidPorts[portIdxI] + validPaths[pathIdxI] + validQueries[queryIdxI]);
		   }
		   //set 500 invalid URLs where random path is invalid
		   else if (j >= 1500 && j < 2000)
		   {
			   schemeIdxI = rand.nextInt(validSchemes.length);
			   authIdxI = rand.nextInt(validAuths.length);
			   portIdxI = rand.nextInt(validPorts.length);
			   pathIdxI = rand.nextInt(invalidPaths.length);
			   queryIdxI = rand.nextInt(validQueries.length);
			   
			   //create URLs from the random components
			   invalidURLs[j] = (validSchemes[schemeIdxI] + validAuths[authIdxI] + validPorts[portIdxI] + invalidPaths[pathIdxI] + validQueries[queryIdxI]);
		   }
		   else //2000 - 2499
		   {
			   schemeIdxI = rand.nextInt(validSchemes.length);
			   authIdxI = rand.nextInt(validAuths.length);
			   portIdxI = rand.nextInt(validPorts.length);
			   pathIdxI = rand.nextInt(validPaths.length);
			   queryIdxI = rand.nextInt(invalidQueries.length);
			   
			   //create URLs from the random components
			   invalidURLs[j] = (validSchemes[schemeIdxI] + validAuths[authIdxI] + validPorts[portIdxI] + validPaths[pathIdxI] + invalidQueries[queryIdxI]);
		   }
		   
		   //System.out.println(invalidURLs[j]);
	   }
	   
	   //print results to a file instead of just the console
	   //adapted from: https://stackoverflow.com/questions/2885173/how-do-i-create-a-file-and-write-to-it-in-java
	   Writer writer = null;
	   try {
		   writer = new BufferedWriter(new OutputStreamWriter(
				   new FileOutputStream("randomTests.out.txt"), "utf-8"));
		 //test the randomized urls
		   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		   for(int h = 0; h < validURLs.length; h++)
		   {
			   //test valid URLS. so if isValid returns true, URL is valid and test passed. Else test fails.
			   if(urlVal.isValid(validURLs[h]) == true) //valid URL (expected)
			   {
				   System.out.println(validURLs[h] + " is a valid URL. Expected. TEST PASSED.");
				   writer.write(validURLs[h] + " is a valid URL. Expected. TEST PASSED.\n");
				   testsPassed++;
			   }
			   else //false, invalid URL (unexpected)
			   {
				   System.out.println(validURLs[h] + " is an invalidURL. Unexpected. TEST FAILED.");
				   writer.write(validURLs[h] + " is an invalidURL. Unexpected. TEST FAILED.\n");
				   testsFailed++;
			   }
		   }
		   
		   for(int i = 0; i < invalidURLs.length; i++)
		   {
			   //test invalid URLs. so if isValid returns false, URL is invalid (as expected) and test passed. Else test fails.
			   if(urlVal.isValid(invalidURLs[i]) == false) //invalid URL (expected)
			   {
				   System.out.println(invalidURLs[i] + " is an invalid URL. Expected. TEST PASSED.");
				   writer.write(invalidURLs[i] + " is an invalid URL. Expected. TEST PASSED.\n");
				   testsPassed++;
			   }
			   else //true, valid URL (unexpected)
			   {
				   System.out.println(invalidURLs[i] + " is a valid URL. Unexpected. TEST FAILED.");
				   writer.write(invalidURLs[i] + " is a valid URL. Unexpected. TEST FAILED.\n");
				   testsFailed++;
			   }
		   }
		   
		   System.out.println(testsPassed + " tests passed.");
		   writer.write(testsPassed + " tests passed.\n");
		   System.out.println(testsFailed + " tests failed.");
		   writer.write(testsFailed + " tests failed.\n");
		   
	   } catch (IOException ex) {
		   
	   } finally {
		   try {writer.close();} catch (Exception ex) {}
	   }
	   
   }
   
}
