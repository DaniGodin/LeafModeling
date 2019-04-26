import random as rand

from pylab import *

class first_param:

    growth_size = 0

    equation = None

    points = []


    def __init__(self, equation, _growth):
        self.equation = equation
        self.growth_size = _growth


    def plot_shape(self, _growth):
        self.gen_points(1)
        self.plot_points()
        self.growth_size = _growth
        x = np.linspace(-1.0, 1.0, 1000)
        y = np.linspace(-0.5, 1.0, 1000)
        X, Y = np.meshgrid(x, y)
        F = -((self.growth_size * X) ** 2 + (self.growth_size * Y - 1) ** 2 - 1) ** 3 - \
            ((self.growth_size * X) ** 2) * ((self.growth_size * Y - 1) ** 3)
        plt.contour(X, Y, F, [0])
        plt.show()


    def plot_points(self):
        plot(self.points[0][0], self.points[0][1], 'bo')

    def gen_points(self, nb_points):
        find = False
        while not find:
            r1 = random()
            r2 = random()

            if (-((self.growth_size * r1) ** 2 + (self.growth_size * r2 - 1) ** 2 - 1) ** 3 - \
            ((self.growth_size * r1) ** 2) * ((self.growth_size * r2 - 1) ** 3)) >= 0:
                find = True
                self.points.append([r1, r2])




