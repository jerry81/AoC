/*
--- Day 3: Mull It Over ---
"Our computers are having issues, so I have no idea if we have any Chief Historians in stock! You're welcome to check the warehouse, though," says the mildly flustered shopkeeper at the North Pole Toboggan Rental Shop. The Historians head out to take a look.

The shopkeeper turns to you. "Any chance you can see why our computers are having issues again?"

The computer appears to be trying to run a program, but its memory (your puzzle input) is corrupted. All of the instructions have been jumbled up!

It seems like the goal of the program is just to multiply some numbers. It does that with instructions like mul(X,Y), where X and Y are each 1-3 digit numbers. For instance, mul(44,46) multiplies 44 by 46 to get a result of 2024. Similarly, mul(123,4) would multiply 123 by 4.

However, because the program's memory has been corrupted, there are also many invalid characters that should be ignored, even if they look like part of a mul instruction. Sequences like mul(4*, mul(6,9!, ?(12,34), or mul ( 2 , 4 ) do nothing.

For example, consider the following section of corrupted memory:

xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))
Only the four highlighted sections are real mul instructions. Adding up the result of each instruction produces 161 (2*4 + 5*5 + 11*8 + 8*5).

Scan the corrupted memory for uncorrupted mul instructions. What do you get if you add up all of the results of the multiplications?
*/


use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;


fn main() -> io::Result<()> {
  // Specify the file name
  let filename = "example.txt";

  // TIL: Open the file in read-only mode (returns a Result)
  let path = Path::new(filename);
  let file = File::open(&path)?;

  // Create a buffered reader
  let reader = io::BufReader::new(file);
  let mut res = 0;
  // Read the file line by line
  for line in reader.lines() {
      let line = line?; // Handle any errors while reading lines
      println!("line is {}", line);
      if let Some(index) = line.find("mul(") {
        let truncated_line = &line[index+4..];
        if let Some(comma) = truncated_line.find(",") {
          let first_num = &truncated_line[..comma];
          if let Some(as_i) = first_num.parse::<i32>() {
            println!("GOOD NUM {}", first_num);
          } else {
            println!("SKIPPING {}", first_num);
          }
        }
        println!("truncated and is now {}", truncated_line);
      } else {
        println!("not found");
      }

  }
  println!("res is {}", res);
  Ok(())
}