import numpy as np
from scipy import stats
from matplotlib import pyplot as plt

m = [-5, 5]
w = [1, 1]
sig = [.3, 6.0]


t = np.linspace( -10.0, 15.0, num=1000 )

y0 = stats.norm.pdf(t, loc = m[0], scale = sig[0])*w[0]
y1 = stats.norm.pdf(t, loc = m[1], scale = sig[1])*w[1]


#lt.plot(t, y0)
#lt.plot(t, y1)


y = (w[0]*y0 + w[1]*y1)/(w[0]+w[1])

plt.plot(t, y)

plt.show()
