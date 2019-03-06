import numpy as np
from matplotlib.patches import Ellipse
from matplotlib.patches import Polygon
from Leaf_objects import Leaf, VenationPoint, Particle
from Gen_Random import get_initial


if __name__ == '__main__':

    leaf_shape = Polygon([(-3, 0), (0, 6), (3, 0)], closed=True)
    initial_particles = get_initial(leaf_shape, 10)
    print(initial_particles)
    """
    Ven5 = VenationPoint((0.5, 2.5), [])
    Ven4 = VenationPoint((1.5, 2.5), [])
    Ven3 = VenationPoint((1, 2), [Ven4, Ven5])
    Ven2 = VenationPoint((-1, 2), [])
    Ven1 = VenationPoint((0, 1), [Ven2, Ven3])
    """
    L = Leaf(leaf_shape, (0, 0), None)
    for p in initial_particles:
        p.display_particle()
    L.display_leaf()



