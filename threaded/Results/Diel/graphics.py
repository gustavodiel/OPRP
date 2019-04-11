import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

df = pd.DataFrame()

df['N'] = [1, 2, 3, 4, 5, 6, 7, 8, 16]

sum_serial = 0.199
df['SUM'] = [0.199, 0.116, 0.097, 0.088, 0.093, 0.090, 0.083, 0.091, 0.100 ]
df['SUM'] = df['SUM'].apply(lambda parallel: sum_serial / parallel)



sort_serial = 5.201
df['sort'] = [5.201, 2.715, 1.908, 1.518, 1.316, 1.160, 1.087, 1.0, 0.846 ]
df['sort'] = df['sort'].apply(lambda parallel: sort_serial / parallel)





mult_serial = 25.889
df['mult'] = [25.889, 12.987, 8.720, 6.609, 5.298, 4.473, 3.902, 3.409, 3.474]
df['mult'] = df['mult'].apply(lambda parallel: mult_serial / parallel)





sns.lineplot(x='N', y='N', data=df)
sns.lineplot(x='N', y='SUM', data=df)
plt.savefig('SUM.png')
plt.clf()

sns.lineplot(x='N', y='N', data=df)
sns.lineplot(x='N', y='MULT', data=df)
plt.savefig('MULT.png')
plt.clf()

sns.lineplot(x='N', y='N', data=df)
sns.lineplot(x='N', y='SORT-bucket', data=df)
plt.savefig('SORT-bucket.png')
plt.clf()
