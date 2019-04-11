import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

df = pd.DataFrame()

df['N'] = [1, 2, 3, 4, 5, 6, 7, 8, 16]

sum_serial = 0.199
df['sum'] = [0.199, 0.116, 0.097, 0.088, 0.093, 0.090, 0.083, 0.091, 0.100 ]
df['sum'] = df['sum'].apply(lambda parallel: sum_serial / parallel)


df['sum_2'] = [0.191, 0.200, 0.193, 0.199, 0.093, 0.090, 0.083, 0.091, 0.100 ]
df['sum_2'] = df['sum'].apply(lambda parallel: sum_serial / parallel)




sort_serial = 5.201
df['sort'] = [5.201, 2.715, 1.908, 1.518, 1.316, 1.160, 1.087, 1.0, 0.846 ]
df['sort'] = df['sort'].apply(lambda parallel: sort_serial / parallel)


df['sort_2'] = [5.201, 2.715, 1.908, 1.518, 1.316, 1.160, 1.087, 1.0, 0.846 ]
df['sort_2'] = df['sort'].apply(lambda parallel: sort_serial / parallel)





mult_serial = 25.889
df['mult'] = [25.889, 12.987, 8.720, 6.609, 5.298, 4.473, 3.902, 3.409, 3.474]
df['mult'] = df['mult'].apply(lambda parallel: mult_serial / parallel)


df['mult_2'] = [25.889, 12.987, 8.720, 6.609, 5.298, 4.473, 3.902, 3.409, 3.474]
df['mult_2'] = df['mult'].apply(lambda parallel: mult_serial / parallel)




sns.lineplot(x='N', y='N', data=df)
sns.lineplot(x='N', y='sum', data=df)
sns.lineplot(x='N', y='sum_2', data=df)
plt.savefig('sum.png')
plt.clf()

sns.lineplot(x='N', y='N', data=df)
sns.lineplot(x='N', y='mult', data=df)
sns.lineplot(x='N', y='mult_2', data=df)
plt.savefig('mult.png')
plt.clf()

sns.lineplot(x='N', y='N', data=df)
sns.lineplot(x='N', y='sort', data=df)
sns.lineplot(x='N', y='sort_2', data=df)
plt.savefig('sort.png')
plt.clf()
