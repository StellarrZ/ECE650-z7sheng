# !/usr/bin/env python3
import sys
import copy

# YOUR CODE GOES HERE
class NODE(object):
    def __init__ (self, x, y, starflag = False, vflag = False):
        self.x = float(x)
        self.y = float(y)
        self.starflag = starflag
        self.vflag = vflag
    def __repr__ (self):
        return "(" + pprt(self.x) + "," + pprt(self.y) + ")"
    def handnum(self):
        tem = hinit(self.x) + " " + hinit(self.y)
        tem = tem.replace(" ", "v")
        tem = tem.replace("-", "n")
        tem = tem.replace(".", "p")
        return tem


def pprt(x):
    if isinstance(x, float):
        if x.is_integer():
            return str( int(x) )
        else:
            return "{0:.2f}".format(x)
    return str(x)


def hinit(x):
    if isinstance(x, float):
        if x.is_integer():
            return "{0:.2f}".format( float(x) )
        else:
            return "{0:.2f}".format(x)
    return str(x)


def parseNode(lsp):
    for strictt in lsp:
        if len(strictt) <= 2:
            raise Exception("Wrong coordinate format.")
        elif strictt[0] == ")" or strictt[1] == "(":
            raise Exception("Wrong coordinate format.")
        elif strictt[-1] == "(" or strictt[-2] == ")":
            raise Exception("Wrong coordinate format.")

    cache = list( map(lambda x: x.strip("("), lsp) )
    cache = list( map(lambda x: x.strip(")"), cache) )
    cache = list( map(lambda x: x.split( ")(" ), cache) )
    cache = sum(cache, [])

    for strictt in cache:
        if len(strictt) == 0:
            raise Exception("Wrong coordinate format.")
        elif strictt[0] == "," or strictt[-1] == ",":
            raise Exception("Wrong coordinate format.")

    cache = list( map(lambda x: x.split( "," ), cache) )

    chain = []
    for i in range( len(cache) ):
        negf = [False, False]
        if len( cache[i] ) != 2:
            raise Exception("Wrong coordinate format.")
        else:
            negf[0] = cache[i][0][0] == "-"
            if negf[0]:
                cache[i][0] = cache[i][0][1:]
            negf[1] = cache[i][1][0] == "-"
            if negf[1]:
                cache[i][1] = cache[i][1][1:]
            if cache[i][0].isnumeric() and cache[i][1].isnumeric():
                x = int( (-1) ** negf[0] * int( cache[i][0] ) )
                y = int( (-1) ** negf[1] * int( cache[i][1] ) )
                node = NODE(x, y)
            else:
                raise Exception("Wrong coordinate format.")
        chain.append(node)
    return chain


def parseLine(linein):
    lsp = linein.strip().split(" ", 1)
    if not lsp[0] in cmdlib:
        raise Exception("Wrong command.")
    else:
        cmd = lsp.pop(0)
        if cmd == cmdlib[3]:
            stname = ""
            chain = []
            if len(lsp) != 0:
                if lsp[0].lstrip():
                    raise Exception("Command 'gg' should not have argument.")
        else:
            lsp = lsp[0].lstrip()
            lsp = lsp.split("\"", 2)
            empt = lsp.pop(0).lstrip()
            if len(lsp) != 2 or empt != "":
                raise Exception("Wrong street format.")
            elif lsp[0] == "":
                raise Exception("Empty street name.")
            elif cmd == cmdlib[2] and lsp[1].lstrip() != "":
                raise Exception("Command 'rm' should have and only have <\"Street Name\"> as argument.")
            elif cmd != cmdlib[2] and lsp[1] == "":
                raise Exception("Should input coordinate.")
            elif cmd != cmdlib[2] and lsp[1][0] != " ":
                raise Exception("Wrong street format.")
            else:
                stname = "\"" + lsp.pop(0) + "\""
                if cmd == cmdlib[2]:
                    chain = []
                else:
                    lsp = lsp.pop(0).split()
                    chain = parseNode(lsp)
    
    stname = stname.upper()
    return cmd, stname, chain


