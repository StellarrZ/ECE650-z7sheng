class Solution:
    def lastStoneWeight(self, stones: List[int]) -> int:
        hp = [-w for w in stones]
        heapq.heapify(hp)
        while len(hp) > 1:
            w1 = heapq.heappop(hp)
            w2 = heapq.heappop(hp)
            reg = w1 - w2
            if reg < 0:
                heapq.heappush(hp, reg)
        if hp:
            return -heapq.heappop(hp)
        else:
            return 0