#include "pch.h"
#include "road_planner.hpp"


void RoadPlanner::RoadPlanner::ReadFileToVector() {
    std::ifstream file(m_filename);
    if (!file.is_open()) {
        throw std::runtime_error("Die Datei konnte nicht geöffnet werden: " + m_filename);
    }

    m_road.clear();
    int number = 0;
    bool hasDigits = false;
    char ch;

    while (file.get(ch)) {          // Liest Zeichen für Zeichen und extrahiert Zahlen
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            number = number * 10 + (ch - '0');
            hasDigits = true;
        }
        else if (hasDigits) {
            m_road.push_back(number);
            number = 0;
            hasDigits = false;
        }
    }
    if (hasDigits) {
        m_road.push_back(number);
    }

    if (file.bad()) {
        throw std::runtime_error("Fehler beim Lesen der Datei: " + m_filename);
    }
    file.close();
}

bool RoadPlanner::RoadPlanner::IsRoadPossible(int middleStep) {
    int curDay = 1;
    int sum = 0;
    for (int distance : m_road) {
        if (sum + distance > middleStep) {
            curDay++;
            sum = distance;
            if (curDay > m_daysNumber) return false;
        }
        else {
            sum += distance;
        }
    }
    return true;
}

void RoadPlanner::RoadPlanner::GetFilesData(const int& stagesNumber) {
    if (m_road.size() >= 2) {
        m_road.erase(m_road.begin(), m_road.begin() + 2);
        if (m_road.size() < stagesNumber) {
            std::cerr << "Unzureichende Anzahl an Stufen" << std::endl;
            exit(1);
        }
        m_road.erase(m_road.begin() + stagesNumber, m_road.end());
    }
}

int RoadPlanner::RoadPlanner::MaximumDailyDistanceFind() {
    int maxStep = std::accumulate(m_road.begin(), m_road.end(), 0);
    int minStep = *std::max_element(m_road.begin(), m_road.end());

    while (minStep < maxStep) {
        int middleStep = (maxStep + minStep) / 2;
        if (IsRoadPossible(middleStep)) {
            maxStep = middleStep;
        }
        else {
            minStep = middleStep + 1;
        }
    }
    return minStep;
}

void RoadPlanner::RoadPlanner::CalculationDailyDistance(int maximumDailyDistance, std::vector<int>& dailyDistances) {
    int it = 0;

    for (int distance : m_road) {
        if (dailyDistances[it] + distance <= maximumDailyDistance) {
            dailyDistances[it] += distance;
        }
        else {
            it++;
            if (it < m_daysNumber) {
                dailyDistances[it] = distance;
            }
        }
    }
}

void RoadPlanner::RoadPlanner::ResultsOutput() {

    std::vector<int> dailyDistances(m_daysNumber, 0);
    int maximumDailyDistance = MaximumDailyDistanceFind();


    int maximumDailyDistance = MaximumDailyDistanceFind();

    
    CalculationDailyDistance(maximumDailyDistance, dailyDistances);

   
    for (int i = 0; i < m_daysNumber; i++) {  // Ausgabe der täglichen Strecken
        std::cout << (i + 1) << ". Tag: " << dailyDistances[i] << " km" << "\n";
    }

   
    std::cout << "\nMaximum: " << maximumDailyDistance << " km\n";

}





int RoadPlanner::RoadPlanner::Start(array<System::String^>^ args) {

    
    if (args->Length < 2) {
        std::cerr << "Verwendung: program.exe <Dateiname>" << std::endl;
        return 1;
    }
    
    try {
        System::String^ filepath = args[1];
        m_filename = msclr::interop::marshal_as<std::string>(filepath);
        ReadFileToVector();
    }
    catch (const std::exception& e) {
        std::cerr << "Fehler: " << e.what() << std::endl;
        return 1;
    }

    if (m_road.size() < 2) {
        std::cerr << "Fehler: Ungültige Dateistruktur" << std::endl;
        return 1;
    }

    int stagesNumber = m_road[0];
    m_daysNumber = m_road[1];

    GetFilesData(stagesNumber);

    ResultsOutput();

    return 0;
}
