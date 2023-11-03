from PIL import Image, ImageDraw

# Define the image size and colors
image_width = 211
image_height = 4  # Reduce the number of rows to 4
background_color = (255, 255, 255)  # White
row_colors = [(0, 0, 0), (255, 255, 255)]  # Black and White
yellow_color = (255, 255, 0)  # Yellow

# Create a new image with the specified size and background color
image = Image.new("RGB", (image_width, image_height), background_color)
draw = ImageDraw.Draw(image)

# Define the patterns for the finish line rows
patterns = [
    [1, 0] * (image_width // 2),  # Row 1: White and Black
    [0, 1] * (image_width // 2),  # Row 2: Black and White
    [1, 0] * (image_width // 2),  # Row 3: White and Black
    [0, 1] * (image_width // 2)   # Row 4: Black and White
]

# Draw the finish line pattern row by row
for row, pattern in enumerate(patterns):
    for col, color_index in enumerate(pattern):
        color = row_colors[color_index]
        draw.point((col, row), fill=color)

# Draw the yellow fifth row
for col in range(image_width):
    draw.point((col, 3), fill=yellow_color)  # Reduced the row number to 3

# Save the image to a file
image.save("finish_line.png")
image.show()  # Show the generated image
