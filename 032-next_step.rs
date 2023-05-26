fn square(num: i32) -> i32 {
    num * num
}

fn main() {
    let number = 5;
    let result = square(number);
    println!("Het kwadraat van {} is {}", number, result);
}
