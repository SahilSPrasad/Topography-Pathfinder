# Topography Pathfinder

![map](https://github.com/user-attachments/assets/3e6419c1-4a39-4d70-a285-d6f298b7b81e)


![map2](https://github.com/user-attachments/assets/acd008c1-6aeb-4fd8-ae08-55ce32a38614)


## Overview
This project is a simple image processing application that reads a topographic map from a text file, generates a grayscale image representing the topography, and visualizes the elevation data. Additionally, it can calculate and draw the optimal path through the map, based on elevation differences, using a greedy algorithm.

The core functionality revolves around:
- **Reading topographic data**: The map data is stored in a `.txt` file with elevation data for each cell.
- **Processing image**: The data is then used to generate two BMP images:
  1. A grayscale map representing the topography.
  2. A map showing the optimal path based on elevation changes.

## Requirements

- **C++14 or higher**: The project uses features from the C++14 standard.
- **g++**: The project is built using the `g++` compiler (GNU C++ compiler).

## Files
### `Bmp.cpp` & `Bmp.h`
These files define the `Bmp` class, which is used to handle the BMP image format. The class includes:
- Methods to read and write the header and pixel data of a BMP image.
- Pixel manipulation (setting RGB values for each pixel).

### `Topograph.cpp` & `Topograph.h`
These files define the `Topograph` class, which is responsible for:
- Reading topographic data from a file (`map_input.txt`).
- Generating grayscale elevation maps.
- Implementing the logic to calculate the minimum and maximum elevations in the map.
- Drawing a "greedy" path and calculating the best path based on elevation changes.

### `main.cpp`
This file contains the main logic to:
- Instantiate the `Topograph` and `Bmp` objects.
- Draw the elevation map and save it as a BMP file.
- Compute and visualize the best path based on elevation changes.

### `Makefile`
The `Makefile` automates the compilation of the project. It defines:
- The compiler (`g++`).
- The flags for compilation.
- The targets for building the executable (`ImageEditor`).
- Rules for cleaning up object files and running the program.

## Build Instructions

To build the project, follow these steps:

### 1. Compile the Code:
Ensure that `g++` is installed and run the following command in the terminal:

```bash
make
```

This will:
- Compile the source code files (`main.cpp`, `Bmp.cpp`, `Topograph.cpp`).
- Link the object files to create the executable (`ImageEditor`).

### 2. Clean Up:
To remove the compiled object files and executable, run:

```bash
make clean
```

### 3. Run the Program:
Once the program is compiled, you can run it with:

```bash
make run
```

This will execute the `ImageEditor` program, generating two BMP files:
- `map.bmp`: A grayscale topography map.
- `map2.bmp`: A topography map showing the best path based on elevation changes.

The images will be displayed using the `eog` image viewer (you can replace it with a viewer of your choice if you're on a different platform).

## How It Works

1. **Loading the Map Data**:  
   The `Topograph` class reads the input map file (`map_input.txt`), which contains the elevation data for each grid cell. It stores this data in a 2D vector for further processing.

2. **Generating the Grayscale Map**:  
   The `Topograph::drawMap()` method computes the minimum and maximum elevations and uses this information to convert the elevation values to grayscale values. This grayscale map is written to a BMP file using the `Bmp::write()` method.

3. **Finding the Best Path**:  
   The `Topograph::drawBestPath()` method uses a greedy algorithm to find the path with the least elevation change. It starts from different rows and calculates the total elevation change while moving from left to right across the map. The row with the least elevation change is considered the best path.

4. **Saving and Displaying the Results**:  
   The program generates two BMP files: `map.bmp` and `map2.bmp`. The first one shows the grayscale representation of the topography, and the second one shows the best path.

## Example Workflow

1. Place your map data in a file named `map_input.txt` with the following format:
   ```
   MapName <map_name>
   ncols <number_of_columns>
   nrows <number_of_rows>
   xllcorner <x_coordinate_of_lower_left_corner>
   yllcorner <y_coordinate_of_lower_left_corner>
   cellsize <cell_size>
   NODATA_value <no_data_value>
   <elevation_data_grid>
   ```

2. Run `make` to compile the project.

3. Run the program using `make run`.

4. Two BMP images (`map.bmp` and `map2.bmp`) will be generated, visualizing the topography and the best path, respectively.

## File Structure
```
/ImageEditor
    ├── Bmp.cpp
    ├── Bmp.h
    ├── Makefile
    ├── main.cpp
    ├── Topograph.cpp
    ├── Topograph.h
    └── map_input.txt (input map file with elevation data)
```


## Troubleshooting

- **Missing BMP Image Viewer**: If you don't have `eog` installed, replace `eog` in the `main.cpp` with a different image viewer command that is compatible with your operating system.
  
- **Incorrect Map Format**: Ensure that your map file (`map_input.txt`) follows the correct format and that there are no missing or malformed lines in the file.
