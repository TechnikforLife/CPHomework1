#import the needed packages
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc

#***Part 1***

#Load "data/number1.dat" and plot the first column differently
#to make it more visible. The other columns get plotted in different colors
rawdata = np.loadtxt("data/number1.dat",delimiter=";" ,dtype=float)
x_dat=rawdata[1:, 0]
y_dat=rawdata[1:, 1]
plt.scatter(x_dat, y_dat,label="a="+str(rawdata[0,1]),s=5,marker="x",
            linewidth=0.5)
for i in range(2,np.shape(rawdata)[1]):
    y_dat=rawdata[1:, i]
    plt.scatter(x_dat, y_dat,label="a="+str(rawdata[0,i]),s=5,marker="+",
                linewidth=0.5)

#Plot a y_fit corresponding to the estimated graph in H1.3
y_fit=1/x_dat
plt.plot(x_dat, y_fit,label="1/z",linewidth=0.5)

#At essential information to the plot
plt.legend(loc='best',ncol=2)
plt.xlabel("z")
plt.ylabel("V(z)")
plt.yscale("log")

#Save the plot
plt.savefig("data/number1.pdf", bbox_inches=0,format='pdf')
plt.close()

#***Part 2***

rawdata = np.loadtxt("data/number21.dat",delimiter=";" ,dtype=float)
x_dat=rawdata[1:, 0]
y_dat=rawdata[1:, 1]
for i in range(1,np.shape(rawdata)[1]):
    y_dat=rawdata[1:, i]
    plt.scatter(x_dat, y_dat,label="$a_{H2.1}=$"+str(rawdata[0,i]),s=5,marker="+",linewidth=0.5)

rawdata2 = np.loadtxt("data/number22.dat",delimiter=";" ,dtype=float)
x_dat=rawdata2[1:, 0]
y_dat=rawdata2[1:, 1]
for i in range(1,np.shape(rawdata)[1]):
    y_dat=rawdata2[1:, i]
    plt.scatter(x_dat, y_dat,label="$a_{H2.2}=$"+str(rawdata2[0,i]),s=5,marker="x",linewidth=0.5)


plt.legend(loc='best',ncol=2)
plt.xlabel("z")
plt.ylabel("E(z)")
plt.yscale("log")

plt.savefig("data/number2.pdf", bbox_inches=0,format='pdf')
plt.close()

#***Part 3***

rawdata = np.loadtxt("data/number31.dat",delimiter=";" ,dtype=float)
x_dat=rawdata[1:, 0]
y_dat=rawdata[1:, 1]
plt.scatter(x_dat, y_dat,label="$a_{2}=$"+str(rawdata[0,1]),s=5,marker="x",linewidth=0.5)
for i in range(2,np.shape(rawdata)[1]):
    y_dat=rawdata[1:, i]
    plt.scatter(x_dat, y_dat,label="$a_{2}=$"+str(rawdata[0,i]),s=5,marker="+",linewidth=0.5)


plt.legend(loc='best',ncol=2)
plt.xlabel("z")
plt.ylabel("V(z)")

plt.savefig("data/number31.pdf", bbox_inches=0,format='pdf')
plt.close()

rawdata = np.loadtxt("data/number32.dat",delimiter=";" ,dtype=float)
x_dat=rawdata[1:, 0]
y_dat=rawdata[1:, 1]
plt.grid(color='#D3D3D3')
plt.scatter(x_dat, y_dat,label="$a_{2}=$"+str(rawdata[0,1]),s=5,marker="x",linewidth=0.5)
for i in range(2,np.shape(rawdata)[1]):
    y_dat=rawdata[1:, i]
    plt.scatter(x_dat, y_dat,label="$a_{2}=$"+str(rawdata[0,i]),s=5,marker="+",linewidth=0.5)

a=[5.745382e+00]
b=[0.1]
plt.axvline(x=3.462772,ymin=-1,ymax=1,linewidth=0.5,label="abc")

plt.legend(loc='best',ncol=2)
plt.xlabel("z")
plt.ylabel("E(z)")

plt.savefig("data/number32.pdf", bbox_inches=0,format='pdf')
plt.close()

rawdata = np.loadtxt("data/number33.dat",delimiter=";" ,dtype=float)
x_dat=rawdata[:, 0]
y_dat=rawdata[:, 1]

plt.scatter(x_dat, y_dat,label="Location of roots",s=5,marker="x",linewidth=0.5)


plt.legend(loc='best',ncol=2)
plt.xlabel("$a_2$")
plt.ylabel("z")

plt.savefig("data/number33.pdf", bbox_inches=0,format='pdf')
plt.close()
