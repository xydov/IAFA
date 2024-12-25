# -*- coding: utf-8 -*-
import sys 
import pandas as pd 
import time

#initialisation  
argument = sys.argv[1]
df=pd.read_csv(argument)




#drop colonnes

#df.drop('Type', axis=1, inplace = True)
#df.drop('Mach', axis=1, inplace=True)







# renommage 




import matplotlib.pyplot as plt

plt.plot(df['Time_secs'], df['Altitude'])

plt.xlabel('Temps')
plt.ylabel('Altitude')
plt.title('Altitude en fonction du temps')

plt.show(block=False)
plt.pause(0.3)

plt.close()
plt.ioff()
df.to_csv(argument, index=False)
print(df.head())

