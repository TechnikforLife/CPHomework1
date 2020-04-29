import numpy as np
import matplotlib.pyplot as plt

rawdata = np.loadtxt("data/number1.dat",delimiter=";" ,dtype=float)
#print(rawdata)
fig = plt.figure()
x_fit=rawdata[1:, 0]
y_fit=rawdata[1:, 1]
plt.scatter(x_fit, y_fit,label="a="+str(rawdata[0,1]),s=5,marker="x",linewidth=0.5)
for i in range(2,np.shape(rawdata)[1]):
    y_fit=rawdata[1:, i]
    plt.scatter(x_fit, y_fit,label="a="+str(rawdata[0,i]),s=5,marker="+",linewidth=0.5)
#print(len(x_fit),len(rawdata),np.shape(rawdata)[1])





y_fit=1/x_fit
plt.plot(x_fit, y_fit,label="1/z",linewidth=0.5)
plt.legend(loc='best',ncol=2)
plt.xlabel("z")
plt.ylabel("V(z)")
plt.yscale("log")
#plt.xscale("log")
#plt.xlim(0,1)
#plt.ylim(1,100)
# fig = plt.figure()
plt.savefig("data/numb1.pdf", bbox_inches=0,format='pdf')

plt.close()
