import pandas as pd

dfTemp = pd.read_csv("camb_v7.csv")
dfHum = pd.read_csv("humedad_v8.csv")
dfHeat = pd.read_csv("heatIndx_v9.csv")
dfDewp = pd.read_csv("dewpoint_v10.csv")

#guarda el nombre de las columnas que contienen los datos a ser guardados
col = [dfTemp.columns[0], dfHum.columns[0], dfHeat.columns[0], dfDewp.columns[0], dfDewp.columns[1]]

#crea el nombre de los encabezados
headers = ["temp", "hum", "heat", "dewPoint", "tiempo"]

#columnas de datos que constituirán el dataframe
data = [ dfTemp[ col[0]], dfHum[ col[1]], dfHeat[ col[2]], dfDewp[ col[3]], dfDewp[ col[4]] ]

#union de las columnas de datos en un solo dataframe con los encabezados
#predeterminados
dfResult = pd.concat(data, axis = 1, keys = headers)

dfResult.to_csv("generalData.csv")
