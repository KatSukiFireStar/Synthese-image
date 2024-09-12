import ImageCreator as IC
import cmath as cm

squareImage = IC.ImagePBM(200,200)

for i in range(squareImage.width):
    for j in range(squareImage.height):
        if ((i == 50 or i == 150) and 150 >= j >= 50) or ((j == 50 or j == 150) and 50 <= i <= 150):
            squareImage.image[j][i] = 1

squareImage.saveImage("squareImage")

circleImage = IC.ImagePPM(200,200)

cx = circleImage.width / 2
cy = circleImage.height / 2

radius = 50

for i in range(circleImage.width):
    for j in range(circleImage.height):
        if radius**2 / 2 < (i - cx)**2 + (j - cy)**2 < radius**2:
            circleImage.image[j][i][0] = i
            circleImage.image[j][i][1] = j
            circleImage.image[j][i][2] = 0
        else:
            circleImage.image[j][i][0] = j
            circleImage.image[j][i][1] = i
            circleImage.image[j][i][2] = 0

circleImage.saveImage("circleImage")