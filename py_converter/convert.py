import png

reader = png.Reader(filename="terrain.png")

data = reader.asRGBA()

map_data = data[2]


outfile = open("test.js", "w")
outfile.write("""
export const mapData = [""")


for i, row in enumerate(map_data):
    outfile.write("[")
    for i in range(len(row) // 4):
        r, g, b, _ = row[i*4:i*4 + 4]
        if r == 0 and g == 255 and b == 0:
            outfile.write("0,")
        elif r == 0 and g == 0 and b == 255:
            outfile.write("1,")
        elif r == 255 and g == 255 and b == 0:
            outfile.write("2,")
        elif r == 0 and g == 255 and b == 255:
            outfile.write("8,")
        else:
            outfile.write("99,")
        # elif r == 127 and g == 127 and b == 0:
            # outfile.write("3,")
        # elif r == 0 and g == 127 and b == 0:
            # outfile.write("4,")
        # elif r == 0 and g == 0 and b == 127:
            # outfile.write("5,")
        # elif r == 255 and g == 255 and b == 255:
            # outfile.write("6,")
        # elif r == 127 and g == 127 and b == 127:
            # outfile.write("7,")
        # elif r == 0 and g == 127 and b == 127:
            # outfile.write("9,")
        # elif r == 255 and g == 0 and b == 0:
            # outfile.write("10,")
        # elif r == 255 and g == 0 and b == 255:
            # outfile.write("11,")
        # elif r == 127 and g == 0 and b == 0:
            # outfile.write("12,")
        # else:
            # print("Ny!", r, g, b)
    outfile.write("],\n")

outfile.write("]\n")


outfile.close()
