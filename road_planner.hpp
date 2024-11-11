#pragma once



#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <cctype>
#include <msclr/marshal_cppstd.h>


namespace RoadPlanner {
    class RoadPlanner
    {
    public:
        // Funktion zum Lesen von Dateiinhalten in einen ganzzahligen Vektor, wobei nur Ziffern gefiltert werden
        void ReadFileToVector();

        // Funktion zur Überprüfung, ob eine vorgegebene maximale Tagesdistanz einen umsetzbaren Plan zulässt
        bool IsRoadPossible(int middleStep);

        // Findet die maximale Tagesstrecke für den geplanten Roadtrip
        int MaximumDailyDistanceFind();

        // Funktion zur Ausführung der Straßenplanungslogik und Ausgabe der Tagesdistanzen und der maximalen Distanz
        int Start(array<System::String^>^ args);

        //Funktion zum Überprüfen und Abrufen von Daten aus einer Datei
        void GetFilesData(const int& stagesNumber);

        // Berechnet die Strecken pro Tag, basierend auf der maximalen Tagesstrecke  
        void CalculationDailyDistance(int maximumDailyDistance, std::vector<int>& dailyDistances);

        // Gibt die berechneten Ergebnisse auf dem Bildschirm aus
        void ResultsOutput();

    private:
        std::vector<int> m_road;
        int m_daysNumber;
        std::string m_filename;
    };

}



