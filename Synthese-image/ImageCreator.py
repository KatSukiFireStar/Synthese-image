class ImagePBM:
    def __init__(self, width, height):
        self.width = width
        self.height = height

        l = height * [0]
        for i in range(len(l)):
            l[i] = width * [0]
        self.image = l

    def saveImage(self, path):
        path = path + ".pbm"
        fichier=open(path,'w')
        fichier.write("P1\n")
        fichier.write(str(self.width) + " " + str(self.height) + "\n")
        for i in range(self.height):
            for j in range(self.width):
                fichier.write(str(self.image[i][j]) + " ")
            fichier.write("\n")


class ImagePPM:
    def __init__(self, width, height):
        self.width = width
        self.height = height

        l = height * [0]
        for i in range(len(l)):
            l[i] = width * [0]
        for i in range(len(l)):
            for j in range(len(l[i])):
                l[i][j] = 3 * [0]
        self.image = l

    def saveImage(self, path):
        path = path + ".ppm"
        fichier=open(path,'w')
        fichier.write("P3\n")
        fichier.write(str(self.width) + " " + str(self.height) + "\n")
        fichier.write("255\n")
        for i in range(self.height):
            for j in range(self.width):
                fichier.write(str(self.image[i][j][0]) + " " + str(self.image[i][j][1]) + " " + str(self.image[i][j][2]) + "\n")
            fichier.write("\n")