import ImageCreator as IC
import Form
import math

raycastImage = IC.ImagePPM(800,600)

scene = Form.Scene([],[])

sphere = Form.Sphere(180, Form.Vector3(0, 0, 200), Form.Vector3(0, 0, 1))
scene.addSphere(sphere)
lampe = Form.Light(Form.Vector3(300,0,200), Form.Vector3(50000,50000,50000))
scene.addLight(lampe)
lampe2 = Form.Light(Form.Vector3(-300,-100,200), Form.Vector3(0,0,50000))
scene.addLight(lampe2)
lampe3 = Form.Light(Form.Vector3(0,-500,200), Form.Vector3(50000,0,0))
scene.addLight(lampe3)
focal = 10000

sphere2 = Form.Sphere(180, Form.Vector3(-200, -400, 200), Form.Vector3(1, 1, 1))
scene.addSphere(sphere2)

for y in range(raycastImage.height):
    for x in range(raycastImage.width):
        pixel = Form.Vector3(x*2 - raycastImage.width,y*2 - raycastImage.height,0)
        origin = Form.Vector3(0,0,-focal)
        direction = pixel - origin

        rayon = Form.Rayon(pixel, direction)

        for sph in scene.spheres:
            it = Form.intersectSphere(rayon, sph)
            if it is not None:
                for light in scene.lights:
                    N = it[1] - sph.center
                    norm = Form.normalize(N)
                    rayonLampe = Form.Rayon(it[1] + (norm / 1000), light.position - it[1] + (norm / 1000))

                    l_i = Form.Vector3(0,0,0) - rayonLampe.direction
                    sphereAlbedo = sph.albedo

                    it2 = Form.intersectSphere(rayonLampe, sph)
                    if it2 is None:
                        v = math.fabs(Form.dot(norm, l_i))
                        len_l = Form.length(rayonLampe.direction)

                        dist = Form.getIntersectionDistance(rayon, it[0])
                        color = dist * 1
                        col = Form.Vector3(0, 0, 0)
                        col.x = light.intensity.x / (len_l ** 2) * sphereAlbedo.x * v
                        col.y = light.intensity.y / (len_l ** 2) * sphereAlbedo.y * v
                        col.z = light.intensity.z / (len_l ** 2) * sphereAlbedo.z * v
                        if col.x > 255:
                            col.x = 255
                        if col.y > 255:
                            col.y = 255
                        if col.z > 255:
                            col.z = 255
                        raycastImage.image[y][x] = [int(col.x), int(col.y), int(col.z)]

            else:
                interBool = False
                for s in scene.spheres:
                    if s == sph:
                        continue

                    inter = Form.intersectSphere(rayon, s)
                    if inter is not None:
                        interBool = True
                if not interBool:
                    raycastImage.image[y][x] = [0, 0, 0]

raycastImage.saveImage("raycastImage")