from matplotlib.patches import Polygon
from leaf import Leaf
from leaf_shape import first_param
from pylab import *

sys.setrecursionlimit(1800)

if __name__ == '__main__':


    """

    leaf_shape = Polygon([(-1, 0), (0, 3), (1, 0)], closed=True)    

    Bob = Leaf(0.5, 0.6, leaf_shape,150, 4, 0.004)
    

    Bob.run_creation(1300)

    Bob.display(8, 15)
    
    """
    fig, ax = plt.subplots()

    shape3 = lambda x, y, g, a, b :(-b*((g* 2 * a * x)**2 + (g * y - 1)**2 - 1) **3 - ((g*b*x)**2)*(g*y)**3 )

    shape1 = lambda x, y, g, a, b : (-((g * x) ** 2 + (g * y - 1) ** 2 - 1) ** 3 - \
            ((g * x) ** 2) * ((g * y - 1) ** 3))

    leaf_shape1 = first_param(shape1, 12,  ([-0.7, -0.2], 2, 1.4))

    leaf_shape2 = first_param(shape3, 12, ([-0.4, -0.2], 1.7, 2), 2, 4)

    #Bob = Leaf(0.08, 0.09, leaf_shape2 ,85, 6, 0.04)

    Bob = Leaf(0.08, 0.08, leaf_shape1, 75, 4, 0.02)

    #Bob.run_creation(4800)

    Bob.run_creation(1200)

    print(Bob.shape.growth_size)
    print(len(Bob.get_ventree().childrens))

    Bob.display(8, 15, ax)



