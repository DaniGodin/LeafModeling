import numpy as np
from matplotlib import pyplot as plt
from pylab import *
from matplotlib.patches import Polygon
from leaf_object import Leaf, VenationPoint
from particle_object import Particle, Particle_set
from Gen_Random import get_initial


if __name__ == '__main__':

    fig, ax = plt.subplots()

    leaf_shape = Polygon([(-3, 0), (0, 6), (3, 0)], closed=True)
    particles = Particle_set(get_initial(leaf_shape, 1000), [0, 0])

    for i in range(100):
        particles.move_particles(0.2, 1, 2)
        """
        particles.display_particles()
        ylim(0, 6)
        xlim(-4, 4)
        show()
        """

    L = Leaf(leaf_shape, [0, 0], particles.get_venations(), ax)
    L.display_petiole()
    L.display_shape()
    L.display_venation()
    particles.display_particles()

    ylim(0, 6)
    xlim(-4, 4)
    show()
