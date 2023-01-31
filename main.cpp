#include "Topograph.h"

int main()
{
    string fileName = "map.bmp";
    string fileName2 = "map2.bmp";
    Topograph topograph("map_input.txt");

    Bmp bmp(topograph.getHeight(), topograph.getWidth());

    topograph.drawMap(bmp);

    bmp.write("map.bmp");

    system(("eog " + fileName + " &").c_str()); 


    topograph.drawBestPath(bmp);
    bmp.write("map2.bmp");

    system(("eog " + fileName2 + " &").c_str()); 

}