def isBTW(vx, va, vb):
    if va.x != vb.x:
        if vx.x > va.x:
            if vx.x <= vb.x:
                return True
            else:
                return False
        else:
            if vx.x >= vb.x:
                return True
            else:
                return False
    else:
        if vx.y > va.y:
            if vx.y <= vb.y:
                return True
            else:
                return False
        else:
            if vx.y >= vb.y:
                return True
            else:
                return False


def interSection(pa, pb, pc, pd):
    x1, y1 = pa.x, pa.y
    x2, y2 = pb.x, pb.y
    x3, y3 = pc.x, pc.y
    x4, y4 = pd.x, pd.y

    xnum = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4))
    xden = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4))
    xcoor =  xnum / xden

    ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4)
    yden = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)
    ycoor = ynum / yden

    return float(xcoor), float(ycoor)


def Vector(pa, pb):
    return pb.x - pa.x, pb.y - pa.y


def VProduct(l1, l2):
    return l1[0] * l2[1] - l1[1] * l2[0]


def markFlag(tomark):
    for somep in tomark:
        if somep == "a":
            agent[ stts[ii] ][mm].starflag = True
        if somep == "b":
            agent[ stts[ii] ][mm + 1].starflag = True
        if somep == "c":
            agent[ stts[jj] ][nn].starflag = True
        if somep == "d":
            agent[ stts[jj] ][nn + 1].starflag = True
    return


def insrtNS(newsect):
    agent[ stts[ii] ].insert(mm + 1, newsect)
    agent[ stts[jj] ].insert(nn + 1, newsect)
    return


def insrtN(n1, n2, stainflag):
    tpa = agent[ stts[ii] ][mm]
    tpb = agent[ stts[ii] ][mm + 1]
    tpc = agent[ stts[jj] ][nn]
    tpd = agent[ stts[jj] ][nn + 1]
    if n2 not in {"a", "b", "c", "d"}:
        if n1 in {"c", "d"}:
            if stainflag:
                tpd = agent[ stts[jj] ][nn + 2]
            if n1 == "c":
                tempnode = tpc
            else:
                tempnode = tpd
            agent[ stts[ii] ].insert(mm + 1, tempnode)
        else:
            if stainflag:
                tpb = agent[ stts[ii] ][mm + 2]
            if n1 == "a":
                tempnode = tpa
            else:
                tempnode = tpb
            agent[ stts[jj] ].insert(nn + 1, tempnode)
    else:
        xtdic = { tpa.x: tpa, tpb.x: tpb, tpc.x: tpc, tpd.x: tpd }
        ytdic = { tpa.y: tpa, tpb.y: tpb, tpc.y: tpc, tpd.y: tpd }
        if n1 in {"c", "d"}:
            if tpa.x != tpb.x:
                tord = sorted( [ tpa.x, tpc.x, tpd.x ] )
                tdic = xtdic
            else:
                tord = sorted( [ tpa.y, tpc.y, tpd.y ] )
                tdic = ytdic
            if tdic[ tord[0] ] == tpa:
                agent[ stts[ii] ].insert(mm + 1, tdic[ tord[1] ])
                agent[ stts[ii] ].insert(mm + 2, tdic[ tord[2] ])
            else:
                agent[ stts[ii] ].insert(mm + 1, tdic[ tord[1] ])
                agent[ stts[ii] ].insert(mm + 2, tdic[ tord[0] ])
        else:
            if tpc.x != tpd.x:
                tord = sorted( [ tpc.x, tpa.x, tpb.x ] )
                tdic = xtdic
            else:
                tord = sorted( [ tpc.y, tpa.y, tpb.y ] )
                tdic = ytdic
            if tdic[ tord[0] ] == tpc:
                agent[ stts[jj] ].insert(nn + 1, tdic[ tord[1] ])
                agent[ stts[jj] ].insert(nn + 2, tdic[ tord[2] ])
            else:
                agent[ stts[jj] ].insert(nn + 1, tdic[ tord[1] ])
                agent[ stts[jj] ].insert(nn + 2, tdic[ tord[0] ])
    return


