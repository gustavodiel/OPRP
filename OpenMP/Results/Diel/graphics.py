import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

df = pd.DataFrame()

sns.set(style="darkgrid")

df['N'] = [1, 2, 3, 4, 5, 6, 7, 8, 16]

sum_serial = 0.199
df['sum'] = [0.199, 0.116, 0.097, 0.088, 0.093, 0.090, 0.083, 0.091, 0.100 ]
df['sum'] = df['sum'].apply(lambda parallel: sum_serial / parallel)


df['sum_gcc'] = [0.310, 0.183, 0.135, 0.109, 0.098, 0.094, 0.092, 0.092, 0.095 ]
df['sum_gcc'] = df['sum_gcc'].apply(lambda parallel: sum_serial / parallel)


df['sum_clang'] = [0.291, 0.175, 0.127, 0.105, 0.096, 0.101, 0.112, 0.091, 0.103 ]
df['sum_clang'] = df['sum_clang'].apply(lambda parallel: sum_serial / parallel)




sort_serial = 5.201
df['sort'] = [5.201, 2.715, 1.908, 1.518, 1.316, 1.160, 1.087, 1.0, 0.846]
df['sort'] = df['sort'].apply(lambda parallel: sort_serial / parallel)


df['sort_gcc'] = [5.545647, 4.188176, 3.804229, 1.716451, 4.197105, 1.832413, 1.781299, 1.933243, 2.253401]
df['sort_gcc'] = df['sort_gcc'].apply(lambda parallel: sort_serial / parallel)


df['sort_clang'] = [5.467289, 4.118266, 3.670853, 1.711872, 4.155355, 1.965402, 1.919639, 2.173620, 1.652165 ]
df['sort_clang'] = df['sort_clang'].apply(lambda parallel: sort_serial / parallel)





mult_serial = 25.889
df['mult'] = [25.889, 12.987, 8.720, 6.609, 5.298, 4.473, 3.902, 3.409, 3.474]
df['mult'] = df['mult'].apply(lambda parallel: mult_serial / parallel)


df['mult_gcc'] = [25.367889, 12.623965, 8.545570, 6.449573, 5.198901, 4.345502, 3.744567, 3.285817, 3.450596 ]
df['mult_gcc'] = df['mult_gcc'].apply(lambda parallel: mult_serial / parallel)

df['mult_clang'] = [25.808670, 12.869470, 8.678355, 6.597505, 5.246976, 4.430786, 3.789448, 3.358300, 3.441879]
df['mult_clang'] = df['mult_clang'].apply(lambda parallel: mult_serial / parallel)



plt.title('SUM\nCpu: i9 9900K, 8 cores / 16 threads @ 4.7GHz')
sns.lineplot(x='N', y='sum_gcc', color='red', data=df)
sns.lineplot(x='N', y='sum_clang', color='orange', data=df)
sns.lineplot(x='N', y='sum', color='green', data=df)
sns.lineplot(x='N', y='N', color='blue', data=df)

plt.xlabel('Número de Threads')
plt.ylabel('Aceleração')
plt.legend(labels=['OpenMP GCC','OpenMP CLang', 'PThread','Serial'])

plt.savefig('sum.png')
plt.clf()


plt.title('MULT\nCpu: i9 9900K, 8 cores / 16 threads @ 4.7GHz')
sns.lineplot(x='N', y='mult_gcc', color='red', data=df)
sns.lineplot(x='N', y='mult_clang', color='orange', data=df)
sns.lineplot(x='N', y='mult', color='green', data=df)
sns.lineplot(x='N', y='N', color='blue', data=df)

plt.xlabel('Número de Threads')
plt.ylabel('Aceleração')
plt.legend(labels=['OpenMP GCC','OpenMP CLang', 'PThread','Serial'])

plt.savefig('mult.png')
plt.clf()


plt.title('SORT - Quick\nCpu: i9 9900K, 8 cores / 16 threads @ 4.7GHz')
sns.lineplot(x='N', y='sort_gcc', color='red', data=df)
sns.lineplot(x='N', y='sort_clang', color='orange', data=df)
sns.lineplot(x='N', y='sort', color='green', data=df)
sns.lineplot(x='N', y='N', color='blue', data=df)

plt.xlabel('Número de Threads')
plt.ylabel('Aceleração')
plt.legend(labels=['OpenMP GCC','OpenMP CLang', 'PThread','Serial'])

plt.savefig('sort.png')
plt.clf()
