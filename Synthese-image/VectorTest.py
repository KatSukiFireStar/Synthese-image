import math
import unittest
import Form

class TestVector3Operation(unittest.TestCase):
    def test_length_true(self):
        self.assertEqual(Form.length(Form.Vector3(1,1,1)),math.sqrt(3))
        self.assertEqual(Form.length(Form.Vector3(2,2,2)),math.sqrt(12))

    def test_length_false(self):
        self.assertNotEqual(Form.length(Form.Vector3(1,1,1)), 1)

    def test_dot_true(self):
        self.assertEqual(Form.dot(Form.Vector3(1,1,1),Form.Vector3(1,1,1)),3)
        self.assertEqual(Form.dot(Form.Vector3(2,2,2),Form.Vector3(2,2,2)),12)
        self.assertEqual(Form.dot(Form.Vector3(2,3,1),Form.Vector3(5,0,4)), 14)

    def test_dot_false(self):
        self.assertNotEqual(Form.dot(Form.Vector3(1, 1, 1), Form.Vector3(1, 1, 1)), 4)
        self.assertNotEqual(Form.dot(Form.Vector3(2, 2, 2), Form.Vector3(2, 2, 2)), 6)
        self.assertNotEqual(Form.dot(Form.Vector3(2, 3, 1), Form.Vector3(5, 0, 4)), 7)


if __name__ == '__main__':
    unittest.main()
