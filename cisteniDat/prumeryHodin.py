vstupTeploty=[]
file = open("vstup.csv", "r")
file.readline()
for line in file:
    print(line)
    novaTeplota=line.split(",")[1]
    novaTeplotaInt=int(novaTeplota)
    novyCas=line.split(",")[0]

    novaDvojice=[]
    novaDvojice.append(novyCas)
    novaDvojice.append(novaTeplotaInt)

    vstupTeploty.append(novaDvojice)

#print(vstupTeploty)

#
# 2017-04-08 08:48:48,15,23

#vstupTeploty=[['2017-04-08 13:35:45',14],['2017-04-08 13:56:34',25],['2017-04-08 13:58:23',17],
#              ['2017-04-08 13:59:12',14],['2017-04-08 14:00:56',15],
#              ['2017-04-08 14:02:09',14],['2017-04-08 14:07:45',15],['2017-04-08 14:35:45',14],
#              ['2017-04-08 14:56:34',25],['2017-04-08 14:58:03',17],
#              ['2017-04-08 14:58:12',14],['2017-04-08 15:01:56',12],['2017-04-08 15:02:09',14],['2017-04-08 15:05:45',11]]
f = open('vystup.csv', 'wb')
f.write("hodina,prumer")
f.write("\r\n")
for hodina in range(0,24):
  filtrovane=[]
  for aktualni in vstupTeploty:
    cas=aktualni[0]
    aktualniHodina=cas[11:13]
    minuty=cas[14:16]
    if (hodina==int(aktualniHodina)+1 and int(minuty) > 55) or (hodina==int(aktualniHodina) and int(minuty) < 5):
      filtrovane.append(aktualni)

  print(filtrovane)
  pocet=len(filtrovane)
  soucet=0
  prumer=0
  for aktualni in filtrovane:
    teplota=aktualni[1]
    soucet=soucet+teplota
    prumer=soucet/float(pocet)
  print ("hodina: {} prumer: {}".format(hodina, prumer))
  f.write("{},{}".format(hodina, prumer))
  f.write("\r\n")

f.close()
