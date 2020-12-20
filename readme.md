# Librería **AnálisisCultivo**

El objetivo de esta librería es poder hacer un rápido análisis 
de los datos recolectados sobre las variables climáticas a las que
se encuentra expuesto un cultivo, las varibles analizadas son:

* **Humedad relativa (%)**
* **Temperatura (°C)**

Las clases desarrolladas se pueden expandir para analizar más variables 
entre estas: 

* **Indice de calor (°C)**
* **Punto de rocío (°C)**

Los datos para estas variables se encuentran en la carpeta _'DataHandling'_
así como un pequeño script: _'mergeData.py'_, que se encarga de juntar todos 
los datos en un solo _'csv'_ para más fácil manejo.


La clase principal de este módulo es **_'BigTable'_** que es una adaptación de una Hash 
Table y que se contruye integrando la clase **_'List'_** definida en la subcarpeta con 
su nombre.
