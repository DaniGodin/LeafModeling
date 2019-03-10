from scipy.spatial import distance


def translation(point, direction, stepsize):
    """

    :param point: coord of the particle we want to translate
    :param dir_petiole: Unit vector to the petiole
    :param dir_neighbour: Unit vector to the neighbour
    :param s: let us control the translation
    :return: The coord of the point translated by the two vectors
    """
    x = point[0] + stepsize * direction[0]
    y = point[1] + stepsize * direction[1]
    return [x, y]


def compute_dir(dir_t, dir_n, weight_n, weight_t):
    """

    :param dir_t: vector direction to target
    :param dir_n: vector direction to neighbour
    :param weight_n: weight of neighbout
    :param weight_t: weight of target
    :return: normalise vector to the direction
    """

    x = (dir_t[0] * weight_t + dir_n[0] * weight_n) / (weight_t + weight_n)
    y = (dir_t[1] * weight_t + dir_n[1] * weight_n) / (weight_t + weight_n)
    norme = (x**2 + y**2)**0.5
    return [x / norme, y /norme]


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
