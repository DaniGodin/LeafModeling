from matplotlib.patches import Polygon
from leaf import Leaf
from leaf_shape import first_param
from pylab import *



if __name__ == '__main__':


    """

    leaf_shape = Polygon([(-1, 0), (0, 3), (1, 0)], closed=True)    

    Bob = Leaf(0.5, 0.6, leaf_shape,150, 4, 0.004)

    Bob.run_creation(1300)

    Bob.display(8, 15)
    
    """
    fig, ax = plt.subplots()

    shape1 = lambda x, y, g : (-((g * x) ** 2 + (g * y - 1) ** 2 - 1) ** 3 - \
            ((g * x) ** 2) * ((g * y - 1) ** 3))


    leaf_shape = first_param(shape1, 12, ([-0.7, -0.2], 2, 1.4))
    Bob = Leaf(0.08, 0.08, leaf_shape,75, 4, 0.02)

    Bob.run_creation(1050)

    Bob.display(8, 15, ax)

