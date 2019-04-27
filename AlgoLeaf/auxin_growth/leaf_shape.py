import random as rand

from pylab import *
import matplotlib.patches as patches

class first_param:

    growth_size = 0

    equation = None
    rectangle = None #where to project the points
    ax = None

    points = []


    def __init__(self, equation, _growth, rectangle):
        self.equation = equation
        self.growth_size = _growth
        self.rectangle = rectangle
        fig, self.ax = plt.subplots()


    def plot_shape(self):
        x = np.linspace(-1.0, 1.0, 1000)
        y = np.linspace(-0.5, 1.0, 1000)
        X, Y = np.meshgrid(x, y)
        F = -((self.growth_size * X) ** 2 + (self.growth_size * Y - 1) ** 2 - 1) ** 3 - \
            ((self.growth_size * X) ** 2) * ((self.growth_size * Y - 1) ** 3)
        self.ax.contour(X, Y, F, [0])
        x = self.rectangle[0][0]
        y = self.rectangle[0][1]
        x_lim = x + self.rectangle[1]
        y_lim = y + self.rectangle[2]

        rect = patches.Rectangle((x, y), x_lim, y_lim, linewidth=1, edgecolor='r', facecolor='none')
        self.ax.add_patch(rect)
        show()



    def plot_points(self, coord):
        plot(coord[0], coord[1], 'bo')

    def gen_point(self):
        coord = None
        find = False
        x = self.rectangle[0][0]
        y = self.rectangle[0][1]
        x_lim = x + self.rectangle[1]
        y_lim = y + self.rectangle[2]
        while not find:
            r1 = x + random() * (x_lim - x)
            r2 = y + random() * (y_lim - y)

            if (-((self.growth_size * r1) ** 2 + (self.growth_size * r2 - 1) ** 2 - 1) ** 3 - \
            ((self.growth_size * r1) ** 2) * ((self.growth_size * r2 - 1) ** 3)) >= 0:
                find = True
                coord = [r1, r2]
        return coord



