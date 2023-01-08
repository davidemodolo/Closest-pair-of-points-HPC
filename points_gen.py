import random

# Number of dimensions for the points
num_dimensions = 5

# Number of points to generate
num_points = 100000

# Lower and upper bounds for the coordinates
lower_bound = 0
upper_bound = 100

points = []
for i in range(num_points):
    point = []
    for j in range(num_dimensions):
        point.append(random.uniform(lower_bound, upper_bound))
    points.append(point)

# Save the points to a file
with open('points.txt', 'w') as f:
    for point in points:
        f.write(' '.join([str(coordinate) for coordinate in point]) + '\n')