def judgeInsrt(pa, pb, pc, pd):
    lab = list( Vector(pa, pb) )
    lcd = list( Vector(pc, pd) )
    lac = list( Vector(pa, pc) )
    lad = list( Vector(pa, pd) )

    lcb = list( Vector(pc, pb) )
    lca = list( map(lambda x: -1 * x, lac) )

    crit = []
    crit.append( VProduct(lab, lac) * VProduct(lab, lad) )
    crit.append( VProduct(lab, lac) )
    crit.append( VProduct(lab, lad) )
    crit.append( VProduct(lcd, lcb) * VProduct(lcd, lca) )
    crit.append( VProduct(lcd, lcb) )
    crit.append( VProduct(lcd, lca) )

    # ### test
    # print( "mm = ", mm, " nn = ", nn )
    # print( pa, pb, pc, pd )
    # print( "lab=", lab, "lac=", lac, "lad=", lad )
    # print( "lcd=", lcd, "lca=", lca, "lcb=", lcb )
    # print( crit )

    if crit[0] < 0 and crit[3] < 0:
        # intersect
        xcoor, ycoor = interSection(pa, pb, pc, pd)
        newsect = NODE(xcoor, ycoor)
        newsect.starflag = True
        insrtNS(newsect)
        return True
    elif crit[0] * crit[3] != 0:
        # non-intersect
        return False
    elif crit[1] == 0 and crit[2] == 0:
        # collinear: inclusive or connectied or seperated
        order = [ ["a", pa], ["b", pb], ["c", pc], ["d", pd] ]
        if pa.x != pb.x:
            order = sorted(order, key = lambda u: u[1].x)
        else:
            order = sorted(order, key = lambda u: u[1].y)
        if order[0][0] <= "b" and order[3][0] <= "b" or order[0][0] > "b" and order[3][0] > "b":
            if order[0][1].handnum() == order[1][1].handnum():
                markFlag( [ order[0][0], order[1][0], order[2][0] ] )
                insrtN( order[2][0], "0", False )
                return True
            elif order[3][1].handnum() == order[2][1].handnum():
                markFlag( [ order[1][0], order[2][0], order[3][0] ] )
                insrtN( order[1][0], "0", False )
                return True
            else:
                markFlag( [ order[1][0], order[2][0] ] )
                insrtN( order[1][0], order[2][0], False )
                return True
        else:
            if order[1][1].handnum() == order[2][1].handnum():
                markFlag( [ order[1][0], order[2][0] ] )
                return True
            elif order[0][0] <= "b" and order[1][0] <= "b" or order[0][0] > "b" and order[1][0] > "b":
                return False
            elif order[0][1].handnum() == order[1][1].handnum():
                if order[2][1].handnum() == order[3][1].handnum():
                    markFlag( [ order[0][0], order[1][0], order[2][0], order[3][0] ] )
                    return True
                else:
                    markFlag( [ order[0][0], order[1][0], order[2][0] ] )
                    insrtN( order[2][0], "0", False )
                    return True
            if order[3][1].handnum() == order[2][1].handnum():
                markFlag( [ order[1][0], order[2][0], order[3][0] ] )
                insrtN( order[1][0], "0", False )
                return True
            else:
                markFlag( [ order[1][0], order[2][0] ] )
                insrtN( order[1][0], "0", False )
                insrtN( order[2][0], "0", True )
                return True
    else:
        cntz = 0
        for i in range(6):
            if crit[i] == 0:
                cntz += 1
        if cntz == 4:
            # 2 points are coincide
            pdic = { "a": pa, "b": pb, "c": pc, "d": pd }
            for i in {"a", "b", "c", "d"}:
                for j in {"a", "b", "c", "d"}:
                    if j != i:
                        if pdic[i].handnum() == pdic[j].handnum():
                            break
                if pdic[i].handnum() == pdic[j].handnum():
                    break
            markFlag( [i, j] )
            return True
        elif cntz == 2:
            # 1 point is on aother line or apart
            recr = crit[1:3] + crit[4:6]
            zfind = recr.index(0)
            vdic = { 0: "c", 1: "d", 2: "b", 3: "a" }
            pdic = { "a": pa, "b": pb, "c": pc, "d": pd }
            if vdic[ zfind ] not in {"a", "b"}:
                if isBTW( pdic[ vdic[ zfind ] ], pa, pb ):
                    markFlag( vdic[ zfind ] )
                    insrtN( vdic[ zfind ], "0", False )
                    return True
                else:
                    return False
            else:
                if isBTW( pdic[ vdic[ zfind ] ], pc, pd ):
                    markFlag( vdic[ zfind ] )
                    insrtN( vdic[ zfind ], "0", False )
                    return True
                else:
                    return False


