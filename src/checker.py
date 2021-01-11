import sqlite3
import random 
import os
import string
from tqdm import tqdm

def gen_sql():
    a = random.randint(1, 500000)
    b = ''.join(random.sample(string.ascii_letters + string.digits, 10))
    return "insert into testTable values (%d, '%s');"%(a, b)

def gen_where(flag=True):
    a = random.randint(1, 100000 if flag else 1000000)
    b = ''.join(random.sample(string.ascii_letters + string.digits, 10))
    return "where a < %d;"%(a)

def check(row, test_row):
    test_row = test_row.split('|')[1:-1]
    test_row = [i[1:-1] for i in test_row]

    assert(str(row[0]) == test_row[0])
    assert(row[1] == test_row[1])
    # print(test_row)


if __name__ == "__main__":

    f = open('test.in', 'w')
    f.write('use myDB;\n')
    f.write('create table testTable (a INT(4), b VARCHAR(10));\n')



    conn = sqlite3.connect('test.db')
    c = conn.cursor()
    c.execute(
        '''CREATE TABLE testTable
        (a INT,
        b CHAR(10));''')

    for i in tqdm(range(500)):
        sql = gen_sql()
        c.execute(sql)
        f.write(sql + '\n')
    conn.commit()

    for i in tqdm(range(2000)):
        sql = 'delete from testTable ' + gen_where()
        c.execute(sql)
        f.write(sql + '\n')
    conn.commit()

    for i in tqdm(range(10000)):
        sql = "update testTable set a = 100, b = '0000000000'" + gen_where()
        c.execute(sql)
        f.write(sql + '\n')
    conn.commit()

    select = "select * from testTable " + gen_where(False)
    cursor = c.execute(select)

    true_rows = []
    for row in cursor:
        true_rows.append(row)

    c.execute("drop table testTable;")
    conn.commit()
    conn.close()

    f.write(select + '\n')
    f.write('drop table testTable;')

    f.close()

    os.system('./main < test.in > test.out')

    f = open('test.out', 'r')
    lines = f.readlines() 
    for i in range(len(lines)):
        check(true_rows[i], lines[i])

