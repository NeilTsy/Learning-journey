#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Wed Feb 8 14:44:33 2023
Based on: https://www.kaggle.com/datasets/arbazmohammad/world-airports-and-airlines-datasets
Sample input: --AIRLINES="airlines.yaml" --AIRPORTS="airports.yaml" --ROUTES="routes.yaml" --QUESTION="q1" --GRAPH_TYPE="bar"
@author: rivera
@author: shiyutang
"""
import argparse
import pandas as pd

def sample_function(input: str) -> str:
    """Sample function (removable) that illustrations good use of documentation.
            Parameters
            ----------
                input : str, required
                    The input message.

            Returns
            -------
                str
                    The text returned.
    """
    return input.upper()

def parse_arguments() -> tuple:
    """
    Parses the command-line arguments.

    Returns:
        tuple: A tuple containing the parsed arguments.
            The elements in the tuple correspond to:
            - sort_by (str): Csv file was sorted by popularity, energy, or danceability.
            - display (int): Number of songs to display.
            - files (list): The csv file(s) to be read.
    """
    parser: argparse.ArgumentParser = argparse.ArgumentParser(description='music_manager Program')

    parser.add_argument('--sortBy', type=str, help='Csv file was sorted by popularity, energy or danceability')
    parser.add_argument('--display', type=int, help='Number of songs to display')
    parser.add_argument('--files', type=str, help='The csv file(s) to be read')

    args: argparse.Namespace = parser.parse_args()

    sort_by: str = args.sortBy
    display: int = args.display
    files: list = args.files.split(',')

    return sort_by, display, files
    
def read_csv(file: str) -> pd.DataFrame:
    """
    Reads a CSV file and performs initial data processing.

    Parameters:
        file (str): The name of the CSV file to be read.

    Returns:
        pd.DataFrame: The processed DataFrame containing the songs data.
    """
    top_songs: pd.DataFrame = pd.read_csv(file)
    top_songs.drop(['duration_ms','explicit','key','loudness','mode','speechiness','acousticness','instrumentalness','liveness','valence','tempo','genre'], axis=1, inplace=True)

    return top_songs

def merge_and_sorted(sorted_songs: pd.DataFrame, sorted_songs_complete: pd.DataFrame, sort_by: str) -> pd.DataFrame:
    """
    Merges and sorts two DataFrames based on the specified attribute.

    Parameters:
        sorted_songs (pd.DataFrame): The DataFrame containing sorted songs data.
        sorted_songs_complete (pd.DataFrame): The DataFrame containing complete songs data.
        sort_by (str): The attribute to sort the songs by (popularity, energy, or danceability).

    Returns:
        pd.DataFrame: The merged and sorted DataFrame, where songs are sorted in descending order of the specified attribute.
                      If two songs have the same value for the sorting attribute, they are sorted in lexicographical order
                      based on the 'song' column in descending order.
    """
    merged_songs: pd.DataFrame = pd.concat([sorted_songs, sorted_songs_complete])
    merged_sorted_songs: pd.DataFrame = merged_songs.sort_values(by=[sort_by, 'song'], ascending=[False, False])

    return merged_sorted_songs

def process_files(files: list, sort_by: str) -> pd.DataFrame:
    """
    Processes CSV file(s) and merges the data.

    Parameters:
        files (List[str]): The list of CSV file names to be processed.
        sort_by (str): The attribute to sort the songs by (popularity, energy, or danceability).

    Returns:
        pd.DataFrame: The merged DataFrame containing the songs data.
    """
    sorted_songs_complete: pd.DataFrame = pd.DataFrame()

    for file in files:
        top_songs: pd.DataFrame = read_csv(file)
        if sort_by == 'popularity':
            top_songs.drop(['energy', 'danceability'], axis=1, inplace=True)
        elif sort_by == 'energy':
            top_songs.drop(['popularity', 'danceability'], axis=1, inplace=True)
        elif sort_by == 'danceability':
            top_songs.drop(['popularity', 'energy'], axis=1, inplace=True)
        sorted_songs_complete: pd.DataFrame = merge_and_sorted(top_songs, sorted_songs_complete, sort_by)

    return sorted_songs_complete

def generate_output_file(sorted_songs_complete: pd.DataFrame, sort_by: str, display: int) -> None:
    """
    Generates the output CSV file with selected columns.

    Parameters:
        sorted_songs_complete (pd.DataFrame): The merged and sorted DataFrame.
        sort_by (str): The attribute used for sorting the songs.
        display (int): The number of songs to display.

    Returns:
        None
    """
    sorted_display_songs: pd.DataFrame = sorted_songs_complete.head(display)
    sorted_display_songs[['artist', 'song', 'year', sort_by]].to_csv('output.csv', index=False)

def main():
    """
    Main function that executes the program.

    It parses the command-line arguments, reads and handles CSV files,
    merges and sorts the data, selects the top songs to display,
    and writes the result to an output file.
    """
    arguments: list = parse_arguments()
    sorted_display_songs: pd.DataFrame = process_files(arguments[2],arguments[0])
    generate_output_file(sorted_display_songs,arguments[0],arguments[1])

if __name__ == '__main__':
    main()
