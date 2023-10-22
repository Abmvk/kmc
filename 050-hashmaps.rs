use std::collections::HashMap;

#[derive(Debug, PartialEq, Eq, Hash)]
enum Seizoen {
    Lente,
    Zomer,
    Herfst,
    Winter,
    Onbekend,
}

fn main() {
    let mut seizoenen = HashMap::new();
    let mut ook_een_voorbeeld = HashMap::new();

    seizoenen.insert(String::from("seizoen1"), Seizoen::Lente);
    seizoenen.insert(String::from("seizoen2"), Seizoen::Herfst);

    ook_een_voorbeeld.insert(4, vec![3, 6, 2]);
    ook_een_voorbeeld.insert(2, vec![1, 2, 4, 6]);

    let voorbeeld = ook_een_voorbeeld.get(&2);

    println!("\n\nDe voorbeeld HashMap = {:?}", ook_een_voorbeeld);
    println!("voorbeeld = {:?}", voorbeeld);
    println!("\n\nDe seizoenen HashMap = {:?}", seizoenen);

    seizoenen.insert(String::from("seizoen1"), Seizoen::Winter);

    println!(
        "\n\nAls het goed is, is seizoen1 nu vervangen door Winter: {:?}",
        seizoenen
    );

    seizoenen
        .entry(String::from("seizoen1"))
        .or_insert(Seizoen::Lente);
    seizoenen
        .entry(String::from("seizoen3"))
        .or_insert(Seizoen::Zomer);

    println!(
        "\n\nNu zou seizoen1 nog steeds Winter moeten zijn, en seizoen3 Zomer: {:?}",
        seizoenen
    );
}
