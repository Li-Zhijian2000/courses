#! sudo /usr/local/python3/bin/python3.7
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

v1 = np.arange(3, 13, 0.5) # m/s
v1 = np.hstack([v1, np.arange(13, 26, 1.0)])
p1 = [27.00, 56.41, 96.76, 140.10, 191.13, 254.97, 335.13, 423.64, 527.61, 650.08, 789.66, 951.86, 1120.18, 1308.91, 1516.25, 1730.77, 1912.29, 2003.52, 2010.00, 2010.00, 2010.00, 2010.00, 2010.00, 2010.00, 2010.00, 2010.00, 2010.00, 2010.00, 2010.00, 2010.00, 2010.00, 2010.00, 2010.00]

v2 = np.arange(3.5, 24, 1.0)
p2 = [40, 74, 164, 293, 471, 702, 973, 1269, 1544, 1544, 1544, 1544, 1544, 1544, 1544, 1544, 1544, 1544, 1544, 1544, 1544]

# 拟合
tv1 = np.arange(3, 11.5, 0.5)
tp1 = p1[0:len(tv1)]
f1 = np.polyfit(tv1, tp1, 2)
x = np.arange(3, 11.1, 0.1)
y = np.polyval(f1, x)

plt.subplot(121).set_title('机型1 功率曲线')
plt.plot(x, y, 'r*', label = r'$28.17x^2-158.67x+268.77$')
plt.plot(v1, p1, label = r'$actual$')
plt.xlabel('风速(m/s)')
plt.ylabel('功率(kW)')
plt.legend(loc='lower right', fontsize=6)


tv2 = np.array([3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0])
tp2 =  p2[0:len(tv2)]
f2 = np.polyfit(tv2, tp2, 2)
x = np.arange(3, 11.1, 0.1)
y = np.polyval(f2, x)

plt.subplot(122).set_title('机型2 功率曲线')
plt.plot(x, y, 'r*', label = r'$18.92x^2-69.24x+42.85$')
plt.plot(v2, p2, label = r'$actual$')
plt.xlabel('风速(m/s)')
plt.ylabel('功率(kW)')
plt.legend(loc='lower right', fontsize=6)

plt.savefig('foo.png')
