from pylab import *
from matplotlib import collections as mc


class VenationPoint:

    position = None

    def __init__(self, coord):
        self.position = coord

    def display(self):
        plot(self.position[0], self.position[1], 'bo')

class VenNodePlot:

    position = None
    radius = 0
    childrens = []

    def __init__(self, child_list, position):
        self.position = position
        self.childrens = child_list
        if self.childrens:
            sum = 0
            for c in self.childrens:
                sum += c.radius**2
            self.radius = sum ** 0.5
        else:
            self.radius = 1

    def display_ven(self, ax):
        if self.childrens:
            for elt in self.childrens:
                line = [self.position, elt.position]
                lc = mc.LineCollection([line], linewidths= elt.radius , color='black')
                ax.add_collection(lc)
                elt.display_ven(ax)





