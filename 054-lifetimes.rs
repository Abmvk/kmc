fn langste<'a>(s1: &'a str, s2: &'a str) -> &'a str {
    if s1.len() > s2.len() {
        s1
    } else {
        s2
    }
}

fn main() {
    let st1 = String::from("kort");
    let st2 = String::from("veel langer");
    let result = langste(&st1, &st2);
    println!("De langste string is: {}", result);
}
