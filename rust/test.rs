use std::env;

fn main()
{
	let args: Vec<String> = env::args().collect();
	let program_path = &args[0];

	println!("Programma pad: {}", program_path);

	if args.len() > 1
		{
		println!("Extra argumenten:");
		for arg in args.iter().skip(1)
			{
				println!("{} ", arg);
			}
		}
}

