

class Texture:
    vertex = []
    nvertex = []
    faces = []

    def __init__(self, name):
        self.name = name


    def export_texture(self):
        f = open(self.name)


    def merge_texture(self, texure2):
        # ghetto
        print("merge")
    def add_vertice(self, point):
        self.vertex.append(point)

    def add_nornal(self, vector):
        self.nvertex.append(vector)




if __name__ == '__main__':
    Cube = Texture("Cube")


