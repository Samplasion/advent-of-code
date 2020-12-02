// Copyright (c) 2020 Samplasion <samplasion@gmail.com>
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

use std::{fs, env};

fn main() {
    println!("=============");
    println!("= AoC Day 2 =");
    println!("=============");
    println!();

    let filename = format!("{}/input.txt", env::current_dir().expect("Unable to get current dir").to_str().unwrap().to_string());
    let contents = fs::read_to_string(filename)
        .expect("Something went wrong reading the file");

    let lines: Vec<&str> = contents.split("\n").collect();

    let mut valid = 0;

    for line in &lines {
        let string_line = String::from(*line);
        let space_sep: Vec<&str> = string_line.split(" ").collect();
        let min_max: Vec<&str> = space_sep[0].split("-").collect();
        let min = min_max[0].parse().unwrap_or(0);
        let max = min_max[1].parse().unwrap_or(0);
        let letter = space_sep[1].chars().nth(0).expect("Failed to get chharacter at index 0");
        let password = space_sep[2];

        let str_pw = String::from(password);
        let char_pw: Vec<char> = str_pw.chars().filter(|c| -> bool {
            return c == &letter;
        }).collect();

        if char_pw.len() >= min && char_pw.len() <= max {
            valid += 1;
        }
    }

    println!("[Phase 1] The valid passwords in your input are {}", valid);

    let mut valid2 = 0;

    for line in lines {
        let string_line = String::from(line);
        let space_sep: Vec<&str> = string_line.split(" ").collect();
        let min_max: Vec<&str> = space_sep[0].split("-").collect();
        let min = min_max[0].parse().unwrap_or(0);
        let max = min_max[1].parse().unwrap_or(0);
        let letter = space_sep[1].chars().nth(0).expect("Failed to get character at index 0");
        let password = space_sep[2];

        let str_pw = String::from(password);
        let char_pw: Vec<char> = str_pw.chars().collect();

        // println!("{:>20}: [{}] {} {} {}", str_pw, letter, char_pw.len(), min, max);

        if char_pw.len() < min || char_pw.len() < max {
            continue;
        }
        
        // println!("[{}] {} {}, {} {}", letter, char_pw[min - 1], min-1, char_pw[max - 1], max-1);

        if (char_pw[min - 1] == letter && char_pw[max - 1] != letter) ||
           (char_pw[min - 1] != letter && char_pw[max - 1] == letter) {
            valid2 += 1;
        }
    }

    println!("[Phase 2] The valid passwords in your input are {}", valid2);
}
