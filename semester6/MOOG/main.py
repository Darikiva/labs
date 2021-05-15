import sympy as sp
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from matplotlib.collections import LineCollection
import numpy as np
import math

LEFT, ON, RIGHT = (-1, 0, 1)


class ZeroBasicFunction:
    def __init__(self, left, right):
        super().__init__()
        self.left_border = left
        self.right_border = right

    def __call__(self, u) -> float:
        left = self.left_border
        right = self.right_border
        if left <= u and u < right:
            return 1
        else:
            return 0


class BasicFunction:
    def __init__(self, left, right, u_i, u_i1, u_ip, u_ip1):
        super().__init__()
        self.left_basic_function = left
        self.right_basic_function = right
        self.u_i = u_i
        self.u_i1 = u_i1
        self.u_ip = u_ip
        self.u_ip1 = u_ip1

    def __call__(self, u=0.0) -> float:
        left_res = 0.0
        if self.u_ip != self.u_i:
            left_res = ((u - self.u_i) / (float)(self.u_ip -
                                                 self.u_i)) * self.left_basic_function(u)
        right_res = 0.0
        if self.u_ip1 != self.u_i1:
            right_res = ((self.u_ip1 - u) / (float)(self.u_ip1 - self.u_i1)) * \
                self.right_basic_function(u)

        return left_res + right_res


class BSpline:
    def __init__(self, N=[], points=[]):
        super().__init__()
        self.N = N.copy()
        self.points = points.copy()
        self.n = len(points)
        self.degree = len(N) - 1

    def __call__(self, x):
        n_sum = 0.0
        degree = self.degree
        points = self.points
        N = self.N
        for i in range(0, len(points)):
            n_sum += N[degree][i](x)
        res_x = 0.0
        res_y = 0.0
        for i in range(0, len(points)):
            res_x += (N[degree][i](x) * points[i][0]) / n_sum
            res_y += (N[degree][i](x) * points[i][1]) / n_sum
        return [res_x, res_y]


def check_side(start_point, end_point, target):
    x1 = start_point[0]
    y1 = start_point[1]
    x2 = end_point[0]
    y2 = end_point[1]
    x0 = target[0]
    y0 = target[1]
    dist = (y2 - y1) * x0 - (x2 - x1) * y0 + x2 * y1 - y2 * x1
    if dist < 0:
        return LEFT
    elif dist == 0:
        return ON
    elif dist > 0:
        return RIGHT


def generate_polygon(points=[]):
    p = sorted(points, key=lambda x: x[0])
    result_points = [p[0]]
    polygon = [
        [p[0], p[1]],
    ]
    heh = check_side(p[0], p[1], p[2])
    index = 0
    if heh == RIGHT:
        result_points.append(p[2])
        result_points.append(p[1])
        polygon.append([p[1], p[2]])
        polygon.append([p[0], p[2]])
        index = 1
    else:
        result_points.append(p[1])
        result_points.append(p[2])
        polygon.append([p[0], p[2]])
        polygon.append([p[1], p[2]])
        index = 2
    for i in range(3, len(points)):
        side = check_side(polygon[-1][0], polygon[-1][1], p[i])
        last_edge = [[], []]
        if side == RIGHT:
            last_edge = polygon[-1].copy()
            polygon.remove(polygon[-1])
            result_points.insert(index, p[i])
        else:
            last_edge = polygon[-2].copy()
            polygon.remove(polygon[-2])
            index += 1
            result_points.insert(index, p[i])
        if last_edge[0][1] > last_edge[1][1]:
            polygon.append([last_edge[0], p[i]])
            polygon.append([last_edge[1], p[i]])
        else:
            polygon.append([last_edge[1], p[i]])
            polygon.append([last_edge[0], p[i]])

    return polygon, result_points


def generate_knots(amount=0):
    res = []
    for i in range(0, amount):
        res.append(i / (amount - 1))
    return res


def generate_basic_functions(degree=0, knots=[]):
    knots_amount = len(knots)
    N = []
    zero_basic = []

    for p in range(0, knots_amount - 1):
        zero_basic.append(ZeroBasicFunction(knots[p], knots[p + 1]))
    N.append(zero_basic)
    for p in range(1, degree + 1):
        basic_functions = []
        for i in range(0, knots_amount - p - 1):
            basic_functions.append(BasicFunction(
                N[p - 1][i], N[p - 1][i + 1], knots[i], knots[i + 1], knots[i + p], knots[i + p + 1]))
        N.append(basic_functions)
    return N


def generate_bspline(points=[], degree=0):
    polygon, points_in_order = generate_polygon(points)
    for p in range(0, 3):
        points_in_order.append(points_in_order[p])
    knots_amount = len(points_in_order) + degree + 1
    knots = generate_knots(knots_amount)
    N = generate_basic_functions(degree, knots)
    return BSpline(N, points_in_order), knots


def draw_spline(spline, points=[], knots=[]):

    X = []
    Y = []

    parameter = np.linspace(knots[spline.degree],
                            knots[-spline.degree - 1], 1000)
    for i in parameter:
        wow = spline(i)
        X.append(wow[0])
        Y.append(wow[1])
    fig, ax = plt.subplots()

    min_x = min(points, key=lambda x: x[0])[0]
    min_y = min(points, key=lambda x: x[1])[1]
    min_lim = min([min_x, min_y]) - 1
    max_x = max(points, key=lambda x: x[0])[0]
    max_y = max(points, key=lambda x: x[1])[1]
    max_lim = max([max_x, max_y]) + 1

    ax.set_xlim([min_lim, max_lim])
    ax.set_ylim([min_lim, max_lim])
    ps = []
    for point in points:
        circle = patches.Circle((point[0], point[1]), radius=0.15, color='g')
        ax.add_patch(circle)

    lc1 = LineCollection(ps, linewidths=10, colors='r')
    ax.add_collection(lc1)
    ax.plot(X, Y)
    plt.show()


points = [
    [1., 1.],
    [2., 3.],
    [3., 2.],
    [4., 4.],
    [5., 1.],
    [6., 5.],
    [7., 3.],
    [9., 1.],
    [10., 2.], ]

spline, knots = generate_bspline(points, 3)
draw_spline(spline, points, knots)