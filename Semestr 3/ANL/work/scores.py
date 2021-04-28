gapa_file = "/home/suprememe/Desktop/University/Semestr 3/ANL/work/garmisch.txt"
oberstdorf_file = "/home/suprememe/Desktop/University/Semestr 3/ANL/work/oberstdorf.txt"
bisochsofen_file = (
    "/home/suprememe/Desktop/University/Semestr 3/ANL/work/bischofshofen.txt"
)
bad_file = "/home/suprememe/Desktop/University/Semestr 3/ANL/work/bad.txt"

files = []

files.append(gapa_file)
files.append(oberstdorf_file)
files.append(bisochsofen_file)
files.append(bad_file)

arr = []


def deleteContent(pfile):
    pfile.seek(0)
    pfile.truncate()


def search(name, l):
    iter = 0
    for i in l:
        if i["name"] == name:
            return [i["points"], iter]
        iter += 1
    return False


for file in files:
    iter, begin = 1, True
    with open(file, "r") as input:
        for line in input:
            curr_line = line.split()
            searched = search(curr_line[2] + " " + curr_line[3], arr)
            if searched == False:
                if iter <= 30:
                    jumper = {
                        "name": curr_line[2] + " " + curr_line[3],
                        "points": float(curr_line[9]),
                    }
                else:
                    jumper = {
                        "name": curr_line[2] + " " + curr_line[3],
                        "points": float(curr_line[7]),
                    }
                arr.append(jumper)
            else:
                if iter <= 30:
                    jumper = {
                        "name": curr_line[2] + " " + curr_line[3],
                        "points": float(curr_line[9]) + float(searched[0]),
                    }
                else:
                    jumper = {
                        "name": curr_line[2] + " " + curr_line[3],
                        "points": float(curr_line[7]) + float(searched[0]),
                    }
                arr[searched[1]].update(jumper)
            iter += 1

arr = sorted(arr, key=lambda i: i["points"], reverse=True)

to_write = open(
    "/home/suprememe/Desktop/University/Semestr 3/ANL/work/results.txt", "a"
)

deleteContent(to_write)

iter = 1
for i in arr:
    to_write.write(
        str(iter) + ".  " + i["name"] + "   " + str(round(i["points"], 2)) + "\n"
    )
    iter += 1

to_write.close()