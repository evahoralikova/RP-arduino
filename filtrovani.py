teploty=[10,14,10,15,11,11,22,12,12,17,13]
filtrovane=[]
delkaHistorie=8
historie=[]
for n in range(0,delkaHistorie):
  historie.append(10)
print (teploty)
for aktualni in teploty:
  print (historie)
  prumer=sum(historie)/delkaHistorie
  print(prumer)
  if (aktualni-prumer<2):
    filtrovane.append(aktualni)
  for n in range(0,delkaHistorie-1):
    historie[n]=historie[n+1]
  historie[delkaHistorie-1]=aktualni
print(filtrovane)
