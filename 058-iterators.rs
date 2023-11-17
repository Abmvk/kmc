fn main() {
    let array = [1, 2, 3, 4, 5];
    let mut totaal = 0;

    // met een for loop, klassiek

    for i in 0..5 {
        totaal += array[i];
    }

    println!("totaal is {}", totaal);

    // for loop, maar direct itereren over de array

    totaal = 0;

    for element in array.iter() {
        totaal += element;
    }

    println!("totaal is {}", totaal);

    // puur gebruik maken van de iterator

    let tot: i32 = array.iter().sum();

    println!("totaal is {}", tot);

    let totaal2: i32 = array.iter().map(|&x| x * x).sum();

    println!("De som van de kwadraten is {}", totaal2);

    // de C methode

    let mut tot2 = 0;
    let mut i = 0;

    while i < 5 {
        tot2 += array[i] * array[i];
        i += 1;
    }

    println!("De som van de kwadraten is {}", tot2);
}
