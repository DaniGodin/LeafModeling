from leaf_object import VenationPoint
from pylab import *
from math_stuff import translation, get_unit_vector,nearest_neigbour, get_distance, merge_pos, compute_dir


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
            p.dir_to_p = get_unit_vector(p.coord, self.petiole)

    def get_closest(self, particle):
        neighbours = list(self.particles)
        neighbours.remove(particle)
        return nearest_neigbour(particle, neighbours)

    def move_particles(self, stepsize, weight_n, weight_t):
        print(len(self.particles))
        if len(self.particles) == 1:
            return
        else:
            for p in self.particles:
                q = self.get_closest(p)
                if get_distance(p, q) < 0.01:
                    p.last_venation = VenationPoint(merge_pos(p, q), [p.last_venation, q.last_venation])
                    self.particles.remove(q)
                else:
                    dir_closer = get_unit_vector(p.coord, q.coord)
                    p.move(dir_closer, stepsize, weight_n, weight_t)
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

    def move(self, dir_closer, stepsize, weight_n, weight_t):

        direction = compute_dir(self.dir_to_p, dir_closer, weight_n, weight_t)
        self.coord = translation(self.coord, direction, stepsize)
        self.last_venation = VenationPoint(self.coord, [self.last_venation])

