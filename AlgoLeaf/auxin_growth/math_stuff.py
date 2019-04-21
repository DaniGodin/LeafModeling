from venationPoint import VenationPoint

class Vector:

    x_coord = None
    y_coord = None

    def __init__(self, _x, _y):
        self.x_coord = _x
        self.y_coord = _y


    def normalize(self):
        norme = (self.x_coord**2 + self.y_coord**2)**0.5
        self.x_coord = self.x_coord / norme
        self.y_coord = self.y_coord / norme

    def __add__(self, other):
        return Vector(self.x_coord + other.x_coord, self.y_coord + other.y_coord)

    def __rmul__(self, other):
        if isinstance(other, (int, float)):
            return Vector(self.x_coord * other,
                          self.y_coord * other)
        else:
            return NotImplemented


def get_distance(particule1, particule2):
    """

    :param particule1: a particle
    :param particule2: another particle
    :return: distance between both particle
    """
    x = particule2.position[0] - particule1.position[0]
    y = particule2.position[1] - particule1.position[1]

    return (x**2 + y**2)**0.5


def get_newNode(parentNode, auxin_list, step):

    direction = Vector(0, 0)
    for a in auxin_list:
        a_dir = Vector(a.position[0] - parentNode.position[0], a.position[1] - parentNode.position[1])
        a_dir.normalize()
        direction = direction + a_dir
    direction.normalize()
    direction = step * direction
    return VenationPoint([parentNode.position[0] + direction.x_coord, parentNode.position[1] + direction.y_coord])



