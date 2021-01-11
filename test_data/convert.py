with open('region.tbl.csv', 'r') as f: 
    lines = f.readlines()[1:]


with open('region.in', 'w') as f: 
    f.write("use myDB;\n")
    for line in lines: 
        tu = line.split('|')
        sql = "insert into region values (%s, '%s', '%s');"%(tu[0], tu[1], tu[2])
        f.write(sql + '\n')

with open('nation.tbl.csv', 'r') as f: 
    lines = f.readlines()[1:]


with open('nation.in', 'w') as f:
    f.write("use myDB;\n")
    for line in lines: 
        tu = line.split('|')
        sql = "insert into nation values (%s, '%s', %s, '%s');"%(tu[0], tu[1], tu[2], tu[3])
        f.write(sql + '\n')

with open('part.tbl.csv', 'r') as f: 
    lines = f.readlines()[1:]

varchars = [1, 2, 3, 4, 6, 8]
with open('part.in', 'w') as f:
    f.write("use myDB;\n")
    for line in lines: 
        tu = line.split('|')
        for idx in varchars:
            tu[idx] = "'%s'"%(tu[idx])
        sql = "insert into part values (%s);"%(', '.join(tu))
        f.write(sql + '\n')


with open('supplier.tbl', 'r') as f: 
    lines = f.readlines()

varchars = [1, 2,  4, 6]
with open('supplier.in', 'w') as f:
    f.write("use myDB;\n")
    for line in lines: 
        tu = line.split('|')
        for idx in varchars:
            tu[idx] = "'%s'"%(tu[idx])
        sql = "insert into supplier values (%s);"%(', '.join(tu))
        f.write(sql + '\n')



with open('customer.tbl.csv', 'r') as f: 
    lines = f.readlines()[1:]

varchars = [1, 2,  4, 6, 7]
with open('customer.in', 'w') as f:
    f.write("use myDB;\n")
    for line in lines: 
        tu = line.split('|')
        for idx in varchars:
            tu[idx] = "'%s'"%(tu[idx])
        sql = "insert into customer values (%s);"%(', '.join(tu))
        f.write(sql + '\n')


def date(d):
    tmp = d.split('-')
    if len(tmp[1]) == 1:
        tmp[1] = '0' + tmp[1]
    if len(tmp[2]) == 1:
        tmp[2] = '0' + tmp[2]
    return '-'.join(tmp)


with open('orders.tbl.csv', 'r') as f: 
    lines = f.readlines()[1:]

varchars = [2, 4, 5, 6, 8]
with open('orders.in', 'w') as f:
    f.write("use myDB;\n")
    for line in lines: 
        tu = line.split('|')
        tu[4] = date(tu[4])
        for idx in varchars:
            tu[idx] = "'%s'"%(tu[idx])
        sql = "insert into orders values (%s);"%(', '.join(tu))
        f.write(sql + '\n')






with open('lineitem.tbl.csv', 'r') as f: 
    lines = f.readlines()[1:]

varchars = [8, 9, 10, 11, 12, 13, 14, 15]
with open('lineitem.in', 'w') as f:
    f.write("use myDB;\n")
    for line in lines: 
        tu = line.split('|')
        for idx in varchars:
            tu[idx] = "'%s'"%(tu[idx])
        sql = "insert into lineitem values (%s);"%(', '.join(tu))
        f.write(sql + '\n')

with open('partsupp.tbl.csv', 'r') as f: 
    lines = f.readlines()[1:]

varchars = [4]
with open('partsupp.in', 'w') as f:
    f.write("use myDB;\n")
    for line in lines: 
        tu = line.split('|')
        for idx in varchars:
            tu[idx] = "'%s'"%(tu[idx])
        sql = "insert into partsupp values (%s);"%(', '.join(tu))
        f.write(sql + '\n')