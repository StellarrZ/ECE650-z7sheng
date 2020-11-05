#!/usr/bin/env python3

#
# Skeleton for ECE650 Test 1.5
# DO NOT DISTRIBUTE
#
# Complete the two provided functions. Implement as much functionality as you
# can. Make sure to not change the interface.
#
# More details are in the question on LEARN.
#
# You are allowed to use a Python IDE and Python Documentation available at
# https://docs.python.org/3/
#
# You are very likely to need to add extra functions and/or classes to organize
# your code. We will mark your code for functionality only. Using extra
# functions is not required, but is highly advised
#


def test_string(s):
    ban = ["\"", "\'", "-", ":", "\n"]
    for ch in ban:
        if ch in s:
            return False
    return True


def print_syaml(data):
    """Print data in SYAML format. Raise an exception if this is not possible"""

    if isinstance(data, dict) or isinstance(data, list):
        print("---")
        # YOUR CODE TO PRINT DATA GOES HERE

        if isinstance(data, dict):
            for key in data:
                ele = data[key]
                if isinstance(ele, list):
                    print(key + ":")
                    for quark in ele:
                        if test_string(quark):
                            print("- " + quark)
                        else:
                            raise Exception("Wrong type of data: " + "Special character(s)")
                elif isinstance(ele, str):
                    if test_string(ele):
                        print(key + ": " + ele)
                    else:
                        raise Exception("Wrong type of data: " + "Special character(s)")
                else:
                    raise Exception("Wrong type of data: " + str(ele.__class__))
                # data.pop(key)
        else:
            for ele in data:
                if isinstance(ele, dict):
                    bar = {False: "- ", True: "  "}
                    for i, key in ele:
                        quark = ele[key]
                        if test_string(quark):
                            print(bar[i > 0] + key + " : " + quark)
                        else:
                            raise Exception("Wrong type of data: " + "Special character(s)")
                elif isinstance(ele, str):
                    if test_string(ele):
                        print("- " + ele)
                    else:
                        raise Exception("Wrong type of data: " + "Special character(s)")
                else:
                    raise Exception("Wrong type of data: " + str(ele.__class__))

        print("...")
    else:
        raise Exception("Wrong type of data: " + str(data.__class__))


def parse_syaml(lines):
    if not isinstance(lines, list):
        raise Exception("Expecting a list of strings")
    if not (len(lines) >= 2 and lines[0] == "---\n" and lines[-1] == "...\n"):
        raise Exception("Begin or end document is missing")

    # YOUR CODE GOES HERE
    lines.pop(0)
    lines.pop()

    if lines:
        if lines[0][:2] == "- ":
            func = True
            inner = ": " in lines[0]
            doc = []
        elif ": " in lines[0] or ":\n" in lines[0]:
            func = False
            inner = ":\n" in lines[0]
            doc = {}
        else:
            raise Exception("Wrong content")
            return None

        if func:
            if inner:
                baby = {}
                for lx in lines:
                    if ": " not in lx:
                        raise Exception("Wrong content")
                        return None
                    else:
                        sep = lx.index(":")
                        left = lx[:sep].strip()
                        right = lx[sep + 2:].strip("\n")
                        if lx[:2] == "- ":
                            if baby:
                                doc.append(baby)
                                baby = {}
                            baby[left[2:]] = right
                        else:
                            baby[left] = right
                if baby:
                    doc.append(baby)
            else:
                for lx in lines:
                    doc.append( lx.strip("\n").strlip("- ") )
        else:
            if inner:
                baby = []
                key = -1
                for lx in lines:
                    if ":\n" in lx or ": " in lx:
                        if baby:
                            doc[key] = baby
                        sep = lx.index(":")
                        key = lx[:sep]
                        baby = []
                    elif "- " in lx:
                        lx = lx.lstrip().lstrip("- ").strip("\n")
                        baby.append(lx)
                    else:
                        raise Exception("Wrong content")
                        return None
                if baby:
                    doc[key] = baby
            else:
                for lx in lines:
                    lx = lx.strip("\n")
                    sep = lx.index(":")
                    doc[lx[:sep]] = lx[sep + 2:]
        
        return doc
    else:
        return None


# This is a simple test function provided from your convenience
if __name__ == "__main__":
    d1 = ["one", "two", "three"]
    print_syaml(d1)

    t1 = ["---\n",
          "one: un\n",
          "two: deux\n",
          "three: trois\n",
          "...\n"]
    d2 = parse_syaml(t1)
    print(d2)
    print_syaml(d2)
