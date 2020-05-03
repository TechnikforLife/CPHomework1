import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
#rc('text', usetex=True)

rawdata = np.loadtxt("data/number1.dat",delimiter=";" ,dtype=float)
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


rawdata = np.loadtxt("data/number21.dat",delimiter=";" ,dtype=float)
x_fit=rawdata[1:, 0]
y_fit=rawdata[1:, 1]
for i in range(1,np.shape(rawdata)[1]):
    y_fit=rawdata[1:, i]
    plt.scatter(x_fit, y_fit,label="$a_{H2.1}=$"+str(rawdata[0,i]),s=5,marker="+",linewidth=0.5)

rawdata2 = np.loadtxt("data/number22.dat",delimiter=";" ,dtype=float)
x_fit=rawdata2[1:, 0]
y_fit=rawdata2[1:, 1]
for i in range(1,np.shape(rawdata)[1]):
    y_fit=rawdata2[1:, i]
    plt.scatter(x_fit, y_fit,label="$a_{H2.2}=$"+str(rawdata2[0,i]),s=5,marker="x",linewidth=0.5)


plt.legend(loc='best',ncol=2)
plt.xlabel("z")
plt.ylabel("E(z)")
plt.yscale("log")
#plt.xscale("log")

plt.savefig("data/number2.pdf", bbox_inches=0,format='pdf')
plt.close()

rawdata = np.loadtxt("data/number31.dat",delimiter=";" ,dtype=float)
x_fit=rawdata[1:, 0]
y_fit=rawdata[1:, 1]
plt.scatter(x_fit, y_fit,label="$a_{2}=$"+str(rawdata[0,1]),s=5,marker="x",linewidth=0.5)
for i in range(2,np.shape(rawdata)[1]):
    y_fit=rawdata[1:, i]
    plt.scatter(x_fit, y_fit,label="$a_{2}=$"+str(rawdata[0,i]),s=5,marker="+",linewidth=0.5)


plt.legend(loc='best',ncol=2)
plt.xlabel("z")
plt.ylabel("V(z)")
#plt.yscale("log")
#plt.xscale("log")

plt.savefig("data/number31.pdf", bbox_inches=0,format='pdf')
plt.close()

rawdata = np.loadtxt("data/number32.dat",delimiter=";" ,dtype=float)
x_fit=rawdata[1:, 0]
y_fit=rawdata[1:, 1]
plt.grid(color='#D3D3D3')
plt.scatter(x_fit, y_fit,label="$a_{2}=$"+str(rawdata[0,1]),s=5,marker="x",linewidth=0.5)
for i in range(2,np.shape(rawdata)[1]):
    y_fit=rawdata[1:, i]
    plt.scatter(x_fit, y_fit,label="$a_{2}=$"+str(rawdata[0,i]),s=5,marker="+",linewidth=0.5)

a=[5.745382e+00]
b=[0.1]
plt.axvline(x=3.462772,ymin=-1,ymax=1,linewidth=0.5,label="abc")
#plt.scatter(a,b,s=5,marker="x",linewidth=0.5)

plt.legend(loc='best',ncol=2)
plt.xlabel("z")
plt.ylabel("E(z)")
#plt.yscale("log")
#plt.xscale("log")

plt.savefig("data/number32.pdf", bbox_inches=0,format='pdf')
plt.close()

rawdata = np.loadtxt("data/number33.dat",delimiter=";" ,dtype=float)
x_fit=rawdata[:, 0]
y_fit=rawdata[:, 1]

plt.scatter(x_fit, y_fit,label="Location of roots",s=5,marker="x",linewidth=0.5)



plt.legend(loc='best',ncol=2)
plt.xlabel("a")
plt.ylabel("z")
#plt.yscale("log")
#plt.xscale("log")

plt.savefig("data/number33.pdf", bbox_inches=0,format='pdf')
plt.close()
