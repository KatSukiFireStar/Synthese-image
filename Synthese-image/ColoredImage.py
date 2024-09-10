import ImageCreator as IC

imagePink = IC.ImagePPM(200,100)

for line in range(imagePink.width):
    for column in range(imagePink.height):
        imagePink.image[column][line][0] = 255
        imagePink.image[column][line][1] = 192
        imagePink.image[column][line][2] = 203

imagePink.saveImage("imagePink")