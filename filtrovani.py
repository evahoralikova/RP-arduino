teploty=[]
file = open("jedenDen.csv", "r")
file.readline()
for line in file:
    novaTeplota=line.split(",")[1]
    print(novaTeplota)
    novaTeplotaInt=int(novaTeplota)
    teploty.append(novaTeplotaInt)
filtrovane=[]
delkaHistorie=240
historie=[]
for n in range(0,delkaHistorie):
  historie.append(10)
print (teploty)
for aktualni in teploty:
  print (historie)
  prumer=sum(historie)/float(delkaHistorie)
  print(prumer)
  if (abs(aktualni-prumer)<5):
    filtrovane.append(aktualni)
  for n in range(0,delkaHistorie-1):
    historie[n]=historie[n+1]
  historie[delkaHistorie-1]=aktualni
print(filtrovane)
f = open('vystup.csv', 'wb')
f.write("teplota")
f.write("\r\n")
for teplota in filtrovane:
  f.write(str(teplota))
  f.write("\r\n")
f.close()
