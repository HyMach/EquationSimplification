from JaroSimilarity import JaroSimilarity
class JaroWinkler:
    """
    to calculate the jaro distance between two strings
    """
    @staticmethod
    def jaroWinkler(s1,s2):
        jaroSim = JaroSimilarity.jaroSimilarity(s1,s2)
        boostThreshold = 0.7
        prefixSizeMax = 4
        jaroWinklerSim = jaroSim

        if jaroSim > boostThreshold:
            prefixSize = 0
            for i in range(0, min(prefixSizeMax,min(len(s1),len(s2)))):
                if s1[i] == s2[i]:
                    prefixSize += 1

            jaroWinklerSim = jaroSim + 0.1 * prefixSize * (1-jaroSim)
            jaroWinklerDistance = 1 - jaroWinklerSim


        return jaroWinklerDistance




if __name__ == "__main__":
   # print(1-JaroWinkler.jaroWinkler("AL","AL"))
    print(1 - JaroWinkler.jaroWinkler("MARTHA", "MARHTA"))
    print(1 - JaroWinkler.jaroWinkler("JONES","JOHNSON"))








