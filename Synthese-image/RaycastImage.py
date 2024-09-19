import ImageCreator as IC
import Form
import math

raycastImage = IC.ImagePPM(800, 600)

scene = Form.Scene([], [])

sphere = Form.Sphere(180, Form.Vector3(0, 0, 200), Form.Vector3(0, 0, 1))
scene.addSphere(sphere)
lampe = Form.Light(Form.Vector3(300, -200, 200), Form.Vector3(100000, 100000, 100000))
scene.addLight(lampe)
lampe3 = Form.Light(Form.Vector3(0, -500, 200), Form.Vector3(100000, 0, 0))
scene.addLight(lampe3)
focal = 10000

sol = Form.Sphere(10000,Form.Vector3(0,10400,-1000),Form.Vector3(1,1,1))
scene.addSphere(sol)

sphere2 = Form.Sphere(180, Form.Vector3(-200, -400, 200), Form.Vector3(1, 1, 1))
scene.addSphere(sphere2)

for y in range(raycastImage.height):
    for x in range(raycastImage.width):
        pixel = Form.Vector3(x * 2 - raycastImage.width, y * 2 - raycastImage.height, 0)
        origin = Form.Vector3(0, 0, -focal)
        direction = pixel - origin

        rayon = Form.Rayon(pixel, direction)
        it = Form.intersectSphere(rayon, scene.spheres)
        if it is not None:
            sph = it.sphere
            col = Form.Vector3(0, 0, 0)
            N = it.intersection - sph.center
            norm = Form.normalize(N)
            for light in scene.lights:
                rayonLampe = Form.Rayon(it.intersection + (norm / 1000), light.position - it.intersection + (norm / 1000))

                l_i = Form.Vector3(0, 0, 0) - rayonLampe.direction
                sphereAlbedo = sph.albedo

                it2 = Form.intersectSphere(rayonLampe, scene.spheres)
                if it2 is None:
                    v = math.fabs(Form.dot(norm, l_i))
                    len_l = Form.length(rayonLampe.direction)

                    col.x += light.intensity.x / (len_l ** 2) * sphereAlbedo.x * v
                    col.y += light.intensity.y / (len_l ** 2) * sphereAlbedo.y * v
                    col.z += light.intensity.z / (len_l ** 2) * sphereAlbedo.z * v

                if it2 is not None:
                    len_l = Form.length(rayonLampe.direction)
                    if len_l < Form.getIntersectionDistance(rayonLampe, it2.distance):
                        v = math.fabs(Form.dot(norm, l_i))

                        col.x += light.intensity.x / (len_l ** 2) * sphereAlbedo.x * v
                        col.y += light.intensity.y / (len_l ** 2) * sphereAlbedo.y * v
                        col.z += light.intensity.z / (len_l ** 2) * sphereAlbedo.z * v
                if col.x > 255:
                    col.x = 255
                if col.y > 255:
                    col.y = 255
                if col.z > 255:
                    col.z = 255
            raycastImage.image[y][x] = [int(col.x), int(col.y), int(col.z)]

        else:
            raycastImage.image[y][x] = [0, 0, 0]

raycastImage.saveImage("raycastImage")
