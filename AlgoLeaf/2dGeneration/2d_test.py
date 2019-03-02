
class TreePoint:
    coord = None
    childrens = None

    def __init__(self, point):
        self.coord = point
        self.childrens = []

    def display_Tree(self):
        print(self.coord)
        for elt in self.childrens:
            elt.display_Tree()



def gen_tree(size, root, shape):
    print("ouais")




if __name__ == '__main__':

    Root = TreePoint((0,0))
    Root.display_Tree()
