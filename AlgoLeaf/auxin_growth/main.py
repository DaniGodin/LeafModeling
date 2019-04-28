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

    leaf_shape = first_param(None, 6, ([-0.7, -0.2], 2, 1.4))
    Bob = Leaf(0.05, 0.06, leaf_shape,75, 4, 0.004)

    Bob.run_creation(1000)

    Bob.display(8, 15, ax)

