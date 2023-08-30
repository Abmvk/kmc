fn main() {

	let mut x = inc(5);
	druk_af(x);
	x = inc(inc(x));
	druk_af(x);

	let y = {
		let x = 10;
		println!("\nx in scope y-expressie is {x}");
		x + 5
	};

	println!("y is {y}");
	druk_af(x);


}

fn inc(x : i32) -> i32 {

	return x + 1;

}


fn druk_af(x: i32) {

	println!("x is {x}");

}


