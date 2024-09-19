import unittest
import Form

class TestIntersection(unittest.TestCase):
    def test_intersection_false(self):
        scene = Form.Scene([], [])
        rayon = Form.Rayon(Form.Vector3(0,0,0), Form.Vector3(0,0,-1))
        sphere = Form.Sphere(100, Form.Vector3(0,0,200), Form.Vector3(0,0,0))
        scene.addSphere(sphere)
        self.assertIsNone(Form.intersectSphere(rayon, scene.spheres))

        rayon.direction = Form.Vector3(0,1,0)
        self.assertIsNone(Form.intersectSphere(rayon, scene.spheres))

        rayon.direction = Form.Vector3(1, 0, 0)
        self.assertIsNone(Form.intersectSphere(rayon, scene.spheres))

        rayon.direction = Form.Vector3(1, 1, 0)
        self.assertIsNone(Form.intersectSphere(rayon, scene.spheres))

        rayon.direction = Form.Vector3(1, 1, 1)
        self.assertIsNone(Form.intersectSphere(rayon, scene.spheres))

        rayon.direction = Form.Vector3(0, 116, 200)
        self.assertIsNone(Form.intersectSphere(rayon, scene.spheres))

    def test_intersection_true(self):
        scene = Form.Scene([], [])
        rayon = Form.Rayon(Form.Vector3(0, 0, 0), Form.Vector3(0, 0, 1))
        sphere = Form.Sphere(100, Form.Vector3(0, 0, 200), Form.Vector3(0, 0, 0))
        scene.addSphere(sphere)
        self.assertIsNotNone(Form.intersectSphere(rayon, scene.spheres))

        rayon.direction = Form.Vector3(0, 1, 2)
        self.assertIsNotNone(Form.intersectSphere(rayon, scene.spheres))


if __name__ == '__main__':
    unittest.main()
