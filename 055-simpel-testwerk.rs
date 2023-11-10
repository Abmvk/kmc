use std::f64::consts;

fn main() {
    let resultaat = 22.0 / 7.0;
    if resultaat == consts::PI {
        println!("Pi = 22/7");
    }
    assert!(
        resultaat == consts::PI,
        "\nresultaat = {}\nPI is       {}\n",
        resultaat,
        consts::PI
    );
}
