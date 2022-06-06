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
    
    def get_weight(self, units="grams"):
        return self.weight[units]

def main():
    battery = element()
    battery.set_weight(48, "grams")
    print(battery.get_weight("grams"))

if __name__ == '__main__':
    main()