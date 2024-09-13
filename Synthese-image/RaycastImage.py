import ImageCreator as IC
import Form

raycastImage = IC.ImagePPM(800,600)

sphere = Form.Sphere(180, Form.Vector3(0, 0, 200))
radius = sphere.radius
focal = 10000

for y in range(raycastImage.height):
    for x in range(raycastImage.width):
        pixel = Form.Vector3(x*2 - raycastImage.width,y*2 - raycastImage.height,0)
        origin = Form.Vector3(0,0,-focal)
        direction = pixel - origin

        rayon = Form.Rayon(pixel, direction)

        it = Form.intersectSphere(rayon, sphere)

        if it is not None:
            dist = Form.getIntersectionDistance(rayon, it)
            color = dist * 1
            raycastImage.image[y][x][0] = int(color)
            raycastImage.image[y][x][1] = int(color)
            raycastImage.image[y][x][2] = int(color)
        else:
            raycastImage.image[y][x][0] = 255
            raycastImage.image[y][x][1] = 180
            raycastImage.image[y][x][2] = 0

raycastImage.saveImage("raycastImage")