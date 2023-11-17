fn plus_a(x: i32, a: i32) -> i32 {
    x + a
}

fn main() {
    let a = 5;
    let mut b = 6;
    b = plus_a(b, a);
    println!("b = {:?}", b);

    let mut c = 6;
    let add_a = |x| x + a;
    c = add_a(c);
    println!("c = {:?}", c);
}
