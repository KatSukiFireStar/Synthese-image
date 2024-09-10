import ImageCreator as IC

imageWhite = IC.ImagePBM(200,200)
imageBlack = IC.ImagePBM(200,200)

for line in range(imageBlack.width):
    for column in range(imageBlack.height):
        imageBlack.image[column][line] = 1

imageWhite.saveImage("imageWhite")
imageBlack.saveImage("imageBlack")