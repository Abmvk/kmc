/* Conway's Game of Life in idiomatisch Rust
 *
 * Dit is een Rust-vertaling van de C implementatie (031-life.c), met gebruik van
 * Rust idiomen zoals ownership, enums, pattern matching en iterators.
 *
 * Gebruikt pancurses voor terminal graphics (cross-platform ncurses wrapper)
 */

use pancurses::{initscr, endwin, Input, Window, A_REVERSE, cbreak, noecho};

const WELCOME_TEXT: &str = "\
Welkom bij Conway's Game of Life.

Het 'spel' speelt zich af op een oneindig veld van cellen die leven of niet leven. \
Oneindigheid wordt benaderd doordat het hele scherm (of window) van de terminal wordt \
gebruikt, en doordat het overloopt. Dat betekent dat de cel helemaal links grenst aan \
de cel helemaal rechts, en net zo de cellen helemaal boven en onderaan het scherm.

In eerste instantie kan je cellen aan en uit zetten. De cursor kan je daartoe verplaatsen \
met de q, a, o en p-toetsen. Met de spatiebalk zet je de cel van de cursor aan of uit. \
Je kan ook met t aangeven dat je altijd wil tekenen, met g dat je altijd wil gummen, \
en met b dat je weer een blanco-functie wil. Als je klaar bent druk je op enter.

Daarna zal het programma zelf steeds nieuwe generaties berekenen en afbeelden. Als je \
achter life een aantal hebt opgegeven dan wordt dat aantal generaties uitgevoerd. Als \
je niets hebt opgegeven worden 1.000 generaties uitgevoerd. Als je geen toets indrukt, \
pauzeert het programma tussen twee generaties. Druk je dan op f, dan wordt niet meer \
gepauzeerd.
";

/// De drie modi waarin de cursor zich kan bevinden tijdens het tekenen
#[derive(Debug, Clone, Copy, PartialEq)]
enum DrawMode {
    Blank,  // alleen togglen met spatie
    Draw,   // overal waar je komt wordt getekend
    Erase,  // overal waar je komt wordt gewist
}

/// De Game of Life structuur met twee velden voor double-buffering
struct GameOfLife {
    field: Vec<Vec<bool>>,      // het huidige, zichtbare veld
    buffer: Vec<Vec<bool>>,     // buffer voor berekening volgende generatie
    max_x: usize,
    max_y: usize,
}

impl GameOfLife {
    /// Maak een nieuw, leeg Game of Life veld van de opgegeven grootte
    fn new(max_x: usize, max_y: usize) -> Self {
        let field = vec![vec![false; max_y + 1]; max_x + 1];
        let buffer = vec![vec![false; max_y + 1]; max_x + 1];

        GameOfLife {
            field,
            buffer,
            max_x,
            max_y,
        }
    }

    /// Zet een cel aan of uit (alleen voor weergave, verandert het veld niet)
    fn draw_cell(&self, window: &Window, x: i32, y: i32, alive: bool) {
        if alive {
            window.mvaddch(x, y, (' ' as u32) | A_REVERSE);
        } else {
            window.mvaddch(x, y, ' ');
        }
    }

    /// Teken het hele veld op het scherm
    fn draw_field(&self, window: &Window) {
        for (x, row) in self.field.iter().enumerate() {
            for (y, &cell) in row.iter().enumerate() {
                self.draw_cell(window, x as i32, y as i32, cell);
            }
        }
        window.refresh();
    }

    /// Tel het aantal levende buren rondom een cel (met wrapping aan de randen)
    fn count_neighbors(&self, x: usize, y: usize) -> usize {
        let mut count = 0;

        // Doorloop alle 9 cellen (3x3 grid) rondom de cel
        for dx in -1..=1 {
            for dy in -1..=1 {
                // Skip de cel zelf
                if dx == 0 && dy == 0 {
                    continue;
                }

                // Bereken buur-coördinaten met wrapping (toroidal topology)
                let nx = if x == 0 && dx == -1 {
                    self.max_x
                } else if x == self.max_x && dx == 1 {
                    0
                } else {
                    (x as i32 + dx) as usize
                };

                let ny = if y == 0 && dy == -1 {
                    self.max_y
                } else if y == self.max_y && dy == 1 {
                    0
                } else {
                    (y as i32 + dy) as usize
                };

                if self.field[nx][ny] {
                    count += 1;
                }
            }
        }

        count
    }

