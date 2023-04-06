from sense_hat import SenseHat
from time import sleep

sense = SenseHat()
sense.set_rotation(180)

sense.clear((100,30,60))
sense.show_message("Bericht")
sense.clear()

x=0

while x<100000:
    for event in sense.stick.get_events():
        print(event.direction, event.action)
    x=x+1

X = [255,0,0]
O = [255, 255, 255]

vraagteken = [
O, O, O, X, X, O, O, O,
O, O, X, O, O, X, O, O,
O, O, O, O, O, X, O ,O,
O, O, O, O, X, O, O, O,
O, O, O, X, O, O, O, O,
O, O, O, X, O, O, O, O,
O, O, O, O, O, O, O, O,
O, O, O, X, O, O, O, O
]

sense.set_pixels(vraagteken)

x=0

while x<1000:
    sense.flip_h()
    sleep(1)
    sense.flip_v()
    sleep(1)
    print(sense.get_temperature())
    
    x=x+1
    
sense.clear(0,0,0)