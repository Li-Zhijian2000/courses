#! sudo /usr/local/python3/bin/python3.7
import xlrd
import calendar
import numpy as np
from collections import Counter
import matplotlib.pyplot as plt

rho = 0.9762 # kg/m3
total_p = 198.5

def check_data(p, v):
    if (p == '' or not isinstance(p, float)):
        print("{} Sheel{} {}{} P: {}".format(file_path, i + 1, k + 1, chr(j + 1 + ord('A')), p))
    
    if (v == '' or not isinstance(v, float)):
        print("{} Sheel{} {}{} V: {}".format(file_path, i + 1, k + 1, chr(j + 2 + ord('A')), v))

def avep_calc(ps):
    return np.mean(ps)

def avev_calc(vs):
    return np.mean(vs)

# 有效风能密度
def dwe_calc(vs):
    # return sum([ pow(v, 3) * k for (v, cnt) in Counter(vs).items()])  * 0.25 * rho / 2
    return sum([pow(v, 3) for v in vs]) * 0.25 * rho / 2
        
# 平均风功率密度
def dwp_calc(vs):
    return 0.5 * rho * np.mean([pow(v, 3) for v in vs])
   
# 有效小时
def effec_hours(vs):
    return len([v for v in vs if v >= 3 and v <= 25]) / 4

year_p = [] # 全年的全部功率
year_v = [] # 全年的全部风速

avep_rs = []
hours_rs = []

print("{: ^4}{: ^12}{: ^12}{: ^12}{: ^12}{: ^12}{: ^12}{: ^12}".format(\
    '月份', '月平均风速', '月平均功率', '月平均功率/额定功率', '月平均风功率密度', '月有效风功率密度', '月有效小时数', '月有效小时比例'))
for i in range(12):
    mouth = i + 1
    file_path = "附件1  平均风速和风电场日实际输出功率表/2015{0:0>2}.xls".format(mouth)
    data = xlrd.open_workbook(file_path)

    mouth_p, mouth_v = [], [] # 单个月的全部数据
    for i in range(data.nsheets): # i 天
        table = data.sheet_by_index(i)
        day_p, day_v = [], []
        for j in range(0, 10, 3):
            for k in range(3, 27):
                p, v = table.cell(k, j+1).value, table.cell(k, j+2).value
                check_data(p, v)
                day_p.append(p)
                day_v.append(v)
        mouth_p.extend(day_p)
        mouth_v.extend(day_v)
    
    # 处理每个月数据
    year_p.extend(mouth_p)
    year_v.extend(mouth_v)

    ave_v, ave_p, avep_r, dwp, effec_dwp, hours, effehours_r = \
        avev_calc(mouth_v), avep_calc(mouth_p), avep_calc(mouth_p) / total_p, dwp_calc(mouth_v), dwp_calc([v for v in mouth_v if v >= 3 and v <= 25]), effec_hours(mouth_v), effec_hours(mouth_v) / 24 / calendar.monthrange(2015, mouth)[1]

    print("{: ^4}{: ^16.2f}{: ^20.2f}{: ^20.2f}{: ^20.2f}{: ^20.2f}{: ^20.2f}{: ^20.2f}".format(mouth, ave_v, ave_p, avep_r, dwp, effec_dwp, hours, effehours_r))
    
    avep_rs.append(avep_r)
    hours_rs.append(effehours_r)

x = range(1, 13)

plt.plot(x, avep_rs, marker='o', mec='r', mfc='w', label = '可利用功率比')
plt.plot(x, hours_rs, marker='*', ms=10, label = '有效风速时间比')
plt.xlabel('月份')
plt.legend(loc='center', fontsize=10)
plt.savefig('lab1.png')

ave_v, ave_p, avep_r, dwp, effec_dwp, hours, effehours_r = \
    avev_calc(year_v), avep_calc(year_p), avep_calc(year_p) / total_p, dwp_calc(year_v), dwp_calc([v for v in year_v if v >= 3 and v <= 25]), effec_hours(year_v), effec_hours(year_v) / 24 / 365

print("{: ^4}{: ^16.2f}{: ^20.2f}{: ^20.2f}{: ^20.2f}{: ^20.2f}{: ^20.2f}{: ^20.2f}".format('全年', ave_v, ave_p, avep_r, dwp, effec_dwp, hours, effehours_r))

# print("\n# 风能资源评估")
# print("年平均风速: {:.2f} m/s".format(avev_calc(year_v)))
# print("年平均风功率密度: {:.2f} W/m2".format(dwp_calc(year_v)))

# print("\n# 风能利用率评估")
# ap = np.mean(year_p)
# print("年平均输出功率: {:.2f} MW".format(ap))
# print("输出功率/额定功率: {:.2f}%".format(ap / total_p * 100))
# print("年有效风能密度：{:.2f} Wh/m2".format(dwe_calc(year_v)))