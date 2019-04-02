from particle_object import Particle
import random

"""
The goal of this file is to get a list of random point
inside the leaf shapes

"""


def get_initial(shape, num_particles):
    """

    :param shape: the description of the leaf shape
           num_particles: number of random particles you want to generate
    :return: The list of random particles inside the shape
    """
    Vertices = shape.get_xy()
    print(Vertices)
    particles_list = []

    for i in range(num_particles):
        r1 = random.random()
        r2 = random.random()

        x_rand = (1 - r1**0.5) * Vertices[0][0] + (r1**0.5) * (1 - r2) * Vertices[1][0] + Vertices[2][0] * r2 * (r1**0.5)
        y_rand = (1 - r1**0.5) * Vertices[0][1] + (r1**0.5) * (1 - r2) * Vertices[1][1] + Vertices[2][1] * r2 * (r1**0.5)
        P = Particle([x_rand, y_rand])
        particles_list.append(P)

    return particles_list
