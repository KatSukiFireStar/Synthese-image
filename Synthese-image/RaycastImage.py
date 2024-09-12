import ImageCreator as IC
import Form

raycastImage = IC.ImagePPM(800,600)

sphere = Form.Sphere(100, Form.Vector3(0, 0, 200))
radius = sphere.radius
focal = 50

for y in range(raycastImage.height):
    for x in range(raycastImage.width):
        pixel = Form.Vector3(x*2 - raycastImage.width,y*2 - raycastImage.height,0)
        origin = Form.Vector3(0,0,-focal)
        direction = pixel - origin

        rayon = Form.Rayon(origin, direction)

        if Form.intersectSphere(rayon, sphere):
            raycastImage.image[y][x][0] = 255
            raycastImage.image[y][x][1] = 255
            raycastImage.image[y][x][2] = 255
        else:
            raycastImage.image[y][x][0] = 255
            raycastImage.image[y][x][1] = 180
            raycastImage.image[y][x][2] = 0

raycastImage.saveImage("raycastImage")