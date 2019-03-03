import numpy as np
from matplotlib.patches import Ellipse

from Leaf_objects import Leaf, VenationPoint


if __name__ == '__main__':

    leaf_shape = Ellipse((0, 3), 6, 3.5, 90)

    Ven5 = VenationPoint((0.5, 2.5), [])
    Ven4 = VenationPoint((1.5, 2.5), [])
    Ven3 = VenationPoint((1, 2), [Ven4, Ven5])
    Ven2 = VenationPoint((-1, 2), [])

    Ven1 = VenationPoint((0, 1), [Ven2, Ven3])
    L = Leaf(leaf_shape, (0, 0), Ven1)

    L.display_leaf()



