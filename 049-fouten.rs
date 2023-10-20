fn delen(teller: f64, noemer: f64) -> Result<f64, String> {
    if noemer == 0.0 {
        return Err("Noemer mag niet nul zijn.".to_string());
    }
    Ok(teller / noemer)
}

fn main() {
    //1. abort functie

    println!("Deze regel zie je wel");
    std::process::abort();
    println!("En deze ga je dus nooit zien");

    //2. panic macro
    //
    //  let test_string = String::from("Dit moet worden opgeruimd");
    //  panic!("Dit is een panic, maar eerst is wel alles opgeruimd");
    //  println!("De string die opgeruimd moest worden is {:?}", test_string);
    //
    //
    //3. Herstelbare fout, met Result<T, E>
    //
    //  let resultaat = delen(5.0, 0.0);
    //
    //  match resultaat {
    //      Ok(waarde) => println!("Resultaat: {}", waarde),
    //      Err(error) => println!("Foutmelding: {}", error),
    //    }
    //
    //
    //4. En nu met unwrap
    //
    //  let resultaat = delen(5.0, 3.0);
    //
    //  let waarde = resultaat.unwrap();
    //
    //  println!("Resultaat: {waarde}");
    //
    //
    //5. En met een expect
    //
    //  let resultaat = delen(5.0, 0.0);
    //
    //  let waarde = resultaat.expect("Kan de waarde niet berekenen");
    //
    //  println!("Resultaat: {waarde}");
}
