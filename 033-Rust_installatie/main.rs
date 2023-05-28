use std::io;

fn main()
{
	println!("Welkom! Wat is je naam?");

	let mut naam = String::new();

	io::stdin()
		.read_line(&mut naam)
		.expect("Kon de invoer niet lezen");

	println!("Hallo, {}! Welkom bij Rust.", naam.trim());
}

