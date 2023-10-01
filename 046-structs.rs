enum Soort {
    Mens,
    Hond,
    Kat,
}

struct Bewoner {
    mens: bool,
    naam: String,
    woning: u32,
    soort: Soort,
}

impl Bewoner {
    fn voeren(&self) -> bool {
        !self.mens
    }
}

fn main() {
    let mut bewoner: [Bewoner; 4] = [
        Bewoner {
            mens: true,
            naam: String::from("Henk"),
            woning: 2,
            soort: Soort::Mens,
        },
        Bewoner {
            mens: true,
            naam: String::new(),
            woning: 0,
            soort: Soort::Mens,
        },
        Bewoner {
            mens: true,
            naam: String::new(),
            woning: 0,
            soort: Soort::Mens,
        },
        Bewoner {
            mens: true,
            naam: String::new(),
            woning: 0,
            soort: Soort::Mens,
        },
    ];

    bewoner[1] = Bewoner {
        mens: true,
        naam: String::from("Marie"),
        woning: 2,
        soort: Soort::Mens,
    };

    bewoner[2] = nieuwe_kat("Poekie".to_string(), 2);

    bewoner[3] = nieuwe_kat("Bello".to_string(), 2);
    bewoner[3].soort = Soort::Hond;

    println!();

    for bewoner in &bewoner {
        print!(
            "bewoner: naam: {}, woning: {}    ",
            bewoner.naam, bewoner.woning
        );
        println!(
            "moet {} gevoerd worden!",
            if bewoner.voeren() { "WEL" } else { "NIET" }
        );
    }
}

fn nieuwe_kat(naam: String, woning: u32) -> Bewoner {
    Bewoner {
        mens: false,
        naam,
        woning,
        soort: Soort::Kat,
    }
}
