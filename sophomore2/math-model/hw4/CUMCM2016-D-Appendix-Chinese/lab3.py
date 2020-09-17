#! sudo /usr/local/python3/bin/python3.7
import xlrd
import calendar
import numpy as np
from lab2 import f1, f2

vs = [[] for _ in range(6)]
for i in range(12):
    mouth = i + 1
    file_path = "附件2  风电场典型风机报表/{0:0>2}.xls".format(mouth)
    data = xlrd.open_workbook(file_path)

    for i in range(data.nsheets):
        table = data.sheet_by_index(i)

        for j in range(6):
            for k in range(2, 14):
                v = table.cell(j + 3, k).value
                vs[j].append(v)

ps1, ps2 = [[] for _ in range(3)], [[] for _ in range(3)]
ap1, ap2 = [], []
for i in range(3):
    ps1[i] = np.polyval(f1, vs[i])
    ap1.append(np.mean(ps1[i]))

    ps2[i] = np.polyval(f2, vs[i + 3])
    ap2.append(np.mean(ps2[i]))


place = [4, 16, 24, 33, 49, 57]

print("机型1三处的平均年功率: {:.2f}kW".format(np.mean(ap1)))
for i in range(3):
    print("{}# 平均年风速: {:.2f}m/s     平均年功率{:.2f}kW".format(place[i], np.mean(vs[i]), ap1[i]))

print()

print("机型2三处的平均年功率: {:.2f}kW".format(np.mean(ap2)))
for i in range(3):
    print("{}# 平均年风速: {:.2f}m/s     平均年功率{:.2f}kW".format(place[i + 3], np.mean(vs[i]), ap2[i]))

