trait OppervlakteBerekening {
    fn oppervlakte(&self) -> f64;
}

trait Kleur {
    fn kleur(&self) -> String {
        String::from("groen")
    }
}

trait InhoudBerekening: OppervlakteBerekening {
    fn inhoud(&self, hoogte: f64) -> f64 {
        self.oppervlakte() * hoogte
    }
}

struct Vierkant {
    zijde: f64,
}

impl OppervlakteBerekening for Vierkant {
    fn oppervlakte(&self) -> f64 {
        self.zijde * self.zijde
    }
}

impl Kleur for Vierkant {}
impl InhoudBerekening for Vierkant {}

struct Cirkel {
    straal: f64,
}

impl OppervlakteBerekening for Cirkel {
    fn oppervlakte(&self) -> f64 {
        std::f64::consts::PI * self.straal * self.straal
    }
}

impl Kleur for Cirkel {}
impl InhoudBerekening for Cirkel {}

struct Driehoek {
    basis: f64,
    hoogte: f64,
}

impl OppervlakteBerekening for Driehoek {
    fn oppervlakte(&self) -> f64 {
        0.5 * self.basis * self.hoogte
    }
}

impl Kleur for Driehoek {}
impl InhoudBerekening for Driehoek {}


fn main() {
    let vierkant = Vierkant { zijde: 5.0 };
    let cirkel = Cirkel { straal: 3.0 };
    let driehoek = Driehoek {
        basis: 4.0,
        hoogte: 6.0,
    };

    println!("\nOppervlakte van het vierkant: {}", vierkant.oppervlakte());
    println!("Oppervlakte van de cirkel: {}", cirkel.oppervlakte());
    println!("Oppervlakte van de driehoek: {}\n", driehoek.oppervlakte());
    
    println!("De kleur van het vierkant is {}", vierkant.kleur());
    println!("De kleur van de cirkel is {}", cirkel.kleur());
    println!("De kleur van de driehoek is {}\n", driehoek.kleur());
    
    println!("De inhoud van een vierkante plank is {}", vierkant.inhoud(2.0));
    println!("De inhoud van een ronde plank is {}", cirkel.inhoud(2.0));
    println!("De inhoud van een driehoukige plank is {}", driehoek.inhoud(2.0));
}
