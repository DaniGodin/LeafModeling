from leaf_object import VenationPoint
from pylab import *
from math_stuff import *


class Particle_set:
    """
    This object represent a set of Partciles object.
    """

    particles = []
    petiole = None

    def __init__(self, particles, petiole):
        self.particles = particles
        self.petiole = petiole
        self.init_venation()
        self.init_vector()


    def display_particles(self):
         for p in self.particles:
            p.display_particle()

    def init_venation(self):
        for p in self.particles:
            p.last_venation = VenationPoint(p.coord, [])


    def init_vector(self):
        for p in self.particles:
            p.dir_to_p = [self.petiole[0] - p.coord[0], self.petiole[1] - p.coord[1]]

    def move_particles(self):
        for p in self.particles:
            p.move()
        self.init_vector()

    def get_venations(self):
        venations = []
        for p in self.particles:
            venations.append(p.last_venation)
        return venations


class Particle:
    """
    This object represent a Particle of light

    attributes:
        coord: currant position of the particle
        last_venation: VenationPoint object, corresponding to the last position of the particle
        dir_to_p: the direction to go to the petiole
    """
    dir_to_p = None
    coord = None
    last_venation = None

    def __init__(self, coord):
        self.coord = coord

    def display_particle(self):
        plot(self.coord[0], self.coord[1], 'ro')

    def move(self):

        self.coord = translation(self.coord, self.dir_to_p, self.dir_to_p)
        self.last_venation = VenationPoint(self.coord, [self.last_venation])

