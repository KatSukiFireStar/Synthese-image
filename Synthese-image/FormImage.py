import ImageCreator as IC


squareImage = IC.ImagePBM(200,200)

for i in range(squareImage.width):
    for j in range(squareImage.height):
        if ((i == 50 or i == 150) and 150 >= j >= 50) or ((j == 50 or j == 150) and 50 <= i <= 150):
            squareImage.image[j][i] = 1

squareImage.saveImage("squareImage")

circleImage = IC.ImagePBM(200,200)
for i in range(circleImage.width):
    for j in range(circleImage.height):
        if (i - 100)**2 + (j - 100)**2 <= 20**2:
            circleImage.image[j][i] = 1

circleImage.saveImage("circleImage")