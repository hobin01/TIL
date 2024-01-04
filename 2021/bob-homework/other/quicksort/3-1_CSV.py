import csv
import random

# csv 파일 열기
f = open('./RandomNumbers.csv', 'w', newline='')

# csv에 100만개 랜덤한 수 쓰기
wr = csv.writer(f)

total_num_cnt = 1000000
for idx in range(total_num_cnt):
    num = random.randint(1,1000000)
    wr.writerow([num])

f.close()
