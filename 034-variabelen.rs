
const BYTES_PER_64K: u32 = 64 * 1024;

fn main() {

// mutable of niet? Laat mut weg en zie wat er gebeurt bij compileren
	let mut x = 5;
	println!("x is {x}");
	x = 6;
	println!("x is {x}");

//constante. Let op, rekenen binnen {} werkt niet in println!, dus buiten de "" halen
	println!("64K is {BYTES_PER_64K}");
	println!("Het hoogste adres is dan {}",BYTES_PER_64K-1);
	
//shadowing
	let s = 5;
	let s = s + 1;

	{
		let s = s * 2;
		println!("S in de binnenste scope is {s}");
	}

	println!("Maar buiten die scope is s {s}");

// shadowing met verandering van type
	let spaties = "   ";
	let spaties = spaties.len();

	println!("Aantal spaties was {spaties}");

/*	Dit mag dus niet:

	let mut spaties = "   ";
	spaties = spaties.len();

*/

}
