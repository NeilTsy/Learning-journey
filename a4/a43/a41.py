#!/usr/bin/env python
from typing import List

class HtmlComponent:
    def __init__(self, tag: str, elements: str):
        """Initialize an HTML component.

        Args:
            tag (str): The HTML tag for the component.
            elements (str): The elements to be included within the tag.
        """
        self.tag = tag
        self.elements = elements

class HtmlDocument:
    def __init__(self, title: str, body: str = ''):
        """Initialize an HTML document.

        Args:
            title (str): The title of the HTML document.
            body (str, optional): The body content of the HTML document. Defaults to an empty string.
        """
        self.header = f'<html>\n<head>\n   <title><{title}></title>\n</head>\n<body>\n'
        self.body = body
    
    def add_body(self, body: str):
        """Add content to the body of the HTML document.

        Args:
            body (str): The content to be added to the body.
        """
        self.body = body
    
    def gen_html(self) -> str:
        """Generate the HTML code for the document.

        Returns:
            str: The generated HTML code.
        """
        html_code = self.header + self.body
        return html_code
    
    def gen_file(self, filename: str):
        """Generate and write the HTML document to a file.

        Args:
            filename (str): The name of the file to write the HTML content.
        """
        with open(filename, 'w') as file:
            file.write(self.gen_html())

class CircleShape(HtmlComponent):
    def __init__(self, cx: int, cy: int, r: int, fill: str, fill_opacity: float):
        """Initialize a circle shape.

        Args:
            cx (int): The x-coordinate of the circle's center.
            cy (int): The y-coordinate of the circle's center.
            r (int): The radius of the circle.
            fill (str): The fill color of the circle.
            fill_opacity (float): The opacity of the circle's fill color.
        """
        elements = f'cx="{cx}" cy="{cy}" r="{r}" fill="{fill}" fill-opacity="{fill_opacity}"'
        super().__init__("circle", elements=elements)

class RectangleShape(HtmlComponent):
    def __init__(self, x: int, y: int, width: int, height: int, fill: str, fill_opacity: float):
        """Initialize a rectangle shape.

        Args:
            x (int): The x-coordinate of the top-left corner of the rectangle.
            y (int): The y-coordinate of the top-left corner of the rectangle.
            width (int): The width of the rectangle.
            height (int): The height of the rectangle.
            fill (str): The fill color of the rectangle.
            fill_opacity (float): The opacity of the rectangle's fill color.
        """
        elements = f'x="{x}" y="{y}" width="{width}" height="{height}" fill="{fill}" fill-opacity="{fill_opacity}"'
        super().__init__("rect", elements=elements)

class EllipseShape(HtmlComponent):
    def __init__(self, cx: int, cy: int, rx: int, ry: int, fill: str, fill_opacity: float):
        """Initialize an ellipse shape.

        Args:
            cx (int): The x-coordinate of the center of the ellipse.
            cy (int): The y-coordinate of the center of the ellipse.
            rx (int): The horizontal radius of the ellipse.
            ry (int): The vertical radius of the ellipse.
            fill (str): The fill color of the ellipse.
            fill_opacity (float): The opacity of the ellipse's fill color.
        """
        elements = f'cx="{cx}" cy="{cy}" rx="{rx}" ry="{ry}" fill="{fill}" fill-opacity="{fill_opacity}"'
        super().__init__("ellipse", elements=elements)

class SvgCanvas:
    def __init__(self, width: int, height: int, components: list):
        """Initialize an SVG canvas.

        Args:
            width (int): The width of the SVG canvas.
            height (int): The height of the SVG canvas.
            components (list): A list of HtmlComponent objects representing the elements to include in the SVG canvas.
        """
        self.width = width
        self.height = height
        self.components = components
    
    def gen_art(self) -> str:
        """Generate the SVG art content.

        Returns:
            str: The SVG art content as a string.
        """
        svg = f'   <svg width="{self.width}" height="{self.height}">\n'
        for component in self.components:
            svg += f'      <{component.tag} {component.elements}></{component.tag}>\n'
        svg += '   </svg>\n</body>\n</html>'
        return svg

def main():
    """Generate an SVG art and save it to an HTML file."""
    circle1 = CircleShape(50, 50, 50, "rgb(255,0,0)", 1)
    circle2 = CircleShape(150, 50, 50, "rgb(66,100,33)", 1)

    rectangle1 = RectangleShape(150, 50, 60, 40, "rgb(44,20,99)", 0.5)
    rectangle2 = RectangleShape(100, 100, 80, 60, "rgb(125,215,0)", 1)

    ellipse1 = EllipseShape(350, 80, 40, 20, "rgb(10,10,110)", 0.8)
    ellipse2 = EllipseShape(150, 50, 30, 35, "rgb(50,10,20)", 0.5)

    svg_canvas = SvgCanvas(500, 500, [circle1, circle2, rectangle1, rectangle2, ellipse1, ellipse2])

    html_document = HtmlDocument(title="My Art", body=svg_canvas.gen_art())

    html_document.gen_file("a41.html")

if __name__ == "__main__":
    main()




