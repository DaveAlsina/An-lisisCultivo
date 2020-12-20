# Librería **AnálisisCultivo**
--------------------------------

El objetivo de esta librería es poder hacer un rápido análisis 
de los datos recolectados sobre las variables climáticas a las que
se encuentra expuesto un cultivo **_(Desviación estándar, medias, 
porcentaje de veces en rango óptmimo para la variable escogida)_**,
las varibles analizadas son:

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

Al final de este :point_right: [Video](https://youtu.be/X6B4PMEVO5E) se encuentra una demostración
del código en acción y su modo de uso.

# Requisitos
--------------------------

* GCC/G++ (compilador)

# Modo de uso
---------------------------

Para compilar el código ejecute: 

		$ g++ -Wall -Wextra -Werror -std=c++14 main.cpp

El anterior comando producirá un archivo **_'a.out'_**, ejecútelo así: 
		
		$ ./a.out

Para el **_'main.cpp'_** que se tiene construido por defecto en esta librería la salida de este ejecutable 
debería verse así: 

		-----------------------------------------------------------------------------------
		Intervalos de condiciones óptimas:
			 En temperatura(día): 			 mínimo -> 20°C	 máximo -> 23°C
			 En temperatura(noche): 		 mínimo -> 15°C	 máximo -> 18°C
			 En humedad (24h)(humedad relativa %): 	 mínimo -> 60%	 máximo -> 80%
		-----------------------------------------------------------------------------------


		-----------------------------------------------------------------------------------
		Veces que ha estado en condiciones de humedad óptimas (% humedad relativa):  79.935%
		-----------------------------------------------------------------------------------


		----------------------------------------------------------------------------------
		Veces en rango óptimo de temperatura (% sobre el total de datos para cada periodo de tiempo):
			Día:  11.1973%,   Noche: 16.6372%
		-----------------------------------------------------------------------------------

		-----------------------------------------------------------------------------------
		Intervalos de condiciones óptimas:
			 En temperatura(día): 			 mínimo -> 15°C	 máximo -> 20°C
			 En temperatura(noche): 		 mínimo -> 15°C	 máximo -> 20°C
			 En humedad (24h)(humedad relativa %): 	 mínimo -> 50%	 máximo -> 80%
		-----------------------------------------------------------------------------------


		-----------------------------------------------------------------------------------
		Veces que ha estado en condiciones de humedad óptimas (% humedad relativa):  97.1465%
		-----------------------------------------------------------------------------------


		----------------------------------------------------------------------------------
		Veces en rango óptimo de temperatura (% sobre el total de datos para cada periodo de tiempo):
			Día:  68.034%,   Noche: 16.8138%
		-----------------------------------------------------------------------------------

		Promedio de temperatura en el minuto 1000 = 19.05 °C

		Promedio de la temperatura en el minuto 4 del día = 14.775 °C
		Promedio de la humedad en el minuto 4 del día = 70 %

		Promedio de la temperatura en la hora 7 del día = 14.7338 °C
		Promedio de la humedad en la hora 7 del día = 69.8861 %

		Desviación estandar de la temperatura en °C
		Hora: 0	Media: 14.1546	Desviación estandar: 0.876083	||	Hora: 1	Media: 13.8643	Desviación estandar: 0.552825
		Hora: 2	Media: 13.8732	Desviación estandar: 0.627169	||	Hora: 3	Media: 13.8911	Desviación estandar: 0.578394
		Hora: 4	Media: 13.7377	Desviación estandar: 0.731652	||	Hora: 5	Media: 13.7139	Desviación estandar: 0.660736
		Hora: 6	Media: 13.7962	Desviación estandar: 0.484861	||	Hora: 7	Media: 14.7338	Desviación estandar: 0.814142
		Hora: 8	Media: 16.1386	Desviación estandar: 1.52213	||	Hora: 9	Media: 17.3029	Desviación estandar: 1.44552
		Hora: 10	Media: 18.2445	Desviación estandar: 0.971463	||	Hora: 11	Media: 18.6412	Desviación estandar: 1.11986
		Hora: 12	Media: 18.5635	Desviación estandar: 1.03962	||	Hora: 13	Media: 19.038	Desviación estandar: 1.34368
		Hora: 14	Media: 19.2978	Desviación estandar: 1.43678	||	Hora: 15	Media: 19.2046	Desviación estandar: 1.56471
		Hora: 16	Media: 18.7233	Desviación estandar: 1.66472	||	Hora: 17	Media: 17.9379	Desviación estandar: 2.3189
		Hora: 18	Media: 16.7915	Desviación estandar: 2.8523	||	Hora: 19	Media: 16.481	Desviación estandar: 3.00165
		Hora: 20	Media: 16.0266	Desviación estandar: 3.15658	||	Hora: 21	Media: 15.3187	Desviación estandar: 2.8241
		Hora: 22	Media: 14.4376	Desviación estandar: 1.20549	||	Hora: 23	Media: 14.2136	Desviación estandar: 0.999611

		Desviación estandar de la humedad en humedad relativa (%)
		Hora: 0	Media: 70.6345	Desviación estandar: 3.38757	||	Hora: 1	Media: 71.8383	Desviación estandar: 3.78342
		Hora: 2	Media: 71.2971	Desviación estandar: 5.10062	||	Hora: 3	Media: 71.5975	Desviación estandar: 5.70784
		Hora: 4	Media: 71.8136	Desviación estandar: 4.87026	||	Hora: 5	Media: 71.9076	Desviación estandar: 5.17182
		Hora: 6	Media: 72.3096	Desviación estandar: 5.20021	||	Hora: 7	Media: 69.8861	Desviación estandar: 3.99363
		Hora: 8	Media: 66.103	Desviación estandar: 5.00795	||	Hora: 9	Media: 64.2605	Desviación estandar: 6.04946
		Hora: 10	Media: 61.7542	Desviación estandar: 4.18722	||	Hora: 11	Media: 60.3947	Desviación estandar: 3.91717
		Hora: 12	Media: 59.9573	Desviación estandar: 3.78612	||	Hora: 13	Media: 57.8554	Desviación estandar: 3.27875
		Hora: 14	Media: 59.2991	Desviación estandar: 3.47758	||	Hora: 15	Media: 60.2294	Desviación estandar: 2.81423
		Hora: 16	Media: 60.75	Desviación estandar: 2.69849	||	Hora: 17	Media: 61.8333	Desviación estandar: 2.81411
		Hora: 18	Media: 64.2511	Desviación estandar: 1.77954	||	Hora: 19	Media: 64.7026	Desviación estandar: 2.32164
		Hora: 20	Media: 66.0549	Desviación estandar: 3.76318	||	Hora: 21	Media: 67.9404	Desviación estandar: 3.82109
		Hora: 22	Media: 69.4359	Desviación estandar: 3.14163	||	Hora: 23	Media: 69.8559	Desviación estandar: 3.35164

