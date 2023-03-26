from sense_hat import SenseHat

sense = SenseHat()

def tropisch_checker():
    # Haal de temperatuur op van de Sense HAT
    temp = sense.get_temperature()

    if temp >= 30:
        # Verander de achtergrondkleur van de Sense HAT naar rood
        sense.clear((255, 0, 0))
        print("Het is een tropische dag, denk eraan dat je genoeg drinkt!")
    else:
        # Verander de achtergrondkleur van de Sense HAT naar groen
        sense.clear((0, 255, 0))
        print("Het is geen tropische dag.")

# Roep de functie aan
tropisch_checker()