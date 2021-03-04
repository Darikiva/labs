import matplotlib.pyplot as plt
import matplotlib.patches as patches
from matplotlib.collections import LineCollection

# return value of numerator of the 'distance point to line'-formula
def calc_distance(l, r, point) -> float:
    x1 = l[0]
    y1 = l[1]
    x2 = r[0]
    y2 = r[1]
    x0 = point[0]
    y0 = point[1]
    return (y2 - y1) * x0 - (x2 - x1) * y0 + x2 * y1 - y2 * x1

# return the point that is on the greatest distance to the line built on points l and r
def farthest_point(S, l, r):
    dist = -1
    answer = [0, 0]
    for point in S:
        new_dist = abs(calc_distance(l, r, point))
        # print(new_dist)
        if (new_dist > dist):
            dist = new_dist
            answer = point
    # print(dist)
    return answer

# return points on the left of line built on points l and r
def points_on_the_left(S, l, r):
    answer = []
    for point in S:
        if calc_distance(l, r, point) <= 0:
            answer.append(point)
    return answer

# the same idea as in the quick sort
def quick_convex_hull(S, l, r):
    if len(S) == 0:
        return []
    if (S == [l, r]):
         return [l, r]
    elif S == [r, l]:
        return [l, r]
    elif S ==[l]:
        return [l]
    elif S == [r]:
        return [r]
    else :
        h = farthest_point(S, l, r)
        if h == l or h == r:
            return [l, r]
        S1 = points_on_the_left(S, l, h)
        S2 = points_on_the_left(S, h, r)
        return quick_convex_hull(S1, l, h) + quick_convex_hull(S2, h, r)


def read_points():
    fv = open("points.txt")
    points = []
    for line in fv.readlines():
        coordinates = [float(i) for i in line.split(" ")]
        points.append([coordinates[0], coordinates[1]])
    fv.close()
   
    return points


# first point to the algorithm is the point with the smallest x coordinate
def first_point(S):
    answer = S[0]
    for point in S:
        if point[0] < answer[0]:
            answer = point
    return answer

# clown shit but still it works
def draw_smth(points, convex_hull):
    fig, ax = plt.subplots()

    ax.set_xlim([-2, 10])
    ax.set_ylim([-2, 10])

    ps = []
    for point in points:
        circle = patches.Circle((point[0], point[1]), radius=0.15, color='g')
        ax.add_patch(circle)
        
    lc1 = LineCollection(ps, linewidths=10, colors='r')
    ax.add_collection(lc1)

    lines = []
    n = len(convex_hull) - 1
    lines.append([(convex_hull[n][0], convex_hull[n][1]), (convex_hull[0][0], convex_hull[0][1])])
    for i in range(1, len(convex_hull)):
        lines.append([(convex_hull[i - 1][0], convex_hull[i - 1][1]), (convex_hull[i][0], convex_hull[i][1])])
    lc = LineCollection(lines, linewidths=1, colors='k')
    ax.add_collection(lc)
    
    # ax.autoscale()
    plt.show()


S = read_points()
fp = first_point(S)
an = quick_convex_hull(S, fp, [fp[0], fp[1]])
draw_smth(S, an)