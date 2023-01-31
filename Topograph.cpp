#include "Topograph.h"

Topograph::Topograph(string fileName)
{
    ifstream ifs;
    string getData;
    int getNumber;
    int ncols = 0, nrows = 0;

    ifs.open(fileName);

    if (!ifs.is_open()) {
        error("Could not open");
    }

    //Only need ncols and nrows so ignore rest
    ifs >> getData >> ncols >> getData >> nrows;
    //I mixed up width and height for some reason
    width = ncols;
    height = nrows;
    
    ifs >> getData >> getData >> getData >> getData >> getData >> getData;
    cout << "Height: " << height << endl;
    cout << "Width: " << width  << endl;

    //Read into 2D vector v;

    v.resize(height, vector<int>(width));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ifs >> getNumber;
            v.at(i).at(j) = getNumber;
        }
    }

    ifs.close();

}


void Topograph::findMin() {
    min = v.at(0).at(0);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (v.at(i).at(j) < min ) {
                min = v.at(i).at(j);
            }
        }
    }

}


void Topograph::findMax() {
    max = v.at(0).at(0);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (v.at(i).at(j) > max) {
                max = v.at(i).at(j);
            }
        }
    }

}

int Topograph::mapRange(int n, int fromLow, int fromHigh, int toLow, int toHigh) {
    //integer division
    //struggled with this until i figured out the purpose behind the math
    //wants to scale down from min/max to 0/255 within rgb range
    return ((n-fromLow)/static_cast<double>(fromHigh-fromLow)) * (toHigh - toLow) + toLow;
}

void Topograph::drawMap(Bmp& bmp) {
    double greyScaleValue = 0;
    double currentElevation = 0;

    findMax();
    findMin();

    cout << "Max: " << max << endl;
    cout << "Min: " << min << endl;

    
    //i = height(row), j = width(column)
    for (int i = 0; i < getHeight();i++) {

        for (int j = 0; j < getWidth();j++) { 
            currentElevation = v.at(i).at(j);
            greyScaleValue = (mapRange(currentElevation,min,max,0,255));

            bmp(i,j).r = greyScaleValue;
            bmp(i,j).g = greyScaleValue;
            bmp(i,j).b = greyScaleValue;

        }
    }    
}


int Topograph::drawGreedyPath(Bmp& bmp, int startingRow, rgb color) {
    int previousElevation = 0;
    int newElevation = 0;
    int totalElevation = 0;
    
    int currentRow = startingRow;


    bmp(startingRow,0) = color;

    //Starts on given row with column 0 as j
    //Has to run until j is 1320 because moveForward checks 1321
    for (int j = 0; j  < getWidth()-1;) {

            previousElevation = v.at(currentRow).at(j);
            //cout << "prev: " << previousElevation << endl;
            //moveForward returns i and j back

            moveForward(startingRow,j);

            currentRow = startingRow;
            //cout << "currentRow: " << currentRow << endl;
            //cout << "starting row: " << startingRow << endl;

            newElevation = v.at(currentRow).at(j);
            //cout << "new: "<< newElevation << endl;

            bmp(startingRow,j) = color;


            totalElevation += fabs(previousElevation - newElevation);
        
   
    }

    return totalElevation;
}


void Topograph::moveForward(int& i, int& j) {

    int currentElevation = v.at(i).at(j);
    //cout << "currentElevation: " << currentElevation << endl;


    //cout << "fwdUp: " << fwdUp << endl;
   // cout << "fwd: " << fwd << endl;
    //cout << "fwdDown: " << fwdDown << endl;


    //int changeFwd = fabs(currentElevation - fwd);
    //int changeUp = fabs(currentElevation - fwdUp);
    //int changeDown = fabs(currentElevation - fwdDown);

    //cout << "changeFwd: " << changeFwd << endl;
    //cout << "changeUp: " << changeUp << endl;
    //cout << "changeDown: " << changeDown << endl;


    //Check Upper ledge i = 0
    if (i == 0) {

        int fwd = v.at(i).at(j+1); 
        int fwdDown = v.at(i+1).at(j+1);

        //cout << "fwd: " << fwd << endl;
        //cout << "fwdDown: " << fwdDown << endl;

        int changeFwd = fabs(currentElevation - fwd);
        int changeDown = fabs(currentElevation - fwdDown);


        //cout << "changeFwd: " << changeFwd << endl;
        //cout << "changeDown: " << changeDown << endl;


        if ( (changeFwd == changeDown) || (changeFwd < changeDown) ) {
            j = j + 1;
        } 
        else {
            i = i + 1;
            j = j + 1;
        }
    }
    //Check lower edge i = 481
    else if (i == height-1) {
        int fwd = v.at(i).at(j+1); 
        int fwdUp = v.at(i-1).at(j+1);

        //cout << "fwd: " << fwd << endl;
        //cout << "fwdUp: " << fwdUp << endl;

        int changeFwd = fabs(currentElevation - fwd);
        int changeUp = fabs(currentElevation - fwdUp);


        //if i = 481, can only go up and fwd
       if ( (changeFwd == changeUp) || (changeFwd < changeUp) ) {
            j = j + 1;
        } 
        else {
            i = i - 1;
            j = j + 1;
        }
    }
    else {
        int fwd = v.at(i).at(j+1); 
        int fwdUp = v.at(i-1).at(j+1);
        int fwdDown = v.at(i+1).at(j+1);

        // cout << "elsefwd: " << fwd << endl;
        // cout << "elseup: " << fwdUp << endl;
        // cout << "elsedown: " << fwdDown << endl;

        int changeFwd = fabs(currentElevation - fwd);
        int changeUp = fabs(currentElevation - fwdUp);
        int changeDown = fabs(currentElevation - fwdDown);


        if ( ( (changeFwd == changeUp) || (changeFwd == changeDown) ) || ( (changeFwd < changeUp) && (changeFwd < changeDown) ) ) {
            //if fwd is the same as up or down, move forward
            j = j + 1;
        }
        else if ((changeDown == changeUp) || ((changeDown < changeUp) && (changeDown < changeFwd))) {
            //if outside changes are the same move down
            i = i + 1;
            j = j + 1;
        }
        else {
            i = i - 1;
            j = j + 1;
        }
    }
}

void Topograph::drawBestPath(Bmp& bmp) {
    int lowestElevation = 0;
    int temp = 0;
    int lowestIndex = 0;
    rgb rgb;
    rgb.r = 0;
    rgb.g = 0;
    rgb.b = 0;

    temp = drawGreedyPath(bmp, 0, rgb);

    for (int i = 0; i < getHeight();i++) {
            //cout << "i: " << i << endl;

            rgb.r = 255;
            lowestElevation = drawGreedyPath(bmp, i, rgb);

            if (lowestElevation <= temp) {
                temp = lowestElevation;
                lowestIndex = i;
            }
    

    }

    //cout << "Lowest Value Row Index: " << lowestIndex << endl;
    rgb.r = 0;
    rgb.b = 255;

    drawGreedyPath(bmp, lowestIndex, rgb);
    cout << "Lowest Elevation: " << temp << endl;








}