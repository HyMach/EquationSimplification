from JaroSimilarity import  JaroSimilarity
import unittest

__author__ = "Liang Chen @ liangchenubc@gmail.com"

class TestDistance(unittest.TestCase):
    def testJaroDistance(self):
        self.assertAlmostEqual(0.822222222222222,JaroSimilarity.jaroSimilarity("DWAYNE","DUANE"))
        self.assertAlmostEqual(0.9444444444444, JaroSimilarity.jaroSimilarity("MARTHA", "MARHA"))
        self.assertAlmostEqual(0.76666666666, JaroSimilarity.jaroSimilarity("DIXON", "DICKSONX"))
        self.assertAlmostEqual(0.8962963, JaroSimilarity.jaroSimilarity("JELLYFISH", "SMELLYFISH"))




if __name__ == "__main__":
    unittest.main()
