from pylab import *
class AuxinNode:

    position = None
    closest  = None #closest venationpoint

    def __init__(self, coord):
       self.position = coord

    def display(self):
        plot(self.position[0], self.position[1], 'ro')