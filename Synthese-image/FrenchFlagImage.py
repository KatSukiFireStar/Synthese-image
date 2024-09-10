import ImageCreator as IC

frenchFlag = IC.ImagePPM(300,100)

for i in range(frenchFlag.width):
    for j in range(frenchFlag.height):
        if i < 100:
            frenchFlag.image[j][i][0] = 0
            frenchFlag.image[j][i][1] = 0
            frenchFlag.image[j][i][2] = 255
        elif i < 200:
            frenchFlag.image[j][i][0] = 255
            frenchFlag.image[j][i][1] = 255
            frenchFlag.image[j][i][2] = 255
        else:
            frenchFlag.image[j][i][0] = 255
            frenchFlag.image[j][i][1] = 0
            frenchFlag.image[j][i][2] = 0

frenchFlag.saveImage("frenchFlag")