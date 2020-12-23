class Solution:
    def firstUniqChar(self, s: str) -> int:
        repo = collections.defaultdict(int)
        for i, ch in enumerate(s):
            repo[ch] = i + 1 if repo[ch] == 0 else -1
        ans = float('inf')
        for key in repo:
            if repo[key] > 0:
                ans = min(ans, repo[key])
        return ans - 1 if ans != float('inf') else -1