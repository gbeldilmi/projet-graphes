import random
import matplotlib.pyplot as plt

def draw_graph(graph = None):
    assert graph != None
    assert isinstance(graph, Graph)
    assert graph.get_width() > 0
    assert graph.get_height() > 0
    plt.figure("graph")
    plt.clf()
    plt.axis("off")
    for v in graph.get_vertices():
        plt.plot(v.get_coordinates()[0], v.get_coordinates()[1], "ko")
    for e in graph.get_edges():
        plt.plot([e.get_vertices()[0].get_coordinates()[0], e.get_vertices()[1].get_coordinates()[0]], [e.get_vertices()[0].get_coordinates()[1], e.get_vertices()[1].get_coordinates()[1]], "k-")
    plt.show()
class Vertice:
    def __init__(self, coordinates = (0,0), color = None):
        assert coordinates != None
        self.coordinates = coordinates
        self.set_color(color)
    def __str__(self):
        return f"{str(self.coordinates)}   \t{str(self.color)}"
    def get_color(self):
        return self.color
    def get_coordinates(self):
        return self.coordinates
    def is_in_interval(self, width = 0, height = 0):
        return self.coordinates[0] >= 0 and self.coordinates[1] >= 0 and self.coordinates[0] <= width and self.coordinates[1] <= height
    def set_color(self, color = None):
        self.color = color
class Edge:
    def __init__(self, vertices = (None, None), color = None):
        assert vertices != None
        assert vertices[0] != None
        assert vertices[1] != None
        assert isinstance(vertices[0], Vertice)
        assert isinstance(vertices[1], Vertice)
        self.vertices = vertices
        self.set_color(color)
    def __str__(self):
        return f"{str(self.vertices[0].get_coordinates())}   \t------\t\t{str(self.vertices[1].get_coordinates())}   \t{str(self.color)}"
    def get_color(self):
        return self.color
    def get_vertices(self):
        return self.vertices
    def is_in_interval(self, width = 0, height = 0):
        return self.vertices[0].is_in_interval(width, height) and self.vertices[1].is_in_interval(width, height)
    def reverse_vertices(self):
        (self.vertices[0], self.vertices[1]) = (self.vertices[1], self.vertices[0])
    def set_color(self, color = None):
        self.color = color
class Graph:
    def __init__(self, width = 100, height = 100, random_generation = False, vertice_number = 0, edge_probability = 1.0):
        self.width = width
        self.height = height
        self.vertices = []
        self.edges = []
        if random_generation:
            for n in range(vertice_number):
                x = random.random() * self.get_width()
                y = random.random() * self.get_height()
                new_vertice = Vertice((x,y))
                self.add_vertice(new_vertice)
                for v in self.get_vertices():
                    if random.random() <= edge_probability:
                        self.add_edge(Edge((new_vertice,v)))
    def __str__(self):
        output = "Graph:\n\tVertices:\n"
        for v in self.get_vertices():
            output += "\t\t" + str(v) + "\n"
        output += "\tEdges:\n"
        for e in self.get_edges():
            output += "\t\t" +str(e) + "\n"
        return output
    def add_edge(self, edge = None):
        assert edge != None
        assert isinstance(edge, Edge)
        assert edge.is_in_interval(self.width, self.height)
        for v in edge.get_vertices():
            if not v in self.get_vertices():
                self.add_vertice(v)
        self.edges.append(edge)
    def add_vertice(self, vertice = None):
        assert vertice != None
        assert isinstance(vertice, Vertice)
        assert vertice.is_in_interval(self.width, self.height)
        self.vertices.append(vertice)
    def get_edges(self):
        return self.edges
    def get_height(self):
        return self.height
    def get_vertices(self):
        return self.vertices
    def get_width(self):
        return self.width
    def get_vertice_degree(self, vertice = None):
        assert vertice != None
        assert isinstance(vertice, Vertice)
        assert vertice in self.get_vertices()
        degree = 0
        for e in self.edges:
            for i in range(2):
                if e.get_vertices()[i] == vertice:
                    degree += 1
        return degree
    def get_vertice_neighborhood(self, vertice = None):
        assert vertice != None
        assert isinstance(vertice, Vertice)
        assert vertice in self.vertices
        neighborhood = []
        for e in self.edges:
            for i in range(2):
                if e.get_vertices()[i] == vertice:
                    t = e.get_vertices()[0 if i == 1 else 1]
                    if not t in n: 
                        neighborhood.append(t)
        return neighborhood
    def is_in(self, object = None):
        if isinstance(object, Vertice):
            return object in self.get_vertices()
        if isinstance(object, Vertice):
            return object in self.get_edges()
        return False
    def reset_color(self):
        for v in self.get_vertices():
            v.set_color(None)
        for e in self.get_edges():
            e.set_color(None)
    def color_dsatur(self, k_improper = 0):
        self.reset_color()
        #############################################
        ## TODO
        #############################################

if __name__ == "__main__":
    g = Graph(random_generation = True, vertice_number = 10, edge_probability = 0.5)
    print(g)
    draw_graph(g)
