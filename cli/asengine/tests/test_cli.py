import unittest
import asengine

class TestASEngineCLI(unittest.TestCase):
    def test_example(self):
        a = 2 + 2
        self.assertEqual(a, 4)

if __name__ == "__main__":
    unittest.main()