def geneGraph():
    global agent, stts
    global ii, jj, mm, nn
    agent = copy.deepcopy(dbase)

    stts = list(agent)
    for ii in range( len(stts) ):
        for jj in range( ii + 1, len(stts) ):
            mm = -1
            while True:
                mm += 1
                if mm >= len( agent[ stts[ii] ] ) - 1:
                    break
                nn = -1
                while True:
                    nn += 1
                    if nn >= len( agent[ stts[jj] ] ) - 1:
                        break
                    pa = agent[ stts[ii] ][mm]
                    pb = agent[ stts[ii] ][mm + 1]
                    pc = agent[ stts[jj] ][nn]
                    pd = agent[ stts[jj] ][nn + 1]

                    # # test
                    # print( stts[ii], "  ", stts[jj] )
                    # print( "fa=", pa.starflag, " fb=", pb.starflag, " fc=", pc.starflag, " fd=", pd.starflag, )

                    intsctf = judgeInsrt(pa, pb, pc, pd) # Judgeeeeeee banana
                    
                    # # test
                    # print( "fa=", pa.starflag, " fb=", pb.starflag, " fc=", pc.starflag, " fd=", pd.starflag, )
                    # print()
    return


def geneVE():
    for travel in agent:
        for i in range( len( agent[ travel ] ) - 1  ):
            if agent[ travel ][i].starflag or agent[ travel ][i + 1].starflag:
                agent[ travel ][i].vflag = True
                agent[ travel ][i + 1].vflag = True
    return


# being adapted to Assignment 3
def outVE():
    sv = set()
    nickname = {}
    cnt = 0
    for travel in agent:
        for ver in agent[travel]:
            if ver.vflag and ver.handnum() not in sv:
                sv.add(ver.handnum())
                cnt += 1
                nickname[ver.handnum()] = cnt

    print("V " + str(cnt), file = sys.stdout)

    se = set()
    oeline = ""
    for travel in agent:
        for i, ver in enumerate(agent[travel][:-1]):
            if ver.starflag or agent[travel][i + 1].starflag:
                nn1 = nickname[ver.handnum()]
                nn2 = nickname[agent[travel][i + 1].handnum()]
                if (nn1, nn2) not in se and (nn2, nn1) not in se:
                    se.add((nn1, nn2))
                    oeline += "<" + str(nn1) + "," + str(nn2) + ">,"
    oeline = oeline.rstrip(",")

    print("E {" + oeline + "}", file = sys.stdout)
    return
    


def execute(cmd, stname, chain):
    try:
        if cmd in cmdlib[1:3] and stname not in dbase:
                raise Exception("This street isn't exist.")
        elif cmd == cmdlib[0] and stname in dbase:
                raise Exception("This street has already existed.")
    except Exception as ex:
        print("Error: " + str(ex), file = sys.stderr)
        return

    if cmd == cmdlib[3]:
        geneGraph()
        geneVE()
        outVE()
    elif cmd == cmdlib[2]:
        del dbase[stname]
    else:
        dbase[stname] = chain    

    # # test
    # if cmd == "gg":
    #     print(dbase)
    #     print(agent)
    #     for ttt in agent:
    #         for TTT in agent[ttt]:
    #             print(TTT.starflag, "  ", TTT.vflag)
    #         print()
    return


def main():
    # YOUR MAIN CODE GOES HERE

    # sample code to read from stdin.
    # make sure to remove all spurious print statements as required
    # by the assignment
    global cmdlib, dbase
    cmdlib = ["add", "mod", "rm", "gg"]
    dbase = {}
    while True:
        line = sys.stdin.readline()
        if line == "\n" or line == '':
            break
        if line.strip(" ") == "\n":
            break
        try:
            cmd, stname, chain = parseLine(line)
            execute(cmd, stname, chain)
        except Exception as ex:
            print("Error: " + str(ex), file = sys.stderr)

        # print("read a line:", line)

    # print("Finished reading input")
    # print( line ) 

    # return exit code 0 on successful termination
    sys.exit(0)


if __name__ == "__main__":
    main()
