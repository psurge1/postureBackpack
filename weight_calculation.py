class element:
    def __init__(self):
        self.weight = {"pounds":0, "grams":0}

    def set_weight(self, weight, units="grams"):
        if units == "pounds":
            self.weight["pounds"] = weight*1.0
            self.weight["grams"] = weight*453.59237
        elif units == "grams":
            self.weight["pounds"] = weight/453.59237
            self.weight["grams"] = weight*1.0
        else:
            print("ERR: wrong units")
    
    def get_weight(self, units="pounds"):
        return self.weight[units]
    
    def __str__(self):
        return self.get_weight("pounds")

def main():
    battery = element()
    battery.set_weight(48)
    motor = element()
    motor.set_weight(104)
    arduino_uno = element()
    arduino_uno.set_weight(25)
    wifi_sheild = element()
    wifi_sheild.set_weight(15)
    tennis_ball = element()
    tennis_ball.set_weight(57)
    accessories_and_wires = element()
    accessories_and_wires.set_weight(10)

    print(2*(battery.get_weight("grams")+motor.get_weight("grams")+tennis_ball.get_weight("grams"))+arduino_uno.get_weight("grams")+wifi_sheild.get_weight("grams")+accessories_and_wires.get_weight("grams"))
    print(2*(battery.get_weight()+motor.get_weight()+tennis_ball.get_weight())+arduino_uno.get_weight()+wifi_sheild.get_weight()+accessories_and_wires.get_weight())

if __name__ == '__main__':
    main()