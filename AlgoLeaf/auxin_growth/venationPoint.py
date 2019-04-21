from pylab import *


class VenationPoint:

    position = None

    def __init__(self, coord):
        self.position = coord

    def display(self):
        plot(self.position[0], self.position[1], 'bo')
