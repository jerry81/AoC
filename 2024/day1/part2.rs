/*

This time, you'll need to figure out exactly how often each number from the left list appears in the right list. Calculate a total similarity score by adding up each number in the left list after multiplying it by the number of times that number appears in the right list.

Here are the same example lists again:

3   4
4   3
2   5
1   3
3   9
3   3
For these example lists, here is the process of finding the similarity score:

The first number in the left list is 3. It appears in the right list three times, so the similarity score increases by 3 * 3 = 9.
The second number in the left list is 4. It appears in the right list once, so the similarity score increases by 4 * 1 = 4.
The third number in the left list is 2. It does not appear in the right list, so the similarity score does not increase (2 * 0 = 0).
The fourth number, 1, also does not appear in the right list.
The fifth number, 3, appears in the right list three times; the similarity score increases by 9.
The last number, 3, appears in the right list three times; the similarity score again increases by 9.
So, for these example lists, the similarity score at the end of this process is 31 (9 + 4 + 0 + 0 + 9 + 9).

Once again consider your left and right lists. What is their similarity score?
*/

use std::fs::File;  // TIL
use std::io::{self, BufRead};
use std::path::Path;
use std::collections::HashMap;

fn main() -> io::Result<()> {
  // Specify the file name
  let filename = "input.txt";

  // TIL: Open the file in read-only mode (returns a Result)
  let path = Path::new(filename);
  let file = File::open(&path)?;

  // Create a buffered reader
  let reader = io::BufReader::new(file);

  let mut l1:Vec<i32> = vec![];
  let mut hm: HashMap<i32,i32> = HashMap::new();
  // Read the file line by line
  for line in reader.lines() {
      let line = line?; // Handle any errors while reading lines
      // Process each line here
      let spl: Vec<&str> = line.split_whitespace().collect(); // TIL: split_whitespace() method
      l1.push(spl[0].parse::<i32>().unwrap());
      *hm.entry(spl[1].parse::<i32>().unwrap()).or_insert(0)+=1;
  }

  println!("ans is {}", l1.iter()
    .map(|item| item*hm.get(item).unwrap_or(&0)) // TIL get..unwrap_or pattern
    .sum::<i32>());
  Ok(())
}