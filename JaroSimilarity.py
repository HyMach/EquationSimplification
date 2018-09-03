class JaroSimilarity:
    """
    to calculate the jaro distance between two strings
    """
    @staticmethod
    def jaroSimilarity(s1,s2):
        nLen1 = len(s1)
        nLen2 = len(s2)

        if nLen1 == 0 or nLen2 == 0: # consider the corner case
            return 0

        nMatch = 0               # number of matching characters
        nTransposition = 0   # number of the half transposition characters

        nMatchRange = max(max(nLen1,nLen2) // 2 - 1, 0)
        bS2Match = [False]*nLen2
        sMatch1 = ""
        sMatch2 = ""

        for i in range(0,nLen1):
            nMinIndex = max(i-nMatchRange,0)
            nMaxIndex = min(i+nMatchRange,nLen2-1)
            for j in range(nMinIndex,nMaxIndex+1):
                if (not bS2Match[j]) and s1[i] == s2[j]:
                    sMatch1  = sMatch1 + s1[i]
                    bS2Match[j] = True
                    break

        nMatch = len(sMatch1)
        nS2MatchSize = 0
        for i in range(0,nLen2):
            if bS2Match[i]:
                sMatch2 += s2[i]
                nS2MatchSize += 1
                if nS2MatchSize == nMatch:
                    break

        nIndexMatch = 0
        for i in range(0,nMatch):
            if sMatch1[i] == sMatch2[i]:
                nIndexMatch += 1
        nTransposition = (nMatch - nIndexMatch) // 2
        jaroSim = (nMatch/nLen1 + nMatch/nLen2 + (nMatch - nTransposition) / nMatch)/3.0

        return jaroSim



if __name__ == "__main__":
    print(JaroSimilarity.jaroSimilarity("ABCVWXYZ","CABVWXYZ"))