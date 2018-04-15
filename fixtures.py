from itertools import product
from math import pi, cos, sin


def _inner_points(center, radius, produce=100):
    """
    Generates all inner points of a circle with center **center** and radius
    **radius**.
    """
    result = list()
    shorter_radius = radius / 2

    for i in range(produce):
        x = center[0] + shorter_radius * cos(2 * pi * i / produce)
        y = center[1] + shorter_radius * sin(2 * pi * i / produce)

        result.append((x, y))

    return result


def _boundary_points(center, radius, produce=100):
    """
    Generates all boundary points of a circle with center **center** and
    radius **radius**.
    """
    result = list()

    for i in range(produce):
        x = center[0] + radius * cos(2 * pi * i / produce)
        y = center[1] + radius * sin(2 * pi * i / produce)

        result.append((x, y))

    return result


def _external_points(center, radius, produce=100):
    """
    Generates all outer, or external points of a circle with center
    **center** and radius **radius**.
    """
    result = list()
    longer_radius = 2 * radius

    for i in range(produce):
        x = center[0] + longer_radius * cos(2 * pi * i / produce)
        y = center[1] + longer_radius * sin(2 * pi * i / produce)

        result.append((x, y))

    return result


def generate_is_within_circle_fixture():
    centers = (
        (0, 0),
        (1, 0), (0, 1), (-1, 0), (0, -1),
        (3, 0), (0, 3), (-3, 0), (0, -3),
        (4, 4), (-4, 4), (-4, -4), (4, -4),
    )
    radiuses = (.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5)
    # rows stores the cartesian product between centers, radiuses and a long
    # series of points pointed at a value of centers away a value contained in
    # radiuses
    rows = list()

    for c, r in product(centers, radiuses):
        points = (
            (_inner_points(c, r), -1),
            (_boundary_points(c, r), 0),
            (_external_points(c, r), 1),
        )

        # classes is a set of points inside, on the boundary or
        # outside a given circle. zone is whether these points lie
        # inside, on the boundary or on the outside
        for classes, zone in points:
            rows.extend(
                product((c, ), (r, ), classes, (zone, ))
            )

    with open("fixtures/test_is_within_circle.csv", "w") as out:
        for r in rows:
            # Flattening a single row
            r = (*r[0], r[1], *r[2], r[3])
            # ... and turning all its elements to string values
            r = tuple(str(i) for i in r)

            out.write(",".join(r) + "\n")


if __name__ == "__main__":
    procedures = (generate_is_within_circle_fixture, )

    for p in procedures:
        print("Running %s()... " % p.__name__, end="")
        p()
        print("OK")
