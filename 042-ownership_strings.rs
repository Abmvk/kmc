fn main() {
    let s1 = "Hallo";
    let s2 = String::from("Hallo");
    // let mut s3 = "Hallo"; //aangezien we niks gaan doen met s3 is de mut overbodig, en de compiler geeft een warning
    let mut s4 = String::from("Hallo");

    // s1 += "wereld":      mag niet, want s1 is nit mutable
    // s2.push_str(" wereld"); mag niet, want s2 is niet mutable
    // s3 += "wereld";      mag niet, je kan geen twee string-constanten aan elkaar knopen met +
    // de enige manier om zo met strings te werken is ze niet als constante definieren, mutable
    // maken, en gebruik maken van .push_str()

    s4.push_str(" wereld");
    s4.push_str(s1); // dit mag, omdat s1 een string-literal is
                     // s4.push_str(s2); dit mag niet, omdat s2 geen string-literal is

    println!("s1: {}", s1);
    println!("s2: {}", s2);
    // println!("s3: {}", s3);
    println!("s4: {}", s4);

    // verschillen tussen simpele variabelen, met een bekende lengte, en complexere variabelen, met
    // onbekende lengte.

    let x = 1; // x == 1
    let y = x; // y == 1 en x == 1. Omdat dit simpele typen zijn, integers, kan de waarde doorgegeven worden zonder dat de oude waarde verdwijnt

    println!("\nx={x} en y={y}");

    let sa = String::from("Hallo"); // sa = "Hallo" (let op, geen string-literal!)
    let sb = sa; // sb = "Hallo", maar sa niet meer! Ownership van de string is overgedragen, niet de waarde zelf

    // println!("\nsa = {}", sa); dit mag dus niet, want sa is ownership kwijt
    println!("\nsb = {}", sb);
}
