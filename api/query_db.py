import sqlite3
con = sqlite3.connect('jobs.db')
cur = con.cursor()
print("4ce6b77e-689e-4068-b704-bf1989ba3dbb")
results = cur.execute('SELECT * FROM jobs WHERE pid = "4ce6b77e-689e-4068-b704-bf1989ba3dbb"')
for a in results:
    print(a)
 

