fn main() {
    let tekst = "Voorbeeldtekst"; // type van tekst = &str
    let slice1 = &tekst[..9]; // slice, ook type &str, verwijst naar eerste 8 letters van tekst
    let slice2 = &tekst[9..]; // slice, verwijst naar de laatste letters vanaf positie 9
    let mut stekst = String::from("Voorbeeldtekst in een String"); // De String wordt gevormd uit een &str
    let mut slice3 = &stekst[..]; // een slice, type &str dus weer, met daarin de gehele String

    println!("tekst, een literal = {}", tekst);
    println!(
        "Eerste slice van de literal ..9, dat is exclusief karakter 9 = {}",
        slice1
    );
    println!(
        "Tweede slice van de literal 9.., dat is inclusief karakter 9 = {}",
        slice2
    );
    println!("Nu een String-variabele: {}", stekst);
    println!("En een slice met range .., dus de hele reeks: {}", slice3);

    stekst = String::from("Nu veranderen we stekst");

    println!("Nu is de variabele stekst: {}", stekst);
    println!("En de slice is: {}", slice3);
}
