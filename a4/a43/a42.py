import random
from collections import namedtuple

Shape = namedtuple("Shape", ["shape", "cx", "cy", "radius", "width", "height", "rx", "ry", "R", "G", "B", "op"])

class PyArtConfig:
    SHA_Range = (0, 3)
    X_Range = (0, 501)
    Y_Range = (0, 501)
    RAD_Range = (0, 101)
    RX_Range = (10, 31)
    RY_Range = (10, 31)
    W_Range = (10, 101)
    H_Range = (10, 101)
    C_Range = (0, 256)
    OP_Range = (0, 1)

    def __init__(self, X_Range=501, Y_Range=501, RAD_Range=(0, 101), C_Range=(0, 256)):
        """Initialize PyArtConfig.

        Args:
            X_Range (int, optional): Range of X values for shapes. Defaults to (0, 501).
            Y_Range (int, optional): Range of Y values for shapes. Defaults to (0, 501).
            RAD_Range (tuple, optional): Range of radius values for circle shapes. Defaults to (0, 101).
            C_Range (tuple, optional): Range of color component values (R, G, B) for shapes. Defaults to (0, 256)
        """
        self.RAD_Range = RAD_Range
        self.C_Range = C_Range
        self.X_Range = (0, X_Range)
        self.Y_Range = (0, Y_Range)

class RandomShape(PyArtConfig):
    def __init__(self, X_Range: int, Y_Range: int):
        """Initialize RandomShape.

        Args:
            X_Range (int): Range of X values for shapes.
            Y_Range (int): Range of Y values for shapes.
        """
        super().__init__(X_Range, Y_Range)
        self.shape = random.randrange(*self.SHA_Range)
        self.cx = random.randrange(*self.X_Range)
        self.cy = random.randrange(*self.Y_Range)
        self.radius = random.randrange(*self.RAD_Range)
        self.rx = random.randrange(*self.RX_Range)
        self.ry = random.randrange(*self.RY_Range)
        self.width = random.randrange(*self.W_Range)
        self.height = random.randrange(*self.H_Range)
        self.R = random.randrange(*self.C_Range)
        self.G = random.randrange(*self.C_Range)
        self.B = random.randrange(*self.C_Range)
        self.colour = f'rgb({self.R},{self.G},{self.B})'
        self.op = round(random.random(), 1)

    def __str__(self) -> str:
        """Return a string representation of the RandomShape object.

        Returns:
            str: String representation of the RandomShape object.
        """
        if self.shape == 0:
            return f'Shape: {self.shape}, Radius: {self.radius} Color: {self.colour}'
        elif self.shape == 1:
            return f'Shape: {self.shape}, Width {self.width}, Height: {self.height}, Color: {self.colour}'
        else:
            return f'Shape: {self.shape}, Color: {self.colour}'
        
    def as_Part2_line(self, count: int) -> str:
        """Generate a formatted string of the object data for Part 2.

        Args:
            count (int): The shape count.

        Returns:
            str: Formatted string of the object data for Part 2.
        """
        attributes = [count, self.shape, self.cx, self.cy, self.radius, self.rx, self.ry, self.width, self.height, self.R, self.G, self.B, self.op]
        numbers = [str(num).rjust(3) for num in attributes]
        result = " ".join(numbers) + "\n"
        return result
    
    def as_svg(self) -> str:
        """Generate an SVG representation of the RandomShape object.

        Returns:
            str: SVG representation of the RandomShape object.
        """
        if self.shape == 0:
            return f'<circle cx="{self.cx}" cy="{self.cy}" r="{self.radius}" fill={self.colour} fill-opacity="{self.op}" />\n'
        elif self.shape == 1:
            return f'<rect x="{self.rx}" y="{self.ry}" width="{self.width}" height="{self.height}" fill={self.colour} fill-opacity="{self.op}" />\n'
        elif self.shape == 2:
            return f'<ellipse cx="{self.cx}" cy="{self.cy}" rx="{self.rx}" ry="{self.ry}" fill=rgb{self.colour} fill-opacity="{self.op}" />\n'
        
def main():
    """ This function generates 10 random shapes using the RandomShape class and prints their attributes in a nicely formatted
    table format as depicted in Table 1."""
    print("CNT SHA   X   Y RAD  RX  RY   W   H   R   G   B  OP\n")
    table = []
    for i in range(0, 10):
        shape = RandomShape(501, 501)
        shape_data = Shape(shape=shape.shape, cx=shape.cx, cy=shape.cy, radius=shape.radius,
                           width=shape.width, height=shape.height, rx=shape.rx, ry=shape.ry,
                           R=shape.R, G=shape.G, B=shape.B, op=shape.op)
        table.append(shape_data)
        print(shape.as_Part2_line(i))

if __name__ == "__main__":
    main()


