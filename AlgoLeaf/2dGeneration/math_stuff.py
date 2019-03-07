from scipy.spatial import distance


def translation(point, dir_petiole, dir_neighbour, s):
    """

    :param point: coord of the particle we want to translate
    :param dir_petiole: Unit vector to the petiole
    :param dir_neighbour: Unit vector to the neighbour
    :param s: let us control the translation
    :return: The coord of the point translated by the two vectors
    """
    x = point[0] + 2 * s * dir_petiole[0] + s * dir_neighbour[0]
    y = point[1] + 2 * s * dir_petiole[1] + s * dir_neighbour[1]
    return [x, y]


def get_unit_vector(point1, point2):
    """

    :param point1: first point
    :param point2: second point
    :return: A unit vector computed with the two points
    """
    x = point2[0] - point1[0]
    y = point2[1] - point1[1]
    norme = (x**2 + y**2)**0.5
    return [x / norme, y / norme]


def nearest_neigbour(particle, particle_set):
    """

    :param particle: coord of the particle we want to find the neighbour
    :param particle_set: list of all the coord of all particles
    :return: the coordinate of the nearest particle of "particle"
    """
    closest_index = distance.cdist([particle.coord], [x.coord for x in particle_set]).argmin()

    return particle_set[closest_index]


def get_distance(particule1, particule2):
    """

    :param particule1: a particle
    :param particule2: another particle
    :return: distance between both particle
    """
    x = particule2.coord[0] - particule1.coord[0]
    y = particule2.coord[1] - particule1.coord[1]

    return (x**2 + y**2)**0.5


def merge_pos(particule1, particule2):
    """

    :param particule1: a particle
    :param particule2: another particle
    :return: the mean distance between both
    """

    x = (particule1.coord[0] + particule2.coord[0]) / 2
    y = (particule1.coord[1] + particule2.coord[1]) / 2

    return [x, y]
