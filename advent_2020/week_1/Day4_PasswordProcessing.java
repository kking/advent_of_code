import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;

/**
 * Advent of Code 2020, Day 4: Passport Processing
 * kking, 12/05/20
 *
 * Part 1:
 * "... The automatic passport scanners are slow because they're having trouble detecting which passports 
 * have all required fields. The expected fields are as follows:
 * 			byr (Birth Year)	iyr (Issue Year)	eyr (Expiration Year)	hgt (Height)
 * 			hcl (Hair Color)	ecl (Eye Color)		pid (Passport ID)		cid (Country ID)
 * Passport data is validated in batch files (your puzzle input). Each passport is represented as a sequence 
 * of key:value pairs separated by spaces or newlines. Passports are separated by blank lines.
 * ... Count the number of valid passports - those that have all required fields. Treat cid as optional. In 
 * your batch file, how many passports are valid?"
 *
 * Part 2:
 * "... You can continue to ignore the cid field, but each other field has strict rules about what values are 
 * valid for automatic validation:
 * 			byr (Birth Year) - four digits; at least 1920 and at most 2002.
 * 			iyr (Issue Year) - four digits; at least 2010 and at most 2020.
 * 			eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
 * 			hgt (Height) - a number followed by either cm or in:
 * 				- If cm, the number must be at least 150 and at most 193.
 * 				- If in, the number must be at least 59 and at most 76.
 * 			hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
 * 			ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
 * 			pid (Passport ID) - a nine-digit number, including leading zeroes.
 * 			cid (Country ID) - ignored, missing or not.
 * Your job is to count the passports where all required fields are both present and valid according to the 
 * above rules.
 * ... Count the number of valid passports - those that have all required fields and valid values. Continue to 
 * treat cid as optional. In your batch file, how many passports are valid?
 */
public class Day4_PasswordProcessing {
	
	/** A model for a passport processing. */
	protected static class Passport
	{
		/** Each field name as they appear in the text file. */
		private static final String[] KEYS = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid" };
		/** The country ID field is optional. */
		private static final String OPT_KEY = "cid";
		/** Regular expression patterns corresponding to each item in KEYS. */
		private static final String[] V_PATTERNS = { "([1][9][2-9][0-9])|([2][0][0][0-2])", 
					"[2][0]([1][0-9]|[2][0])", 
					"[2][0]([2][0-9]|[3][0])", 
					"(([1][5-8][0-9]|[1][9][0-3])[c][m])|(([5][9]|[6][0-9]|[7][0-6])[i][n])", 
					"\\#([0-9]|[a-z]){6}", 
					"(amb|blu|brn|gry|grn|hzl|oth){1}", 
					"[0-9]{9}", 
					"." };
		
		/** A map containing String values for each passport field. */
		protected HashMap<String, String> mPassport;
		
		public Passport() {
			mPassport = new HashMap<>();
		}
		
		/**
		 * @return true if key and value correspond to values in the parallel arrays; false otherwise
		 */
		public boolean setEntry(String key, String value) {
			for (int i = 0; i < KEYS.length; i++) {
				if (key.equals(KEYS[i]) && value.matches(V_PATTERNS[i])) {
					mPassport.put(key, value);
					return true;
				}
			}
			return false;
		}
		
		/** 
		 * @return true if this passport has all 8 keys, or 7 without the global ID; false otherwise 
		 */
		public boolean isValid() {
			return ((mPassport.size() == KEYS.length) 
						|| (mPassport.size() == KEYS.length-1 && !mPassport.containsKey(OPT_KEY)));
		}
		
	} // end of class Passport
	
	/**
	 * Reads a text file and counts each passport according to the validity criteria established in its 
	 * model class.
	 * @param fileName  The name of the text file containing a sequence of key-value pairs for passports
	 * @return  The number of valid passports from the text file
	 */
	public static int getValidPassports(String fileName) 
	{
		Scanner inFile = null;
		String line;
		Passport passport = new Passport(); // a local Passport for reading the file
		ArrayList<Passport> valid = new ArrayList<>(), invalid = new ArrayList<>();
		
		// open a Scanner for file input
		try {
			inFile = new Scanner(new File(fileName));
		}
		catch (FileNotFoundException fnfe) {
			return -1;
		}
		
		while (inFile.hasNextLine()) {
			line = inFile.nextLine();
			
			if (line.length() == 0) {
				// empty line encountered - end of one passport entry
				// process this passport as valid or invalid
				if (passport.isValid()) {
					valid.add(passport);
				}
				else {
					invalid.add(passport);
				}
				// reset local passport
				passport = new Passport(); 
			}
			else {
				// add all entries on this line to this passport
				for (String t : line.split(" ")) {
					passport.setEntry(t.substring(0, 3), t.substring(4)); // key is 3 chars long followed by a ':'
				}
			}
		}
		// process final passport
		if (passport.isValid()) {
			valid.add(passport);
		}
		else {
			invalid.add(passport);
		}
		
		return valid.size();
		
	} // end of getValidPassports
	
	/** for command-line argument execution */
	public static void main(String[] args) 
	{
		if (args.length == 1) {
			System.out.println("Number of valid passports: " + getValidPassports(args[0]));
		}
	}
	
} // end of class Day4_PasswordProcessing

// 1. off-by-one in counting the final password, resolved by checking the last passport read
// 2. inflexible switch statement in setEntry; resolved using parallel arrays for the keys
// 3. followed a hint on r/adventofcode to use regex; hacked together a solution on regexr.com
