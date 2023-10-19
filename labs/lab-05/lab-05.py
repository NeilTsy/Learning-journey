#!/usr/bin/env python
import pandas as pd

def main():
	df_drivers: pd.DataFrame = pd.read_csv("drivers.csv")
	df_results: pd.DataFrame = pd.read_csv("results.csv")
	df_drivers.drop(['driverRef', 'number', 'code','forename','surname','dob','url'], inplace=True, axis=1)
	df_results.drop(['resultId', 'raceId' , 'constructorId', 'number', 'grid','positionText','positionOrder','points','laps','time','milliseconds','fastestLap','rank','fastestLapSpeed','fastestLapTime','statusId'], inplace=True,axis=1)
	merged_df: pd.DataFrame = df_results.merge(df_drivers,on='driverId',how='left')
	merged_df = merged_df[merged_df['position'] == '1']
	country_counts = merged_df['nationality'].value_counts()
	print("The top 10 countryies with most race_winners in F1 history are: ")
	print(country_counts.head(10))

if __name__ == "__main__":
	main()
