import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

/*
 * A java implementation of the alternating character problem. 
 * Given a string, it returns the longest string length that 
 * constitutes alternating characters formed form the given string
 * Alternating is defined as ab, aba, baba. 
 * Runs in Big O(N^2)
 */
 
public class Solution{
	static String stripChar(String input, char a, char b){
		StringBuilder builder = new StringBuilder();
		for(int i = 0; i < input.length(); i++){
			char c = input.charAt(i);
			if(c == a || c == b)builder.append(c);
		}
		return builder.toString();
	}
	static int score(String str){
		if(str.length() < 2)return 0;

		for(int i = 0; i < str.length() - 1; i++){
			char curr = str.charAt(i);
			char next = str.charAt(i+1);
			if(curr == next){
				return 0;
			}
		}
		return str.length();
	}
	static int twoCharacters(String s){
		int maxScore = 0;
		for(char pairA = 'a'; pairA <= 'z'; pairA++){
			for(pairB = (char)(pairA + 1); pairB <= 'z'; pairB++){
				String stripped = stripChar(s, pairA, pairB);
				maxScore = Math.max(score(stripped), maxScore);
			}
		}
		return maxScore;
	}
	public static void main(String []args){
		Scanner in = new Scanner(System.in);
		int l = in.nextInt();
		String s = in.next();
		int result = twoCharacters(s);
		System.out.println(result);
		in.close();
	}
}