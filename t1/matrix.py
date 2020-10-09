import sys

# question a)
class Matrix(object):
    def __init__ (self, mat):
        self.mat = list(mat)
    def __repr__ (self):
        return str( self.mat )
    def row(self):
        if self.mat == []:
            return 0
        elif self.mat[0] == []:
            return 0
        return len( self.mat )
    def col(self):
        if self.mat == []:
            return 0
        elif self.mat[0] == []:
            return 0
        return len( self.mat[0] )
    def value(self, a, b):
        return self.mat[a][b]

# question b)
def print_matrix(mt):
    print( mt.row() )
    for k in range( mt.row() ):
        echo = str( mt.mat[k] ).strip("[").strip("]")
        print("|", echo, "|")
    return

# question c)
def parse_matrix(input):
    lines = input.split("\n")
    rnum = int( lines.pop(0).strip()[0] )
    mt = []
    for k in range( rnum ):
        tline = str( lines[k] )
        tline = list( tline.strip().strip("|").strip().split(", ") )
        for i in range( len(tline) ):
            if tline[i].isnumeric():
                tline[i] = int(tline[i])
        mt.append( tline )
    return Matrix(mt)

# question d)
def matrix_mul(A, B):
    try:
        if A.col() != B.row():
            raise Exception("Cannot multiply")
        else:
            product = [ [0] * B.col() for k in range( A.row() ) ]
            for i in range( A.row() ):
                for j in range( B.col() ):
                    for k in range( B.row() ):
                        product[i][j] = int( A.value(j, k) ) * int( B.value(k, j) )
            return Matrix(product)
    except Exception as ex:
        print("Error: " + str(ex), file = sys.stderr)
        return


# question e)
class SparseMatrix(object):
    def __init__ (self, mat, row, col):
        self.mat = dict(mat)
        self.row = int(row)
        self.col = int(col)
    def __repr__ (self):
        return str( self.mat )
    def row(self):
        return len( self.row )
    def col(self):
        return len( self.col )
    def value(self, a, b):
        if [a,b] in mat:
            return self.mat[ [a][b] ]
        else return 0

# question f)
def sparse(M):
    spm = {}
    for i in range( M.row() ):
        for j in range( M.col() ):
            if M.value(i, j) != 0:
                spm[ [i,j] ] = M.value(i, j)
    return SparseMatrix(spm, M.row(), M.col())

# question g)
# No. For example, there is no 0 element in matrix, 
# each element should be presented by 3 numbers rather than one.

# question h)
# Yes. Because the interface parameters are well defined, 
# icluding the number of rows / columns, the index of rows / columns.
# For example, when we call the .value(index1, index2), 
# the return values of the two ways are same.
# Finally, matrix_mul(A, B) returns an type Matrix value.

# question i)
def sparse_matrix_mul(A, B):
    try:
        if A.col() != B.row():
            raise Exception("Cannot multiply")
        else:
            product = {}
            for keya in A.mat:
                for keyb in B.mat:
                    if keya[1] == keyb[0]:
                        if [keya[0], keyb[1]] not in product:
                            product[ [keya[0], keyb[1]] ] = 0
            for keya in A.mat:
                for keyb in B.mat:
                    if keya[1] == keyb[0]:
                            product[ [keya[0], keyb[1]] ] += A.value(keya[0], keya[1]) * B.value(keyb[0], keyb[1])
            return SparseMatrix(product, A.row(), B.col())
    except Exception as ex:
        print("Error: " + str(ex), file = sys.stderr)
        return