#!/usr/bin/env python3
"""
Obtain and print the names of the packages without the cpu architecture (similar to A\installed4.py) that were installed within
the range of dates provided by the user (i.e., variables date_from and date_to). 

* Dates provided by the user should follow the format yyyy-mm-dd
* The output for each package belonging to the specified range should be:
yyyy-mm-dd: NAME_OF_PACKAGE
* An example of output from the program is described in range-2020-07-15-to-2020-07-16.txt

"""

import re
import sys
from datetime import datetime

def main():
    if len(sys.argv) < 3:
        sys.exit(0)
    date_from = sys.argv[1]
    date_to   = sys.argv[2]
    # TODO: Your code.
    startD = datetime.strptime(date_from, "%Y-%m-%d")
    endD = datetime.strptime(date_to, "%Y-%m-%d")
    pattern = r"(\d{4}-\d{2}-\d{2}) \d{2}:\d{2}:\d{2} install (.+?):"
    with open("dpkg.log", 'r') as file:
        for line in file:
            date = datetime.strptime(line[:10], "%Y-%m-%d")
            if startD<=date<=endD:
                matches = re.search(pattern, line)
                if matches:
                    date = matches.group(1)
                    package_name = matches.group(2)
                    print(f"{date}: {package_name}")


if __name__ == "__main__":
    main()
