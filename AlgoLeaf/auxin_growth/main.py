from matplotlib.patches import Polygon
from leaf import Leaf
from pylab import *

if __name__ == '__main__':

    fig, ax = plt.subplots()
    leaf_shape = Polygon([(-1, 0), (0, 2), (1, 0)], closed=True)

    Bob = Leaf(0.5, 0.5, leaf_shape, ax, 4)

    Bob.run_creation(10)

    Bob.display()



    ylim(0, 6)
    xlim(-4, 4)
    show()
