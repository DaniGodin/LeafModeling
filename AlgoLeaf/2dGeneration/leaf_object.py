"""
This module implement the class Leaf and Venation Point
"""


import numpy as np
from pylab import *
from matplotlib import collections as mc
import matplotlib.pyplot as plt
from matplotlib.patches import Ellipse


class Leaf:
    """
    This object decribe the leaf shape

    attributes:
        shape: parametric descrption of the leaf shape
        petiole: coordinate of the petiole point #for some species it will be a list of petioles (reed)
        venation: VenationPoint structure containing recursively treepoints, representing the venations of the leaf

    """

    shape = "basic"
    petiole = (0, 0)
    venation = None
    ax = None

    def __init__(self, shape, petiole, venations, ax):
        self.shape = shape
        self.petiole = petiole
        self.venation = VenationPoint(petiole, venations)
        self.ax = ax

    def display_venation(self):
        if self.venation:
            line = [[self.petiole, self.venation.coord]]
            lc = mc.LineCollection(line, linewidths= 0.01, color='black')
            self.ax.add_collection(lc)
            self.venation.display_venation(self.ax)

        self.ax.autoscale()

    def display_petiole(self):
        plot(self.petiole[0], self.petiole[1], 'bo')

    def display_shape(self):
        self.shape.set_alpha(0.1)
        self.shape.set_facecolor("Green")
        self.ax.add_artist(self.shape)


class VenationPoint:
    """
    This object represent a venation point

    attributes:
        coord: coordinate of the point
        childrens: list of the point directly connected to this one
        PhotoEnergy: quantity of PhotoEnergy  going through this point

    """
    coord = None
    children = None
    PhotoEnergy = 1

    def __init__(self, point, children):
        self.coord = point
        self.children = children
        self.compute_energy()

    def display_venation(self, ax):
        if self.children:
            for elt in self.children:
                line = [self.coord, elt.coord]
                lc = mc.LineCollection([line], linewidths=elt.PhotoEnergy, color='black')
                ax.add_collection(lc)
                elt.display_venation(ax)

    def compute_energy(self):
        energy = 0
        for child in self.children:
            energy += child.PhotoEnergy
        self.PhotoEnergy = max(energy, 1)
