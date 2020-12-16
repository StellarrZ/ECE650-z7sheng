# Question 18
# (a)
class ST:
    def __init__(self, n):
        self.n = n
        self.A = [0] * n
        self.ps1 = -1
        self.ps2 = n
    def isEmpty(self, sNum):
        return self.ps1 == -1 if sNum == 1 else self.ps2 == self.n
    def isFull(self, sNum):
        return self.ps1 + 1 == self.ps2
    def push(self, sNum, x):
        if self.isFull(1):
            return True     # Overflow
        elif sNum == 1:
            self.ps1 += 1
            self.A[self.ps1] = x
            return False
        else:
            self.ps2 -= 1
            self.A[self.ps2] = x
            return False
    def pop(self, sNum):
        if self.isEmpty(sNum):
            return None     # Empty
        elif sNum == 1:
            self.ps1 -= 1
            return self.A[self.ps1 + 1]
        else:
            self.ps2 += 1
            return self.A[self.ps2 - 1]


# (b)
class ST:
    def __init__(self, n):
        self.n = n
        self.A = [0] * n
        self.ps1 = -1
        self.ps2 = n
    # here
    def double(self):
        self.ps2 += self.n
        self.n << 1
        self.A = self.A + self.A    # worst-case θ(n) due to duplicating A
        return
    def isEmpty(self, sNum):
        return self.ps1 == -1 if sNum == 1 else self.ps2 == self.n
    def isFull(self, sNum):
        return self.ps1 + 1 == self.ps2
    def push(self, sNum, x):
        if self.isFull(1):
            # and here
            self.double()
            return True     # have been doubled
        elif sNum == 1:
            self.ps1 += 1
            self.A[self.ps1] = x
            return False
        else:
            self.ps2 -= 1
            self.A[self.ps2] = x
            return False
    def pop(self, sNum):
        if self.isEmpty(sNum):
            return None     # Empty
        elif sNum == 1:
            self.ps1 -= 1
            return self.A[self.ps1 + 1]
        else:
            self.ps2 += 1
            return self.A[self.ps2 - 1]