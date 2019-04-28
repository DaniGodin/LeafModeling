from auxin import AuxinNode
from venationPoint import VenationPoint, VenNodePlot
from math_stuff import get_distance
from math_stuff import get_newNode
from scipy.spatial import distance
from pylab import *


import random


class Leaf:

    #struct shape
    VenationsList = {} #graphe
    AuxinsList = [] #just a list
    shape = None #for the momentb only a triangle
    birth_distance = None
    KD_venation = None
    dart_step = None
    petiole = None
    growth_step = None

    def __init__(self, _birth, kd_venation, _shape, _dart_step, _initial, _growth):
        self.birth_distance = _birth
        self.KD_venation = kd_venation
        self.shape = _shape
        self.dart_step = _dart_step
        self.petiole = VenationPoint([0, 0])
        self.VenationsList[self.petiole] = []
        self.gen_auxin(_initial)
        self.growth_step = _growth

    def display(self, x, y, ax):
        self.shape.plot_shape(ax)
        self.display_auxins()
        #self.display_venNodes()
        Root = self.get_ventree()
        Root.display_ven(ax)
        show()


    def display_auxins(self):
        for auxin in self.AuxinsList:
            auxin.display()

    def display_venNodes(self):
        for ven in self.VenationsList:
            ven.display()


    def build_venation(self, VenPoint):
        childrens = self.VenationsList[VenPoint]
        if childrens == []:
            return VenNodePlot([], VenPoint.position)
        else:
            ven_c = []
            for c in childrens:
                ven_c.append(self.build_venation(c))
            return VenNodePlot(ven_c, VenPoint.position)

    def get_ventree(self):
        root = self.petiole
        childrens = self.VenationsList[root]
        ven_c = []
        for c in childrens:
            ven_c.append(self.build_venation(c))
        return VenNodePlot(ven_c, root.position)



    def run_creation(self, nb_iterations):


        for i in range(nb_iterations):
            self.gen_nodes(0.0006)
            self.kill_auxins()
            self.gen_auxin(self.dart_step)
            self.grow_shape(self.growth_step)

    def get_closest(self, aux):
        all_vens = list(self.VenationsList.keys())
        closest_index = distance.cdist([aux.position], [x.position for x in all_vens]).argmin()
        aux.closest = all_vens[closest_index]


    def gen_nodes(self, step):
        new_nodes =[]
        for ven in self.VenationsList.keys():
            aux = []
            for a in self.AuxinsList:
                if a.closest == ven:
                    aux.append(a)
            if aux:
                new_ven = get_newNode(ven, aux, step)
                for a in aux:
                    if get_distance(a, new_ven) < get_distance(a, ven):
                        a.closest = new_ven
                new_nodes.append(new_ven)
                self.VenationsList[ven].append(new_ven)
        for node in new_nodes:
            self.VenationsList[node] = []


    def gen_auxin(self, nb_auxin):
        for i in range(nb_auxin):
            """
            r1 = random.random()
            r2 = random.random()

            #general growth

            x_rand = (1 - r1 ** 0.5) * Vertices[0][0] + (r1 ** 0.5) * (1 - r2) * Vertices[1][0] + Vertices[2][
                0] * r2 * (r1 ** 0.5)
            y_rand = (1 - r1 ** 0.5) * Vertices[0][1] + (r1 ** 0.5) * (1 - r2) * Vertices[1][1] + Vertices[2][
                1] * r2 * (r1 ** 0.5)


            #marginal growth
            """
            x_rand, y_rand = self.shape.gen_point()

            A = AuxinNode([x_rand, y_rand])

            to_append = True
            for auxin in self.AuxinsList:
                if get_distance(auxin, A) < self.birth_distance:
                    to_append = False
                    break
            for ven in self.VenationsList:
                if get_distance(A,ven) < self.birth_distance:
                    to_append = False
                    break
            if to_append:
                self.get_closest(A)
                self.AuxinsList.append(A)

    def kill_auxins(self):
        to_remove = []
        for aux in self.AuxinsList:
            if get_distance(aux, aux.closest) < self.KD_venation:
                to_remove.append(aux)
        for aux in to_remove:
            self.AuxinsList.remove(aux)

    def grow_shape(self, step):
        """
        vertices = self.shape.get_xy()
        sign = lambda a: 1 if a > 0 else -1 if a < 0 else 0
        for v in vertices:
            v[0] += step * sign(v[0])
            v[1] += step * sign(v[1])
        vertices[1][1] += step * sign(vertices[1][1])
        """
        self.shape.growth_size -= step