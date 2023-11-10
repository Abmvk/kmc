use std::env;
use std::fs::File;
use std::io::{self, Read};

fn main() -> io::Result<()> {
    println!("\n\n");
    let args: Vec<String> = env::args().collect();

    assert!(
        args.len() == 3 && args[2].len() == 1,
        "Gebruik {} <bestandsnaam> <letter>\n",
        args[0]
    );

    let letter = args[2].chars().next().unwrap();

    assert!(
        letter.is_ascii_alphabetic(),
        "Gebruik {} <bestandsnaam> <letter>, andere tekens zijn niet toegestaan\n",
        args[0]
    );

    let mut bestand = File::open(args[1].as_str())?;
    let mut buffer = [0u8; 1];
    let mut teller = 0;

    while bestand.read_exact(&mut buffer).is_ok() {
        let karakter = buffer[0] as char;
        if karakter.to_ascii_uppercase() == letter.to_ascii_uppercase() {
            teller += 1;
        }
        print!("{}", karakter);
    }

    println!(
        "\n De letter {} kwam {} keer voor in {}, in hoofd- of kleine letter\n",
        letter, teller, args[1]
    );

    Ok(())
}
