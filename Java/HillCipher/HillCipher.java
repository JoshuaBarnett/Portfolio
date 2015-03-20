//Josh Barnett
//CIS 3360
//Program 1 -- Hill Cipher
//10/3/14

import java.util.*;
import java.io.*;
import java.util.Scanner;
import java.nio.*;
import java.nio.charset.Charset;

public class HillCipher
{
public static int[][] encryptKey = new int[10][10]; //...stores the encryption key
public static char[] plaintextRaw = new char[10000];//raw data from plaintext file
public static int[] plaintext = new int[10000]; //integer values (0-25) of the plaintext
public static int[] ciphertext = new int[10000]; //same deal but for the cipher text
public static int plaintextLength;
public static Scanner sc;
public static Scanner sc2;
public static String[] tempString = new String[10];
public static String[] tempString2 = new String[10];
public static int[] tempInt = new int[10];

public static void main(String[] args) {
HillCipher cipher = new HillCipher();
int i, j, n;
n = 0;
//read the encryption key

try{
sc = new Scanner(new File(args[0]));}
catch(FileNotFoundException fnfe){};
try{
n = sc.nextInt();}
catch(NullPointerException npe){}; //get key size
try{
tempString[0] = sc.nextLine(); //discard remainder of first line (will be overwritten in next statement
for (i=0;i<n;i++){
		tempString[i] = sc.nextLine(); //read in text
		tempString2 = tempString[i].split(","); //separate integers out
		for (j=0;j<n;j++)
			encryptKey[i][j] = Integer.parseInt(tempString2[j].trim()); //populate key
		}
}
catch (NullPointerException npe){};

//print encryption key
for (i=0;i<n;i++){
	for (j=0;j<n;j++)
		System.out.print(encryptKey[i][j] + " ");
	System.out.println("");
		}
	//extra line for spacing
System.out.println("");


try{ //open the plaintext file
	sc2 = new Scanner(new File(args[1]));}
catch(FileNotFoundException fnfe){};	

int plaintextIndex = 0;
char tempChar;
try{
BufferedReader reader = new BufferedReader(
    new InputStreamReader(
        new FileInputStream(args[1]),Charset.forName("UTF-8")));
int c;
try{
while((c = reader.read()) != -1) {
if ((c >= 97) && (c<=122)) //lower case letter
	{
	plaintext[plaintextIndex] = c-97; //compensate for offset
	plaintextIndex++;
	}
	if ((c >= 65) && (c<=90)) //uppercase
	{
	plaintext[plaintextIndex] = c-65;
	plaintextIndex++;
	}
}}
catch (IOException ioe){};}
catch (FileNotFoundException fnfe){};


int temp1 = plaintextIndex;
if (temp1%n != 0)
	for (i=0;i<(n-(temp1%n));i++){
		plaintext[temp1+i] = 25;
		plaintextIndex++;}
	
	
for (i=0;i<=plaintextIndex/80;i++)
{
	if (plaintextIndex < (80*(i+1))) //plaintext will be ending on this line
		for (j=0;j<plaintextIndex%80;j++) //print remaining characters
			System.out.print(intToChar(plaintext[(80*i)+j]));
	else
		for (j=0;j<80;j++) //print next 80 char
			System.out.print(intToChar(plaintext[(80*i)+j]));
		System.out.println();

}
	
	
	
	for (i=0;i<=plaintextIndex/n;i+=n) //break that badboy up into blocks of n
		for(j=0;j<n;j++)
			for(int k=0;k<n;k++)
				ciphertext[i+j] += encryptKey[j][k]*plaintext[i+k]; //matrix multiply each aforementioned block
			
	for (i=0;i<plaintextIndex;i++)
		ciphertext[i] = ciphertext[i]%26;
	
//NOTE: plaintextIndex reused because it's same length as ciphertext
for (i=0;i<=plaintextIndex/80;i++)
{
	if (plaintextIndex < (80*(i+1))) //ciphertext will be ending on this line
		for (j=0;j<plaintextIndex%80;j++) //print remaining characters
			System.out.print(intToChar(ciphertext[(80*i)+j]));
	else
		for (j=0;j<80;j++) //print next 80 char
			System.out.print(intToChar(ciphertext[(80*i)+j]));
		System.out.println();

}
	
	
	
}

public static char intToChar(int a)
{
	return (char) (a+97);
}








}
