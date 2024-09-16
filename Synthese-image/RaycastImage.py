import ImageCreator as IC
import Form
import math

raycastImage = IC.ImagePPM(800,600)

sphere = Form.Sphere(180, Form.Vector3(0, 0, 200))
radius = sphere.radius
lampe = Form.Lampe(Form.Vector3(50,0,100), 10000)
focal = 10000

for y in range(raycastImage.height):
    for x in range(raycastImage.width):
        pixel = Form.Vector3(x*2 - raycastImage.width,y*2 - raycastImage.height,0)
        origin = Form.Vector3(0,0,-focal)
        direction = pixel - origin

        rayon = Form.Rayon(pixel, direction)

        it = Form.intersectSphere(rayon, sphere)

        if it is not None:
            N = it[1] - sphere.center
            norm = Form.normalize(N)
            rayonLampe = Form.Rayon(it[1], lampe.position - it[1])

            l_i = Form.Vector3(0,0,0) - rayonLampe.direction
            albedo = Form.Vector3(1,0,0)

            v = math.fabs(Form.dot(norm, l_i))
            len_l = Form.length(rayonLampe.direction)

            dist = Form.getIntersectionDistance(rayon, it[0])
            color = dist * 1
            col = lampe.intensity / len_l**2 * v
            raycastImage.image[y][x][0] = int(col)
            raycastImage.image[y][x][1] = int(col)
            raycastImage.image[y][x][2] = int(col)
        else:
            raycastImage.image[y][x][0] = 0
            raycastImage.image[y][x][1] = 0
            raycastImage.image[y][x][2] = 0

raycastImage.saveImage("raycastImage")