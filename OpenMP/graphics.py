import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

df = pd.DataFrame()

df['N'] = [1, 2, 3, 4, 5, 6, 7, 8, 16]

sum_serial = 0.415
df['SUM'] = [0.415, 0.218, 0.148, 0.118, 0.136, 0.124, 0.111, 0.104, 0.107]
df['SUM'] = df['SUM'].apply(lambda parallel: sum_serial / parallel)

mult_serial = 72.692
df['MULT'] = [72.692, 35.865, 24.450, 18.608, 20.731, 17.477, 16.614, 15.280, 16.432]
df['MULT'] = df['MULT'].apply(lambda parallel: mult_serial / parallel)

sort_serial = 13.333
df['SORT-bucket'] = [13.333, 6.985, 4.688, 3.749, 3.700, 3.195, 2.935, 2.668, 2.596]
df['SORT-bucket'] = df['SORT-bucket'].apply(lambda parallel: sort_serial / parallel)

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
