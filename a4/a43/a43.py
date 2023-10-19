#!/usr/bin/env python

import random
import sys

from a41 import HtmlDocument, SvgCanvas, CircleShape, RectangleShape, EllipseShape
from a42 import PyArtConfig, RandomShape

def generate_card(config,width,height,count,file_name) -> None:
    """
    Generate a greeting card with random SVG art.

    This function generates a greeting card containing random art in the form of an HTML-SVG page.
    The art is generated using random shapes like circles, rectangles, and ellipses with random colors
    and opacity within the specified ranges.

    Arguments:
        config (PyArtConfig): The configuration object with ranges for random art.
        width (int): The width of the SVG canvas.
        height (int): The height of the SVG canvas.
        count (int): The number of random shapes to generate in the SVG canvas.
        file_name (str): The name of the output file where the HTML-SVG page will be saved.

    Returns:
        None.
    """
    table: list = []
    for i in range(0,count):
        config = RandomShape(width,height)
        if config.shape == 0:
            shape = CircleShape(config.cx, config.cy, config.radius, config.colour,config.op)
        elif config.shape == 1:
            shape = RectangleShape(config.cx, config.cy, config.width, config.height, config.colour, config.op)
        else:
            shape = EllipseShape(config.cx,config.cy,config.rx,config.ry,config.colour,config.op)
        table.append(shape)
    
    svg_canvas = SvgCanvas(width, height, table)
    html_document = HtmlDocument(title="My Art", body=svg_canvas.gen_art())
    html_document.gen_file(file_name)

def main():
    """
    This function reads the command-line arguments for width, height, count, and file_name.
    It then generates a greeting card using the generate_card function with the provided arguments.

    Command-line Arguments:
        width (int): The width of the SVG canvas.
        height (int): The height of the SVG canvas.
        count (int): The number of random shapes to generate in the SVG canvas.
        file_name (str): The name of the output file where the HTML-SVG page will be saved.

    Returns:
        None
    """
    if len(sys.argv) != 5:
        print("Wrong arguments")
        sys.exit(1)

    width = int(sys.argv[1])
    height = int(sys.argv[2])
    shape_count = int(sys.argv[3])
    file_name = sys.argv[4]
    config = PyArtConfig()
    
    generate_card(config, width, height, shape_count, file_name)

if __name__ == "__main__":
    main()