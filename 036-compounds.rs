fn print_hello() -> () {
	println!("\nHello world!");
}


fn main() {
	let voorbeeld_tuple: (i32, i32, bool) = (10, 20, true);

	let (a, b, c) = voorbeeld_tuple;

	let b2 = voorbeeld_tuple.1;

	println!("\n\nde tuple is ({a},{b2},{c})\n\n");

	let array1 = ["maandag", "dinsdag", "woensdag", "donderdag", "vrijdag"];

	let array2: [f64; 3] = [1.0, 2.0, 3.0];
	
	let array3 = [0; 10];

	println!("\narray1, index 3 = {}", array1[3]);

	println!("\narray2, index 1/index 2 = {}", array2[1]/array2[2]);

	println!("\narray3, index 8 = {}", array3[8]);

	print_hello();
}
