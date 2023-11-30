use clap::Parser;
use std::io::{self, BufRead, BufReader};

#[derive(Parser, Debug, Clone)]
struct Args {
    #[clap(short, long, default_value = "x")]
    ch: char,
}

fn main() -> io::Result<()> {
    let args = Args::parse();

    let search_char = args.ch.to_lowercase().next().unwrap();

    let r = BufReader::new(io::stdin());
    let n = r.lines().try_fold(0, |partial, line| -> io::Result<_> {
        let count = line?
            .chars()
            .filter(|&c| c.to_lowercase().next().unwrap() == search_char)
            .count();
        Ok(partial + count)
    })?;

    println!("\nHet karakter {} komt {n} maal voor.\n", args.ch);

    Ok(())
}
