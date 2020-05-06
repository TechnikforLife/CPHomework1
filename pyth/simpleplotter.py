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
plt.grid(color='#D3D3D3',zorder=0)
plt.scatter(x_dat, y_dat,label="a="+str(rawdata[0,1]),s=5,marker="x",
            linewidth=0.5,zorder=3)
for i in range(2,np.shape(rawdata)[1]):
    y_dat=rawdata[1:, i]
    plt.scatter(x_dat, y_dat,label="a="+str(rawdata[0,i]),s=5,marker="+",
                linewidth=0.5,zorder=3)

#Plot a y_fit corresponding to the estimated graph in H1.3
x_dat=np.linspace(0.001,10,1000)
y_fit=1/x_dat
plt.plot(x_dat, y_fit,label="1/z",linewidth=0.5,color='#19D6E9')

#Add essential information to the plot
plt.legend(loc='best',ncol=2)
plt.xlabel("z")
plt.ylabel("V(z)")
plt.yscale("log")

#Save the plot
plt.savefig("data/number1.pdf", bbox_inches=0,format='pdf')
plt.close()

#***Part 2***

#Load "data/number21.dat". The columns get plotted in different colors
rawdata = np.loadtxt("data/number21.dat",delimiter=";" ,dtype=float)
x_dat=rawdata[1:, 0]
y_dat=rawdata[1:, 1]
plt.grid(color='#D3D3D3',zorder=0)
for i in range(1,np.shape(rawdata)[1]):
    y_dat=rawdata[1:, i]
    plt.scatter(x_dat, y_dat,label="$a_{H2.1}=$"+str(rawdata[0,i]),s=5,
                marker="+",linewidth=0.5,zorder=3)

#Load "data/number22.dat". The columns get plotted in different colors
rawdata2 = np.loadtxt("data/number22.dat",delimiter=";" ,dtype=float)
x_dat=rawdata2[1:, 0]
y_dat=rawdata2[1:, 1]
for i in range(1,np.shape(rawdata)[1]):
    y_dat=rawdata2[1:, i]
    plt.scatter(x_dat, y_dat,label="$a_{H2.2}=$"+str(rawdata2[0,i]),s=5,
                marker="x",linewidth=0.5,zorder=3)

#Add essential information to the plot
plt.legend(loc='best',ncol=2)
plt.xlabel("z")
plt.ylabel("$E_z(z)$")
plt.yscale("log")

#Save the plot
plt.savefig("data/number2.pdf", bbox_inches=0,format='pdf')
plt.close()

#***Part 3***

#Load "data/number31.dat" and plot the first column differently
#to make it more visible. The other columns get plotted in different colors
rawdata = np.loadtxt("data/number31.dat",delimiter=";" ,dtype=float)
x_dat=rawdata[1:, 0]
y_dat=rawdata[1:, 1]
plt.grid(color='#D3D3D3',zorder=0)
plt.scatter(x_dat, y_dat,label="$a_{2}=$"+str(rawdata[0,1]),s=5,marker="x",
            linewidth=0.5,zorder=3)
for i in range(2,np.shape(rawdata)[1]):
    y_dat=rawdata[1:, i]
    plt.scatter(x_dat, y_dat,label="$a_{2}=$"+str(rawdata[0,i]),s=5,marker="+",
                linewidth=0.5,zorder=3)

#Add essential information to the plot
plt.legend(loc='best',ncol=2)
plt.xlabel("z")
plt.ylabel("V(z)")

#Save the plot
plt.savefig("data/number31.pdf", bbox_inches=0,format='pdf')
plt.close()


#Load "data/number32.dat" and plot the first column differently
#to make it more visible. The other columns get plotted in different colors
rawdata = np.loadtxt("data/number32.dat",delimiter=";" ,dtype=float)
x_dat=rawdata[1:, 0]
y_dat=rawdata[1:, 1]
plt.grid(color='#D3D3D3',zorder=0)
plt.scatter(x_dat, y_dat,label="$a_{2}=$"+str(rawdata[0,1]),s=5,marker="x",
            linewidth=0.5,zorder=3)
for i in range(2,np.shape(rawdata)[1]):
    y_dat=rawdata[1:, i]
    plt.scatter(x_dat, y_dat,label="$a_{2}=$"+str(rawdata[0,i]),s=5,marker="+",
                linewidth=0.5,zorder=3)

#Add essential information to the plot
plt.legend(loc='best',ncol=2)
plt.xlabel("z")
plt.ylabel("$E_z(z)$")

#Save the plot
plt.savefig("data/number32.pdf", bbox_inches=0,format='pdf')
plt.close()


#Load "data/number33.dat". Just 1 column needs to be plotted.
rawdata = np.loadtxt("data/number33.dat",delimiter=";" ,dtype=float)
x_dat=rawdata[:, 0]
y_dat=rawdata[:, 1]
plt.grid(color='#D3D3D3',zorder=0)
plt.scatter(x_dat, y_dat,label="Location of roots",s=5,marker="x",
            linewidth=0.5,zorder=3)

#Add essential information to the plot
plt.legend(loc='best',ncol=2)
plt.xlabel("$a_2$")
plt.ylabel("z")

#Save the plot
plt.savefig("data/number33.pdf", bbox_inches=0,format='pdf')
plt.close()