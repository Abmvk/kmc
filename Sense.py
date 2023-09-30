from sense_hat import SenseHat

sense = SenseHat()

for a in range(0,100):
    for x in range(0,255):
        for wacht in range(0,5):
            sense.clear((x,0,0))

    for x in range(0,255):
        for wacht in range(0,5):
            sense.clear((0, x, 0))

    for x in range(0,255):
        for wacht in range(0,5):
            sense.clear((0,0,x))