    /// Bereken de volgende generatie volgens de regels van Conway's Game of Life
    ///
    /// Regels:
    /// - Levende cel met 2 of 3 buren blijft leven
    /// - Dode cel met exact 3 buren komt tot leven
    /// - Alle andere cellen sterven of blijven dood
    fn next_generation(&mut self) {
        // Bereken nieuwe status in buffer
        for x in 0..=self.max_x {
            for y in 0..=self.max_y {
                let neighbors = self.count_neighbors(x, y);
                let alive = self.field[x][y];

                self.buffer[x][y] = match (alive, neighbors) {
                    (true, 2) | (true, 3) => true,  // blijft leven
                    (false, 3) => true,              // wordt geboren
                    _ => false,                      // sterft of blijft dood
                };
            }
        }

        // Kopieer buffer naar field
        for x in 0..=self.max_x {
            for y in 0..=self.max_y {
                self.field[x][y] = self.buffer[x][y];
            }
        }
    }

    /// Laat de gebruiker het startveld tekenen met interactieve cursor
    fn edit_field(&mut self, window: &Window) {
        let mut x = self.max_x / 2;
        let mut y = self.max_y / 2;
        let mut mode = DrawMode::Blank;

        loop {
            // Teken het hele veld
            self.draw_field(window);

            // Toon cursor positie met # of _ afhankelijk van cel status
            window.mv(x as i32, y as i32);
            if self.field[x][y] {
                window.addch('#');
            } else {
                window.addch('_');
            }
            window.mv(x as i32, y as i32);

            // Lees toetsenbord input
            match window.getch() {
                Some(Input::Character('t')) => mode = DrawMode::Draw,
                Some(Input::Character('g')) => mode = DrawMode::Erase,
                Some(Input::Character('b')) => mode = DrawMode::Blank,

                Some(Input::Character('q')) => {
                    if x > 0 { x -= 1; }
                }
                Some(Input::Character('a')) => {
                    if x < self.max_x { x += 1; }
                }
                Some(Input::Character('o')) => {
                    if y > 0 { y -= 1; }
                }
                Some(Input::Character('p')) => {
                    if y < self.max_y { y += 1; }
                }

                Some(Input::Character(' ')) => {
                    self.field[x][y] = !self.field[x][y];
                }

                Some(Input::Character('\n')) => break,

                _ => {}
            }

            // Pas teken/gum mode toe
            match mode {
                DrawMode::Draw => self.field[x][y] = true,
                DrawMode::Erase => self.field[x][y] = false,
                DrawMode::Blank => {}
            }
        }
    }

    /// Run de simulatie voor een aantal generaties
    fn run_simulation(&mut self, window: &Window, generations: usize) {
        let mut remaining = generations;
        let mut paused = true;

        while remaining > 0 {
            self.next_generation();
            self.draw_field(window);

            // Toon aantal resterende generaties linksboven
            window.mv(0, 0);
            window.printw(&format!("{}", remaining));
            window.refresh();

            // Wacht op toets als gepauzeerd, of check voor 'f' om te unpauzeren
            if paused {
                if let Some(Input::Character('f')) = window.getch() {
                    paused = false;
                }
            }

            remaining -= 1;
        }

        // Eind-boodschap
        window.mv(0, 0);
        window.printw("Dat waren alle generaties");
        window.getch();
    }
}

/// Parse command-line argument voor aantal generaties
fn parse_generations(args: &[String]) -> usize {
    if args.len() > 1 {
        args[1].parse().unwrap_or(1000)
    } else {
        1000
    }
}

fn main() {
    // Parse argumenten
    let args: Vec<String> = std::env::args().collect();
    let generations = parse_generations(&args);

    // Initialiseer ncurses
    let window = initscr();
    cbreak();
    noecho();
    window.keypad(true);
    window.clear();

    // Bepaal schermgrootte
    let max_y = window.get_max_y() - 1;
    let max_x = window.get_max_x() - 1;

    // Toon welkomstscherm
    window.printw(WELCOME_TEXT);
    window.printw(&format!("\n\n\nEr worden {} generaties berekend.", generations));
    window.printw("\n\n\nDruk op een toets als je dit hebt begrepen.\n\n\n");
    window.getch();
    window.clear();

    // Maak het spel
    let mut game = GameOfLife::new(max_x as usize, max_y as usize);

    // Laat gebruiker het startveld tekenen
    game.edit_field(&window);

    // Run de simulatie
    game.run_simulation(&window, generations);

    // Cleanup
    window.clear();
    window.refresh();
    endwin();
}
