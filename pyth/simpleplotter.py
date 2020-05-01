import numpy as np
import matplotlib.pyplot as plt

rawdata = np.loadtxt("data/number1.dat",delimiter=";" ,dtype=float)
fig = plt.figure()
x_fit=rawdata[1:, 0]
y_fit=rawdata[1:, 1]
plt.scatter(x_fit, y_fit,label="a="+str(rawdata[0,1]),s=5,marker="x",linewidth=0.5)
for i in range(2,np.shape(rawdata)[1]):
    y_fit=rawdata[1:, i]
    plt.scatter(x_fit, y_fit,label="a="+str(rawdata[0,i]),s=5,marker="+",linewidth=0.5)

y_fit=1/x_fit
plt.plot(x_fit, y_fit,label="1/z",linewidth=0.5)

plt.legend(loc='best',ncol=2)
plt.xlabel("z")
plt.ylabel("V(z)")
plt.yscale("log")
#plt.xscale("log")

plt.savefig("data/number1.pdf", bbox_inches=0,format='pdf')
plt.close()


rawdata = np.loadtxt("data/number2.dat",delimiter=";" ,dtype=float)
fig = plt.figure()
x_fit=rawdata[1:, 0]
y_fit=rawdata[1:, 1]
plt.scatter(x_fit, y_fit,label="a="+str(rawdata[0,1]),s=5,marker="x",linewidth=0.5)
for i in range(2,np.shape(rawdata)[1]):
    y_fit=rawdata[1:, i]
    plt.scatter(x_fit, y_fit,label="a="+str(rawdata[0,i]),s=5,marker="+",linewidth=0.5)


plt.legend(loc='best',ncol=2)
plt.xlabel("z")
plt.ylabel("E(z)")
plt.yscale("log")
#plt.xscale("log")

plt.savefig("data/number2.pdf", bbox_inches=0,format='pdf')
plt.close()