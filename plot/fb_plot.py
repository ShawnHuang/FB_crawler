import matplotlib.pyplot as plt
import numpy as np
import json
from datetime import datetime
import matplotlib.dates as dates
import time
from pprint import pprint
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.ticker as ticker

#option 1
feeds = []
for line in open('./f3_cpp.json', 'r'):
    feeds.append(json.loads(line))

#pprint(feeds[0])
#option 2
#with open('./test.json') as data_file:
#    print(data_file)
#    feeds = json.load(data_file)

#pprint(feeds)

#acc_feed = []
#month = datetime.fromtimestamp(int(ts)).strftime('%Y-%m')
#acc_feed.append(month)
d = {}
for feed in feeds:
    ts = feed["timestamp"]
    cmts = feed["num_comments"]
    likes = feed["num_likes"]
    tag = time.mktime(time.strptime("%s%s" % (month,'-1 0:0:0'), '%Y-%m-%d %H:%M:%S'))
    data = d.get(tag, [0,0,0])
    d[tag] = [data[0] + 1,data[1] + int(cmts),data[2] + int(likes)]
print(d)
x=[]
y=[]
z=[]
w=[]
for k,v in d.items():
    x.append(datetime.fromtimestamp(int(k)))
    y.append(v[0])
    z.append(v[1])
    w.append(int(v[2]/5))

plt.switch_backend('WebAgg')
#plt.switch_backend('Qt4Agg')

fig = plt.figure(figsize=plt.figaspect(1.))

######
# first plot
######
fig.suptitle('2-dim display')
ax = fig.add_subplot(3, 1, 1)
ax.plot_date(x, z, markerfacecolor='CornflowerBlue', markeredgecolor='white')
fig.autofmt_xdate()
ax.set_xlim([datetime(2014, 5, 1), datetime(2015, 7, 1)])
ax.set_ylim([0, 250])
ax.set_ylabel('The number of feeds')

######
# second plot
######
def format_date(x, pos=None):
    return dates.num2date(x).strftime('%Y-%m') #use FuncFormatter to format dates

ax = fig.add_subplot(3, 1, 3, projection='3d')
X = np.array(dates.date2num(x))
xlen = len(X)
Y = np.array(y)
ylen = len(Y)
Z = np.array(z)
zlen = len(Z)
W = np.array(w)
#surf = ax.plot_surface(X, Y, Z, rstride=1, cstride=1,
#        linewidth=0, antialiased=False)

ax.scatter(X, Y, zs=Z, zdir='y', s=W, color='y')

ax.w_xaxis.set_major_locator(ticker.FixedLocator(X)) # I want all the dates on my xaxis
ax.w_xaxis.set_major_formatter(ticker.FuncFormatter(format_date))
for tl in ax.w_xaxis.get_ticklabels(): # re-create what autofmt_xdate but with w_xaxis
       tl.set_ha('right')
       tl.set_rotation(30)     
ax.set_zlim3d(0, 300)
ax.set_ylim3d(0, 1000)
#ax.set_xlabel('Date')
#ax.set_xlabel('The size of scatter is the number of likes')
ax.set_ylabel('\n\nfeeds')
ax.set_zlabel('comments')

plt.show()
# vim: autoindent tabstop=4 shiftwidth=4 expandtab softtabstop=4 filetype=python
