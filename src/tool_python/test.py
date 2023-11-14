from PIL import Image
import math
import struct
import os

def color_distance(color1, color2):
    # Calculate the Euclidean distance between two RGB colors
    r1, g1, b1 = color1
    r2, g2, b2 = color2
    return math.sqrt((r1 - r2) ** 2 + (g1 - g2) ** 2 + (b1 - b2) ** 2)


path = os.path.dirname(__file__)
path = os.path.join(path, "..\..\media\\")
files = [f for f in os.listdir(path) if os.path.isfile(os.path.join(path, f))]

for fileName in files:
    if fileName[-1] != 'g' : continue
    if fileName != "blueEsc.png" and fileName != "blackEsc.png" : continue
    fileName = fileName[:-4]
    pathImage = path + fileName + ".png"
    # print(pathImage)
    # exit(0)
    image = Image.open(pathImage)

    # Get the dimensions of the image
    width, height = image.size

    color_list = {
        0: (0, 0, 0),    # Black
        16: (0, 0, 255),  # Blue
        32: (27,161,52),  # Green
        48: (135,206,235),  # Cyan
        64: (255, 0, 0),  # Red
        80: (255, 0, 255),  # Magenta
        96: (156, 90, 60),  # Yellow
        112: (255, 255, 255),  # White
        128: (158, 158, 158), # Grey
        160: (168, 230, 29), #Lime
        224: (255,165,0) #Orange
    }

    with open(path + f"colorCode_{fileName}.txt", "w") as fo:
        pass 

    def write2BinaryFile(x):
        with open(path + f"colorCode_{fileName}.txt", "ab") as fo:
            packed_data = struct.pack("i", x)
            fo.write(packed_data)

    # Iterate through each pixel in the image
    for x in range(width):
        for y in range(height):
            # Get the color values of the pixel at (x, y)
            pixel_color = image.getpixel((x, y))

            if len(pixel_color) == 3:  # RGB color
                red, green, blue = pixel_color
            else:  # Handle other color modes (e.g., RGBA)
                red, green, blue, alpha = pixel_color[:4]  # Extract RGB and alpha
            closest_color_code = min(color_list, key=lambda code: color_distance((red, green, blue), color_list[code]))
            if closest_color_code == 128 : closest_color_code = 112
            write2BinaryFile(x);
            write2BinaryFile(y);
            write2BinaryFile(32);
            write2BinaryFile(closest_color_code);
                # fo.write(f"{x} {y} {closest_color_code} \n")

    # Close the image file when you're done
    image.close()