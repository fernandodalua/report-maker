#include <iostream>
#include <stdio.h>
#include <time.h>

#define CYCLES_REQUIRED 5000

using namespace std;

typedef struct Packages_S{
    //Package Data
    int package_number;
    //BMP Data
    double   pressure;
	  double   temperature_bmp;
	  double   altitude_bmp;
    //GPS Data
    double  longitude;
    double  latitude;
    double  altitude_gps;
    int16_t   time;

}Package;


Package *packageConstruct(int cycle){
    Package *package;
    package = (Package*)malloc(sizeof(Package));
    package->package_number   =  cycle;
    if(cycle <= 2500){
        package->pressure         =  90000 - 34*cycle + (rand() % 150);
        package->temperature_bmp  = 20 + (rand() % 5) + 0.01*cycle;
        package->altitude_bmp     =  17 + (rand() % 4)+ 0.0066*cycle;

    }
    else{
        package->pressure         =  5000 +  34*cycle + (rand() % 150);
        package->temperature_bmp  =  (rand() % 5) - 0.01*cycle - 30;
        package->altitude_bmp     =  50 + (rand() % 4) - 0.0066*cycle;
    }

	  package->longitude        =  47 + (rand() %20) * 0.05;
	  package->latitude         =  22 + (rand() %20) * 0.05;
    package->altitude_gps     =  0.9*package->altitude_bmp;
	  package->time             =  2*cycle + (rand() % 2);

    return package;
}



int main(){
    Package *package;
    FILE *log;
    int cycle = 0;
    srand(time(NULL));

    system("clear");
    cout << " Initializing LOG Maker..." << endl;
    log = fopen("/home/jmssouza/LOG.dat","wb");
    cout << " Creating LOG file..." << endl;
    if(log != NULL){
        cout << " File created!" << endl;
        cout << " Generating data..." << endl;
        while(cycle<=CYCLES_REQUIRED){
            package = packageConstruct(cycle);
            log = fopen("LOG.dat","r+b");
            fseek(log, cycle*sizeof(Package), SEEK_SET);
            fwrite(package, sizeof(Package), 1, log);
            fclose(log);
            free(package);

            if(cycle % 500 == 0){
                cout << "==";
                if(cycle == 5000){
                    cout << "== 100/%" << endl;
                    cout << " LOG created!" << endl;
                }
            }
            cycle++;
        }
        return 0;
    }
    else{
        cout << "File cannot be created :(" << endl;
        cout << "LOG Maker unable to run!" << endl;
        return -1;
    }
}
