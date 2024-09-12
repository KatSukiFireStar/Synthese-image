class ImagePBM:
    def __init__(self, width, height):
        self.width = width
        self.height = height

        l = height * [0]
        for i in range(height):
            l[i] = width * [0]
        self.image = l

    def saveImage(self, path):
        path = path + ".pbm"
        file=open(path,'w')
        file.write("P1\n")
        file.write(str(self.width) + " " + str(self.height) + "\n")
        for i in range(self.height):
            for j in range(self.width):
                file.write(str(self.image[i][j]) + " ")
            file.write("\n")


class ImagePPM:
    def __init__(self, width, height):
        self.width = width
        self.height = height

        l = height * [0]
        for i in range(height):
            l[i] = width * [0]
        for i in range(height):
            for j in range(width):
                l[i][j] = 3 * [0]
        self.image = l

    def saveImage(self, path):
        path = path + ".ppm"
        file=open(path,'w')
        file.write("P3\n")
        file.write(str(self.width) + " " + str(self.height) + "\n")
        file.write("255\n")
        for i in range(self.height):
            for j in range(self.width):
                file.write(str(self.image[i][j][0]) + " " + str(self.image[i][j][1]) + " " + str(self.image[i][j][2]) + "\n")
            file.write("\n")