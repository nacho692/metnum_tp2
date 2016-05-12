import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patheffects as path_effects




def plotConf(df_confusion,titulo,savefile):
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

  plt.yticks( np.arange(height) )
  plt.xticks( np.arange(width) )
  plt.ylabel('Valor real')
  plt.xlabel('Valor predicho')
  cb = fig.colorbar(res)
  plt.title(titulo,fontsize=16)

  plt.savefig(savefile)
  return

