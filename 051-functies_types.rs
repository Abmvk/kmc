fn largest<T: std::cmp::PartialOrd>(list: &[T]) -> &T {
    let mut largest = &list[0];

    for item in list {
        if item > largest {
            largest = item;
        }
    }
    largest
}

fn aantal<T>(list: &[T]) -> u16 {
    let mut teller = 0;

    for _ in list {
        teller += 1;
    }
    teller
}

fn main() {
    let number_list = vec![34, 50, 25, 100, 65];

    let result = largest(&number_list);
    let lengte = aantal(&number_list);
    println!("Van de {} nummers, is {} het grootst", lengte, result);

    let char_list = vec!['y', 'm', 'a', 'q'];

    let result = largest(&char_list);
    let lengte = aantal(&char_list);
    println!("Van de {} characters, is '{}' het grootst", lengte, result);
}
