import matplotlib.pyplot as plt
import matplotlib.patches as patches

class Node:
    def __init__(self, lx, rx, left_son, right_son):
        self.lx = lx
        self.rx = rx
        self.left_son = left_son
        self.right_son = right_son
        self.node = None
        self.points = []

    def __repr__(self):
        answer = "{" + str(self.lx) + ", " + str(self.rx) + "}\n"
        if self.points.__len__() != 0:
            answer += "points:" + self.points.__repr__()
        else:
            answer += "subtree:" + self.node.__repr__()
        answer += '\n'
        if (self.left_son):
            answer += "left: " + self.left_son.__repr__()
        if (self.right_son):
            answer += "right: " + self.right_son.__repr__()
        return answer


def build_tree(points, l_ind, r_ind, dimension) -> Node:
    lx = points[l_ind][dimension]
    rx = points[r_ind][dimension]
    new_node = Node(lx, rx, None, None)
    if (dimension == len(points[0]) - 1):
        for i in range(0, r_ind - l_ind + 1):
            new_node.points.append(points[l_ind + i])
    elif dimension < len(points[0]) - 1:
        new_points = []
        for i in range(0, r_ind - l_ind + 1):
            new_points.append(points[l_ind + i])
        new_points = sorted(new_points, key=lambda x: x[dimension + 1])
        new_node.node = build_tree(
            new_points, 0, len(new_points) - 1, dimension + 1)
    if (r_ind == l_ind + 1):
        new_node.left_son = build_tree(points, l_ind, l_ind, dimension)
        new_node.right_son = build_tree(points, r_ind, r_ind, dimension)
        return new_node
    if (r_ind - l_ind > 0):
        m_ind = int((r_ind + l_ind) / 2)
        mx = points[m_ind][dimension]
        new_node.left_son = build_tree(points,l_ind, m_ind, dimension)
        new_node.right_son = build_tree(points, m_ind, r_ind, dimension)
    return new_node

def find_points_in_region(root, dimension, answer, region):
    if root == None: 
        return
    l = root.lx
    r = root.rx
    if region[dimension][0] <= l and region[dimension][1] >= r:
        if root.node == None:
            for point in root.points:
                answer.append(point)
            return
        find_points_in_region(root.node, dimension + 1, answer, region)
    else:
        if region[dimension][0] <= r:
            find_points_in_region(root.left_son, dimension, answer, region)
        if region[dimension][1] >= l:
            find_points_in_region(root.right_son, dimension, answer, region)

def read_points(file_name):
    points_list = []
    input_array = open(file_name).read().split()

    i = 0
    while i < len(input_array):
        points_list.append([int(input_array[i]), int(input_array[i + 1])])
        i += 2
    points_list = sorted(points_list, key=lambda x: x[0])
    return points_list

def draw_points(points, region):
    fig, ax = plt.subplots()

    rect = patches.Rectangle((region[0][0], region[1][0]), region[0][1], region[1][1], linewidth = 1, edgecolor='r', facecolor='none')
    ax.add_patch(rect)

    for point in points:
        circle = patches.Circle((point[0], point[1]), radius=0.051, color='g')
        ax.add_patch(circle)
    ax.autoscale()
    plt.show()

points = read_points("points.txt")
region = read_points("region.txt")
draw_points(points, region)
tree = build_tree(points, 0, len(points) - 1, 0)
answer = []
find_points_in_region(tree, 0, answer, region)
print(answer)
print(region)
print(tree)
draw_points(answer, region)