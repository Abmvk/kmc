enum Bewoner {
    Mens { naam: String, leeftijd: u32 },
    Kat { naam: String },
    Kanarie,
}

impl Bewoner {
    fn print(&self) {
        match self {
            Bewoner::Mens { naam, leeftijd } => {
                println!("Bewoner heet {} en is {} jaar oud", naam, leeftijd)
            }
            Bewoner::Kat { naam } => println!("De bewoner heet {} en is een kat", naam),
            Bewoner::Kanarie => println!("De bewoner is een kanarie"),
        }
    }
}

fn huisdier(bewoner: Bewoner) -> u8 {
    match bewoner {
        Bewoner::Mens {
            naam: _,
            leeftijd: _,
        } => {
            println!("In dit huis woont ook een mens!");
            0
        }
        Bewoner::Kat { naam: _ } => 1,
        Bewoner::Kanarie => 1,
    }
}

fn main() {
    let bewoner1 = Bewoner::Mens {
        naam: String::from("Henk"),
        leeftijd: 50,
    };

    let bewoner2 = Bewoner::Kat {
        naam: String::from("Poekie"),
    };

    let bewoner3 = Bewoner::Kanarie;

    print!("\n\n\nDe eerste bewoner: ");
    bewoner1.print();
    print!("De tweede bewoner: ");
    bewoner2.print();
    print!("De derde bewoner: ");
    bewoner3.print();

    let aantal_huisdieren;

    aantal_huisdieren = huisdier(bewoner1) + huisdier(bewoner2) + huisdier(bewoner3);

    println!("In dit huishouden wonen {aantal_huisdieren } huisdieren\n\n\nEn nu nog wat andere rariteiten met enums en matching");

    let x = Some(1);
    let y = Some('y');
    let z: Option<i16> = None;

    println!("{:?}", x);
    println!("{:?}", y);
    println!("{:?}\n", z);
}
