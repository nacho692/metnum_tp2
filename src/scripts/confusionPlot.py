import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patheffects as path_effects

# from sklearn.metrics import confusion_matrix
# y_true = [2, 0, 2, 2, 0, 1, 5, 9, 10, 6 , 55]
# y_pred = [0, 0, 2, 2, 0, 2, 5, 8, 2, 55, 6]
# df_confusion = confusion_matrix(y_true, y_pred)



df_confusion = [[33,2,0,0,0,0,0,0,0,1,3], 
            	[3,31,0,0,0,0,0,0,0,0,0], 
            	[0,4,41,0,0,0,0,0,0,0,1], 
            	[0,1,0,30,0,6,0,0,0,0,1], 
            	[0,0,0,0,38,10,0,0,0,0,0], 
            	[0,0,0,3,1,39,0,0,0,0,4], 
            	[0,2,2,0,4,1,31,0,0,0,2],
            	[0,1,0,0,0,0,0,36,0,2,0], 
            	[0,0,0,0,0,0,1,5,37,5,1], 
            	[3,0,0,0,0,0,0,0,0,39,0], 
            	[0,0,0,0,0,0,0,0,0,0,38]]

fig = plt.figure()
plt.clf()
ax = fig.add_subplot(111)
ax.set_aspect(1)
res = ax.imshow(np.array(df_confusion), cmap=plt.cm.jet, 
                interpolation='nearest')

width, height = np.array(df_confusion).shape

for x in xrange(width):
    for y in xrange(height):
        ax.annotate(str(df_confusion[x][y]), xy=(y, x), 
                    horizontalalignment='center',
                    verticalalignment='center', color='white', 
                    fontweight='bold',
                    path_effects=[path_effects.withSimplePatchShadow(alpha=0.5)])

plt.ylabel('Valor real')
plt.xlabel('Valor predicho')
cb = fig.colorbar(res)
plt.show()